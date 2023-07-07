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
#ifndef IOTREAM2_API_H
#define IOTREAM2_API_H

#include <iostream>
#include <vector>

#define TEST std::cout << __LINE__ << std::endl;

namespace Utility
{

namespace Iostream2
{

template < typename T >
inline void cout_array( T ** data, const unsigned int & rows, const unsigned int & columns )
{
	for ( T ** outer_ptr = data; outer_ptr < data + rows; ++outer_ptr )
	{
		T * inner_ptr = * outer_ptr;
		std::cout << * inner_ptr;
		++inner_ptr;
		for ( ; inner_ptr != ( * outer_ptr ) + columns; ++inner_ptr )
		{
			std::cout << ", " << * inner_ptr;
		}
		std::cout << std::endl;
	}
}

template < typename T >
inline void cout_array( T * data, const unsigned int & columns )
{
	std::cout << * data;
	for ( T * inner_ptr = data + 1; inner_ptr != data + columns; ++inner_ptr )
	{
		std::cout << ", " << * inner_ptr;
	}
	std::cout << std::endl;
}

template < typename T >
inline void cout_array( const typename std::vector< T > data )
{
	std::cout << data.at( 0 );
	for ( typename std::vector< T >::const_iterator it = data.begin() + 1; it != data.end(); ++it )
	{
		std::cout << ", " << * it;
	}
	std::cout << std::endl;
}

} // Utility

} // Iostream2

#endif // IOTREAM2_API_H
