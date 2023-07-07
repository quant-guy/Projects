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
#define ALLOCATE_MEMORY_TWO_DATASETS( data1, data2, rows, columns1, columns2 )						\
        for ( double ** outer_ptr = data1; outer_ptr < data1 + rows; ++outer_ptr )					\
        {														\
                * outer_ptr = new double [ columns1 ];									\
        }														\
															\
        for ( double ** outer_ptr = data2; outer_ptr < data2 + rows; ++outer_ptr )					\
        {														\
                * outer_ptr = new double [ columns2 ];									\
        }														\
															\
        for ( double ** outer_ptr = data1; outer_ptr < data1 + rows; ++outer_ptr )					\
        {														\
                for ( double * inner_ptr = * outer_ptr; inner_ptr < ( * outer_ptr ) + columns1; ++inner_ptr )		\
                {													\
                        * inner_ptr = 0.0;										\
                }													\
        }														\
															\
        for ( double ** outer_ptr = data2; outer_ptr < data2 + rows; ++outer_ptr )					\
        {														\
                for ( double * inner_ptr = * outer_ptr; inner_ptr < ( * outer_ptr ) + columns2; ++inner_ptr )		\
                {													\
                        * inner_ptr = 0.0;										\
                }													\
        }

#define ALLOCATE_MEMORY_ONE_DATASET( data1, rows, columns1 )								\
        for ( double ** outer_ptr = data1; outer_ptr < data1 + rows; ++outer_ptr )					\
        {														\
                * outer_ptr = new double [ columns1 ];									\
        }														\
															\
        for ( double ** outer_ptr = data1; outer_ptr < data1 + rows; ++outer_ptr )					\
        {														\
                for ( double * inner_ptr = * outer_ptr; inner_ptr < ( * outer_ptr ) + columns1; ++inner_ptr )		\
                {													\
                        * inner_ptr = 0.0;										\
                }													\
        }

#define DELETE_MEMORY_TWO_DATASETS( data1, data2, rows )								\
        for ( unsigned int i = 0; i < rows; ++i )									\
        {														\
                delete [] data1[ i ];											\
        }														\
	delete [] data1;												\
															\
        for ( unsigned int i = 0; i < rows; ++i )									\
        {														\
                delete [] data2[ i ];											\
        }														\
	delete [] data2;

#define DELETE_MEMORY_ONE_DATASET( data1, rows )									\
        for ( unsigned int i = 0; i < rows; ++i )									\
        {														\
                delete [] data1[ i ];											\
        }														\
	delete [] data1;
	
#define DELETE_VECTOR_MEMORY( data )											\
	while ( ! data.empty() )											\
	{														\
		delete data.back();											\
		data.pop_back();											\
	} 