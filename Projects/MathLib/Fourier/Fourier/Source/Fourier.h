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
#ifndef FOURIER_H
#define FOURIER_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>

#ifndef PI
#define PI M_PI 
#endif  // PI

namespace MathLib
{

namespace Fourier
{

	void real_abs_dft1( const float * __restrict,   // input array
		            const unsigned int &,  	// size input array 
                            float * __restrict,    	// output array
			    const unsigned int & );	// size output array

	void real_abs_dft1( const double *,		// input array
		            const unsigned int &,  	// size input array 
                            double *,			// output array
			    const unsigned int & );	// size output array

	void real_abs_dft2( const float * __restrict,   // input array
			    const unsigned int &,       // size input array
		            float * __restrict,    	// output array
	                    const unsigned int & );	// size output array

	void real_abs_dft2( const double *,   		// input array
			    const unsigned int &,       // size input array
		            double *,    		// output array
	                    const unsigned int & );	// size output array

	void pwr_spec_dns1( const float * __restrict,   // input array
			    const unsigned int &,       // size input array
		            float * __restrict,    	// output array
	                    const unsigned int & );	// size output array

	void pwr_spec_dns1( const double *,	   	// input array
			    const unsigned int &,       // size input array
		            double *,    		// output array
	                    const unsigned int & );	// size output array

	void pwr_spec_dns2( const float * __restrict,   // input array
			    const unsigned int &,       // size input array
		            float * __restrict,    	// output array
	                    const unsigned int & );	// size output array

	void pwr_spec_dns2( const double *,   		// input array
			    const unsigned int &,       // size input array
		            double *, 		   	// output array
	                    const unsigned int & );	// size output array

	void real_abs_dft1( float * __restrict,    	// input output array
			    const unsigned int & );	// size input output array

	void real_abs_dft1( double *,		    	// input output array
			    const unsigned int & );	// size input output array

	void real_abs_dft2( float * __restrict,    	// input output array
			    const unsigned int & );	// size input output array

	void real_abs_dft2( double *,		    	// input output array
			    const unsigned int & );	// size input output array

	void pwr_spec_dns1( float * __restrict,    	// input output array
			    const unsigned int & );	// size input output array

	void pwr_spec_dns1( double *,		    	// input output array
			    const unsigned int & );	// size input output array

	void pwr_spec_dns2( float * __restrict,    	// input output array
			    const unsigned int & );	// size input output array

	void pwr_spec_dns2( double *,		    	// input output array
			    const unsigned int & );	// size input output array
} // Fourier

} // MathLib

#endif // FOURIER_H
