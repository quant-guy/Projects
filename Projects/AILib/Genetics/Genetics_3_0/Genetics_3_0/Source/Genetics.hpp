///////////////////////////////////////////////////////////////////////////////////
// COPYRIGHT 2015 KovachTechnologies LLC
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
#ifndef TEMPLATE_GENETIC_STRUCTURE_3_0_H
#define TEMPLATE_GENETIC_STRUCTURE_3_0_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>

#include "Random.hpp"

#define GA_INDEX_SWAP    0
#define GA_INDEX_DELETE  1

using namespace std;

static MathLib::Random::MersenneTwister mt;

namespace AILib
{

namespace Genetics
{

	//////////////////////////////////////////////////////////////////
	// Class structure for genetics : consists of a container for the
	// elements (the gene_), functors for perturbing the gene_, and
	// a parent functor for the perturbation methods for the elements
	// contained in the gene_, themselves 
	//////////////////////////////////////////////////////////////////
	template < class T > 
	class ParentGenetic
	{
		friend ostream & operator << ( ostream & strm, const ParentGenetic & gene )
		{
			for ( typename std::vector< value_type >::const_iterator it = gene.gene_.begin();
			      it != gene.gene_.end();
			      ++it )
			{
				strm << ( ** it ) << endl;
			}
			return strm;
		}

		public :

			typedef T 							value_type;
										
			typedef std::vector< value_type >                               element_vector;
											
			typedef typename element_vector::iterator                       element_vector_iterator;

			typedef typename element_vector::iterator                       genetic_iterator;

			typedef typename element_vector::const_iterator                 const_genetic_iterator;

		public : 
		
			ParentGenetic ( void ) : 
				probabilities_( 0 ), gene_( 0 ), gene_perturbation_functors_( 0 ) {}

			ParentGenetic ( const ParentGenetic & gene ) : probabilities_( gene.probabilities_ ) 
			{
				// add in everything from within child class
			}

			virtual ~ParentGenetic ( void )
			{
				while ( ! gene_.empty() )
				{
					delete gene_.back();
					gene_.pop_back();
				}

				while ( ! gene_perturbation_functors_.empty() )
				{
					delete gene_perturbation_functors_.back();
					gene_perturbation_functors_.pop_back();
				}
			} 

			virtual inline genetic_iterator Begin( void ) { return gene_.begin(); }

			virtual inline const_genetic_iterator Begin( void ) const { return gene_.begin(); }

			virtual inline genetic_iterator End( void ) { return gene_.end(); }

			virtual inline const_genetic_iterator End( void ) const { return gene_.end(); }

			virtual value_type At( const unsigned int & index ) { return gene_.at( index ); }

			virtual inline void AddElement( const value_type & element ) { gene_.push_back( element ); }

			virtual void PutGenetic( const char * filename )
			{
				ofstream output( filename );
				output << * this << endl;
				output.close();
			}

			virtual void Reverse( void ) { reverse( this->gene_.begin(), this->gene_.end() ); }

			virtual void DeleteElement( const unsigned int & index1, const unsigned int & index2 ) 
			{ 
				if ( index1 == index2 ) return;
				assert( index2 > index1 ); assert( index2 <= this->gene_.size() );
				for ( unsigned int i = index1; i < index2; ++i )
					delete this->gene_.at( i );
				this->gene_.erase( this->gene_.begin() + index1, this->gene_.begin() + index2 );
			}

			virtual void Perturbation( void )
			{
				( * ( * ( gene_perturbation_functors_.begin() + MutationOffset() ) ) )( gene_ );
			}

			virtual void Perturbation( const unsigned int & num_times )
			{
				for ( unsigned int i = 0; i < num_times; ++i )
					Perturbation();
			}

			virtual void RandomPerturbations( const unsigned int & upper_bound )
			{
				this->Perturbation( mt.Generate( ( const unsigned int ) 0, upper_bound ) );
			}

			virtual inline const unsigned int Size( void ) const { return gene_.size(); } 

			virtual inline void SetDistribution( const double * array, unsigned int size )
			{
				copy( array, array + size, back_inserter( probabilities_ ) );
			}

			virtual inline void SetDistribution( const std::vector< double > & array )
			{
				copy( array.begin(), array.end(), back_inserter( probabilities_ ) );
			}

			virtual const unsigned int ElementOffset( void ) const
			{
				return mt.Generate( ( const unsigned int ) 0, ( gene_.size() - 1 ) );
			}

			virtual const unsigned int MutationOffset( void ) const
			{
				return mt.Generate( ( const unsigned int ) 0, ( gene_perturbation_functors_.size() - 1 ) );
			}

