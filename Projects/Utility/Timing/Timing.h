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
#include <iostream>

#ifndef TIMING_VARIABLE_BEFORE
#define TIMING_VARIABLE_BEFORE

long long before = 0;

#endif //TIMING_VARIABLE_BEFORE


#ifndef TIMING_VARIABLE_AFTER
#define TIMING_VARIABLE_AFTER

long long after  = 0;

#endif //TIMING_VARIABLE_AFTER

#ifndef READ_TIME_STAMP_COUNTER
#define READ_TIME_STAMP_COUNTER

#ifndef WIN32
	inline long long RDTSC()
	{
	   register long long TSC asm("eax");
	   asm volatile (".byte 15, 49" : : : "eax", "edx");
	   return TSC;
	}
#else
	__declspec( naked )
	unsigned __int64 _cdecl RDTSC()
	{
		__asm
		{
			rdtsc;
			ret;
		}
	}
#endif

#endif //READ_TIME_STAMP_COUNTER 

#ifndef START
void start()
{
	before = RDTSC();
}
#define START  start();
#endif //START

#ifndef STOP
void stop()
{
	after = RDTSC();
	std::cout << ( after - before ) << std::endl;
}
#define STOP stop();
#endif //STOP

#ifndef STOPN
void stopn()
{
	after = RDTSC();
	std::cout << ( after - before ) << std::endl << std::endl;
}
#define STOPN stopn();
#endif //STOPN
