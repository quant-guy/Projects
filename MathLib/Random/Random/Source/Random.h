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
// Implementations for random class

#ifndef SRAND
static unsigned int r_seed = 0;
#define SRAND srand( r_seed == 0 ? ( unsigned int ) time( 0 ) : r_seed )
#endif // SRAND

#ifndef RAND_0
#define RAND_0 ( ( float )( random_number_generator() % 10000 ) )/10000
#endif // RAND_0

#ifndef RAND_1
#define RAND_1 ( ( float )( random_number_generator() % 2000 ) - 1000 )/1000
#endif // RAND_1

#ifndef RAND_4
#define RAND_4 ( ( float )( random_number_generator() % 2000 ) - 1000 )/4000
#endif // RAND_4

#ifndef RANDOM_BIN
#define RANDOM_BIN ( ( random_number_generator()%2 == 1 ) ? 1 : -1 )
#endif // RANDOM_BIN

#ifndef WIN32
	#ifndef RANDOM_NUMBER_GENERATOR
	#define RANDOM_NUMBER_GENERATOR
	static unsigned int random_number_generator( void )
	{
		unsigned int output = 0;

		// if r_seed == 0, grap the time stamp counter,
		// else use r_seed value to seed	
		if ( r_seed == 0 )
		{
		   register long long TSC asm("eax");
		   __asm__ __volatile__  ( ".byte 15, 49;	\n"
					   "imul  $13, %%eax;	\n"		// multiply by 13
					   "movl  %%eax, %%edx;	\n"		// mov eax into edx
					   "shl   $16, %%eax;	\n"		// shift left 16 bits
					   "shr   $16, %%edx;	\n"		// shift left 16 bits
					   "movw  %%dx, %%ax;	\n"		// mov dx to ax (swapping segments)
					   "movl  %%eax, %0;	\n"		// load into result	   						   
						: "=r"(output)
						: 
						: "eax", "edx");
		   return TSC;

		}
		else
		{
			__asm__ __volatile__ ( 	"movl  %1, %%eax;	\n" 
							"imul  $13, %%eax;	\n"	// multiply by 13
							"movl  %%eax, %%edx;\n"		// mov eax into edx
							"shl   $16, %%eax;	\n"	// shift left 16 bits
							"shr   $16, %%edx;	\n"	// shift left 16 bits
							"movw  %%dx, %%ax;	\n"	// mov dx to ax (swapping segments)
							"movl  %%eax, %0;	\n"	// load into result	   						   
							: "=r"(output)
							: "r"(r_seed) 
							: "eax", "edx");
		}
		
		return output;
	}
	static float random_number_generator( float min, float max )
	{
		return min + ( ( max - min ) * RAND_0 );
	}

	#endif // RANDOM_NUMBER_GENERATOR
#else
	#ifndef RANDOM_NUMBER_GENERATOR
	#define RANDOM_NUMBER_GENERATOR
	static unsigned int random_number_generator( void )
	{
		unsigned int output = 0;

		if ( r_seed == 0 )
		{
			__asm
			{
				rdtsc;
				imul eax, 0x0d;
				mov  eax, edx;
				shl  eax, 0x0F;
				shr  edx, 0x0F;
				mov  ax, dx;
				mov  output, eax;
			}
		}
		else
		{
			__asm
			{
				mov  eax, r_seed;
				imul eax, 0x0d;
				mov  eax, edx;
				shl  eax, 0x0F;
				shr  edx, 0x0F;
				mov  ax, dx;
				mov  output, eax;
			}
		}

		return output;
	}

	static float random_number_generator( float min, float max )
	{
		return min + ( ( max - min ) * RAND_0 );
	}
	#endif // RANDOM_NUMBER_GENERATOR
#endif // WIN32