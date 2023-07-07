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
#include "Fourier.h"

namespace MathLib
{

namespace Fourier
{

	/*
	Discrete Fourier Transform
	*/
	bool DFT(int dir,int m,double *x1,double *y1)
	{
		long i,k;
		double arg;
		double cosarg,sinarg;
		double *x2=NULL,*y2=NULL;

		x2 = ( double * ) malloc( m * sizeof( double ) );
		y2 = ( double * ) malloc( m * sizeof( double ) );

		if (x2 == NULL || y2 == NULL)
			return(false);

		for (i=0;i<m;i++)
		{
			x2[i] = 0;
			y2[i] = 0;
			arg = - dir * 2.0 * PI * (double)i / (double)m;
			for (k=0;k<m;k++)
			{
				cosarg = cos(k * arg);
				sinarg = sin(k * arg);
				x2[i] += (x1[k] * cosarg - y1[k] * sinarg);
				y2[i] += (x1[k] * sinarg + y1[k] * cosarg);
			}
		}

		/* Copy the data back */
		if (dir == 1) 
		{
			for (i=0;i<m;i++)
			{
				x1[i] = x2[i] / (double)m;
				y1[i] = y2[i] / (double)m;
			}
		}
		else 
		{
			for (i=0;i<m;i++) 
			{
				x1[i] = x2[i];
				y1[i] = y2[i];
			}
		}

		free(x2);
		free(y2);
		return(true);
	}


	/*
	Fast Fourier Transform
	----------------------

	This computes an in-place complex-to-complex FFT
	x and y are the real and imaginary arrays of 2^m points.
	dir =  1 gives forward transform
	dir = -1 gives reverse transform
	*/
	bool FFT(short int dir,long m,double *x,double *y)
	{
		long n,i,i1,j,k,i2,l,l1,l2;
		double c1,c2,tx,ty,t1,t2,u1,u2,z;

		/* Calculate the number of points */
		n = 1;
		for (i=0;i<m;i++)
		n *= 2;

		/* Do the bit reversal */
		i2 = n >> 1;
		j = 0;
		for (i=0;i<n-1;i++)
		{
			if (i < j)
			{
				tx = x[i];
				ty = y[i];
				x[i] = x[j];
				y[i] = y[j];
				x[j] = tx;
				y[j] = ty;
			}

			k = i2;
			while (k <= j)
			{
				j -= k;
				k >>= 1;
			}
			j += k;
		}

		/* Compute the FFT */
		c1 = -1.0;
		c2 = 0.0;
		l2 = 1;

		for (l=0;l<m;l++) 
		{
			l1 = l2;
			l2 <<= 1;
			u1 = 1.0;
			u2 = 0.0;
			for (j=0;j<l1;j++) 
			{
				for (i=j;i<n;i+=l2) 
				{
					i1 = i + l1;
					t1 = u1 * x[i1] - u2 * y[i1];
					t2 = u1 * y[i1] + u2 * x[i1];
					x[i1] = x[i] - t1;
					y[i1] = y[i] - t2;
					x[i] += t1;
					y[i] += t2;
				}

				z =  u1 * c1 - u2 * c2;
				u2 = u1 * c2 + u2 * c1;
				u1 = z;
			}

			c2 = sqrt((1.0 - c1) / 2.0);
			if (dir == 1)
				c2 = -c2;

			c1 = sqrt((1.0 + c1) / 2.0);
		}

		/* Scaling for forward transform */
		if (dir == 1) 
		{
			for (i=0;i<n;i++) 
			{
				x[i] /= n;
				y[i] /= n;
			}
		}

		return(false);
	}

	
	////////////////////////////////////////////////////////////////////
	// discrete fourier transform using direct references of the array
	////////////////////////////////////////////////////////////////////
	void real_abs_dft1( const float * __restrict input, 
			    const unsigned int & input_size, 
			    float * __restrict output, 
			    const unsigned int & output_size )
	{
		// instantiate the float arg outside of the loop??
		float arg = 0; 
		float real = 0;
		float imaginary = 0;
		float cosarg = 0; 
		float sinarg = 0; 

		for ( int i = 0; i < output_size; ++i )
		{
			// function to clear arrays, set to zero or memset??  xor??
			output[i] = 0;

			// instantiate the float arg outside of the loop??
			arg = -2.0 * PI * ( float ) i / output_size;
			real = 0;
			imaginary = 0;

			for ( int k = 0; k < input_size; ++k )
			{ 
				cosarg = cos(k * arg);
				sinarg = sin(k * arg);
				real += input[k] * cosarg;
				imaginary += input[k] * sinarg;
			}

			output[i] = pow( ( real*real ) / (float) output_size
			               + ( imaginary*imaginary ) / (float) output_size,
		                       0.5f );
		}
	}