			virtual ParentGenetic & operator = ( const ParentGenetic & gene )
			{
				while ( ! gene_.empty() )
				{
					delete gene_.back();
					gene_.pop_back();
				}

				while ( ! gene_perturbation_functors_.empty() )
				{
					delete gene_perturbation_functors_.back();
					gene_perturbation_functors_.pop_back();
				}

				this->probabilities_.clear();

				copy( gene.gene_perturbation_functors_.begin(),
                                      gene.gene_perturbation_functors_.end(),
                                      back_inserter( gene_perturbation_functors_ ) );

				copy( gene.gene_.begin(),
                                      gene.gene_.end(),
                                      back_inserter( gene_ ) );

				copy( gene.probabilities_.begin(),
                                      gene.probabilities_.end(),
                                      this->probabilities_.begin() );

				return * this;
			}

			virtual ParentGenetic & operator + ( ParentGenetic & gene )
			{
				unsigned int index1 = mt.Generate( ( const unsigned int ) 0, ( gene_.size() - 1 ) );
				unsigned int index2 = 0;
				if ( gene_.size() - 1 - index1 != 0 )
					int index2 = mt.Generate( ( const unsigned int ) 0, ( gene_.size() - 1 - index1 ) );

				if ( gene.gene_.size() >= ( index1 + index2 ) )
				{
					swap_ranges( this->gene_.begin() + index1, 
						this->gene_.begin() + index1 + index2,
						gene.gene_.begin() );
				}
				return * this;
			}

		public :

			//////////////////////////////////////////////////////////////////
			// Functors to Perturb the gene 
			//////////////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////////////
			// This is the parent class of the purturbation class for the
			// CONTAINER of template T's, ie the gene_
			// Purely virtual operator () meant to implement perturbation
			//   functor
			//////////////////////////////////////////////////////////////////
			class PerturbationFunctor
			{
				public : 

					PerturbationFunctor( void ) {}

					PerturbationFunctor( const PerturbationFunctor & ) {}

					virtual ~PerturbationFunctor( void ) {}

					virtual inline void operator () ( element_vector & element ) {}; 

					virtual inline unsigned int ChooseRandom( const unsigned int & max ) { return mt.Generate( ( const unsigned int ) 0, max ); }
			};

		public : 

			virtual inline void AddFunctor( const PerturbationFunctor * functor ) 
				{ gene_perturbation_functors_.push_back( ( PerturbationFunctor * ) functor ); }

			typedef std::vector< PerturbationFunctor * >             gene_perturbation_functors;
											
			typedef typename gene_perturbation_functors::iterator    gene_perturbation_functors_iterator;

			//////////////////////////////////////////////////////////////////
			// Swap two randomly selected elements 
			//////////////////////////////////////////////////////////////////
			class Swap : public PerturbationFunctor
			{
				public : inline void operator () ( element_vector & gene ) 
				{
					unsigned int temp_random1 = this->ChooseRandom( gene.size() - 1 );
					unsigned int temp_random2 = this->ChooseRandom( gene.size() - 1 );
					value_type temp = * ( gene.begin() + temp_random1 );
					* ( gene.begin() + temp_random1 ) = * ( gene.begin() + temp_random2 );
					* ( gene.begin() + temp_random2 ) = temp;
				}
			};

			//////////////////////////////////////////////////////////////////
			// Swap Block - swap multiple elements 
			//////////////////////////////////////////////////////////////////
			class SwapBlock : public PerturbationFunctor
			{
				public : inline void operator () ( element_vector & gene ) 
				{
					unsigned int temp_random1 = this->ChooseRandom( gene.size() - 1 );
					unsigned int temp_random2 = this->ChooseRandom( gene.size() - 1 );
					unsigned int extent = 
						this->ChooseRandom( ( gene.size() - max( temp_random1, temp_random2 ) ) );
					swap_ranges( ( gene.begin() + temp_random1 ), 
						( gene.begin() + temp_random1 + extent ), 
						( gene.begin() + temp_random2 ) );
				}
			};

			//////////////////////////////////////////////////////////////////
			// Delete a randomly selected element 
			//////////////////////////////////////////////////////////////////
			class Delete : public PerturbationFunctor
			{
				public : inline void operator () ( element_vector & gene )
				{
					if ( gene.size() > 1 ) 
						gene.erase( ( gene.begin() + this->ChooseRandom( gene.size() - 1 ) ) );
				}
			};

		protected: 

			gene_perturbation_functors    gene_perturbation_functors_;

			element_vector                gene_;

			std::vector< double >         probabilities_;
	};

	//////////////////////////////////////////////////////////////////
	// Parent class for fitness function
	//////////////////////////////////////////////////////////////////
	template< class T, class U >
	class ParentFitness
	{
		public :

			typedef T value_type;

			typedef U fitness_type;

		public :

			ParentFitness( void ) {}

			virtual ~ParentFitness( void ) {}

//			virtual fitness_type operator () ( const ParentGenetic< value_type > & f ) = 0;
	};

} // Genetics

} // AILib

#endif // TEMPLATE_GENETIC_STRUCTURE_3_0_H
