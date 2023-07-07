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
	SwitchArg		GP_Constructor1;
	SwitchArg		GP_Constructor2;
	SwitchArg		GP_GetFirst;
	SwitchArg		GP_GetSecond;
	SwitchArg		GP_SetFirst;
	SwitchArg		GP_SetSecond;
	SwitchArg		GP_Swap;          

	SwitchArg		GG_Constructor1;
	SwitchArg		GG_Constructor2;
	SwitchArg		GG_Constructor3;
	SwitchArg		GG_PutGenetic;
	SwitchArg		GG_Mutate1;
	SwitchArg		GG_Mutate2;
	SwitchArg		GG_Ostream;
	SwitchArg		GG_OutputMutate;

	SwitchArg		GPA_Constructor1;
	SwitchArg		GPA_Constructor2;
	SwitchArg		GPA_Constructor3;
	SwitchArg		GPA_Constructor4;
	SwitchArg		GPA_Constructor5;
	SwitchArg		GPA_Assignment;
	SwitchArg		GPA_Perturb;
	SwitchArg		GPA_Copy;
	SwitchArg		GPA_Plus;

	SwitchArg		Verbose;
	ValueArg<string>         GeneticFilename;

	CommandLineOptions( void ) :
		cmd	         ( "TradingEngine", ' ', "0.1" ),	
		GP_Constructor1  ( "", "GP_Constructor1", "Test GP_Constructor1", cmd, false ),
		GP_Constructor2  ( "", "GP_Constructor2", "Test GP_Constructor2", cmd, false ),
		GP_GetFirst      ( "", "GP_GetFirst",     "Test GP_GetFirst",     cmd, false ),
		GP_GetSecond     ( "", "GP_GetSecond",    "Test GP_GetSecond",    cmd, false ),
		GP_SetFirst      ( "", "GP_SetFirst",     "Test GP_SetFirst",     cmd, false ),
		GP_SetSecond     ( "", "GP_SetSecond",    "Test GP_SetSecond",    cmd, false ),
		GP_Swap          ( "", "GP_Swap",         "Test GP_Swap",         cmd, false ),
		GG_Constructor1  ( "", "GG_Constructor1", "Test GG_Constructor1", cmd, false ),
		GG_Constructor2  ( "", "GG_Constructor2", "Test GG_Constructor2", cmd, false ),
		GG_Constructor3  ( "", "GG_Constructor3", "Test GG_Constructor3", cmd, false ),
		GG_PutGenetic    ( "", "GG_PutGenetic",   "Test GG_PutGenetic",   cmd, false ),
		GG_Mutate1       ( "", "GG_Mutate1",      "Test GG_Mutate1",      cmd, false ),
		GG_Mutate2       ( "", "GG_Mutate2",      "Test GG_Mutate2",      cmd, false ),
		GG_Ostream       ( "", "GG_Ostream",      "Test GG_Ostream",      cmd, false ),
		GG_OutputMutate  ( "", "GG_OutputMutate", "Test GG_OutputMutate", cmd, false ),
		GPA_Constructor1 ( "", "GPA_Constructor1","Test GPA_Constructor1",cmd, false ),
		GPA_Constructor2 ( "", "GPA_Constructor2","Test GPA_Constructor2",cmd, false ),
		GPA_Constructor3 ( "", "GPA_Constructor3","Test GPA_Constructor3",cmd, false ),
		GPA_Constructor4 ( "", "GPA_Constructor4","Test GPA_Constructor4",cmd, false ),
		GPA_Constructor5 ( "", "GPA_Constructor5","Test GPA_Constructor5",cmd, false ),
		GPA_Assignment   ( "", "GPA_Assignment",  "Test GPA_Assignment",  cmd, false ),
		GPA_Perturb      ( "", "GPA_Perturb",     "Test GPA_Perturb",     cmd, false ),
		GPA_Copy         ( "", "GPA_Copy",        "Test GPA_Copy",        cmd, false ),
		GPA_Plus         ( "", "GPA_Plus",        "Test GPA_Plus",        cmd, false ),
		Verbose          ( "", "Verbose",         "Toggle verbosity",     cmd, false ),
		GeneticFilename  ( "", "GeneticFilename", "Genetic input filename", false, "string", "string", cmd ) {}
};

CommandLineOptions options;