	////////////////////////////////////////////////////////////////////
	// discrete fourier transform using direct references of the array
	////////////////////////////////////////////////////////////////////
	void real_abs_dft1( const double * input, 
			    const unsigned int & input_size, 
			    double * output, 
			    const unsigned int & output_size )
	{
		// instantiate the double arg outside of the loop??
		double arg = 0; 
		double real = 0;
		double imaginary = 0;
		double cosarg = 0; 
		double sinarg = 0; 

		for ( int i = 0; i < output_size; ++i )
		{
			// function to clear arrays, set to zero or memset??  xor??
			output[i] = 0;

			// instantiate the double arg outside of the loop??
			arg = -2.0 * PI * ( double ) i / output_size;
			real = 0;
			imaginary = 0;

			for ( int k = 0; k < input_size; ++k )
			{ 
				cosarg = cos(k * arg);
				sinarg = sin(k * arg);
				real += input[k] * cosarg;
				imaginary += input[k] * sinarg;
			}

			output[i] = pow( ( real*real ) / (double) output_size
			               + ( imaginary*imaginary ) / (double) output_size,
		                       (double) 0.5 );
		}
	}

	////////////////////////////////////////////////////////////////////
	// Power spectral density function = F * F* / 2 PI
	////////////////////////////////////////////////////////////////////
	void pwr_spec_dns1( const float * __restrict input, 
			    const unsigned int & input_size, 
			    float * __restrict output, 
			    const unsigned int & output_size )
	{
		// instantiate the float arg outside of the loop??
		float arg = 0; 
		float real = 0;
		float imaginary = 0;
		float cosarg = 0; 
		float sinarg = 0; 

		for ( int i = 0; i < output_size; ++i )
		{
			// function to clear arrays, set to zero or memset??  xor??
			output[i] = 0;

			// instantiate the float arg outside of the loop??
			arg = -2.0 * PI * ( float ) i / output_size;
			real = 0;
			imaginary = 0;

			for ( int k = 0; k < input_size; ++k )
			{ 
				cosarg = cos(k * arg);
				sinarg = sin(k * arg);
				real += input[k] * cosarg;
				imaginary += input[k] * sinarg;
			}

			output[i] = ( ( ( real * real ) + ( imaginary * imaginary ) ) 
					/ ( ( float ) output_size * 2.0 * PI ) );
		}
	}	

	////////////////////////////////////////////////////////////////////
	// Power spectral density function = F * F* / 2 PI
	////////////////////////////////////////////////////////////////////
	void pwr_spec_dns1( const double * input, 
			    const unsigned int & input_size, 
			    double * output, 
			    const unsigned int & output_size )
	{
		// instantiate the double arg outside of the loop??
		double arg = 0; 
		double real = 0;
		double imaginary = 0;
		double cosarg = 0; 
		double sinarg = 0; 

		for ( int i = 0; i < output_size; ++i )
		{
			// function to clear arrays, set to zero or memset??  xor??
			output[i] = 0;

			// instantiate the double arg outside of the loop??
			arg = -2.0 * PI * ( double ) i / output_size;
			real = 0;
			imaginary = 0;

			for ( int k = 0; k < input_size; ++k )
			{ 
				cosarg = cos(k * arg);
				sinarg = sin(k * arg);
				real += input[k] * cosarg;
				imaginary += input[k] * sinarg;
			}

			output[i] = ( ( ( real * real ) + ( imaginary * imaginary ) ) 
					/ ( ( double ) output_size * 2.0 * PI ) );
		}
	}	

