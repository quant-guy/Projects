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

	// operating modes
	SwitchArg MulConstMatrix;    
	SwitchArg Ostream;    
	SwitchArg Transpose;    
	SwitchArg Sigmoid;    
	SwitchArg DSigmoid;    
	SwitchArg Err;    
	SwitchArg Comp;    
	SwitchArg Kro;    
	SwitchArg Dot;    
	SwitchArg Sum;    
	SwitchArg Constructor1;    
	SwitchArg Constructor2;    
	SwitchArg Constructor3;    
	SwitchArg Fill1;    
	SwitchArg Fill2;    
	SwitchArg Fill3;    
	SwitchArg PutMatrix;    
	SwitchArg GetMatrix;    
	SwitchArg GetRows;    
	SwitchArg GetColumns;    
	SwitchArg Size;    
	SwitchArg At;    
	SwitchArg Addition;
	SwitchArg Subtraction;
	SwitchArg Multiplication;    
	SwitchArg Assignment;    
	SwitchArg AdditionAssignment;    
	SwitchArg SubtractionAssignment;    
	SwitchArg Verbose;    


	CommandLineOptions( void ) :
		cmd	             ( "test_matrix", ' ', "0.2" ),	
		MulConstMatrix       ( "", "MulConstMatrix",        "Test MulConstMatrix",         cmd, false ),  
		Ostream              ( "", "Ostream",               "Test Ostream",                cmd, false ),
		Transpose            ( "", "Transpose",             "Test Transpose",              cmd, false ),
		Sigmoid              ( "", "Sigmoid",               "Test Sigmoid",                cmd, false ),
		DSigmoid             ( "", "DSigmoid",              "Test DSigmoid",               cmd, false ),
		Err                  ( "", "Err",                   "Test Err",                    cmd, false ),
		Comp                 ( "", "Comp",                  "Test Comp",                   cmd, false ),
		Kro                  ( "", "Kro",                   "Test Kro",                    cmd, false ),
		Dot                  ( "", "Dot",                   "Test Dot",                    cmd, false ),
		Sum                  ( "", "Sum",                   "Test Sum",                    cmd, false ),
		Constructor1         ( "", "Constructor1",          "Test Constructor1",           cmd, false ),
		Constructor2         ( "", "Constructor2",          "Test Constructor2",           cmd, false ),
		Constructor3         ( "", "Constructor3",          "Test Constructor3",           cmd, false ),
		Fill1                ( "", "Fill1",                 "Test Fill1",                  cmd, false ),
		Fill2                ( "", "Fill2",                 "Test Fill2",                  cmd, false ),
		Fill3                ( "", "Fill3",                 "Test Fill3",                  cmd, false ),
		PutMatrix            ( "", "PutMatrix",             "Test PutMatrix",              cmd, false ),
		GetMatrix            ( "", "GetMatrix",             "Test GetMatrix",              cmd, false ),
		GetRows              ( "", "GetRows",               "Test GetRows",                cmd, false ),
		GetColumns           ( "", "GetColumns",            "Test GetColumns",             cmd, false ),
		Size                 ( "", "Size",                  "Test Size",                   cmd, false ),
		At                   ( "", "At",                    "Test At",                     cmd, false ),
		Addition             ( "", "Addition",              "Test Addition",               cmd, false ),
		Subtraction          ( "", "Subtraction",           "Test Subtraction",            cmd, false ),
		Multiplication       ( "", "Multiplication",        "Test Multiplication",         cmd, false ),
		Assignment           ( "", "Assignment",            "Test Assignment",             cmd, false ),
		AdditionAssignment   ( "", "SubtractionAssignment", "Test SubtractionAssignment",  cmd, false ),
		SubtractionAssignment( "", "AdditionAssignment",    "Test AdditionAssignment",     cmd, false ),
		Verbose              ( "", "Verbose",               "Verbose Output",              cmd, false )
		{}                                                                                                  
};                                                                                                                   
                                                                                                                     
CommandLineOptions options;                                                                                          
