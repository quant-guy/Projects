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
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>

#include <Iostream2.h>
#include <Preprocessor.hpp>
#include <Timing.h>
#include "CommandLineOptions.h"

int main( int argc, char ** argv )
{
	options.cmd.parse( argc, argv );

	if ( ! options.Filename.isSet() )
	{
		cerr << "Error: please enter input filename" << endl;
		exit( 1 );
	}

	// run tests
	if ( options.Output.isSet() )
	{
		DEFAULT_GET_DATA( options.Filename.getValue(), options.Tokens.getValue().c_str() );
START;
			DEFAULT_OUTPUT_MACRO;
STOP;
	}

	if ( options.CountFields1.isSet() )
	{
		DEFAULT_GET_DATA( options.Filename.getValue(), options.Tokens.getValue().c_str() );
START;
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.CountFields2.isSet() )
	{
		DEFAULT_GET_DATA( options.Filename.getValue(), options.Tokens.getValue().c_str() );
START;
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.CountLines.isSet() )
	{
		DEFAULT_GET_DATA( options.Filename.getValue(), options.Tokens.getValue().c_str() );
START;
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.Parser1.isSet() )
	{
		DEFAULT_GET_DATA( options.Filename.getValue(), options.Tokens.getValue().c_str() );
START;
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.Parser2.isSet() )
	{
		DEFAULT_GET_DATA( options.Filename.getValue(), options.Tokens.getValue().c_str() );
START;
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.Echo.isSet() )
	{
		DEFAULT_GET_DATA( options.Filename.getValue(), options.Tokens.getValue().c_str() );
START;
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.CoutArray1.isSet() )
	{
		DEFAULT_GET_DATA( options.Filename.getValue(), options.Tokens.getValue().c_str() );
START;
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.CoutArray2.isSet() )
	{
		DEFAULT_GET_DATA( options.Filename.getValue(), options.Tokens.getValue().c_str() );
START;
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.NormalizeR1.isSet() )
	{
START;
		DEFAULT_NORMALIZE_BY_ROW_0( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.NormalizeR2.isSet() )
	{
START;
		DEFAULT_NORMALIZE_BY_ROW_1( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.NormalizeC1.isSet() )
	{
START;
		DEFAULT_NORMALIZE_BY_COL_0( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.NormalizeC2.isSet() )
	{
START;
		DEFAULT_NORMALIZE_BY_COL_1( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.Increasing0.isSet() )
	{
START;
		DEFAULT_INCREASING_PREPROCESSOR_0( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.Increasing1.isSet() )
	{
START;
		DEFAULT_INCREASING_PREPROCESSOR_1( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.Mean0.isSet() )
	{
START;
		DEFAULT_MEAN_PREPROCESSOR_0( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.Mean1.isSet() )
	{
START;
		DEFAULT_MEAN_PREPROCESSOR_1( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.StdDev0.isSet() )
	{
START;
		DEFAULT_STD_DEV_PREPROCESSOR_0( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.StdDev1.isSet() )
	{
START;
		DEFAULT_STD_DEV_PREPROCESSOR_1( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.Fourier0.isSet() )
	{
START;
		DEFAULT_FOURIER_PREPROCESSOR_0( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.Fourier1.isSet() )
	{
START;
		DEFAULT_FOURIER_PREPROCESSOR_1( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.Bias0.isSet() )
	{
START;
		DEFAULT_BIAS( options.Filename.getValue(), options.Tokens.getValue().c_str() );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}

	if ( options.Bias1.isSet() )
	{
		unsigned int default_node_size = 5;
START;
		DEFAULT_NODE_BIAS( options.Filename.getValue(), options.Tokens.getValue().c_str(), default_node_size );
STOP;
		if ( options.Verbose.isSet() )
			DEFAULT_OUTPUT_MACRO;
	}


	return 0;
}
