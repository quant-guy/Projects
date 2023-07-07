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
#ifndef TEMPLATE_NEURAL_NETWORK_LIBRARY_H
#define TEMPLATE_NEURAL_NETWORK_LIBRARY_H

#include <fstream>
#include <vector>
#include <iterator>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <functional>

#include <ActivationFunctions.hpp>
#include <GeneticPair.hpp>
#include <Matrix.hpp>

using namespace std;

namespace AILib
{

namespace NeuralNetwork
{

///////////////////////////////////////////////////////////////////////////////
// Fun with functors! 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Neural Class and methods
///////////////////////////////////////////////////////////////////////////////
template < class T >
class NeuralUnit
{
	friend ostream & operator << ( ostream & strm, const NeuralUnit & nu )
	{
		strm << nu.weights_; return strm;
	}

	public :

		typedef T value_type;

		typedef typename MathLib::Matrix::Matrix< T >::matrix_iterator m_iterator;

		typedef typename MathLib::Activation::InverseTangent<value_type>::Activation activation;

		typedef typename MathLib::Activation::InverseTangent<value_type>::Derivative derivative;

		NeuralUnit( void ) :
			prev1_( 0 ),
			prev2_( 0 ),
			prev3_( 0 ),
			prev4_( 0 ),
			next1_( 0 ),
			next2_( 0 ),
			next3_( 0 ),
			next4_( 0 ),
			learning_rate_( 0.0 ),
			sigmoid_parameter_( 0.0 ),
			back_propagation_error_delta_(),
			input_(),
			weights_(),
			output_() {}

		NeuralUnit( const NeuralUnit & n ) :
			prev1_( n.prev1_ ),
			prev2_( n.prev1_ ),
			prev3_( n.prev1_ ),
			prev4_( n.prev1_ ),
			next1_( n.next1_ ),
			next2_( n.next2_ ),
			next3_( n.next3_ ),
			next4_( n.next4_ ),
			learning_rate_( n.learning_rate_ ),
			back_propagation_error_delta_( n.back_propagation_error_delta_ ),
			sigmoid_parameter_( n.sigmoid_parameter_ ),
			input_( n.input_ ),
			weights_( n.weights_ ),
			output_( n.output_ ) {} 

		NeuralUnit( const unsigned int & rows,
                            const unsigned int & cols ) :
			prev1_( 0 ),
			prev2_( 0 ),
			prev3_( 0 ),
			prev4_( 0 ),
			next1_( 0 ),
			next2_( 0 ),
			next3_( 0 ),
			next4_( 0 ),
			learning_rate_( ( value_type ) 0.05 ),
			back_propagation_error_delta_( rows, 1 ),
			sigmoid_parameter_( 1 ),
			input_( cols, 1 ),
			weights_( rows, cols ),
			output_( rows, 1 ) 
		{
			MathLib::Random::MersenneTwister m;
			for ( m_iterator it = weights_.Begin();
                              it != weights_.End();
                              ++it )
			{
				* it = ( ( value_type ) ( m.Generate( ( double ) -10.0, ( double ) 10.0 ) ) );
			}
			Fill( input_, 0.0 );
			Fill( output_, 0.0 );
			Fill( back_propagation_error_delta_, 0.0 );
		}

		~NeuralUnit( void ) {}

		inline void SetLearningRate( const value_type & lr ) { this->learning_rate_ = lr; }

		inline const value_type GetLearningRate( void ) const { return this->learning_rate_; }

		inline void SetSigmoidParameter( const value_type & sp ) { this->sigmoid_parameter_ = sp; }

		inline const value_type GetSigmoidParameter( void ) { return sigmoid_parameter_; }

		inline void SetNext( NeuralUnit< value_type > * next ) 
		{ 
			if ( ! next1_ )
			{
				next1_ = next;
				return;
			}
			if ( ! next2_ )
			{
				next2_ = next;
				return;
			}
			if ( ! next3_ )
			{
				next3_ = next;
				return;
			}
			if ( ! next4_ )
			{
				next4_ = next;
				return;
			}
		}

