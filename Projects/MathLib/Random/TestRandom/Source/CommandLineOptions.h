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

	// testing modes
	SwitchArg		RandomConstructor1;
	SwitchArg		RandomConstructor2;
	SwitchArg		RandomConstructor3;
	SwitchArg		RandomConstructor4;
	SwitchArg		TestSetSeed;
	SwitchArg		TestGetSeed;
	SwitchArg		TestGenerate1;
	SwitchArg		TestGenerate2;
	SwitchArg		TestGenerate3;
	SwitchArg		TestGenerate4;
	SwitchArg		Generate;
	ValueArg<unsigned int>  Values;
	ValueArg<unsigned int>  Seed;

	SwitchArg		Verbose;
	ValueArg<string>        OutputFilename;

	CommandLineOptions( void ) :
		cmd	           ( "test_random", ' ', "0.0" ),	
		RandomConstructor1 ( "", "RandomConstructor1", "Test RandomConstructor1", cmd, false ),
		RandomConstructor2 ( "", "RandomConstructor2", "Test RandomConstructor2", cmd, false ),
		RandomConstructor3 ( "", "RandomConstructor3", "Test RandomConstructor3", cmd, false ),
		RandomConstructor4 ( "", "RandomConstructor4", "Test RandomConstructor4", cmd, false ),
		TestSetSeed        ( "", "TestSetSeed",        "Test TestSetSeed",        cmd, false ),
		TestGetSeed        ( "", "TestGetSeed",        "Test TestGetSeed",        cmd, false ),
		TestGenerate1      ( "", "TestGenerate1",      "Test TestGenerate1",      cmd, false ),
		TestGenerate2      ( "", "TestGenerate2",      "Test TestGenerate2",      cmd, false ),
		TestGenerate3      ( "", "TestGenerate3",      "Test TestGenerate3",      cmd, false ),
		TestGenerate4      ( "", "TestGenerate4",      "Test TestGenerate4",      cmd, false ),
		Generate           ( "", "Generate",           "Test Generate",           cmd, false ),
		Verbose            ( "", "Verbose",            "Toggle verbosity",        cmd, false ),
		Values             ( "", "Values",             "Number Values", false, 1000, "u_int32", cmd ),
		Seed               ( "", "Seed",               "Seed",          false, 1000, "u_int32", cmd ),
		OutputFilename     ( "", "OutputFilename",     "Output filename", false, "string", "string", cmd ) {}
};

CommandLineOptions options;