	////////////////////////////////////////////////////////////////////
	// discrete fourier transform using indirect references of the array
	// ie pointer arithmetic
	////////////////////////////////////////////////////////////////////
	void real_abs_dft2( const float * __restrict input, 
			    const unsigned int & input_size, 
			    float * __restrict output, 
			    const unsigned int & output_size )
	{
		int outer_index = 0;
		float arg = 0; 
		float real = 0;
		float imaginary = 0;
		int inner_index = 0;

		float * output_ptr = output;
		for ( const float * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++outer_index,
		      ++output_ptr )
		{
			// function to clear arrays, set to zero or memset??  xor??

			// instantiate the float arg outside of the loop??
			arg = -2.0 * PI * ( ( float ) outer_index / output_size );
			real = 0;
			imaginary = 0;
			inner_index = 0;

			for ( const float * k = input; 
			      k != input + output_size; 
			      ++k,
			      ++inner_index )
			{
				real += ( * k ) * ( cos( ( float ) inner_index * arg ) );
				imaginary += ( * k ) * ( sin( ( float ) inner_index * arg ) );
			}

			* output_ptr = pow( ( real*real ) / (float) input_size
			                  + ( imaginary*imaginary ) / (float) input_size,
		                          0.5f );
		}
	}

	////////////////////////////////////////////////////////////////////
	// discrete fourier transform using indirect references of the array
	// ie pointer arithmetic
	////////////////////////////////////////////////////////////////////
	void real_abs_dft2( const double * input, 
			    const unsigned int & input_size, 
			    double * output, 
			    const unsigned int & output_size )
	{
		int outer_index = 0;
		double arg = 0; 
		double real = 0;
		double imaginary = 0;
		int inner_index = 0;

		double * output_ptr = output;
		for ( const double * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++outer_index,
		      ++output_ptr )
		{
			// function to clear arrays, set to zero or memset??  xor??

			// instantiate the double arg outside of the loop??
			arg = -2.0 * PI * ( ( double ) outer_index / output_size );
			real = 0;
			imaginary = 0;
			inner_index = 0;

			for ( const double * k = input; 
			      k != input + output_size; 
			      ++k,
			      ++inner_index )
			{
				real += ( * k ) * ( cos( ( double ) inner_index * arg ) );
				imaginary += ( * k ) * ( sin( ( double ) inner_index * arg ) );
			}

			* output_ptr = pow( ( real*real ) / (double) input_size
			                  + ( imaginary*imaginary ) / (double) input_size,
		                          (double) 0.5 );
		}
	}

	////////////////////////////////////////////////////////////////////
	// Power spectral density function = F * F* / 2 PI
	////////////////////////////////////////////////////////////////////
	void pwr_spec_dns2( const float * __restrict input, 
			    const unsigned int & input_size, 
			    float * __restrict output, 
			    const unsigned int & output_size )
	{
		int outer_index = 0;
		float arg = 0; 
		float real = 0;
		float imaginary = 0;
		int inner_index = 0;

		float * output_ptr = output;
		for ( const float * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++outer_index,
		      ++output_ptr )
		{
			// function to clear arrays, set to zero or memset??  xor??

			// instantiate the float arg outside of the loop??
			arg = -2.0 * PI * ( ( float ) outer_index / output_size );
			real = 0;
			imaginary = 0;
			inner_index = 0;

			for ( const float * k = input; 
			      k != input + output_size; 
			      ++k,
			      ++inner_index )
			{
				real += ( * k ) * ( cos( ( float ) inner_index * arg ) );
				imaginary += ( * k ) * ( sin( ( float ) inner_index * arg ) );
			}

			* output_ptr = ( ( ( real * real ) + ( imaginary * imaginary ) ) 
					/ ( ( float ) output_size * 2.0 * PI ) );
		}
	}	

