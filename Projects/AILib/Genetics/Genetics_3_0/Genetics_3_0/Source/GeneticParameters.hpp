///////////////////////////////////////////////////////////////////////////////////
// COPYRIGHT 2015 Kovach Technologies, Inc.
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the Kovach Technologies, LLC.
// 4. Neither the name of the Kovach Technologies, LLC nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY Kovach Technologies, LLC AS IS AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL Kovach Technologies, LLC BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// AUTHOR : Daniel Kovach
// DATE : 2015-12-30 10:19:06.739857
///////////////////////////////////////////////////////////////////////////////////
#ifndef GENETIC_PARAMETER_H 
#define GENETIC_PARAMETER_H 

#include <Genetics.hpp>

#define DEFAULT_MAX        -1.0
#define DEFAULT_MIN         1.0
#define DEFAULT_GRANULARITY 0.1
#define MAX_VALUE_SIZE      200

namespace AILib
{

/////////////////////////////////////////////////////////////////////////
// Genetic structure.  Contains functionality to manipulate genetic
// weights 
/////////////////////////////////////////////////////////////////////////
namespace Genetics
{

template < class T >
class ParameterVector : public ParentGenetic< T * >
{
	friend ostream & operator << ( ostream & strm, const ParameterVector & rnv )
	{
		for ( typename ParentGenetic< value_type * >::const_genetic_iterator it = rnv.Begin();
                      it != rnv.End();
                      ++it )
		{
			strm << ** it << endl;
		}
		return strm;
	}

	public :

	typedef T value_type;

	typedef typename ParentGenetic< value_type * >::genetic_iterator r_iter; 

	typedef typename ParentGenetic< value_type * >::const_genetic_iterator const_r_iter; 

	public :

		ParameterVector( void ) {}

		ParameterVector( const ParameterVector & rnv ) : 
			ParentGenetic< value_type * >( rnv ),
			granularity_( rnv.granularity_ ),
			min_( rnv.min_ ),
			max_( rnv.max_ )
		{
			for ( unsigned int i = 0; i < rnv.gene_.size(); ++i )
				this->gene_.push_back( new value_type ( * rnv.gene_.at( i ) ) );
			for ( unsigned int i = 0; i < rnv.gene_perturbation_functors_.size(); ++i )
				this->AddFunctor( new typename ParentGenetic<value_type *>::PerturbationFunctor( * rnv.gene_perturbation_functors_.at( i ) ) );
		}

		ParameterVector( const typename std::vector< value_type > & input ) : 
			ParentGenetic< value_type * >(),
			granularity_( DEFAULT_GRANULARITY )
		{
			for ( unsigned int i = 0; i < input.size(); ++i )
				this->gene_.push_back( new value_type ( input.at( i ) ) );
			this->min_ = * min_element( input.begin(), input.end() );
			this->max_ = * max_element( input.begin(), input.end() );
			if ( this->min_ >= this->max_ )
			{
				this->min_ = DEFAULT_MIN;
				this->max_ = DEFAULT_MAX;
			}
			PushFunctors();
		}

		ParameterVector( const value_type * input, const unsigned int & size_input ) : 
			ParentGenetic< value_type * >(),
			granularity_( DEFAULT_GRANULARITY )
		{
			for ( unsigned int i = 0; i < size_input; ++i )
				this->gene_.push_back( new value_type ( * ( input + i ) ) );
			this->min_ = * min_element( input, input + size_input );
			this->max_ = * max_element( input, input + size_input );
			if ( this->min_ >= this->max_ )
			{
				this->min_ = DEFAULT_MIN;
				this->max_ = DEFAULT_MAX;
			}
			PushFunctors();
		}

		ParameterVector( const unsigned int & values, 
			const value_type & granularity, 
			const value_type & min, 
			const value_type & max ) : 
			ParentGenetic< value_type * >(),
			granularity_( granularity ),
			min_( min ),
			max_( max )
		{
			for ( unsigned int i = 0; i < values; ++i )
				this->gene_.push_back( new value_type ( mt.Generate( min, max) ) );
			PushFunctors();
		}

