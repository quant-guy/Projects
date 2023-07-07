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
#include "Metrics.h"
#include <iostream>
using namespace std;

namespace MathLib
{

namespace Metrics
{

        //////////////////////////////////////////////////////////////////////////////
	// Compression distance (Shannon entropy)
        //////////////////////////////////////////////////////////////////////////////
	double CompressionDistance( const char * data, const unsigned int & size )
	{
		const unsigned int map_size = 256;
		double probability = 0.0;
		double entropy = 0.0;
		const unsigned int base = 8;
		unsigned int map[ map_size ] = { 0 };

		for ( register int i = 0; i < size; ++i )
		{
			map[ ( unsigned int ) ( unsigned char ) data[ i ] ]++;
		}

		for ( unsigned int i = 1; i < map_size; ++i )
		{
			if ( map[ i ] > 0 )
			{
				probability = ( ( double ) ( unsigned char ) map[ i ] / ( double ) size );
				entropy -= probability * Log( base, probability );
			}
		}

		return entropy;
	}

        //////////////////////////////////////////////////////////////////////////////
	// Normalized Compression Distance
        //////////////////////////////////////////////////////////////////////////////
	double NormalizedCompressionDistance( const char * __restrict data1, 
	     const unsigned int & size1,
	     const char * __restrict data2,
	     const unsigned int & size2 )
	{
		double data1_compression = CompressionDistance( data1, size1 );
		double data2_compression = CompressionDistance( data2, size2 );
		double concat_compression = 0.0;
		double min, max;
		unsigned int concat_length = size1 + size2;

		if ( data1_compression > data2_compression )
		{
			min = data2_compression; max = data1_compression;
		}
		else
		{
			min = data1_compression; max = data2_compression;
		}

		char * data_concatenation = new char[ concat_length ];

		strncpy( data_concatenation, data1, size1 );
		strncpy( data_concatenation + size1, data2, size2 );

		concat_compression = CompressionDistance( data_concatenation, concat_length );

		delete [] data_concatenation;

		return ( concat_compression - min ) / max;
	}

} // Metrics

} // MathLib
