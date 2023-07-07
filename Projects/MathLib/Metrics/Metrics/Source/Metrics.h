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
#include <string.h>

#include <vector>
#include <cmath>
#include <cstdlib>

namespace MathLib
{

namespace Metrics
{
        //////////////////////////////////////////////////////////////////////////////
        // Log function - implements change of base formula
        //////////////////////////////////////////////////////////////////////////////
	double Log( const unsigned int & base, const double & argument )
	{
		return ( log( argument ) / log( base ) );
	}
	
        //////////////////////////////////////////////////////////////////////////////
        // Euclidean distance function definition normalized
        //////////////////////////////////////////////////////////////////////////////
	template< typename type_name >
        inline type_name EuclideanDistance( const type_name * a, const type_name * b,
		 const unsigned int & size, const type_name & norm )
        {
                type_name return_value = 0.0;
                const type_name * jt = b;
                for ( const type_name * it = a;
                      it != a + size;
                      ++it,
                      ++jt )
                {
                        return_value += ( ( * it - * jt ) * ( * it - * jt ) );
                }
                return ( pow( return_value, 0.5 ) / norm );
        }

        //////////////////////////////////////////////////////////////////////////////
        // Manhattan distance function definition normalized
        //////////////////////////////////////////////////////////////////////////////
	template< typename type_name >
        inline type_name ManhattanDistance( const type_name * a, const type_name * b,
		 const unsigned int & size, const type_name & norm )
        {
                type_name return_value = 0.0;
                const type_name * jt = b;
                for ( const type_name * it = a;
                      it != a + size;
                      ++it,
                      ++jt )
                {
                        return_value += abs( * it - * jt );
                }
                return return_value / norm;
        }

        //////////////////////////////////////////////////////////////////////////////
        // Euclidean distance function definition 
        //////////////////////////////////////////////////////////////////////////////
	template< typename type_name >
        inline type_name EuclideanDistance( const type_name * a, const type_name * b,
		 const unsigned int & size )
        {
                type_name return_value = 0.0;
                const type_name * jt = b;
                for ( const type_name * it = a;
                      it != a + size;
                      ++it,
                      ++jt )
                {
                        return_value += ( ( * it - * jt ) * ( * it - * jt ) );
                }
                return pow( return_value, 0.5 );
        }

        //////////////////////////////////////////////////////////////////////////////
        // Manhattan distance function definition normalized
        //////////////////////////////////////////////////////////////////////////////
	template< typename type_name >
        inline type_name ManhattanDistance( const type_name * a, const type_name * b,
		 const unsigned int & size )
        {
                type_name return_value = 0.0;
                const type_name * jt = b;
                for ( const type_name * it = a;
                      it != a + size;
                      ++it,
                      ++jt )
                {
                        return_value += abs( * it - * jt );
                }
                return return_value;
        }

        //////////////////////////////////////////////////////////////////////////////
        // Euclidean distance function prototype
        //////////////////////////////////////////////////////////////////////////////
	template< typename type_name >
        inline type_name EuclideanDistance( const typename std::vector< type_name > & a, 
		 const typename std::vector< type_name > & b )
	{
		type_name return_value = 0.0;
		typename std::vector< type_name >::const_iterator jt = b.begin();
		for ( typename std::vector< type_name >::const_iterator it = a.begin();
		      it != a.end();
		      ++it,
                      ++jt )
		{
			return_value += ( ( * it - * jt ) * ( * it - * jt ) );
		}
		return pow( return_value, 0.5 );
	}
                        
        //////////////////////////////////////////////////////////////////////////////
        // Manhattan distance function prototype
        //////////////////////////////////////////////////////////////////////////////
	template< typename type_name >
        inline type_name ManhattanDistance( const typename std::vector< type_name > & a,
		 const typename std::vector< type_name > & b )
	{
		type_name return_value = 0.0;
		typename std::vector< type_name >::const_iterator jt = b.begin();
		for ( typename std::vector< type_name >::const_iterator it = a.begin();
		      it != a.end();
		      ++it,
                      ++jt )
		{
			return_value += abs( * it - * jt );
		}
		return return_value;
	}

