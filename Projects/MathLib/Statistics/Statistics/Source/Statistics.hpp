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
#ifndef MATHLIB_STATISTICS_H
#define MATHLIB_STATISTICS_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

namespace MathLib
{

namespace Statistics
{

#ifndef MATHLIB_STATISTICS_OUTER_PRODUCT_DOUBLE
#define MATHLIB_STATISTICS_OUTER_PRODUCT_DOUBLE
inline void OuterProduct( const double * column, double ** result, const unsigned int & size_column )
{
	double ** r_ptr = result;
	for ( const double * i_ptr = column; 
              i_ptr != column + size_column; 
              ++i_ptr, 
              ++r_ptr )
	{
		double * r_r_ptr = * r_ptr;
		for ( const double * j_ptr = column; 
                      j_ptr != column + size_column; 
                      ++j_ptr, 
                      ++r_r_ptr )
		{
			* r_r_ptr = * i_ptr * * j_ptr;
		}
	}
}
#endif // MATHLIB_STATISTICS_OUTER_PRODUCT_DOUBLE

#ifndef MATHLIB_STATISTICS_MEAN_DOUBLE
#define MATHLIB_STATISTICS_MEAN_DOUBLE
inline double Mean( double * input, const unsigned int & size_input )
{
	double return_value = 0.0f;
	for ( const double * i_ptr = input; 
              i_ptr != input + size_input; 
              ++i_ptr )
	{
		return_value += * i_ptr;
	}
	return ( return_value / ( ( double ) size_input ) );
}
#endif // MATHLIB_STATISTICS_MEAN_DOUBLE

#ifndef MATHLIB_STATISTICS_MEAN_TEMPLATE_VECTOR
#define MATHLIB_STATISTICS_MEAN_TEMPLATE_VECTOR
template< typename T >
inline T Mean( const typename std::vector< T > input )
{
	return ( accumulate( input.begin(), input.end(), 0.0 ) / ( ( T ) input.size() ) );
}
#endif // MATHLIB_STATISTICS_MEAN_TEMPLATE_VECTOR

#ifndef MATHLIB_STATISTICS_MEAN_TEMPLATE
#define MATHLIB_STATISTICS_MEAN_TEMPLATE
template< typename T >
inline T Mean( const T * input, const unsigned int & size_input )
{
	return ( accumulate( input, input + size_input, 0.0 ) / ( ( T ) size_input ) );
}
#endif // MATHLIB_STATISTICS_MEAN_TEMPLATE

#ifndef MATHLIB_STATISTICS_MEAN_DOUBLE_2D
#define MATHLIB_STATISTICS_MEAN_DOUBLE_2D
void Mean( const double ** input, double * means, const unsigned int & rows, const unsigned int & columns )
{
	double * m_ptr = means;
	for ( const double ** i_ptr = input; 
              i_ptr != input + rows; 
              ++i_ptr,
              ++m_ptr )
	{
		for ( const double * i_i_ptr = * i_ptr; 
                      i_i_ptr != ( * i_ptr ) + columns ; 
                      ++i_i_ptr )
		{
			* m_ptr += * i_i_ptr;
		}
		* m_ptr /= ( double ) columns;
	}
}
#endif // MATHLIB_STATISTICS_MEAN_DOUBLE_2D

#ifndef MATHLIB_STATISTICS_STDDEV_DOUBLE
#define MATHLIB_STATISTICS_STDDEV_DOUBLE
inline double StandardDeviation( const double * input, const double & mean, const unsigned int & columns )
{
	double return_value = 0.0f;
	for ( const double * i_ptr = input;
              i_ptr != input + columns;
              ++i_ptr )
	{
		return_value += ( ( ( * i_ptr ) - mean ) * ( ( * i_ptr ) - mean ) );
	}
	return_value /= ( double ) columns;
	return sqrt( return_value );
}
#endif // MATHLIB_STATISTICS_STDDEV_DOUBLE

#ifndef MATHLIB_STATISTICS_STDDEV_TEMPLATE_VECTOR
#define MATHLIB_STATISTICS_STDDEV_TEMPLATE_VECTOR
template< typename T >
inline T StandardDeviation( const typename std::vector< T > input )
{
	T return_value = ( T ) 0.0;
	T mean = Mean< T >( input );
	for ( typename std::vector< T >::const_iterator it = input.begin();
              it != input.end();
              ++it )
	{
		return_value += ( ( ( * it ) - mean ) * ( ( * it ) - mean ) );
	}
	return_value /= ( T ) input.size();
	return sqrt( return_value );
}
#endif // MATHLIB_STATISTICS_STDDEV_TEMPLATE_VECTOR

#ifndef MATHLIB_STATISTICS_STDDEV_TEMPLATE
#define MATHLIB_STATISTICS_STDDEV_TEMPLATE
template< typename T >
inline T StandardDeviation( const T * input, const unsigned int & size_input )
{
	T return_value = ( T ) 0.0;
	T mean = Mean< T >( input, size_input );
	for ( const T * it = input;
              it != input + size_input;
              ++it )
	{
		return_value += ( ( ( * it ) - mean ) * ( ( * it ) - mean ) );
	}
	return_value /= ( T ) size_input;
	return sqrt( return_value );
}
#endif // MATHLIB_STATISTICS_STDDEV_TEMPLATE

#ifndef MATHLIB_STATISTICS_VAR_DOUBLE
#define MATHLIB_STATISTICS_VAR_DOUBLE
inline double Variance( const double * input, const double & mean, const unsigned int & columns )
{
	double return_value = 0.0f;
	for ( const double * i_ptr = input;
              i_ptr != input + columns;
              ++i_ptr )
	{
		return_value += ( ( ( * i_ptr ) - mean ) * ( ( * i_ptr ) - mean ) );
	}
	return ( return_value / ( ( double ) ( columns - 1 ) ) );
}
#endif // MATHLIB_STATISTICS_VAR_DOUBLE

#ifndef MATHLIB_STATISTICS_STDDEV_DOUBLE_2D
#define MATHLIB_STATISTICS_STDDEV_DOUBLE_2D
void StandardDeviation( const double ** input, double * std_dev, const unsigned int & rows, const unsigned int & columns ) 
{
	double * mean = new double [ rows ];
	Mean( input, mean, rows, columns );

	double * m_ptr = mean;
	double * s_ptr = std_dev;
	for ( const double ** i_ptr = input; 
              i_ptr != input + rows; 
              ++i_ptr,
              ++m_ptr,
              ++s_ptr )
	{
		for ( const double * i_i_ptr = * i_ptr; 
                      i_i_ptr != * ( i_ptr ) + columns; 
                      ++i_i_ptr )
		{
			* s_ptr += ( * i_i_ptr - * m_ptr ) * ( * i_i_ptr - * m_ptr );
		}
		* s_ptr /= ( double ) columns;
	}	

	for ( s_ptr = std_dev; s_ptr != std_dev + rows; ++s_ptr )
	{
		* s_ptr = sqrt( * s_ptr );
	}

	delete [] mean;
}
#endif // MATHLIB_STATISTICS_STDDEV_DOUBLE_2D

#ifndef MATHLIB_STATISTICS_STDDEV_DOUBLE_2D_2
#define MATHLIB_STATISTICS_STDDEV_DOUBLE_2D_2
void StandardDeviation( const double ** input, const double * mean, double * std_dev, const unsigned int & rows, const unsigned int & columns ) 
{
	const double * m_ptr = mean;
	double * s_ptr = std_dev;
	for ( const double ** i_ptr = input; 
              i_ptr != input + rows; 
              ++i_ptr,
              ++m_ptr,
              ++s_ptr )
	{
		for ( const double * i_i_ptr = * i_ptr; 
                      i_i_ptr != * ( i_ptr ) + columns; 
                      ++i_i_ptr )
		{
			* s_ptr += ( * i_i_ptr - * m_ptr ) * ( * i_i_ptr - * m_ptr );
		}
		* s_ptr /= ( double ) columns;
	}	

	for ( s_ptr = std_dev; s_ptr != std_dev + rows; ++s_ptr )
	{
		* s_ptr = sqrt( * s_ptr );
	}
}
#endif // MATHLIB_STATISTICS_STDDEV_DOUBLE_2D_2

#ifndef MATHLIB_STATISTICS_MEAN_CENTERED_CORRELATION
#define MATHLIB_STATISTICS_MEAN_CENTERED_CORRELATION
void MeanCenteredCorrelation( const double ** input, double ** m_c_cov, const unsigned int & rows, const unsigned int & columns )
{
	double * mean    = new double [ rows ];
	double * std_dev = new double [ rows ];
	Mean( input, mean, rows, columns );
	StandardDeviation( input, mean, std_dev, rows, columns );

	for ( unsigned int i = 0; i < rows; ++i )
	{
		for ( unsigned int j = i; j < rows; ++j )
		{
			* ( * ( m_c_cov + i ) + j ) = 
			  ( ( * ( * ( input + i ) + 0 ) - * ( mean + i ) ) * 
			    ( * ( * ( input + j ) + 0 ) - * ( mean + j ) ) ) ;
			for ( unsigned int k = 1; k < columns; ++k )
			{
				* ( * ( m_c_cov + i ) + j ) += 
                                  ( ( * ( * ( input + i ) + k ) - * ( mean + i ) ) * 
                                    ( * ( * ( input + j ) + k ) - * ( mean + j ) ) ) ;
			}
		}
	}

	for ( unsigned int i = 0; i < rows; ++i )
	{
		for ( unsigned int j = i; j < rows; ++j )
		{
			* ( * ( m_c_cov + i ) + j ) /= ( ( ( double ) columns ) * * ( std_dev + i ) * * ( std_dev + j ) );
			* ( * ( m_c_cov + j ) + i ) = * ( * ( m_c_cov + i ) + j );
		}
	}

	delete [] mean;
	delete [] std_dev;
}
#endif // MATHLIB_STATISTICS_MEAN_CENTERED_CORRELATION

} // Statistics

} // MathLib

#endif // MATHLIB_STATISTICS_H
