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
#include <vector>
#include <string>

#include <CommandLineParser.hpp>

using namespace Utility::CommandLineParser;
using namespace std;

struct CommandLineOptions
{
	// instantiate parser
	CmdLine cmd;

	// test parser 
	SwitchArg	Output;
	SwitchArg	CountFields1;
	SwitchArg	CountFields2;
	SwitchArg	CountLines;
	SwitchArg	Parser1;
	SwitchArg	Parser2;
	SwitchArg	Echo;
	SwitchArg	NormalizeR1;
	SwitchArg	NormalizeR2;
	SwitchArg	NormalizeC1;
	SwitchArg	NormalizeC2;
	SwitchArg	Increasing0;
	SwitchArg	Increasing1;
	SwitchArg	Mean0;
	SwitchArg	Mean1;
	SwitchArg	StdDev0;
	SwitchArg	StdDev1;
	SwitchArg	Fourier0;
	SwitchArg	Fourier1;
	SwitchArg	Bias0;
	SwitchArg	Bias1;

	// test iostream
	SwitchArg	CoutArray1;
	SwitchArg	CoutArray2;

	SwitchArg	Verbose;
	
	ValueArg<string> Filename;
	ValueArg<string> Tokens;

	CommandLineOptions( void ) :
		cmd          ( "TestUtility", ' ', "0.0" ),
		Output       ( "", "Output",       "Output",           cmd, false ),
		CountFields1 ( "", "CountFields1", "CountFields1",     cmd, false ),
		CountFields2 ( "", "CountFields2", "CountFields2",     cmd, false ),
		CountLines   ( "", "CountLines",   "CountLines",       cmd, false ),
		Parser1      ( "", "Parser1",      "Parser1",          cmd, false ),
		Parser2      ( "", "Parser2",      "Parser2",          cmd, false ),
		Echo         ( "", "Echo",         "Echo",             cmd, false ),
		CoutArray1   ( "", "CoutArray1",   "CoutArray1",       cmd, false ),
		CoutArray2   ( "", "CoutArray2",   "CoutArray2",       cmd, false ),
		NormalizeR1  ( "", "NormalizeR1",  "Test NormalizeR1", cmd, false ),
		NormalizeR2  ( "", "NormalizeR2",  "Test NormalizeR2", cmd, false ),
		NormalizeC1  ( "", "NormalizeC1",  "Test NormalizeC1", cmd, false ),
		NormalizeC2  ( "", "NormalizeC2",  "Test NormalizeC2", cmd, false ),
		Increasing0  ( "", "Increasing0",  "Test Increasing0", cmd, false ),
		Increasing1  ( "", "Increasing1",  "Test Increasing1", cmd, false ),
		Mean0        ( "", "Mean0",        "Test Mean0",       cmd, false ),
		Mean1        ( "", "Mean1",        "Test Mean1",       cmd, false ),
		StdDev0      ( "", "StdDev0",      "Test StdDev0",     cmd, false ),
		StdDev1      ( "", "StdDev1",      "Test StdDev1",     cmd, false ),
		Fourier0     ( "", "Fourier0",     "Test Fourier0",    cmd, false ),
		Fourier1     ( "", "Fourier1",     "Test Fourier1",    cmd, false ),
		Bias0        ( "", "Bias0",        "Test Bias",        cmd, false ),
		Bias1        ( "", "Bias1",        "Test Node Bias",   cmd, false ),
		Verbose      ( "", "Verbose",      "Verbose output",   cmd, false ),
		Filename     ( "", "InputFile",    "Input file for training/ trading", false, "", "string", cmd ),
		Tokens       ( "", "Tokens",       "Delimeters used in parsing",       false, "", "string", cmd ) {}
};

CommandLineOptions options;
