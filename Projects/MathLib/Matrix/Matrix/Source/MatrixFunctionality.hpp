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
#include "Matrix.hpp"

#define PI_CONSTANT 3.1415926535897932385

namespace MathLib
{

namespace Matrix
{

	////////////////////////////////////////////////////////////////////
	// Matrix Operations - basic matrix functionality 
	////////////////////////////////////////////////////////////////////
	namespace Operations
	{
	template < class T >
	inline Matrix< T > AddColumns( const Matrix< T > & matrix, const T & multiple,
				const unsigned int & index1, const unsigned int & index2 )
	{
		Matrix< T > return_value( matrix );
		for ( unsigned int i = 0; i < return_value.GetRows(); ++i )
		{
			return_value.At( i, index2 ) += return_value.At( i, index1 );
		}

		return return_value;
	}

	template < class T >
	inline Matrix< T > AddRows( const Matrix< T > & matrix, const T & multiple,
				const unsigned int & index1, const unsigned int & index2 )
	{
		Matrix< T > return_value( matrix );
		for ( unsigned int i = 0; i < return_value.GetColumns(); ++i )
		{
			return_value.At( index2, i ) += return_value.At( index1, i );
		}

		return return_value;
	}

	template < class T >
	inline T DotColumns( const Matrix< T > & matrix, const unsigned int & index1, const unsigned int & index2 )
	{
		T return_value = 0;
		for ( unsigned int i = 0; i < matrix.GetColumns(); ++i )
		{
			return_value += matrix.At( i, index2 ) * matrix.At( i, index1 );
		}

		return return_value;
	}

	template < class T >
	inline T DotRows( const Matrix< T > & matrix, const unsigned int & index1, const unsigned int & index2 )
	{
		T return_value = 0;
		for ( unsigned int i = 0; i < matrix.GetRows(); ++i )
		{
			return_value += matrix.At( index2, i ) * matrix.At( index1, i );
		}

		return return_value;
	}

	template < class T >
	inline T MaxInRow( const Matrix< T > & matrix, const unsigned int & row )
	{
		assert( row < matrix.GetRows() );
		return * max_element( matrix.Begin( row ), matrix.End( row ) );
	}

	template < class T >
	inline T MinInRow( const Matrix< T > & matrix, const unsigned int & row )
	{
		assert( row < matrix.GetRows() );
		return * min_element( matrix.Begin( row ), matrix.End( row ) );
	}

	template < class T >
	inline T MinInColumn( const Matrix< T > & matrix, const unsigned int & column )
	{
		assert( column < matrix.GetColumns() );

		T min_value = matrix.At( 0, column );
		for ( unsigned int i = 1; i < matrix.GetRows(); ++i )
		{
			if ( matrix.At( i, column ) < min_value )
			{
				min_value = matrix.At( i, column );
			}
		}

		return min_value;
	}

	template < class T >
	inline T MaxInColumn( const Matrix< T > & matrix, const unsigned int & column )
	{
		assert( column < matrix.GetColumns() );

		T max_value = matrix.At( 0, column );
		for ( unsigned int i = 1; i < matrix.GetColumns(); ++i )
		{
			if ( matrix.At( i, column ) > max_value )
			{
				max_value = matrix.At( i, column );
			}
		}

		return max_value;
	}
	}

	////////////////////////////////////////////////////////////////////
	// Fourier analysis - Fourier analysis package 
	////////////////////////////////////////////////////////////////////
	namespace Fourier
	{
	template < class T >
	inline Matrix< T > PSD( const Matrix< T > & matrix )
	{
                T arg = 0;
                T real = 0;
                T imaginary = 0;
                T cosarg = 0;
                T sinarg = 0;

		Matrix< T > return_value( matrix );
		for ( unsigned int i = 0; i < return_value.GetRows(); ++i )
		{
			unsigned int j = 0;
			typename std::vector< T >::iterator jt = return_value.Begin( i );
			for ( typename std::vector< T >::const_iterator it = matrix.Begin( i ); 
				it != matrix.End( i ); 
				++it,
				++jt,
				++j )
			{
				// instantiate the T arg outside of the loop??
				arg = -2.0 * PI_CONSTANT * ( T ) j / return_value.GetColumns();
				real = 0;
				imaginary = 0;

				for ( unsigned int k = 0; k < matrix.GetColumns(); ++k )
				{
					cosarg = cos( k * arg );
					sinarg = sin( k * arg );
					real += * ( matrix.Begin( i ) + k ) * cosarg;
					imaginary += * ( matrix.Begin( i ) + k ) * sinarg;
				}

				* jt = ( ( ( real * real ) + ( imaginary * imaginary ) ) / 
					( ( T ) matrix.GetColumns() * 2.0 * PI_CONSTANT ) );
			}
		}
		return return_value;
	}