		inline void SetPrev( NeuralUnit< value_type > * prev )
		{ 
			if ( ! prev1_ )
			{
				prev1_ = prev;
				return;
			}
			if ( ! prev2_ )
			{
				prev2_ = prev;
				return;
			}
			if ( ! prev3_ )
			{
				prev3_ = prev;
				return;
			}
			if ( ! prev4_ )
			{
				prev4_ = prev;
				return;
			}
		}

		inline void SetInput( const MathLib::Matrix::Matrix< value_type > & data ) { input_ = data; }

		inline const MathLib::Matrix::Matrix< value_type > GetOutput( void ) const { return output_; }

		inline MathLib::Matrix::Matrix< value_type > GetOutput( void ) { return output_; }

		inline void GetOutput( typename std::vector< value_type >::iterator & it ) const 
		{
			copy( output_.Begin(), output_.End(), it );
		}

		inline void GetOutput( value_type * it ) const 
		{
			copy( output_.Begin(), output_.End(), it );
		}

		inline unsigned int GetRows( void ) const { return weights_.GetRows(); }

		inline unsigned int GetCols( void ) const { return weights_.GetColumns(); }

		inline unsigned int GetSizeInput( void ) const { return weights_.GetColumns(); }

		inline unsigned int GetSizeOutput( void ) const { return weights_.GetRows(); }

		inline unsigned int Size( void ) const { return weights_.Size(); }

		inline void PutNeuralUnit( std::ofstream * output )
		{
			assert( output->is_open() );
			this->weights_.PutMatrix( output );
		}

		inline void PutNeuralUnit( typename std::vector< value_type > & output )
		{
			copy( this->weights_.Begin(), this->weights_.End(), back_inserter( output ) );
		}

		inline void GetNeuralUnit( const typename std::vector< value_type > & input, const unsigned int & index )
		{
			copy( input.begin() + index, input.begin() + index + weights_.Size(), weights_.Begin() );
		}

		inline void GetNeuralUnit( typename std::vector< value_type >::const_iterator & begin , const unsigned int & index )
		{
			copy( begin, begin + index, weights_.Begin() );
		}

		inline void GetNeuralUnit( const value_type * input, const unsigned int & index )
		{
			copy( input + index, input + index + weights_.Size(), weights_.Begin() );
		}

		inline void Propagate( const MathLib::Matrix::Matrix< value_type > & data )
		{
			this->input_ = data;

			if ( this->prev1_ )
			{
				this->input_ += this->prev1_->output_;
			}
			if ( this->prev2_ )
			{
				this->input_ += this->prev2_->output_;
			}
			if ( this->prev3_ )
			{
				this->input_ += this->prev3_->output_;
			}
			if ( this->prev4_ )
			{
				this->input_ += this->prev4_->output_;
			}

			this->output_ = this->weights_ * this->input_;
			transform( this->output_.Begin(), this->output_.End(), this->output_.Begin(), 
					activation( this->sigmoid_parameter_ ) );
		}

		inline void Propagate( const std::vector< value_type > & input_data )
		{
			this->Propagate( MathLib::Matrix::Matrix< value_type > ( input_data.begin(), input_data.size(), 1 ) );
		}

		inline void Propagate( void )
		{
			Fill( input_, 0.0 );

			if ( this->prev1_ )
			{
				this->input_ += this->prev1_->output_;
			}
			if ( prev2_ )
			{
				this->input_ += this->prev2_->output_;
			}
			if ( prev3_ )
			{
				this->input_ += this->prev3_->output_;
			}
			if ( prev4_ )
			{
				this->input_ += this->prev4_->output_;
			}

			this->output_ = this->weights_ * this->input_;
			transform( this->output_.Begin(), this->output_.End(), this->output_.Begin(), 
					activation( this->sigmoid_parameter_ ) );
		}