	////////////////////////////////////////////////////////////////////
	// Power spectral density function = F * F* / 2 PI
	////////////////////////////////////////////////////////////////////
	void pwr_spec_dns2( const double * input, 
			    const unsigned int & input_size, 
			    double * output, 
			    const unsigned int & output_size )
	{
		int outer_index = 0;
		double arg = 0; 
		double real = 0;
		double imaginary = 0;
		int inner_index = 0;

		double * output_ptr = output;
		for ( const double * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++outer_index,
		      ++output_ptr )
		{
			// function to clear arrays, set to zero or memset??  xor??

			// instantiate the double arg outside of the loop??
			arg = -2.0 * PI * ( ( double ) outer_index / output_size );
			real = 0;
			imaginary = 0;
			inner_index = 0;

			for ( const double * k = input; 
			      k != input + output_size; 
			      ++k,
			      ++inner_index )
			{
				real += ( * k ) * ( cos( ( double ) inner_index * arg ) );
				imaginary += ( * k ) * ( sin( ( double ) inner_index * arg ) );
			}

			* output_ptr = ( ( ( real * real ) + ( imaginary * imaginary ) ) 
					/ ( ( double ) output_size * 2.0 * PI ) );
		}
	}	

	////////////////////////////////////////////////////////////////////
	// discrete fourier transform using direct references of the array
	// only two arguments, so result is copied back into first
	////////////////////////////////////////////////////////////////////
	void real_abs_dft1( float * __restrict input, 
			    const unsigned int & input_size )
	{
		
		float * output = ( float * ) malloc( input_size * sizeof( float ) );

		// instantiate the float arg outside of the loop??
		float arg = 0; 
		float real = 0;
		float imaginary = 0;
		float cosarg = 0; 
		float sinarg = 0; 

		for ( int i = 0; i < input_size; ++i )
		{
			// function to clear arrays, set to zero or memset??  xor??
			output[i] = 0;

			// instantiate the float arg outside of the loop??
			arg = -2.0 * PI * ( float ) i / input_size;
			real = 0;
			imaginary = 0;

			for ( int k = 0; k < input_size; ++k )
			{ 
				cosarg = cos(k * arg);
				sinarg = sin(k * arg);
				real += input[k] * cosarg;
				imaginary += input[k] * sinarg;
			}

			output[i] = pow( ( real*real ) / (float) input_size
			               + ( imaginary*imaginary ) / (float) input_size,
		                       0.5f );
		}

		float * o = output;
		for ( float * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++o )
		{
			* i = * o;
		}

		free( output );
	}

	////////////////////////////////////////////////////////////////////
	// discrete fourier transform using direct references of the array
	// only two arguments, so result is copied back into first
	////////////////////////////////////////////////////////////////////
	void real_abs_dft1( double * input, 
			    const unsigned int & input_size )
	{
		
		double * output = ( double * ) malloc( input_size * sizeof( double ) );

		// instantiate the double arg outside of the loop??
		double arg = 0; 
		double real = 0;
		double imaginary = 0;
		double cosarg = 0; 
		double sinarg = 0; 

		for ( int i = 0; i < input_size; ++i )
		{
			// function to clear arrays, set to zero or memset??  xor??
			output[i] = 0;

			// instantiate the double arg outside of the loop??
			arg = -2.0 * PI * ( double ) i / input_size;
			real = 0;
			imaginary = 0;

			for ( int k = 0; k < input_size; ++k )
			{ 
				cosarg = cos(k * arg);
				sinarg = sin(k * arg);
				real += input[k] * cosarg;
				imaginary += input[k] * sinarg;
			}

			output[i] = pow( ( real*real ) / (double) input_size
			               + ( imaginary*imaginary ) / (double) input_size,
		                       (double) 0.5 );
		}

		double * o = output;
		for ( double * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++o )
		{
			* i = * o;
		}

		free( output );
	}