        //////////////////////////////////////////////////////////////////////////////
        // Euclidean distance function prototype
        //////////////////////////////////////////////////////////////////////////////
	template< typename type_name >
        inline type_name EuclideanDistance( const typename std::vector< type_name > & a, 
		 const typename std::vector< type_name > & b,
		 const type_name & norm )
	{
		type_name return_value = 0.0;
		typename std::vector< type_name >::const_iterator jt = b.begin();
		for ( typename std::vector< type_name >::const_iterator it = a.begin();
		      it != a.end();
		      ++it,
                      ++jt )
		{
			return_value += ( ( * it - * jt ) * ( * it - * jt ) );
		}
		return ( pow( return_value, 0.5 ) / norm );
	}
                        
        //////////////////////////////////////////////////////////////////////////////
        // Manhattan distance function prototype
        //////////////////////////////////////////////////////////////////////////////
	template< typename type_name >
        inline type_name ManhattanDistance( const typename std::vector< type_name > & a, 
		 const typename std::vector< type_name > & b,
		 const type_name & norm )
	{
		type_name return_value = 0.0;
		typename std::vector< type_name >::const_iterator jt = b.begin();
		for ( typename std::vector< type_name >::const_iterator it = a.begin();
		      it != a.end();
		      ++it,
                      ++jt )
		{
			return_value += abs( * it - * jt );
		}
		return ( return_value / norm );
	}

        //////////////////////////////////////////////////////////////////////////////
        // Determine normalization value for use in normalized distance metrics 
        //////////////////////////////////////////////////////////////////////////////
	template< typename type_name >
	inline type_name DetermineNormalizationValue( const type_name ** data, 
		const unsigned int & rows, 
		const unsigned int & cols,
		type_name ( * distance_function )( const type_name *, const type_name * , const unsigned int & ) )
	{
		type_name return_value = 0.0;
		type_name temp = 0.0;

		for ( const type_name ** i_ptr = data;
                      i_ptr != data + rows;
                      ++i_ptr )
		{
			for ( const type_name ** j_ptr = data;
			      j_ptr != data + rows;
			      ++j_ptr )
			{
				if ( j_ptr != i_ptr )
				{
					temp = distance_function( * i_ptr, * j_ptr, cols );
					if ( return_value < temp )
					{
						return_value = temp;
					}
				}
			}
		}

		return return_value;
	}

        //////////////////////////////////////////////////////////////////////////////
	// find largest value in matrix
        //////////////////////////////////////////////////////////////////////////////
	template< typename type_name >
	inline type_name DetermineNormalizationValue( const type_name ** data, 
		const unsigned int & rows, 
		const unsigned int & cols )
	{
		type_name return_value = **data;

		for ( const type_name ** i_ptr = data;
                      i_ptr != data + rows;
                      ++i_ptr )
		{
			for ( const type_name * j_ptr = * i_ptr;
			      j_ptr != ( * i_ptr ) + cols;
			      ++j_ptr )
			{
				if ( return_value < * j_ptr )
				{
					return_value = * j_ptr;
				}
			}
		}

		return return_value;
	}

        //////////////////////////////////////////////////////////////////////////////
	// Compression distance (Shannon entropy)
        //////////////////////////////////////////////////////////////////////////////
	double CompressionDistance( const char *, const unsigned int & );

        //////////////////////////////////////////////////////////////////////////////
	// Normalized Compression Distance
        //////////////////////////////////////////////////////////////////////////////
	double NormalizedCompressionDistance( const char * __restrict, 
                                             const unsigned int &,
                                             const char * __restrict,
                                             const unsigned int & );
		
} // Metrics

} // MathLib
