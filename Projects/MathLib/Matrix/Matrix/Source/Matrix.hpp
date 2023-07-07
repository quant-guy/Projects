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
#ifndef MATHLIB_MATRIX_H
#define MATHLIB_MATRIX_H

#include <assert.h>
#include <iostream>										// i/o functionality
#include <fstream>										// i/o file functionality
#include <cmath>										// exp function
#include <vector>										// vector 
#include <string>										// string
#include <iterator>										// iterator, and iterator manipulation
#include <algorithm>										// copy, for_each, transform
#include <numeric>										// accumulate
#include <functional>										// plus< T >, minus< T >, multiplies< T >

using namespace std;

namespace MathLib
{

namespace Matrix
{
	/////////////////////////////////////////////////////////////////////////
	// parent class to functor classes, purely virtual
	/////////////////////////////////////////////////////////////////////////
	template< class T >
	class template_functor
	{
		public : virtual T operator () ( const T & ) = 0;
	};


	/////////////////////////////////////////////////////////////////////////
	// Functors 
	/////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////
	// sigmoid function functor 
	/////////////////////////////////////////////////////////////////////////
	template< class T >
	class sigmoid_functor : public template_functor< T > 
	{
		private: T parameter_;

		public : sigmoid_functor( void ) : parameter_( 1.0 ) {}

		public : sigmoid_functor( const T & parameter ) : parameter_( parameter ) {}

		public : inline virtual T operator () ( const T & x )
		{
			return ( ( 2 / ( 1 + exp( - parameter_ * x ) ) - 1 ) );
		}
	};


	/////////////////////////////////////////////////////////////////////////
	// derivative of sigmoid function functor 
	/////////////////////////////////////////////////////////////////////////
	template< class T >
	class dsigmoid_functor : public template_functor< T > 
	{
		private: T parameter_;

		public : dsigmoid_functor( void ) : parameter_ ( 1.0 ) {}

		public : dsigmoid_functor( const T & parameter ) : parameter_ ( parameter ) {}

		public : inline virtual T operator () ( const T & x )
		{
			return ( 2 * parameter_ * exp( - parameter_ * x ) / 
				( ( 1 + exp( - parameter_ * x ) ) * ( 1 + exp( - parameter_ * x ) ) ) ) ;
		}
	};



	/////////////////////////////////////////////////////////////////////////
	// Multiplication by constant functor
	/////////////////////////////////////////////////////////////////////////
	template< class T >
	class multiplication_by_constant_functor : public template_functor< T > 
	{
		private: T parameter_;

		public : multiplication_by_constant_functor( const T & parameter ) :
			parameter_( parameter ) {}

		public : inline virtual T operator () ( const T & x )
		{
			return x * parameter_;
		}
	};


	/////////////////////////////////////////////////////////////////////////
	// Addition by constant functor
	/////////////////////////////////////////////////////////////////////////
	template< class T >
	class addition_by_constant_functor : public template_functor< T > 
	{
		private: T parameter_;

		public : addition_by_constant_functor( const T & parameter ) :
			parameter_( parameter ) {}

		public : inline virtual T operator () ( const T & x )
		{
			return x + parameter_;
		}
	};


	/////////////////////////////////////////////////////////////////////////
	// Error function 
	/////////////////////////////////////////////////////////////////////////
	template< class T >
	class error_functor : public template_functor< T > 
	{ 
		public : inline virtual T operator () ( const T & x ) { return x; }

		public : inline virtual T operator () ( const T & y, const T & x ) 
		{
			return ( 0.5 * ( x - y ) * ( x - y ) );
		}
	};



	/////////////////////////////////////////////////////////////////////////
	// parent class to matrix objects 
	/////////////////////////////////////////////////////////////////////////
	template< class T >
	class Matrix
	{
		public :

		typedef T value_type;

		typedef typename std::vector< value_type > matrix_template;

		typedef const typename std::vector< value_type > const_matrix_template;

		typedef typename std::vector< value_type >::iterator matrix_iterator;

		typedef typename std::vector< value_type >::const_iterator const_matrix_iterator;

		///////////////////////////////////////////////////////////////////////////////////////////
		// multiplication by constant operator 
		///////////////////////////////////////////////////////////////////////////////////////////
		friend Matrix< value_type > operator * ( const value_type & multiple, const Matrix< value_type > & right )	
		{
			Matrix< value_type > return_value( right.rows_, right.columns_ );
			transform( right.matrix_.begin(), right.matrix_.end(),
				return_value.matrix_.begin(), multiplication_by_constant_functor< value_type >( multiple ) );
			return return_value;
		}