		inline void BackPropagate( const MathLib::Matrix::Matrix< value_type > & output )
		{
			// p_n
			this->back_propagation_error_delta_ = this->weights_ * this->input_;

			// desired_output - output
			this->output_ = output - this->output_;

			// S'( p_n )
			transform( this->back_propagation_error_delta_.Begin(), this->back_propagation_error_delta_.End(), 
				this->back_propagation_error_delta_.Begin(), derivative( this->sigmoid_parameter_ ) );

			// delta = ( desired_output - output ) . S'( p_n )
			transform( this->output_.Begin(), this->output_.End(),
				this->back_propagation_error_delta_.Begin(),
				this->back_propagation_error_delta_.Begin(), multiplies< value_type >() );

			if ( next1_ )
			{
				this->back_propagation_error_delta_ +=
					( next1_->back_propagation_error_delta_.ColumnTranspose() * next1_->weights_ ).ColumnTranspose();
					next1_->back_propagation_error_delta_.ColumnTranspose();
			}
			if ( next2_ )
			{
				this->back_propagation_error_delta_ +=
					( next2_->back_propagation_error_delta_.ColumnTranspose() * next2_->weights_ ).ColumnTranspose();
					next2_->back_propagation_error_delta_.ColumnTranspose();
			}
			if ( next3_ )
			{
				this->back_propagation_error_delta_ +=
					( next3_->back_propagation_error_delta_.ColumnTranspose() * next3_->weights_ ).ColumnTranspose();
					next3_->back_propagation_error_delta_.ColumnTranspose();
			}
			if ( next4_ )
			{
				this->back_propagation_error_delta_ +=
					( next4_->back_propagation_error_delta_.ColumnTranspose() * next4_->weights_ ).ColumnTranspose();
					next4_->back_propagation_error_delta_.ColumnTranspose();
			}

			// rho * delta_n * h_n-1
			// adjust weights as the inner product of the: (1) back propagated error delta
                        //                                             (2) input vector
			weights_ += ( this->learning_rate_ * 
				( this->back_propagation_error_delta_ * this->input_.ColumnTranspose() ) );

			// replace orientation of input as it should be
			this->input_.ColumnTranspose();
		}

		inline void BackPropagate( const std::vector< value_type > & output_data )
		{
			this->BackPropagate( MathLib::Matrix::Matrix< value_type > ( output_data.begin(), output_data.size(), 1 ) );
		}

		inline void BackPropagate( void )
		{
			Fill( back_propagation_error_delta_, 0.0 );
			if ( next1_ )
			{
				this->back_propagation_error_delta_ +=
					( next1_->back_propagation_error_delta_.ColumnTranspose() * next1_->weights_ ).ColumnTranspose();
					next1_->back_propagation_error_delta_.ColumnTranspose();
			}
			if ( next2_ )
			{
				this->back_propagation_error_delta_ +=
					( next2_->back_propagation_error_delta_.ColumnTranspose() * next2_->weights_ ).ColumnTranspose();
					next2_->back_propagation_error_delta_.ColumnTranspose();
			}
			if ( next3_ )
			{
				this->back_propagation_error_delta_ +=
					( next3_->back_propagation_error_delta_.ColumnTranspose() * next3_->weights_ ).ColumnTranspose();
					next3_->back_propagation_error_delta_.ColumnTranspose();
			}
			if ( next4_ )
			{
				this->back_propagation_error_delta_ +=
					( next4_->back_propagation_error_delta_.ColumnTranspose() * next4_->weights_ ).ColumnTranspose();
					next4_->back_propagation_error_delta_.ColumnTranspose();
			}

			// S'( p_n )
			this->output_ = this->weights_ * this->input_;
			transform( this->output_.Begin(), this->output_.End(), 
				this->output_.Begin(), derivative( this->sigmoid_parameter_ ) );

			// delta_n+1 * weights_n-1 . S'( p_n )
			transform( this->output_.Begin(), this->output_.End(),
				this->back_propagation_error_delta_.Begin(),
				this->back_propagation_error_delta_.Begin(), multiplies< value_type >() );

			// rho * delta_n * h_n-1
			// adjust weights as the inner product of the: (1) back propagated error delta
                        //                                             (2) input vector
			// note: "-=" instead of "+=" since we took ( output_from_net - desired_output)
			// instead of vice versa
			weights_ += ( this->learning_rate_ * 
				( this->back_propagation_error_delta_ * this->input_.ColumnTranspose() ) );

			// replace orientation of input as it should be
			this->input_.ColumnTranspose();
		}