	////////////////////////////////////////////////////////////////////
	// Power spectral density function = F * F* / 2 PI
	////////////////////////////////////////////////////////////////////
	void pwr_spec_dns1( float * __restrict input, 
			    const unsigned int & input_size )
	{
		
		float * output = ( float * ) malloc( input_size * sizeof( float ) );

		// instantiate the float arg outside of the loop??
		float arg = 0; 
		float real = 0;
		float imaginary = 0;
		float cosarg = 0; 
		float sinarg = 0; 

		for ( int i = 0; i < input_size; ++i )
		{
			// function to clear arrays, set to zero or memset??  xor??
			output[i] = 0;

			// instantiate the float arg outside of the loop??
			arg = -2.0 * PI * ( float ) i / input_size;
			real = 0;
			imaginary = 0;

			for ( int k = 0; k < input_size; ++k )
			{ 
				cosarg = cos(k * arg);
				sinarg = sin(k * arg);
				real += input[k] * cosarg;
				imaginary += input[k] * sinarg;
			}

			output[i] = ( ( ( real * real ) + ( imaginary * imaginary ) ) 
					/ ( ( float ) input_size * 2.0 * PI ) );
		}

		float * o = output;
		for ( float * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++o )
		{
			* i = * o;
		}

		free( output );
	}	

	////////////////////////////////////////////////////////////////////
	// Power spectral density function = F * F* / 2 PI
	////////////////////////////////////////////////////////////////////
	void pwr_spec_dns1( double * input, 
			    const unsigned int & input_size )
	{
		
		double * output = ( double * ) malloc( input_size * sizeof( double ) );

		// instantiate the double arg outside of the loop??
		double arg = 0; 
		double real = 0;
		double imaginary = 0;
		double cosarg = 0; 
		double sinarg = 0; 

		for ( int i = 0; i < input_size; ++i )
		{
			// function to clear arrays, set to zero or memset??  xor??
			output[i] = 0;

			// instantiate the double arg outside of the loop??
			arg = -2.0 * PI * ( double ) i / input_size;
			real = 0;
			imaginary = 0;

			for ( int k = 0; k < input_size; ++k )
			{ 
				cosarg = cos(k * arg);
				sinarg = sin(k * arg);
				real += input[k] * cosarg;
				imaginary += input[k] * sinarg;
			}

			output[i] = ( ( ( real * real ) + ( imaginary * imaginary ) ) 
					/ ( ( double ) input_size * 2.0 * PI ) );
		}

		double * o = output;
		for ( double * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++o )
		{
			* i = * o;
		}

		free( output );
	}	

	////////////////////////////////////////////////////////////////////
	// discrete fourier transform using indirect references of the array
	// ie pointer arithmetic
	// only two arguments, so result is copied back into first
	////////////////////////////////////////////////////////////////////
	void real_abs_dft2( float * __restrict input, 
			    const unsigned int & input_size )
	{
		
		float * output = ( float * ) malloc( input_size * sizeof( float ) );

		int outer_index = 0;
		float arg = 0; 
		float real = 0;
		float imaginary = 0;
		int inner_index = 0;

		float * output_ptr = output;
		for ( const float * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++outer_index,
	 	      ++output_ptr )
		{
			// function to clear arrays, set to zero or memset??  xor??

			// instantiate the float arg outside of the loop??
			arg = -2.0 * PI * ( ( float ) outer_index / input_size );
			real = 0;
			imaginary = 0;
			inner_index = 0;

			for ( const float * k = input; 
			      k != input + input_size; 
			      ++k,
			      ++inner_index )
			{
				real += ( * k ) * ( cos( ( float ) inner_index * arg ) );
				imaginary += ( * k ) * ( sin( ( float ) inner_index * arg ) );
			}

			* output_ptr = pow( ( real*real ) / (float) input_size
			                  + ( imaginary*imaginary ) / (float) input_size,
		                          0.5f );
		}

		float * o = output;
		for ( float * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++o )
		{
			* i = * o;
		}

		free( output );
	}

