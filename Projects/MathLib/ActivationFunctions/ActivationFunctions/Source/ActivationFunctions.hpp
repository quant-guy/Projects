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
/////////////////////////////////////////////////////////////////////////////////////
// Several classes representing activation functions, specifically sigmoid activation
// functions which map to the interal s |-> (-1, 1 )
//
// functions included are:
// 1. Logistic
// 2. Inverse Tangent
// 3. Hyperbolic Tangent
// 4. Algebraic
// 5. Erf
// 6. Gompertz
/////////////////////////////////////////////////////////////////////////////////////

#ifndef  ACTIVATION_FUNCTIONS_H
#define  ACTIVATION_FUNCTIONS_H

#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>

#ifndef PI
#define PI M_PI 
#endif  // PI
#define PI_CONST  1.1283791670955126L	// 2 / sqrt( Pi ) to 16 decimal places
#define PI_CONST2 0.6366197723675813L   // 2 / PI to 16 decimal places
#define LOG_2     0.6931471805599453L   // Ln( 2 ) to 16 decimal places
#define ERF_LIM   10			// numbe of iterations of series expansion of erf

namespace MathLib
{

namespace Activation
{

/////////////////////////////////////////////////////////////////////////////////////
// Parent class for activation function and it's derivative
/////////////////////////////////////////////////////////////////////////////////////
template< class T >
class ActivationTemplate
{
	public :

	typedef T value_type;

	ActivationTemplate( const value_type & p ) : p_( p ) {}

	ActivationTemplate( void ) : p_( 0.0 ) {}

	virtual ~ActivationTemplate( void ) {}

	virtual inline value_type operator () ( const value_type & ) = 0;

	protected : 

	value_type p_;
};

/////////////////////////////////////////////////////////////////////////////////////
// Parent class containing activation function and its derivative 
/////////////////////////////////////////////////////////////////////////////////////
template< class T >
class ActivationFunction
{
	public :
		typedef T value_type;

		ActivationFunction( void ) {}

		virtual ~ActivationFunction( void ) {}

		class Activation : protected ActivationTemplate< value_type > {};

		class Derivative : protected ActivationTemplate< value_type > {};
};

/////////////////////////////////////////////////////////////////////////////////////
// 1. Logistic
// S  = 2 / ( 1 + exp( -k x ) - 1
// S' = 2 k exp( -k x ) / ( 1 + exp( -k x ) ) ^ 2
/////////////////////////////////////////////////////////////////////////////////////
template< class T >
class Logistic : protected ActivationFunction< T >
{
	public :
		typedef T value_type;

		Logistic( void ) : ActivationFunction< value_type >() {}

		virtual ~Logistic( void ) {}

		class Activation : protected ActivationTemplate< T >
		{
			public :

			Activation( void ) : ActivationTemplate< value_type >::Activation() {}

			Activation( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Activation( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				return ( value_type ) ( ( 2.0 / ( 1.0 + exp( - ( this->p_ ) * x ) ) ) - 1.0 );
			}
		};

		class Derivative : protected ActivationTemplate< value_type>
		{
			public :

			Derivative( void ) : ActivationTemplate< value_type >::Activation() {}

			Derivative( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Derivative( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				return ( value_type ) ( 2.0 * this->p_ * ( exp( -( this->p_  ) * x ) / 
					pow( ( 1.0 + exp( -( this->p_ ) * x ) ), 2.0 ) ) );
			}	
		};
};

/////////////////////////////////////////////////////////////////////////////////////
// 2. InverseTangent 
// S  = 2 * inverse_tan( x ) - 1
// S' = 2 * k / ( 1 + ( k x ) ^ 2 )
/////////////////////////////////////////////////////////////////////////////////////
template< class T >
class InverseTangent : protected ActivationFunction< T >
{
	public :
		typedef T value_type;

		InverseTangent( void ) : ActivationFunction< value_type >() {}

		virtual ~InverseTangent( void ) {}

		class Activation : protected ActivationTemplate< T >
		{
			public :

			Activation( void ) : ActivationTemplate< value_type >::Activation() {}

			Activation( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Activation( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				return ( value_type ) ( PI_CONST2 * atan( this->p_ * x ) );
			}
		};

		class Derivative : protected ActivationTemplate< value_type>
		{
			public :

			Derivative( void ) : ActivationTemplate< value_type >::Activation() {}

			Derivative( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Derivative( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				return ( value_type ) ( ( PI_CONST2 * this->p_ ) 
					/ ( 1 + ( this->p_ * x ) * ( this->p_ * x ) ) );
			}	
		};
};

/////////////////////////////////////////////////////////////////////////////////////
// 3. Hyperbolic 
// S  = 2 tanh( k x ) - 1
// S' = 2 * k / cosh^2( k x )
/////////////////////////////////////////////////////////////////////////////////////
template< class T >
class HyperbolicTangent : protected ActivationFunction< T >
{
	public :
		typedef T value_type;

		HyperbolicTangent( void ) : ActivationFunction< value_type >() {}

		virtual ~HyperbolicTangent( void ) {}

