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
#include <fstream>
#include <iterator>

#include <Timing.h>
#include <ActivationFunctions.hpp>

#include "CommandLineOptions.h"

using namespace std;
using namespace MathLib::Activation;

inline double logistic_function( const double & x )
{
	double k = 1.0;
	return  ( ( 2.0 / ( 1.0 + exp( - k * x ) ) ) - 1.0 );
}

inline double logistic_derivative( const double & x )
{
	double k = 1.0;
	return ( ( 2.0 * k * exp( - k * x ) ) / 
		( pow( ( 1.0 + exp( - k * x ) ), 2.0 ) ) );
}

int main( int argc, char ** argv )
{
	options.cmd.parse( argc, argv );

	const unsigned int size_array = 1000;
	double input[ size_array ] = { 0 };
	double output[ size_array ] = { 0 };
	double denominator = 100.0;

	for ( unsigned int i = 0; i < size_array; ++i )
	{
		input[ i ] = ( ( ( ( double ) i ) / denominator ) - 5.0 );
		output[ i ] = 0.0;
	}

	if ( options.Logistic1.isSet() )
	{
START;
		Logistic< double >::Activation( 1.0 )( 1.0 );
STOP;
	}

	if ( options.Logistic2.isSet() )
	{
START;
		Logistic< double >::Derivative( 1.0 )( 1.0 );
STOP;
	}

	if ( options.Logistic3.isSet() )
	{
START;
		transform( input, input + size_array, output, Logistic< double >::Activation( 1.0 ) );
STOP;
	}

	if ( options.Logistic4.isSet() )
	{
START;
		transform( input, input + size_array, output, Logistic< double >::Derivative( 1.0 ) );
STOP;
	}

	if ( options.InverseTangent1.isSet() )
	{
START;
		InverseTangent< double >::Activation( 1.0 )( 1.0 );
STOP;
	}

	if ( options.InverseTangent2.isSet() )
	{
START;
		InverseTangent< double >::Derivative( 1.0 )( 1.0 );
STOP;
	}

	if ( options.InverseTangent3.isSet() )
	{
START;
		transform( input, input + size_array, output, InverseTangent< double >::Activation( 1.0 ) );
STOP;
	}

	if ( options.InverseTangent4.isSet() )
	{
START;
		transform( input, input + size_array, output, InverseTangent< double >::Derivative( 1.0 ) );
STOP;
	}

	if ( options.HyperbolicTangent1.isSet() )
	{
START;
		HyperbolicTangent< double >::Activation( 1.0 )( 1.0 );
STOP;
	}

	if ( options.HyperbolicTangent2.isSet() )
	{
START;
		HyperbolicTangent< double >::Derivative( 1.0 )( 1.0 );
STOP;
	}

	if ( options.HyperbolicTangent3.isSet() )
	{
START;
		transform( input, input + size_array, output, HyperbolicTangent< double >::Activation( 1.0 ) );
STOP;
	}

	if ( options.HyperbolicTangent4.isSet() )
	{
START;
		transform( input, input + size_array, output, HyperbolicTangent< double >::Derivative( 1.0 ) );
STOP;
	}

	if ( options.Algebraic1.isSet() )
	{
START;
		Algebraic< double >::Activation( 1.0 )( 1.0 );
STOP;
	}

	if ( options.Algebraic2.isSet() )
	{
START;
		Algebraic< double >::Derivative( 1.0 )( 1.0 );
STOP;
	}

	if ( options.Algebraic3.isSet() )
	{
START;
		transform( input, input + size_array, output, Algebraic< double >::Activation( 1.0 ) );
STOP;
	}

	if ( options.Algebraic4.isSet() )
	{
START;
		transform( input, input + size_array, output, Algebraic< double >::Derivative( 1.0 ) );
STOP;
	}

	if ( options.Erf1.isSet() )
	{
START;
		Erf< double >::Activation( 1.0 )( 1.0 );
STOP;
	}

	if ( options.Erf2.isSet() )
	{
START;
		Erf< double >::Derivative( 1.0 )( 1.0 );
STOP;
	}

	if ( options.Erf3.isSet() )
	{
START;
		transform( input, input + size_array, output, Erf< double >::Activation( 1.0 ) );
STOP;
	}

	if ( options.Erf4.isSet() )
	{
START;
		transform( input, input + size_array, output, Erf< double >::Derivative( 1.0 ) );
STOP;
	}

	if ( options.Gompertz1.isSet() )
	{
START;
		Gompertz< double >::Activation( 1.0 )( 1.0 );
STOP;
	}

	if ( options.Gompertz2.isSet() )
	{
START;
		Gompertz< double >::Derivative( 1.0 )( 1.0 );
STOP;
	}

	if ( options.Gompertz3.isSet() )
	{
START;
		transform( input, input + size_array, output, Gompertz< double >::Activation( 1.0 ) );
STOP;
	}

	if ( options.Gompertz4.isSet() )
	{
START;
		transform( input, input + size_array, output, Gompertz< double >::Derivative( 1.0 ) );
STOP;
	}

	if ( options.Control1.isSet() )
	{
START;
		logistic_function( 1.0 );
STOP;
	}

	if ( options.Control2.isSet() )
	{
START;
		logistic_derivative( 1.0 );
STOP;
	}

	if ( options.Control3.isSet() )
	{
START;
		transform( input, input + size_array, output, logistic_function );
STOP;
	}

	if ( options.Control4.isSet() )
	{
START;
		transform( input, input + size_array, output, logistic_derivative );
STOP;
	}

	if ( options.OutputFilename.isSet() )
	{
		ofstream output_file( options.OutputFilename.getValue().c_str(), ios::out | ios::app );
		for ( unsigned int i = 0; i < size_array; ++i ) 
			output_file << input[ i ] << "\t" << output[ i ] << endl;
		output_file << endl; output_file.close();
	}

	return 0;
}