	template < class T >
	inline Matrix< T > DFT( const Matrix< T > & matrix )
	{
                T arg = 0;
                T real = 0;
                T imaginary = 0;
                T cosarg = 0;
                T sinarg = 0;

		Matrix< T > return_value( matrix );
		for ( unsigned int i = 0; i < return_value.GetRows(); ++i )
		{
			unsigned int j = 0;
			typename std::vector< T >::iterator jt = return_value.Begin( i );
			for ( typename std::vector< T >::const_iterator it = matrix.Begin( i ); 
				it != matrix.End( i ); 
				++it,
				++jt,
				++j )
			{
				// instantiate the T arg outside of the loop??
				arg = -2.0 * PI_CONSTANT * ( T ) j / return_value.GetColumns();
				real = 0;
				imaginary = 0;

				for ( unsigned int k = 0; k < matrix.GetColumns(); ++k )
				{
					cosarg = cos( k * arg );
					sinarg = sin( k * arg );
					real += * ( matrix.Begin( i ) + k ) * cosarg;
					imaginary += * ( matrix.Begin( i ) + k ) * sinarg;
				}

				* jt = sqrt( ( ( ( real * real ) / ( T ) matrix.GetColumns()
                                       + ( imaginary * imaginary ) ) / ( T ) matrix.GetColumns() ) );
			}
		}
		return return_value;
	}
	}

	////////////////////////////////////////////////////////////////////
	// Statistics - Statistical packages for matrix manipulation
	////////////////////////////////////////////////////////////////////
	namespace Statistics
	{
	template < class T >
	inline Matrix< T > NormalizeByRow( const Matrix< T > & matrix )
	{
		T row_max = 0;
		T row_min = 0;
		T difference = 0;
		Matrix< T > return_value( matrix );
		for ( unsigned int i = 0; i < return_value.GetRows(); ++i )
		{
			row_min = * min_element( return_value.Begin( i ), return_value.End( i ) );
			row_max = * max_element( return_value.Begin( i ), return_value.End( i ) );
			difference = ( row_max - row_min );
			
			for ( typename std::vector< T >::iterator it = return_value.Begin( i ); 
				it != return_value.End( i ); 
				++it )
			{
				* it -= row_min; * it /= difference;				
			}
		}
		return return_value;
	}

	template < class T >
	inline Matrix< T > NormalizeByColumn( const Matrix< T > & matrix )
	{
		Matrix< T > return_value( matrix );
		for ( unsigned int j = 0; j < matrix.GetColumns(); ++j )
		{
			T min_value = matrix.At( 0, 0 );
			T max_value = matrix.At( 0, 0 );
			for ( unsigned int i = 0; i < matrix.GetRows(); ++i )
			{
				if ( matrix.At( i, j ) < min_value )
				{
					min_value = matrix.At( i, j );
				}

				if ( matrix.At( i, j ) > min_value )
				{
					max_value = matrix.At( i, j );
				}
			}

			T difference = ( max_value - min_value );
			for ( unsigned int i = 0; i < return_value.GetRows(); ++i )
			{
				return_value.At( i, j ) -= min_value; return_value.At( i, j ) /= difference;
			}
		}

		return return_value;
	}