		class Activation: protected ActivationTemplate< T >
		{
			public :

			Activation( void ) : ActivationTemplate< value_type >::Activation() {}

			Activation( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Activation( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				return ( value_type ) ( tanh( this->p_ * x ) );
			}
		};

		class Derivative : protected ActivationTemplate< value_type>
		{
			public :

			Derivative( void ) : ActivationTemplate< value_type >::Activation() {}

			Derivative( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Derivative( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				return ( value_type ) ( this->p_ / 
					( cosh( this->p_ * x ) * cosh( this->p_ * x ) ) );
			}	
		};
};

/////////////////////////////////////////////////////////////////////////////////////
// 4. Algebraic 
// S  = k * x / ( sqrt( 1 + ( k x ) ^ 2 ) )
// S' = k / ( 1 + ( k x ) ^ 2 ) ^ 3 / 2
/////////////////////////////////////////////////////////////////////////////////////
template< class T >
class Algebraic : protected ActivationFunction< T >
{
	public :
		typedef T value_type;

		Algebraic( void ) : ActivationFunction< value_type >() {}

		virtual ~Algebraic( void ) {}

		class Activation : protected ActivationTemplate< T >
		{
			public :

			Activation( void ) : ActivationTemplate< value_type >::Activation() {}

			Activation( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Activation( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				return ( value_type ) ( ( ( this->p_ * x ) / 
					sqrt( 1 + ( this->p_ * x ) * ( this->p_ * x ) ) ) );
			}
		};

		class Derivative : protected ActivationTemplate< value_type>
		{
			public :

			Derivative( void ) : ActivationTemplate< value_type >::Activation() {}

			Derivative( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Derivative( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				return ( value_type ) this->p_ / 
					pow( ( 1 + ( this->p_ * x ) * ( this->p_ * x ) ), ( 1.5 ) );
			}	
		};
};

/////////////////////////////////////////////////////////////////////////////////////
// 5. Erf
// :)
// S  = ( 2 / sqrt( PI ) ) * sum( 0 , infinity ) ( ( -1 ) ^ n * ( k * x ) ^ ( 2 * n + 1 ) 
//		/ n factorial * ( 2 * n * 1 ) )
// S' = ( 2 k / sqrt( PI ) ) * exp ( -( ( k x )* ( k x ) )  ) 
/////////////////////////////////////////////////////////////////////////////////////
template< class T >
class Erf : protected ActivationFunction< T >
{
	public :
		typedef T value_type;

		Erf( void ) : ActivationFunction< value_type >() {}

		virtual ~Erf( void ) {}

		class Activation : protected ActivationTemplate< T >
		{
			public :

			Activation( void ) : ActivationTemplate< value_type >::Activation() {}

			Activation( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Activation( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				value_type x0 = this->p_ * x;
				value_type x1 = this->p_ * x;
				value_type x2 = x1;
				for ( register unsigned int i = 1; i < ERF_LIM; ++i )
				{
					x1 *= - x0 * x0 / ( ( value_type ) i ); 
					x2 += ( x1 / ( ( value_type ) ( 2 * i + 1 ) ) );
				}
				return ( value_type ) ( PI_CONST * x2 );
			}
		};

		class Derivative : protected ActivationTemplate< value_type>
		{
			public :

			Derivative( void ) : ActivationTemplate< value_type >::Activation() {}

			Derivative( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Derivative( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				return ( value_type ) ( PI_CONST * this->p_ ) * 
					exp ( - ( ( this->p_ * x ) * ( this->p_ * x ) ) );
			}	
		};
};

/////////////////////////////////////////////////////////////////////////////////////
// 6. Gompertz 
// S  = 2.0 * exp( - 1.0 * exp( -k x ) ) - 1.0
// S' = 2.0 * k * ( exp( - 1.0 * exp( -k x ) ) + k x )
/////////////////////////////////////////////////////////////////////////////////////
template< class T >
class Gompertz : protected ActivationFunction< T >
{
	public :
		typedef T value_type;

		Gompertz( void ) : ActivationFunction< value_type >() {}

		virtual ~Gompertz( void ) {}

		class Activation : protected ActivationTemplate< T >
		{
			public :

			Activation( void ) : ActivationTemplate< value_type >::Activation() {}

			Activation( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Activation( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				return ( value_type ) ( 2.0 * exp( - LOG_2 * exp( - this->p_ * x ) ) - 1.0 );
			}
		};

		class Derivative : protected ActivationTemplate< value_type>
		{
			public :

			Derivative( void ) : ActivationTemplate< value_type >::Activation() {}

			Derivative( const value_type & p ) : ActivationTemplate< value_type >( p ) {}

			~Derivative( void ) {}

			inline value_type operator () ( const value_type & x )
			{
				return ( value_type ) ( 2.0 * LOG_2 * this->p_ * exp( - ( LOG_2 * exp( -this->p_ * x ) + this->p_ * x ) ) );
			}	
		};
};

} // Activation

} // MathLib

#endif   // ACTIVATION_FUNCTIONS_H