		inline value_type Error( const MathLib::Matrix::Matrix< value_type > & desired_output )
		{
			return ERR( desired_output, this->output_ );
		}

		inline NeuralUnit< value_type > operator *= ( const value_type & constant )
		{
			this->weights_ *= constant;
			return * this;
		}

	private :

		NeuralUnit< value_type > * prev1_;

		NeuralUnit< value_type > * prev2_;

		NeuralUnit< value_type > * prev3_;

		NeuralUnit< value_type > * prev4_;

		value_type learning_rate_;

		value_type sigmoid_parameter_;

		MathLib::Matrix::Matrix< value_type > back_propagation_error_delta_;

		MathLib::Matrix::Matrix< value_type > input_;

		MathLib::Matrix::Matrix< value_type > weights_;	

		MathLib::Matrix::Matrix< value_type > output_;

		NeuralUnit< value_type > * next1_;

		NeuralUnit< value_type > * next2_;

		NeuralUnit< value_type > * next3_;

		NeuralUnit< value_type > * next4_;
};

template < class T >
class NeuralMacroStructure
{
	friend ostream & operator << ( ostream & strm, const NeuralMacroStructure & nms )
	{
		strm << nms.gene_;
		return strm;
	}

	public :

		typedef T value_type;

		typedef typename std::vector< NeuralUnit< value_type > * >::iterator neural_it;

		typedef typename std::vector< NeuralUnit< value_type > * >::const_iterator const_neural_it;

		NeuralMacroStructure( void ) : neural_macro_structure_(), gene_() {}

		NeuralMacroStructure( const NeuralMacroStructure & nms ) : 
			neural_macro_structure_( nms.neural_macro_structure_ ),
			gene_( nms.gene_ ) {}

		NeuralMacroStructure( const char * filename, 
                                      const unsigned int & node_size, 
                                      const value_type & lr, 
                                      const value_type & sp ) : gene_( filename )
		{
			const unsigned int size_nms = this->gene_.GetLargestElement();

			for ( unsigned int i = 0; i < size_nms; ++i )
				this->neural_macro_structure_.push_back( new NeuralUnit< value_type >( node_size, node_size ) );
			NeuralMacroStructure::SetLearningRate( lr );
			NeuralMacroStructure::SetSigmoidParameter( sp );	
			
			for ( Genetics::ParentGenetic<Genetics::GeneticPair *>::genetic_iterator it = this->gene_.Begin();
                              it != this->gene_.End();
                              ++it )
			{
				( * ( this->neural_macro_structure_.begin() + ( * it )->GetFirst() ) )->
					SetNext( ( * ( this->neural_macro_structure_.begin() + ( * it )->GetSecond() ) ) );
				( * ( this->neural_macro_structure_.begin() + ( * it )->GetSecond() ) )->
					SetPrev( ( * ( this->neural_macro_structure_.begin() + ( * it )->GetFirst() ) ) );
			}
		}

		NeuralMacroStructure( const unsigned int & _1, // input dimensions
                                      const unsigned int & _2, // hidden layer dimensions
                                      const unsigned int & _3 )// output dimensions
		{
			neural_macro_structure_.push_back( new NeuralUnit< value_type >( _2, _1 ) );
			neural_macro_structure_.push_back( new NeuralUnit< value_type >( _3, _2 ) );

      			( * ( neural_macro_structure_.begin() + 0 ) )->SetPrev( 0 );
			( * ( neural_macro_structure_.begin() + 0 ) )->SetNext(  ( * ( neural_macro_structure_.begin() + 1 ) ) );
			( * ( neural_macro_structure_.begin() + 1 ) )->SetPrev(  ( * ( neural_macro_structure_.begin() + 0 ) ) );
			( * ( neural_macro_structure_.begin() + 1 ) )->SetNext( 0 );

			this->SetLearningRate( ( value_type ) 0.05 );
			this->SetSigmoidParameter( ( value_type ) 1.0 );

			this->gene_.AddElement( new Genetics::GeneticPair( 0, 1 ) );
			this->gene_.AddElement( new Genetics::GeneticPair( 1, 2 ) );
		}