	template < class T >
	inline Matrix< T > Max( const Matrix< T > & matrix )
	{
		Matrix< T > return_value;
		for ( unsigned int i = 0; i < matrix.GetRows(); ++i )
		{
			return_value.PushBack( * max_element( matrix.Begin( i ), matrix.End( i ) ) );
		}
		return Transpose( return_value );
	}

	template < class T >
	inline Matrix< T > Min( const Matrix< T > & matrix )
	{
		Matrix< T > return_value;
		for ( unsigned int i = 0; i < matrix.GetRows(); ++i )
		{
			return_value.PushBack( * min_element( matrix.Begin( i ), matrix.End( i ) ) );
		}
		return Transpose( return_value );
	}

	template < class T >
	inline Matrix< T > Mean( const Matrix< T > & matrix )
	{
		Matrix< T > return_value;
		T temp_value = 0;
		for ( unsigned int i = 0; i < matrix.GetRows(); ++i )
		{
			temp_value = 0;
			temp_value = accumulate( matrix.Begin( i ), matrix.End( i ), 0.0 );
			temp_value /= matrix.GetColumns();
			return_value.PushBack( temp_value );
		}
		return Transpose( return_value );
	}

	template < class T >
	inline Matrix< T > StdDev( const Matrix< T > & matrix )
	{
		Matrix< T > return_value;
		Matrix< T > means( Mean( matrix ) );
		T temp_value = 0;
		for ( unsigned int i = 0; i < matrix.GetRows(); ++i )
		{
			for ( typename std::vector< T >::const_iterator it = matrix.Begin( i ); 
				it != matrix.End( i ); 
				++it )
			{
				temp_value = ( * it - means.At( i ) ) * ( * it - means.At( i ) );
			}
			temp_value /= ( matrix.GetColumns() - 1 );
			return_value.PushBack( sqrt( temp_value ) );
		}
		return Transpose( return_value );
	}

	template < class T >
	inline Matrix< T > Variance( const Matrix< T > & matrix )
	{
		Matrix< T > return_value;
		Matrix< T > means( Mean( matrix ) );
		for ( unsigned int i = 0; i < return_value.GetRows(); ++i )
		{
			T temp_value = 0;
			for ( typename std::vector< T >::const_iterator it = matrix.Begin( i ); 
				it != matrix.End( i ); 
				++it )
			{
				temp_value += ( * it - means.At( i ) ) * ( * it - means.At( i ) );
			}
			temp_value /= ( matrix.GetColumns() - 1 );
			return_value.PushBack( temp_value );
		}
		return Transpose( return_value );
	}

	template < class T >
	inline Matrix< T > Correlation( const Matrix< T > & matrix1, const Matrix< T > & matrix2 )
	{
		assert( matrix1.GetRows() == matrix2.GetRows() );
		assert( matrix1.GetColumns() == matrix2.GetColumns() );
		Matrix< T > return_value;
		Matrix< T > std_devs1( StdDev( matrix1 ) );
		Matrix< T > std_devs2( StdDev( matrix2 ) );
		Matrix< T > means1( Mean( matrix1 ) );
		Matrix< T > means2( Mean( matrix2 ) );
		for ( unsigned int i = 0; i < matrix1.GetRows(); ++i )
		{
			T temp_value = 0;
			typename std::vector< T >::const_iterator jt = matrix2.Begin( i );
			for ( typename std::vector< T >::const_iterator it = matrix1.Begin( i ); 
				it != matrix1.End( i ); 
				++it )
			{
				temp_value += ( * it - means1.At( i ) ) * ( * jt - means2.At( i ) );
			}
			temp_value /= ( matrix1.GetColumns() - 1 );
			return_value.PushBack( temp_value / ( std_devs1.At( i ) * std_devs2.At( i ) ) );
		}
		return Transpose( return_value );
	}

	template < class T >
	inline Matrix< T > CrossCorrelation( const Matrix< T > & matrix1, const Matrix< T > matrix2 )
	{
		assert( matrix1.GetRows() == matrix2.GetRows() );
		assert( matrix1.GetColumns() == matrix2.GetColumns() );
		return Matrix< T >();
	}