		///////////////////////////////////////////////////////////////////////////////////////////
		// ostream operator 
		///////////////////////////////////////////////////////////////////////////////////////////
		friend ostream & operator << ( ostream & strm, const Matrix< value_type > & right )
		{
			unsigned int index = right.columns_; 

			for ( unsigned int i = 0; i < right.rows_; ++i )
			{
				copy( right.matrix_.begin() + ( i * index ), 
				      right.matrix_.begin() + ( ( ( i + 1 ) * index ) - 1 ),
				      ostream_iterator< value_type >( strm, "," ) );
				strm << * ( right.matrix_.begin() + ( ( ( i + 1 ) * index ) - 1 ) );
				strm << endl;
			}

			return strm;
		}

		///////////////////////////////////////////////////////////////////////////////////////////
		// Transpose operator for column vectors
		///////////////////////////////////////////////////////////////////////////////////////////
		friend Matrix< value_type > Transpose( const Matrix< value_type > & input )				
		{
			Matrix< value_type > temp( input.columns_, input.rows_ );
			for ( register unsigned int i = 0; i < input.columns_; ++i )
			{
				typename std::vector< value_type >::const_iterator it = input.matrix_.begin() + i;
				for ( typename std::vector< value_type >::iterator jt = ( temp.matrix_.begin() + ( i * input.rows_ ) );
				      jt != ( temp.matrix_.begin() + ( ( i + 1 ) * input.rows_ ) );
				      ++jt,
				      it += input.columns_ )
				{
					* jt = * it;
				}
			} 
			return temp;	
		}