	////////////////////////////////////////////////////////////////////
	// discrete fourier transform using indirect references of the array
	// ie pointer arithmetic
	// only two arguments, so result is copied back into first
	////////////////////////////////////////////////////////////////////
	void real_abs_dft2( double * input, 
			    const unsigned int & input_size )
	{
		
		double * output = ( double * ) malloc( input_size * sizeof( double ) );

		int outer_index = 0;
		double arg = 0; 
		double real = 0;
		double imaginary = 0;
		int inner_index = 0;

		double * output_ptr = output;
		for ( const double * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++outer_index,
	 	      ++output_ptr )
		{
			// function to clear arrays, set to zero or memset??  xor??

			// instantiate the double arg outside of the loop??
			arg = -2.0 * PI * ( ( double ) outer_index / input_size );
			real = 0;
			imaginary = 0;
			inner_index = 0;

			for ( const double * k = input; 
			      k != input + input_size; 
			      ++k,
			      ++inner_index )
			{
				real += ( * k ) * ( cos( ( double ) inner_index * arg ) );
				imaginary += ( * k ) * ( sin( ( double ) inner_index * arg ) );
			}

			* output_ptr = pow( ( real*real ) / (double) input_size
			                  + ( imaginary*imaginary ) / (double) input_size,
		                          (double) 0.5 );
		}

		double * o = output;
		for ( double * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++o )
		{
			* i = * o;
		}

		free( output );
	}

	////////////////////////////////////////////////////////////////////
	// Power spectral density function = F * F* / 2 PI
	////////////////////////////////////////////////////////////////////
	void pwr_spec_dns2( float * __restrict input, 
			    const unsigned int & input_size )
	{
		
		float * output = ( float * ) malloc( input_size * sizeof( float ) );

		int outer_index = 0;
		float arg = 0; 
		float real = 0;
		float imaginary = 0;
		int inner_index = 0;

		float * output_ptr = output;
		for ( const float * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++outer_index,
	 	      ++output_ptr )
		{
			// function to clear arrays, set to zero or memset??  xor??

			// instantiate the float arg outside of the loop??
			arg = -2.0 * PI * ( ( float ) outer_index / input_size );
			real = 0;
			imaginary = 0;
			inner_index = 0;

			for ( const float * k = input; 
			      k != input + input_size; 
			      ++k,
			      ++inner_index )
			{
				real += ( * k ) * ( cos( ( float ) inner_index * arg ) );
				imaginary += ( * k ) * ( sin( ( float ) inner_index * arg ) );
			}

			* output_ptr = ( ( ( real * real ) + ( imaginary * imaginary ) ) 
					/ ( ( float ) input_size * 2.0 * PI ) );
		}

		float * o = output;
		for ( float * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++o )
		{
			* i = * o;
		}

		free( output );
	}

	////////////////////////////////////////////////////////////////////
	// Power spectral density function = F * F* / 2 PI
	////////////////////////////////////////////////////////////////////
	void pwr_spec_dns2( double * input, 
			    const unsigned int & input_size )
	{
		
		double * output = ( double * ) malloc( input_size * sizeof( double ) );

		int outer_index = 0;
		double arg = 0; 
		double real = 0;
		double imaginary = 0;
		int inner_index = 0;

		double * output_ptr = output;
		for ( const double * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++outer_index,
	 	      ++output_ptr )
		{
			// function to clear arrays, set to zero or memset??  xor??

			// instantiate the double arg outside of the loop??
			arg = -2.0 * PI * ( ( double ) outer_index / input_size );
			real = 0;
			imaginary = 0;
			inner_index = 0;

			for ( const double * k = input; 
			      k != input + input_size; 
			      ++k,
			      ++inner_index )
			{
				real += ( * k ) * ( cos( ( double ) inner_index * arg ) );
				imaginary += ( * k ) * ( sin( ( double ) inner_index * arg ) );
			}

			* output_ptr = ( ( ( real * real ) + ( imaginary * imaginary ) ) 
					/ ( ( double ) input_size * 2.0 * PI ) );
		}

		double * o = output;
		for ( double * i = input; 
		      i != input + input_size; 
		      ++i,
		      ++o )
		{
			* i = * o;
		}

		free( output );
	}

} // Fourier

} // MathLib