		ParameterVector( const char * filename, 
			const value_type & granularity,
			const value_type & min, 
			const value_type & max ) :
			granularity_( granularity ),
			min_( min ),
			max_( max )
		{
			ifstream input( filename, ios::in );
			
			if ( ! input.is_open() )
			{
				cerr << "Error: Unable to open input file: " << filename << endl;
				exit( 1 );
			}
			
			// initialize input vector and read in data read in value_type vector
			typename std::vector< value_type > contents;
			copy( istream_iterator< value_type >( input ), 
				istream_iterator< value_type >(), back_inserter( contents ) );

			for ( unsigned int i = 0; i < contents.size(); ++i )
				this->gene_.push_back( new value_type ( contents.at( i )  ) );

			PushFunctors();
			input.close();	
		}

		~ParameterVector( void ) {}

		void SetGranularity( const value_type & granularity ) { this->granularity_ = granularity; }

		inline void PushFunctors( void )
		{
			this->gene_perturbation_functors_.push_back( 
				new typename ParentGenetic<value_type *>::Swap() );
			this->gene_perturbation_functors_.push_back( 
				new typename ParentGenetic<value_type *>::SwapBlock() );
			this->gene_perturbation_functors_.push_back( 
				new Replace( this->min_, this->max_) ); 
			this->gene_perturbation_functors_.push_back( 
				new Perturb( this->min_, this->max_, this->granularity_) ); 
		}

		inline const unsigned int Size( void ) const { return this->gene_.size(); }

		inline void Copy( value_type * output, const unsigned int & size_output ) const
		{
			assert( size_output == this->Size() );
			value_type * o_ptr = output;
			for ( const_r_iter it = this->Begin(); it != this->End(); ++it, ++o_ptr )
			{
				* o_ptr = ** it;
			}
		}

		inline void Copy( typename std::vector< value_type > & output ) const
		{
			for ( const_r_iter it = this->Begin(); it != this->End(); ++it )
			{
				output.push_back( ** it );
			}
		}

	public :

		inline ParameterVector & operator = ( const ParameterVector & rnv )
		{
			this->granularity_ = rnv.granularity_;
			this->min_ = rnv.min_;
			this->max_ = rnv.max_;

/*			while ( ! this->gene_perturbation_functors_.empty() )
			{                                                       
				delete this->gene_perturbation_functors_.back();
				this->gene_perturbation_functors_.pop_back();
			}

			copy( rnv.gene_.begin(), rnv.gene_.end(), back_inserter( this->gene_ ) );
			for ( unsigned int i = 0; i < rnv.gene_perturbation_functors_.size(); ++i )
				this->gene_.push_back( rnv.gene_perturbation_functors_.at( i ) );
*/
			return * this;
		}

	public :

		//////////////////////////////////////////////////////////////////
		// Perturbation Functors 
		//////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////
		// Replace random number with a new one
		//////////////////////////////////////////////////////////////////
		class Replace : public ParentGenetic<value_type *>::PerturbationFunctor
		{
			public :

			Replace( const value_type & min, const value_type & max ) : 
				min_( min ), max_( max ) {}

			~Replace( void ) {}

			inline void operator () ( typename ParentGenetic<value_type>::element_vector & elements )
			{
				( ** ( elements.begin() + this->ChooseRandom( elements.size() ) ) )
					= mt.Generate( this->min_, this->max_ );
			}

			private :

			value_type min_, max_;
		};

		//////////////////////////////////////////////////////////////////
		// Perturb existing element 
		//////////////////////////////////////////////////////////////////
		class Perturb : public ParentGenetic<value_type *>::PerturbationFunctor
		{
			public :

			Perturb( const value_type & min, const value_type & max, const value_type & granularity ) : 
				min_( min ), max_( max ), granularity_( granularity ) {}

			~Perturb( void ) {}

			inline void operator () ( typename ParentGenetic<value_type>::element_vector & elements )
			{
				const unsigned int index = this->ChooseRandom( elements.size() );
				value_type temp = ( ** ( elements.begin() + index ) ) 
					+ mt.Generate( ( -1.0 * this->granularity_), this->granularity_ );

				if ( temp > this->max_ )
				{
					( ** ( elements.begin() + index ) ) = this->min_ + ( temp - this->max_ );
				}
				else if ( temp < this->min_ )
				{
					( ** ( elements.begin() + index ) ) = this->max - ( this->min_ - temp );
				}
				else
				{
					( ** ( elements.begin() + index ) ) = temp;
				}
			}

			private :

			value_type min_, max_, granularity_;
		};

	private :

		value_type granularity_, min_, max_;
}; 

} // Genetics

} // AILib 

#endif // GENETIC_PARAMETER_H 