	template < class T >
	inline Matrix< T > AutoCorrelation( const Matrix< T > & matrix )
	{
		assert( matrix.GetRows() == 1 );
		return Matrix< T >();
	}

	template < class T >
	inline Matrix< T > Covariance( const Matrix< T > & matrix1, const Matrix< T > & matrix2 )
	{
		assert( matrix1.GetRows() == matrix2.GetRows() );
		assert( matrix1.GetColumns() == matrix2.GetColumns() );
		Matrix< T > return_value;
		Matrix< T > means1( Mean( matrix1 ) );
		Matrix< T > means2( Mean( matrix2 ) );
		T temp_value = 0;
		for ( unsigned int i = 0; i < matrix1.GetRows(); ++i )
		{
			typename std::vector< T >::const_iterator jt = matrix2.Begin( i );
			for ( typename std::vector< T >::const_iterator it = matrix1.Begin( i ); 
				it != matrix1.End( i ); 
				++it )
			{
				temp_value = ( * it - means1.At( i ) ) * ( * jt - means2.At( i ) );
			}
			temp_value /= ( matrix1.GetColumns() - 1 );
			return_value.PushBack( temp_value );
		}
		return Transpose( return_value );
	}
	}

	////////////////////////////////////////////////////////////////////
	// Preprocessors - functionality to preprocess matrices for input
	// into AI frameworks e.g. neural networks, etc.
	////////////////////////////////////////////////////////////////////
	namespace Preprocessor
	{
	template < class T >
	inline Matrix< T > NormalizeByRow( const Matrix< T > & matrix )
	{
		return 2.0 * Statistics::NormalizeByRow( matrix ) - 1.0;
	}

	template < class T >
	inline Matrix< T > NormalizeByColumn( const Matrix< T > & matrix )
	{
		return 2.0 * Statistics::NormalizeByColumn( matrix ) - 1.0;
	}

	template < class T >
	inline Matrix< T > Mean( const Matrix< T > & matrix )
	{
		Matrix< T > means( Statistics::Mean( matrix ) );
		Matrix< T > return_value( matrix );
		for ( unsigned int i = 0; i < return_value.GetRows(); ++i )
		{
			for ( typename std::vector< T >::iterator it = return_value.Begin( i ); 
				it != return_value.End( i ); 
				++it )
			{
				if ( * it >= means.At( i ) )
				{
					* it = 1.0;
				}
				else
				{
					* it = -1.0;
				}
			}
		}
		return return_value;
	}

	template < class T >
	inline Matrix< T > StdDev( const Matrix< T > & matrix )
	{
		Matrix< T > means( Statistics::Mean( matrix ) );
		Matrix< T > std_dev( Statistics::StdDev( matrix ) );
		Matrix< T > return_value( matrix );
		for ( unsigned int i = 0; i < return_value.GetRows(); ++i )
		{
			for ( typename std::vector< T >::iterator it = return_value.Begin( i ); 
				it != return_value.End( i ); 
				++it )
			{
				if ( * it > means.At( i ) + std_dev.At( i )  )
				{
					* it = 1.0;
				}
				else if ( * it < means.At( i ) - std_dev.At( i )  )
				{
					* it = -1.0;
				}
				else
				{
					* it = 0; 
				}
			}
		}
		return return_value;
	}

	template < class T >
	inline Matrix< T > Increasing( const Matrix< T > & matrix )
	{
		Matrix< T > return_value( matrix );
		for ( unsigned int i = 0; i < return_value.GetRows(); ++i )
		{
			for ( typename std::vector< T >::iterator it = return_value.Begin( i ); 
				it != return_value.End( i ) - 1; 
				++it )
			{
				* it = ( ( * it < * ( it + 1 ) ) ? -1.0 : 1.0 );
			}
			* ( return_value.End( i ) - 1 ) = 1.0;
		}
		return return_value;
	}

	template < class T >
	inline Matrix< T > Fourier( const Matrix< T > & matrix )
	{
		return Matrix< T >( Preprocessor::NormalizeByRow( Fourier::PSD( matrix ) ) );
	}
	}

} // Matrix

} // MathLib