		NeuralMacroStructure( const unsigned int & _1, // input dimensions
                                      const unsigned int & _2, // hidden layer dimensions
                                      const unsigned int & _3, // hidden layer dimensions
                                      const unsigned int & _4 )// output dimensions
		{
			neural_macro_structure_.push_back( new NeuralUnit< value_type >( _2, _1 ) );
			neural_macro_structure_.push_back( new NeuralUnit< value_type >( _3, _2 ) );
			neural_macro_structure_.push_back( new NeuralUnit< value_type >( _4, _3 ) );

			( neural_macro_structure_.begin() + 0 )->SetPrev( 0 );
			( neural_macro_structure_.begin() + 0 )->SetNext( & ( * ( neural_macro_structure_.begin() + 1 ) ) );
			( neural_macro_structure_.begin() + 1 )->SetPrev( & ( * ( neural_macro_structure_.begin() + 0 ) ) );
			( neural_macro_structure_.begin() + 1 )->SetNext( & ( * ( neural_macro_structure_.begin() + 2 ) ) );
			( neural_macro_structure_.begin() + 2 )->SetPrev( & ( * ( neural_macro_structure_.begin() + 1 ) ) );
			( neural_macro_structure_.begin() + 2 )->SetNext( 0 );

			this->SetLearningRate( ( value_type ) 0.05 );
			this->SetSigmoidParameter( ( value_type ) 1.0 );

			this->gene_.AddElement( new Genetics::GeneticPair( 0, 1 ) );
			this->gene_.AddElement( new Genetics::GeneticPair( 1, 2 ) );
			this->gene_.AddElement( new Genetics::GeneticPair( 2, 3 ) );
		}

		~NeuralMacroStructure( void )
		{
			while ( ! neural_macro_structure_.empty() )
			{
				delete neural_macro_structure_.back();
				neural_macro_structure_.pop_back();
			}
		}

		inline void Initialize( const char * filename, 
		      const unsigned int & node_size, 
		      const value_type & lr, 
		      const value_type & sp )
		{
			this->gene_.Initialize( filename );
			const unsigned int size_nms = this->gene_.GetLargestElement();

			for ( unsigned int i = 0; i < size_nms; ++i )
				this->neural_macro_structure_.push_back( new NeuralUnit< value_type >( node_size, node_size ) );
			NeuralMacroStructure::SetLearningRate( lr );
			NeuralMacroStructure::SetSigmoidParameter( sp );	
			
			for ( Genetics::ParentGenetic<Genetics::GeneticPair *>::genetic_iterator it = this->gene_.Begin();
                              it != this->gene_.End();
                              ++it )
			{
				( * ( this->neural_macro_structure_.begin() + ( * it )->GetFirst() ) )->
					SetNext( ( * ( this->neural_macro_structure_.begin() + ( * it )->GetSecond() ) ) );
				( * ( this->neural_macro_structure_.begin() + ( * it )->GetSecond() ) )->
					SetPrev( ( * ( this->neural_macro_structure_.begin() + ( * it )->GetFirst() ) ) );
			}
		}

		inline void PushBack( const NeuralUnit< value_type > & new_member )
		{
			neural_macro_structure_.push_back( new NeuralUnit< value_type >( new_member ) );
		}