		///////////////////////////////////////////////////////////////////////////////////////////
		// sigmoid function applied to a matrix
		///////////////////////////////////////////////////////////////////////////////////////////
		friend Matrix< value_type > SIG ( const Matrix< value_type > & input, const value_type & parameter )
		{
			Matrix< value_type > return_value( input.rows_, input.columns_ );
			transform( input.matrix_.begin(), input.matrix_.end(),
				return_value.matrix_.begin(), sigmoid_functor< value_type >( parameter ) );
			return return_value;
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		// derivative of the sigmoid function applied to a matrix
		///////////////////////////////////////////////////////////////////////////////////////////
		friend Matrix< value_type > DSIG ( const Matrix< value_type > & input, const value_type & parameter )
		{
			Matrix< value_type > return_value( input.rows_, input.columns_ );
			transform( input.matrix_.begin(), input.matrix_.end(),
				return_value.matrix_.begin(), dsigmoid_functor< value_type >( parameter ) );
			return return_value;
		}

		///////////////////////////////////////////////////////////////////////////////////////////
		// error matrix 
		///////////////////////////////////////////////////////////////////////////////////////////
		friend value_type ERR ( const Matrix< value_type > & left, const Matrix< value_type > & right )
		{
			assert( ( left.rows_ == right.rows_ ) && ( left.columns_ == right.columns_ ) );
			Matrix< value_type > return_value( left.rows_, left.columns_ );
			transform( left.matrix_.begin(), left.matrix_.end(), right.matrix_.begin(),
				return_value.matrix_.begin(), error_functor< value_type >() );
			return accumulate( return_value.matrix_.begin(), return_value.matrix_.end(), 0.0 );
		}

		///////////////////////////////////////////////////////////////////////////////////////////
		// componentwise multiplication 
		///////////////////////////////////////////////////////////////////////////////////////////
		friend Matrix< value_type > COMP ( const Matrix< value_type > & left, const Matrix< value_type > & right )	
		{
			assert( ( left.rows_ == right.rows_ ) && ( left.columns_ == right.columns_ ) );
			Matrix< value_type > return_value( left.rows_, left.columns_ );
			transform( left.matrix_.begin(), left.matrix_.end(), right.matrix_.begin(),
				return_value.matrix_.begin(), multiplies< value_type >() );
			return return_value;
		}

		///////////////////////////////////////////////////////////////////////////////////////////
		// dot product, aka inner product 
		///////////////////////////////////////////////////////////////////////////////////////////
		friend const value_type DOT ( const Matrix< value_type > & left, const Matrix< value_type > & right )	
		{
			assert( ( left.rows_ == right.rows_ ) && ( left.columns_ == right.columns_ ) );
			return inner_product( left.matrix_.begin(), left.matrix_.end(), right.matrix_.begin(), 0.0 );
		}

		///////////////////////////////////////////////////////////////////////////////////////////
		// sum
		///////////////////////////////////////////////////////////////////////////////////////////
		friend const value_type SUM ( const Matrix< value_type > & input )
		{
			return accumulate( input.matrix_.begin(), input.matrix_.end(), 0.0 );
		}

		friend void Fill( Matrix< value_type > & input, const value_type & value )
		{
			std::fill( input.matrix_.begin(), input.matrix_.end(), ( value_type ) value );
		}

		public :

			Matrix( void ) :  		
				rows_( 0 ),
				columns_( 0 ) {}

			Matrix( const unsigned int & rows,
				const unsigned int & columns ) :		
				rows_( rows ),
				columns_( columns ),
				matrix_( ( rows * columns ) ) {}	

			Matrix( const Matrix & matrix ) :
				rows_( matrix.rows_ ),
				columns_( matrix.columns_ ),
				matrix_( matrix.matrix_.begin(), matrix.matrix_.end() ) {}

			Matrix( const value_type * array, const unsigned int rows, const unsigned int cols ) :
				rows_( rows ),
				columns_( cols ),
				matrix_( array, array + ( rows * cols ) ) {}

			Matrix( const_matrix_template m, const unsigned int rows, const unsigned int cols ) :
				rows_( rows ),
				columns_( cols ),
				matrix_( m.begin(), m.end() ) { assert( m.size() == ( rows * cols ) ) ;}

			Matrix( matrix_iterator b, const unsigned int rows, const unsigned int cols ) :
				rows_( rows ),
				columns_( cols ),
				matrix_( b, b + ( rows * cols ) ) {}

			Matrix( const_matrix_iterator b, const unsigned int rows, const unsigned int cols ) :
				rows_( rows ),
				columns_( cols ),
				matrix_( b, b + ( rows * cols ) ) {}

			Matrix( const value_type ** array, const unsigned int rows, const unsigned int cols ) :
				rows_( rows ),
				columns_( cols ),
				matrix_( rows * cols )
			{ 
				assert( this->GetRows() == rows );
				assert( this->GetColumns() == cols );
				for ( unsigned int i = 0; i < rows; ++i )
					for ( unsigned int j = 0; j < cols; ++j )
						this->At( i, j ) = * ( * ( array + i ) + j );
			}

			~Matrix( void ) {}       

			inline void GetMatrix( ifstream * input )
			{
				assert( input->is_open() );

				if ( matrix_.size() != 0 )
					copy( istream_iterator< value_type >( * input ), istream_iterator< value_type >(), this->matrix_.begin() );
				else
					copy( istream_iterator< value_type >( * input ), istream_iterator< value_type >(), back_inserter( this->matrix_ ) );
			}

			inline void GetMatrix( const value_type ** array, const unsigned int rows, const unsigned int cols )
			{
				this->rows_ = rows;
				this->columns_ = cols;
				this->matrix_.clear();
				this->matrix_.resize( rows * cols );
				std::fill( this->matrix_.begin(), this->matrix_.end(), ( value_type ) 0.0 );
				for ( unsigned int i = 0; i < rows; ++i )
					for ( unsigned int j = 0; j < cols; ++j )
						this->At( i, j ) = * ( * ( array + i ) + j );
			}

			inline void PutMatrix( ofstream * output ) const
			{
				assert( output->is_open() );
				copy( this->matrix_.begin(), this->matrix_.end(), ostream_iterator< value_type >( * output, "\n" ) );
			}

			inline void PutMatrix( typename std::vector< value_type > & contents ) const
			{
				copy( this->matrix_.begin(), this->matrix_.end(), back_inserter( contents ) );
			}

			inline const unsigned int GetRows( void ) const { return this->rows_; }

			inline void SetRows( const unsigned int & rows ) { this->rows_ = rows; }

			inline const unsigned int GetColumns( void ) const { return this->columns_; }

			inline void SetColumns( const unsigned int & columns ) { this->columns_ = columns; }

			inline const unsigned int Size( void ) const { return this->matrix_.size(); }

			inline matrix_iterator Begin( void ) { return this->matrix_.begin(); }

			inline matrix_iterator End( void ) { return this->matrix_.end(); }

			inline matrix_iterator Begin( const unsigned int & row ) 
			{ 
				assert( row < this->rows_ );
				return this->matrix_.begin() + row * this->columns_; 
			}

			inline matrix_iterator End( const unsigned int & row ) 
			{ 
				assert( row < this->rows_ );
				return this->matrix_.begin() + row * this->columns_ + this->columns_; 
			}

			inline const_matrix_iterator Begin( const unsigned int & row ) const
			{ 
				assert( row < this->rows_ );
				return this->matrix_.begin() + row * this->columns_; 
			}

			inline const_matrix_iterator End( const unsigned int & row ) const
			{ 
				assert( row < this->rows_ );
				return this->matrix_.begin() + row * this->columns_ + this->columns_; 
			}

			inline const_matrix_iterator Begin( void ) const { return this->matrix_.begin(); }

			inline const_matrix_iterator End( void ) const { return this->matrix_.end(); }

			inline const Matrix GetRow( const unsigned int & index ) const
			{
				Matrix< value_type > return_value( this->columns_, 1 );
				copy( this->matrix_.begin() + index * this->columns_, this->matrix_.begin() + 
					( index + 1 ) * this->columns_, return_value.matrix_.begin() );
				return return_value;
			}

			inline void PutRow( const Matrix & matrix, const unsigned int & index )
			{
				assert( matrix.matrix_.size() == this->columns_ );
				copy( matrix.matrix_.begin(), matrix.matrix_.end(), this->matrix_.begin() + index * this->columns_ );
			}

			inline Matrix & GetRow( const unsigned int & index )
			{
				Matrix< value_type > return_value( this->columns_, 1 );
				copy( this->matrix_.begin() + index * this->columns_, this->matrix_.begin() + 
					( index + 1 ) * this->columns_, return_value.matrix_.begin() );
				return return_value;
			}

			inline const value_type & At( const unsigned int & index ) const
			{
				assert( index < this->Size() );
				return this->matrix_.at( index );
			}

			inline value_type & At( const unsigned int & index )
			{
				assert( index < this->Size() );
				return this->matrix_.at( index );
			}

			inline const value_type & At( const unsigned int & index1, const unsigned int & index2 ) const
			{
				assert( index1 < this->rows_ && index2 < this->columns_ );
				return this->matrix_.at( this->columns_ * index1 + index2 );
			}

			inline value_type & At( const unsigned int & index1, const unsigned int & index2 )
			{
				assert( index1 < this->rows_ && index2 < this->columns_ );
				return this->matrix_.at( this->columns_ * index1 + index2 );
			}

			inline void PushBack( const value_type & value )
			{
				this->matrix_.push_back( value );
				this->rows_ = 1; 
				this->columns_ = this->matrix_.size(); 
			}

			inline void PushFront( const value_type & value )
			{
				this->matrix_.insert( this->matrix_.begin(), value );
				this->rows_ = 1; 
				this->columns_ = this->matrix_.size(); 
			}

			inline void Reverse( void ) { reverse( this->matrix_.begin(), this->matrix_.end() ); }

			inline bool CheckDimensions( const Matrix & right ) const
			{
				return ( ( this->rows_ == right.rows_ ) && ( this->columns_ == right.columns_ ) );
			}

			inline typename std::vector< value_type > Convert( void ) { return this->matrix_; }

			inline void Convert( value_type ** array, const unsigned int & rows, const unsigned int & cols ) 
			{ 
				assert( this->GetRows() == rows );
				assert( this->GetColumns() == cols );
				for ( unsigned int i = 0; i < rows; ++i )
					for ( unsigned int j = 0; j < cols; ++j )
						* ( * ( array + i ) + j ) = this->At( i, j );
			}

			inline void Convert( value_type * array, const unsigned int & size ) 
			{ 
				assert( this->matrix_.size() == size );
				copy( this->matrix_.begin(), this->matrix_.end(), array );
			}

			// WARNING: for column matrices ONLY!!
			inline const Matrix ColumnTranspose( void ) const
			{
				Matrix< value_type > return_value( * this );	
				return_value.rows_ = this->columns_;
				return_value.columns_ = this->rows_;
				return return_value;
			}

			inline const Matrix operator + ( const Matrix & right ) const
			{
				assert( this->CheckDimensions( right ) );
				Matrix< value_type > temp( this->rows_, this->columns_ );
				temp.matrix_.resize( right.Size() );
				transform( this->matrix_.begin(), this->matrix_.end(), right.matrix_.begin(), temp.matrix_.begin(), plus< value_type >() );
				return temp;
			}

			inline const Matrix operator + ( const value_type & right ) const
			{
				Matrix< value_type > temp( * this );
				for ( typename std::vector<value_type>::iterator it = temp.matrix_.begin();
					it != temp.matrix_.end();
					++it )
				{
					* it += right;
				}
				return temp;
			}

			inline const Matrix operator - ( const Matrix & right ) const
			{
				assert( this->CheckDimensions( right ) );
				Matrix< value_type > temp( this->rows_, this->columns_ );
				transform( this->matrix_.begin(), this->matrix_.end(), right.matrix_.begin(), temp.matrix_.begin(), minus< value_type >() );
				return temp;
			}

			inline const Matrix operator - ( const value_type & right ) const
			{
				Matrix< value_type > temp( * this );
				for ( typename std::vector<value_type>::iterator it = temp.matrix_.begin();
					it != temp.matrix_.end();
					++it )
				{
					* it -= right;
				}
				return temp;
			}

			inline const Matrix operator *  ( const Matrix & right ) const
			{
				assert( this->columns_ == right.rows_ );

				//instantiate matrix to hold output
				Matrix< value_type > output( this->rows_, right.columns_ ); 

				// offset i by -columns_, since first increment is by "columns"
				int i = - ( int ) output.columns_;		   

				// offset k by -1 since first increment is by "1" and we want to start at zero
				int k = -1;					   

				// pointer to matrix on the left
				typename vector< value_type >::const_iterator a = this->matrix_.begin();		   

				// pointer to matrix on the right
				typename vector< value_type >::const_iterator b = right.matrix_.begin();		   

				// pointer to matrix where output will be stored
				typename vector< value_type >::iterator c = output.matrix_.begin();		   

				// stop: stopping condition.  Equivalent to:
				// output.rows_ * output.columns_ * right.rows_ 
				int stop = output.rows_ * output.columns_ * this->columns_;

				for ( register int j = 0; j < stop; ++j )
				{
					if ( j % ( right.columns_ ) == 0 )
					{
						++k;
					}

					if ( j % ( right.rows_ * output.columns_ ) == 0 )
					{
						i += output.columns_;
					}
					
					* ( c + i + j % output.columns_ ) += 
					* ( a + k ) 
					*
					* ( b + j % ( right.rows_ * right.columns_ ) );
				}
				return( output );
			}

			inline const Matrix operator * ( const value_type & constant )
			{
				Matrix< value_type > return_value( this->rows_, this->columns_ );
				transform( return_value.matrix_.begin(), return_value.matrix_.end(), this->matrix_.begin(), 
						multiplication_by_constant_functor< value_type >( constant ) );
				return return_value;
			}

			inline const Matrix operator *= ( const value_type & constant )
			{
				for ( typename std::vector<value_type>::iterator it = this->matrix_.begin(); 
					it != this->matrix_.end(); 
					it++ )
				{
					* it *= constant;
				}

				return * this;
			}

			inline const Matrix operator += ( const Matrix & right )
			{
				assert( this->CheckDimensions( right ) );
				transform( this->matrix_.begin(), this->matrix_.end(), right.matrix_.begin(), this->matrix_.begin(), plus< value_type >() );
				return * this;
			}

			inline const Matrix operator -= ( const Matrix & right )
			{	
				assert( this->CheckDimensions( right ) );
				transform( this->matrix_.begin(), this->matrix_.end(), right.matrix_.begin(), this->matrix_.begin(), minus< value_type >() );
				return * this;
			}

			inline Matrix & operator = ( const Matrix & right )
			{	
				this->matrix_.clear();
				this->matrix_.resize( right.matrix_.size() );
				copy( right.matrix_.begin(), right.matrix_.end(), matrix_.begin() );
				this->rows_ = right.rows_;
				this->columns_ = right.columns_;
				return * this;
			}

		protected :

			unsigned int rows_;

			unsigned int columns_;

			vector< value_type > matrix_;
	};


	/////////////////////////////////////////////////////////////////////////
	// derived class of Matrix: square matrix.  This has n by n dimensions 
	/////////////////////////////////////////////////////////////////////////
	template< class T >
	class SquareMatrix : public Matrix< T >
	{
		public : 

			typedef T value_type;

			SquareMatrix( const unsigned int & dim ) :
				Matrix< value_type >( dim, dim ) {}
		
			~SquareMatrix( void ) {}
	};


	/////////////////////////////////////////////////////////////////////////
	// derived class of Matrix: column matrix.  This has n by 1 dimensions
	/////////////////////////////////////////////////////////////////////////
	template< class T >
	class ColumnMatrix : public Matrix< T >
	{
		public : 

			typedef T value_type;

			ColumnMatrix( const unsigned int & dim ) : 				// everything same except constructor: n by 1
				Matrix< value_type >( dim, 1 ) {}
		
			~ColumnMatrix( void ) {}						// let OS do the cleanup
	};

} // Matrix

} // MathLib
#endif // MATHLIB_MATRIX_H
