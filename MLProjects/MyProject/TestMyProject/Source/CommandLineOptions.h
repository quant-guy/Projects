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
#include <CommandLineParser.hpp>

using namespace Utility::CommandLineParser;

using namespace std;

struct CommandLineOptions
{
	// instantiate parser
	CmdLine cmd;

	SwitchArg		Constructor1;
	SwitchArg		Constructor2;
	SwitchArg		Constructor3;
	SwitchArg		Sanity;
	SwitchArg		Test1;
	SwitchArg		Verbose;
	ValueArg<string>        InputFilename;

	CommandLineOptions( void ) :
		cmd	       ( "test_myproject", ' ', "0.0" ),	
		Constructor1   ( "", "Constructor1", "Test Constructor1",          cmd ),
		Constructor2   ( "", "Constructor2", "Test Constructor2",          cmd ),
		Constructor3   ( "", "Constructor3", "Test Constructor3",          cmd ),
		Sanity         ( "", "Sanity",       "Test Sanity",                cmd ),
		Test1          ( "", "Test1",        "Test Test1",                 cmd ),
		Verbose        ( "", "Verbose",      "Verbose output",             cmd ),
		InputFilename  ( "", "InputFilename","Input file",      false, "string", "string", cmd ) {}
};

CommandLineOptions options;