		// assumes input/output sizes are equal!!
		inline void Mutate( void ) 
		{
			// assumes input/output sizes are equal!!
			unsigned int node_size = neural_macro_structure_.at( 0 )->GetRows();
			value_type lr = neural_macro_structure_.at( 0 )->GetLearningRate();
			value_type sp = neural_macro_structure_.at( 0 )->GetSigmoidParameter();

			while ( ! neural_macro_structure_.empty() )
			{
				delete neural_macro_structure_.back();
				neural_macro_structure_.pop_back();
			}

			this->gene_.Perturbation();
			const unsigned int size_nms = this->gene_.GetLargestElement();

			for ( unsigned int i = 0; i < size_nms; ++i )
				this->neural_macro_structure_.push_back( new NeuralUnit< value_type >( node_size, node_size ) );
			NeuralMacroStructure::SetLearningRate( lr );
			NeuralMacroStructure::SetSigmoidParameter( sp );	
			
			for ( Genetics::ParentGenetic<Genetics::GeneticPair *>::genetic_iterator it = this->gene_.Begin();
                              it != this->gene_.End();
                              ++it )
			{
				( * ( this->neural_macro_structure_.begin() + ( * it )->GetFirst() ) )->
					SetNext( ( * ( this->neural_macro_structure_.begin() + ( * it )->GetSecond() ) ) );
				( * ( this->neural_macro_structure_.begin() + ( * it )->GetSecond() ) )->
					SetPrev( ( * ( this->neural_macro_structure_.begin() + ( * it )->GetFirst() ) ) );
			}
		}

		inline void SetLearningRate( const value_type & value )
		{
			for ( neural_it it = neural_macro_structure_.begin();
                              it != neural_macro_structure_.end();
                              ++it )
			{
				( * it )->SetLearningRate( value );
			}
		}

		inline void SetSigmoidParameter( const value_type & value )
		{
			for ( neural_it it = neural_macro_structure_.begin();
                              it != neural_macro_structure_.end();
                              ++it )
			{
				( * it )->SetSigmoidParameter( value );
			}
		}

		inline unsigned int Size( void ) const
		{
			unsigned int value_type = 0;
			for ( const_neural_it it = neural_macro_structure_.begin();
                              it != neural_macro_structure_.end();
                              ++it )
			{
				value_type += ( * it )->Size();
			}
			return value_type;
		}

		inline unsigned int Nodes( void ) const
		{
			return neural_macro_structure_.size();
		}

		inline MathLib::Matrix::Matrix< value_type > GetOutput( void ) { return this->neural_macro_structure_.back()->GetOutput(); }

		inline void GetOutput( typename std::vector< value_type > & output, const unsigned int & size_output ) 
		{
			neural_it it = neural_macro_structure_.end() - 1;
			output.resize( size_output );
			typename std::vector< value_type >::iterator iit = output.end();

			for ( ; ; --it )
			{
				iit -= ( * it )->GetSizeOutput();
				if ( iit < output.begin() ) break;
				( * it )->GetOutput( iit );
			}
		}	

		inline void GetOutput( value_type * output, const unsigned int & size_output ) 
		{
			neural_it it = neural_macro_structure_.end() - 1;
			value_type * iit = output + size_output;

			for ( ; ; --it )
			{
				iit -= ( * it )->GetSizeOutput();
				if ( iit < output ) break;
				( * it )->GetOutput( iit );
			}
		}	

		inline void PutNeuralMacroStructure( const char * filename )
		{
			ofstream output( filename );

			output.seekp( 0, ios::beg ); // write data starting at offset 0 from the beginning

			if ( ! output.is_open() )
			{
				cerr << "Error: Unable to open output file" << endl;
				exit( 1 );
			}

			for ( neural_it it = neural_macro_structure_.begin();
                              it != neural_macro_structure_.end();
                              ++it )
			{
				( * it )->PutNeuralUnit( & output );
			}

			output.close();
		}

		inline void PutNeuralMacroStructure( typename std::vector< value_type > & contents )
		{
			for ( neural_it it = neural_macro_structure_.begin();
                              it != neural_macro_structure_.end();
                              ++it )
			{
				( * it )->PutNeuralUnit( contents );
			}
		}

