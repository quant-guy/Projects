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
#include <CommandLineParser.hpp>

using namespace Utility::CommandLineParser;
using namespace std;

struct CommandLineOptions
{
	// instantiate parser
	CmdLine cmd;

	// operating modes
	SwitchArg		Logistic1;    
	SwitchArg		Logistic2;    
	SwitchArg		Logistic3;    
	SwitchArg		Logistic4;    

	SwitchArg		InverseTangent1;    
	SwitchArg		InverseTangent2;    
	SwitchArg		InverseTangent3;    
	SwitchArg		InverseTangent4;    

	SwitchArg		HyperbolicTangent1;    
	SwitchArg		HyperbolicTangent2;    
	SwitchArg		HyperbolicTangent3;    
	SwitchArg		HyperbolicTangent4;    

	SwitchArg		Algebraic1;    
	SwitchArg		Algebraic2;    
	SwitchArg		Algebraic3;    
	SwitchArg		Algebraic4;    

	SwitchArg		Erf1;    
	SwitchArg		Erf2;    
	SwitchArg		Erf3;    
	SwitchArg		Erf4;    

	SwitchArg		Gompertz1;    
	SwitchArg		Gompertz2;    
	SwitchArg		Gompertz3;    
	SwitchArg		Gompertz4;    

	SwitchArg		Control1;    
	SwitchArg		Control2;    
	SwitchArg		Control3;    
	SwitchArg		Control4;    

	ValueArg<string>		OutputFilename;    

	CommandLineOptions( void ) :
		cmd	           ( "TestActivationFunctions", ' ', "0.2" ),	
		Logistic1          ( "", "Logistic1",          "Test Activation",       cmd, false ),
		Logistic2          ( "", "Logistic2",          "Test Derivative",       cmd, false ),
		Logistic3          ( "", "Logistic3",          "1000 Activaiton Values",cmd, false ),
		Logistic4          ( "", "Logistic4",          "1000 Derivative Values",cmd, false ),
		InverseTangent1    ( "", "InverseTangent1",    "Test Activation",       cmd, false ),
		InverseTangent2    ( "", "InverseTangent2",    "Test Derivative",       cmd, false ),
		InverseTangent3    ( "", "InverseTangent3",    "1000 Activaiton Values",cmd, false ),
		InverseTangent4    ( "", "InverseTangent4",    "1000 Derivative Values",cmd, false ),
		HyperbolicTangent1 ( "", "HyperbolicTangent1", "Test Activation",       cmd, false ),
		HyperbolicTangent2 ( "", "HyperbolicTangent2", "Test Derivative",       cmd, false ),
		HyperbolicTangent3 ( "", "HyperbolicTangent3", "1000 Activaiton Values",cmd, false ),
		HyperbolicTangent4 ( "", "HyperbolicTangent4", "1000 Derivative Values",cmd, false ),
		Algebraic1         ( "", "Algebraic1",         "Test Activation",       cmd, false ),
		Algebraic2         ( "", "Algebraic2",         "Test Derivative",       cmd, false ),
		Algebraic3         ( "", "Algebraic3",         "1000 Activaiton Values",cmd, false ),
		Algebraic4         ( "", "Algebraic4",         "1000 Derivative Values",cmd, false ),
		Erf1               ( "", "Erf1",               "Test Activation",       cmd, false ),
		Erf2               ( "", "Erf2",               "Test Derivative",       cmd, false ),
		Erf3               ( "", "Erf3",               "1000 Activaiton Values",cmd, false ),
		Erf4               ( "", "Erf4",               "1000 Derivative Values",cmd, false ),
		Gompertz1          ( "", "Gompertz1",          "Test Activation",       cmd, false ),
		Gompertz2          ( "", "Gompertz2",          "Test Derivative",       cmd, false ),
		Gompertz3          ( "", "Gompertz3",          "1000 Activaiton Values",cmd, false ),
		Gompertz4          ( "", "Gompertz4",          "1000 Derivative Values",cmd, false ),
		Control1           ( "", "Control1",           "Test Activation",       cmd, false ),
		Control2           ( "", "Control2",           "Test Derivative",       cmd, false ),
		Control3           ( "", "Control3",           "1000 Activaiton Values",cmd, false ),
		Control4           ( "", "Control4",           "1000 Derivative Values",cmd, false ),
		OutputFilename     ( "", "OutputFilename",     "OutputFilename", false, "string", "string", cmd ) {}
};                                                                                                                   
                                                                                                                     
CommandLineOptions options;                                                                                          