		inline void GetNeuralMacroStructure( const char * filename )
		{
			ifstream input( filename, ios::in );

			if ( ! input.is_open() )
			{
				cerr << "Error: Unable to open input neural input file: " << filename << endl;
				exit( 1 );
			}

			if ( input.peek() == ifstream::traits_type::eof() )
			{
				cerr << "Error: File \"" << filename << "\" is empty!" << endl;	
				exit( 1 );
			}

			std::vector< value_type > input_data;
			copy( istream_iterator< value_type >( input ), istream_iterator< value_type >(), back_inserter( input_data ) );

			unsigned int index = 0;
			for ( neural_it it = neural_macro_structure_.begin();
                              it != neural_macro_structure_.end();
                              ++it )
			{
				( * it )->GetNeuralUnit( input_data, index );
				index += ( * it )->Size();
			}

			input.close();
		}

		inline void GetNeuralMacroStructure( const typename std::vector< value_type > & contents )
		{
			unsigned int index = 0;
			assert( contents.size() >= this->Size() );
			typename std::vector< value_type >::const_iterator iit = contents.begin();
			for ( neural_it it = neural_macro_structure_.begin();
                              it != neural_macro_structure_.end();
                              ++it )
			{
				( * it )->GetNeuralUnit( iit, ( * it )->Size() );
				iit += ( * it )->Size();
			}
		}

		inline void Propagate( const std::vector< value_type > & input, const unsigned int & size_input )
		{
			neural_it it = neural_macro_structure_.begin();
			typename std::vector< value_type >::const_iterator iit = input.begin();

			for ( ; iit < input.end(); ++it )
			{
				( * it )->Propagate( MathLib::Matrix::Matrix< value_type > ( iit, ( * it )->GetSizeInput(), 1 ) );
				iit += ( * it )->GetSizeInput();
			}

			for ( ;
                              it != neural_macro_structure_.end();
                              ++it )
			{
				( * it )->Propagate();
			}
		}

		inline void Propagate( const value_type * input, const unsigned int & size_input )
		{
			neural_it it = neural_macro_structure_.begin();
			const value_type * iit = input;

			for ( ; iit < input + size_input; ++it )
			{
				( * it )->Propagate( MathLib::Matrix::Matrix< value_type > ( iit, ( * it )->GetSizeInput(), 1 ) );
				iit += ( * it )->GetSizeInput();

			}

			for ( ;
                              it != neural_macro_structure_.end();
                              ++it )
			{
				( * it )->Propagate();
			}
		}

		inline MathLib::Matrix::Matrix< value_type > Propagate( const MathLib::Matrix::Matrix< value_type > & input )
		{
			neural_it it = neural_macro_structure_.begin();
			( * it )->Propagate( input );
			++it;

			for ( ;
                              it != neural_macro_structure_.end();
                              ++it )
			{
				( * it )->Propagate();
			}

			return this->GetOutput();
		}

		inline typename std::vector< value_type > Propagate( const std::vector< value_type > & input )
		{
			this->Propagate( MathLib::Matrix::Matrix< value_type >( input.begin(), input.size(), 1 ) );
			return this->GetOutput().Convert();
		}

		// BackPropagation - given vector for desired output
		// ASSUME: a propagate step has happened so that the appropriate buffers are filled
		inline void BackPropagate( const typename std::vector< value_type > & output, 
						const unsigned int & size_output )
		{
			neural_it it = neural_macro_structure_.end() - 1;
			typename std::vector< value_type >::const_iterator iit = output.end();

			for ( ; ; --it )
			{
				iit -= ( * it )->GetSizeOutput();
				if ( iit < output.begin() ) break;
				( * it )->BackPropagate( MathLib::Matrix::Matrix< value_type > ( iit, ( * it )->GetSizeOutput(), 1 ) );
			}

			for ( ;
                              it >= neural_macro_structure_.begin();
                              --it )
			{
				( * it )->BackPropagate();
			}
		}

		// BackPropagation - given value_type array for desired output
		// ASSUME: a propagate step has happened so that the appropriate buffers are filled
		inline void BackPropagate( const value_type * output, 
						const unsigned int & size_output )
		{
			neural_it it = neural_macro_structure_.end() - 1;
			const value_type * iit = output + size_output;

			for ( ; ; --it )
			{
				iit -= ( * it )->GetSizeOutput();
				if ( iit < output ) break;
				( * it )->BackPropagate( MathLib::Matrix::Matrix< value_type > ( iit, ( * it )->GetSizeOutput(), 1 ) );
			}

			for ( ;
                              it >= neural_macro_structure_.begin();
                              --it )
			{
				( * it )->BackPropagate();
			}
		}

		// BackPropagation - given matrix for desired output
		// ASSUME: a propagate step has happened so that the appropriate buffers are filled
		//
		// for linear NMS ONLY!!
		inline void BackPropagate( const MathLib::Matrix::Matrix< value_type > & output )
		{
			neural_it it = neural_macro_structure_.end() - 1;
			( * it )->BackPropagate( output );
			--it;

			for ( ;
                              it >= neural_macro_structure_.begin();
                              --it )
			{
				( * it )->BackPropagate();
			}
		}

		// BackPropagation - given vector for desired output
		// ASSUME: a propagate step has happened so that the appropriate buffers are filled
		//
		// for linear NMS ONLY!!
		inline void BackPropagate( const std::vector< value_type > & output )
		{
			MathLib::Matrix::Matrix< value_type > output_Matrix( output.begin(), output.size(), 1 );
			this->BackPropagate( output_Matrix );
		}

		// Error - returns value_type error, given matrix desired output
		// ASSUME: a propagate step has happened so that the appropriate buffers are filled
		// and thus output_ - desired_output makes sense
		//
		// for linear NMS ONLY!!
		inline const value_type Error( const MathLib::Matrix::Matrix< value_type > & desired_output )
		{
			return this->neural_macro_structure_.back()->Error( desired_output );
		}

		// Error - returns value_type error - given vector desired output
		// ASSUME: a propagate step has happened so that the appropriate buffers are filled
		// and thus output_ - desired_output makes sense
		inline const value_type Error( const typename std::vector< value_type > & output, 
						const unsigned int & size_output )
		{
			value_type return_value = 0.0;
			neural_it it = neural_macro_structure_.end() - 1;
			typename std::vector< value_type >::const_iterator iit = output.end();

			for ( ; ; --it )
			{
				iit -= ( * it )->GetSizeOutput();
				if ( iit < output.begin() ) break;
				return_value += ( * it )->Error( MathLib::Matrix::Matrix< value_type > ( iit, ( * it )->GetSizeOutput(), 1 ) );
			}

			return return_value;
		}

		// Error - returns value_type error - given array desired output
		// ASSUME: a propagate step has happened so that the appropriate buffers are filled
		// and thus output_ - desired_output makes sense
		inline const value_type Error( const value_type * output, 
						const unsigned int & size_output )
		{
			value_type return_value = 0.0;
			neural_it it = neural_macro_structure_.end() - 1;
			const value_type * iit = output + size_output;

			for ( ; ; --it )
			{
				iit -= ( * it )->GetSizeOutput();
				if ( iit < output ) break;
				return_value += ( * it )->Error( MathLib::Matrix::Matrix< value_type > ( iit, ( * it )->GetSizeOutput(), 1 ) );
			}

			return return_value;
		}

		// iterator to the beginning of the nms
		inline typename std::vector< NeuralUnit< value_type > * >::iterator Begin( void ) { return neural_macro_structure_.begin(); }		

		// iterator to the end of the nms
		inline typename std::vector< NeuralUnit< value_type > * >::iterator End( void ) { return neural_macro_structure_.end(); }		

		// multiply all weights by a constant.  used for temporing
		inline NeuralMacroStructure< value_type > operator *= ( const value_type & constant )
		{
			for ( neural_it it = neural_macro_structure_.begin();
                              it != neural_macro_structure_.end();
                              ++it )
			{
				( ** it ) *= constant;
			}
			return * this;
		}


	private :

		std::vector< NeuralUnit< value_type > * > neural_macro_structure_; 

		Genetics::GeneticGraph gene_;
};

} // NeuralNetwork

} // AILib

#endif // TEMPLATE_NEURAL_NETWORK_LIBRARY_H
