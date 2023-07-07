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

	//////////////////////////////////////////////////////////////////////////
	// Testing modes: neural unit.
	//////////////////////////////////////////////////////////////////////////
	SwitchArg		N32_Ostream;
	SwitchArg		N32_CheckDim;
	SwitchArg		N32_Constructor1;
	SwitchArg		N32_Constructor2;
	SwitchArg		N32_Constructor3;
	SwitchArg		N32_GetRows;
	SwitchArg		N32_GetColumns;
	SwitchArg		N32_SetNext;
	SwitchArg		N32_SetPrevious;
	SwitchArg		N32_SetLearningRate;
	SwitchArg		N32_PutNeural;
	SwitchArg		N32_GetNeural;
	SwitchArg		N32_Propagate1;
	SwitchArg		N32_Propagate2;
	SwitchArg		N32_BackPropagate1;
	SwitchArg		N32_BackPropagate2;


	//////////////////////////////////////////////////////////////////////////
	// Testing modes: neural macrostructure.  This structure is composed of
	// neural units (above).
	//////////////////////////////////////////////////////////////////////////
	SwitchArg		NMS_Ostream;
	SwitchArg		NMS_Constructor1;
	SwitchArg		NMS_Constructor2;
	SwitchArg		NMS_PutNeural;
	SwitchArg		NMS_GetNeural;
	SwitchArg		NMS_SetLearningRate1;
	SwitchArg		NMS_SetLearningRate2;
	SwitchArg		NMS_Error;
	SwitchArg		NMS_Propagate;
	SwitchArg		NMS_BackPropagate;

	//////////////////////////////////////////////////////////////////////////
	// Testing modes: test the ability of the system to learn and assimilate
	// information.  Using both NeuralUnits and NeuralMacroStructures 
	//////////////////////////////////////////////////////////////////////////
	SwitchArg		N32_Learning;
	SwitchArg		N32_Learning2;
	SwitchArg		NMS_Learning;
	SwitchArg		NMS_Learning2;
	SwitchArg		NMS_Learning3;
	SwitchArg		NMS_Learning4;
	SwitchArg		NMS_Pyramid;
	SwitchArg		NMS_Macros1;
	SwitchArg		NMS_Macros2;
	SwitchArg		NMS_Genetics;
	SwitchArg		NMS_Mutate;

	//////////////////////////////////////////////////////////////////////////
	// Test marshalling for dll
	//////////////////////////////////////////////////////////////////////////
	SwitchArg		M_NU_ConstDest;
	SwitchArg		M_NU_CopyConstDest;
	SwitchArg		M_NU_DimConstDest;
	SwitchArg		M_NU_Rho;
	SwitchArg		M_NU_Sig;
	SwitchArg		M_NU_SetNext;
	SwitchArg		M_NU_SetPrev;
	SwitchArg		M_NU_SetInput;
	SwitchArg		M_NU_GetOutput;
	SwitchArg		M_NU_PutNeural;
	SwitchArg		M_NU_GetNeural;
	SwitchArg		M_NU_Propagate1;
	SwitchArg		M_NU_Propagate2;
	SwitchArg		M_NU_BackPropagate1;
	SwitchArg		M_NU_BackPropagate2;
	SwitchArg		M_NU_Error;
	SwitchArg		M_NMS_ConstDest;
	SwitchArg		M_NMS_CopyConstDest;
	SwitchArg		M_NMS_DimConstDest;
	SwitchArg		M_NMS_PushBack;
	SwitchArg		M_NMS_SetRho1;
	SwitchArg		M_NMS_SetRho2;
	SwitchArg		M_NMS_SetSig1;
	SwitchArg		M_NMS_SetSig2;
	SwitchArg		M_NMS_PutNeural;
	SwitchArg		M_NMS_Propagate;
	SwitchArg		M_NMS_BackPropagate1;
	SwitchArg		M_NMS_BackPropagate2;
	SwitchArg		M_NMS_Error;

	SwitchArg		SupervisedLearning1;
	SwitchArg		SupervisedXVal1;
	SwitchArg		SupervisedApply1;
	SwitchArg		SupervisedError1;
	SwitchArg		UnsupervisedLearning1;
	SwitchArg		UnsupervisedXVal1;
	SwitchArg		UnsupervisedApply1;

	SwitchArg		SupervisedLearning2;
	SwitchArg		SupervisedXVal2;
	SwitchArg		SupervisedApply2;
	SwitchArg		SupervisedError2;
	SwitchArg		UnsupervisedLearning2;
	SwitchArg		UnsupervisedXVal2;
	SwitchArg		UnsupervisedApply2;

	SwitchArg		SupervisedLearning3;
	SwitchArg		SupervisedXVal3;
	SwitchArg		SupervisedApply3;
	SwitchArg		SupervisedError3;
	SwitchArg		UnsupervisedLearning3;
	SwitchArg		UnsupervisedXVal3;
	SwitchArg		UnsupervisedApply3;

	SwitchArg		Verbose;

	ValueArg<string>         Brains;
	ValueArg<string>         Clusters;
	ValueArg<string>         GeneticFilename;
	ValueArg<string>         InputFilename;
	ValueArg<string>         OutputFilename;

	CommandLineOptions( void ) :
		cmd	             ( "TestNeuralNetTemplate", ' ', "0.2" ),	
		N32_Ostream          ( "", "N32_Ostream",          "Test N32_Ostream",          cmd, false ),
		N32_CheckDim         ( "", "N32_CheckDim",         "Test N32_CheckDim",         cmd, false ),
		N32_Constructor1     ( "", "N32_Constructor1",     "Test N32_Constructor1",     cmd, false ),
		N32_Constructor2     ( "", "N32_Constructor2",     "Test N32_Constructor2",     cmd, false ),
		N32_Constructor3     ( "", "N32_Constructor3",     "Test N32_Constructor3",     cmd, false ),
		N32_GetRows          ( "", "N32_GetRows",          "Test N32_GetRows",          cmd, false ),
		N32_GetColumns       ( "", "N32_GetColumns",       "Test N32_GetColumns",       cmd, false ),
		N32_SetNext          ( "", "N32_SetNext",          "Test N32_SetNext",          cmd, false ),
		N32_SetPrevious      ( "", "N32_SetPrevious",      "Test N32_SetPrevious",      cmd, false ),
		N32_SetLearningRate  ( "", "N32_SetLearningRate",  "Test N32_SetLearningRate",  cmd, false ),
		N32_PutNeural        ( "", "N32_PutNeural",        "Test N32_PutNeural",        cmd, false ),
		N32_GetNeural        ( "", "N32_GetNeural",        "Test N32_GetNeural",        cmd, false ),
		N32_Propagate1       ( "", "N32_Propagate1",       "Test N32_Propagate1",       cmd, false ),
		N32_Propagate2       ( "", "N32_Propagate2",       "Test N32_Propagate2",       cmd, false ),
		N32_BackPropagate1   ( "", "N32_BackPropagate1",   "Test N32_BackPropagate1",   cmd, false ),
		N32_BackPropagate2   ( "", "N32_BackPropagate2",   "Test N32_BackPropagate2",   cmd, false ),
		NMS_Ostream          ( "", "NMS_Ostream",          "Test NMS_Ostream",          cmd, false ),
		NMS_Constructor1     ( "", "NMS_Constructor1",     "Test NMS_Constructor1",     cmd, false ),
		NMS_Constructor2     ( "", "NMS_Constructor2",     "Test NMS_Constructor2",     cmd, false ),
		NMS_PutNeural        ( "", "NMS_PutNeural",        "Test NMS_PutNeural",        cmd, false ),
		NMS_GetNeural        ( "", "NMS_GetNeural",        "Test NMS_GetNeural",        cmd, false ),
		NMS_SetLearningRate1 ( "", "NMS_SetLearningRate1", "Test NMS_SetLearningRate1", cmd, false ),
		NMS_SetLearningRate2 ( "", "NMS_SetLearningRate2", "Test NMS_SetLearningRate2", cmd, false ),
		NMS_Error            ( "", "NMS_Error",            "Test NMS_Error",            cmd, false ),
		NMS_Propagate        ( "", "NMS_Propagate",        "Test NMS_Propagate",        cmd, false ),
		NMS_BackPropagate    ( "", "NMS_BackPropagate",    "Test NMS_BackPropagate",    cmd, false ),
		N32_Learning         ( "", "N32_Learning",         "Test N32_Learning",         cmd, false ),
		N32_Learning2        ( "", "N32_Learning2",        "Test N32_Learning2",        cmd, false ),
		NMS_Learning         ( "", "NMS_Learning",         "Test NMS_Learning",         cmd, false ),
		NMS_Learning2        ( "", "NMS_Learning2",        "Test NMS_Learning2",        cmd, false ),
		NMS_Learning3        ( "", "NMS_Learning3",        "Test NMS_Learning3",        cmd, false ),
		NMS_Learning4        ( "", "NMS_Learning4",        "Test NMS_Learning4",        cmd, false ),
		NMS_Pyramid          ( "", "NMS_Pyramid",          "Test NMS_Pyramid",          cmd, false ),
		NMS_Genetics         ( "", "NMS_Genetics",         "Test NMS_Genetics",         cmd, false ),
		NMS_Mutate           ( "", "NMS_Mutate",           "Test NMS_Mutate",           cmd, false ),
		NMS_Macros1          ( "", "NMS_Macros1",          "Test NMS_Macros1",          cmd, false ),
		NMS_Macros2          ( "", "NMS_Macros2",          "Test NMS_Macros2",          cmd, false ),
		M_NU_ConstDest       ( "", "M_NU_ConstDest",       "Test M_NU_ConstDest",       cmd, false ),
		M_NU_CopyConstDest   ( "", "M_NU_CopyConstDest",   "Test M_NU_CopyConstDest",   cmd, false ),
		M_NU_DimConstDest    ( "", "M_NU_DimConstDest",    "Test M_NU_DimConstDest",    cmd, false ),
		M_NU_Rho             ( "", "M_NU_Rho",             "Test M_NU_Rho",             cmd, false ),
		M_NU_Sig             ( "", "M_NU_Sig",             "Test M_NU_Sig",             cmd, false ),
		M_NU_SetNext         ( "", "M_NU_SetNext",         "Test M_NU_SetNext",         cmd, false ),
		M_NU_SetPrev         ( "", "M_NU_SetPrev",         "Test M_NU_SetPrev",         cmd, false ),
		M_NU_SetInput        ( "", "M_NU_SetInput",        "Test M_NU_SetInput",        cmd, false ),
		M_NU_GetOutput       ( "", "M_NU_GetOutput",       "Test M_NU_GetOutput",       cmd, false ),
		M_NU_PutNeural       ( "", "M_NU_PutNeural",       "Test M_NU_PutNeural",       cmd, false ),
		M_NU_GetNeural       ( "", "M_NU_GetNeural",       "Test M_NU_GetNeural",       cmd, false ),
		M_NU_Propagate1      ( "", "M_NU_Propagate1",      "Test M_NU_Propagate1",      cmd, false ),
		M_NU_Propagate2      ( "", "M_NU_Propagate2",      "Test M_NU_Propagate2",      cmd, false ),
		M_NU_BackPropagate1  ( "", "M_NU_BackPropagate1",  "Test M_NU_BackPropagate1",  cmd, false ),
		M_NU_BackPropagate2  ( "", "M_NU_BackPropagate2",  "Test M_NU_BackPropagate2",  cmd, false ),
		M_NU_Error           ( "", "M_NU_Error",           "Test M_NU_Error",           cmd, false ),
		M_NMS_ConstDest      ( "", "M_NMS_ConstDest",      "Test M_NMS_ConstDest",      cmd, false ),
		M_NMS_CopyConstDest  ( "", "M_NMS_CopyConstDest",  "Test M_NMS_CopyConstDest",  cmd, false ),
		M_NMS_DimConstDest   ( "", "M_NMS_DimConstDest",   "Test M_NMS_DimConstDest",   cmd, false ),
		M_NMS_PushBack       ( "", "M_NMS_PushBack",       "Test M_NMS_PushBack",       cmd, false ),
		M_NMS_SetRho1        ( "", "M_NMS_SetRho1",        "Test M_NMS_SetRho1",        cmd, false ),
		M_NMS_SetRho2        ( "", "M_NMS_SetRho2",        "Test M_NMS_SetRho2",        cmd, false ),
		M_NMS_SetSig1        ( "", "M_NMS_SetSig1",        "Test M_NMS_SetSig1",        cmd, false ),
		M_NMS_SetSig2        ( "", "M_NMS_SetSig2",        "Test M_NMS_SetSig2",        cmd, false ),
		M_NMS_PutNeural      ( "", "M_NMS_PutNeural",      "Test M_NMS_PutNeural",      cmd, false ),
		M_NMS_Propagate      ( "", "M_NMS_Propagate",      "Test M_NMS_Propagate",      cmd, false ),
		M_NMS_BackPropagate1 ( "", "M_NMS_BackPropagate1", "Test M_NMS_BackPropagate1", cmd, false ),
		M_NMS_BackPropagate2 ( "", "M_NMS_BackPropagate2", "Test M_NMS_BackPropagate2", cmd, false ),
		M_NMS_Error          ( "", "M_NMS_Error",          "Test M_NMS_Error",          cmd, false ),
		SupervisedLearning1  ( "", "SupervisedLearning1",  "Test SupervisedLearning1",  cmd, false ),
		SupervisedXVal1      ( "", "SupervisedXVal1",      "Test SupervisedXVal1",      cmd, false ),
		SupervisedApply1     ( "", "SupervisedApply1",     "Test SupervisedApply1",     cmd, false ),
		SupervisedError1     ( "", "SupervisedError1",     "Test SupervisedError1",     cmd, false ),
		UnsupervisedLearning1( "", "UnsupervisedLearning1","Test UnsupervisedLearning1",cmd, false ),
		UnsupervisedXVal1    ( "", "UnsupervisedXVal1",    "Test UnsupervisedXVal1",    cmd, false ),
		UnsupervisedApply1   ( "", "UnsupervisedApply1",   "Test UnsupervisedApply1",   cmd, false ),
		SupervisedLearning2  ( "", "SupervisedLearning2",  "Test SupervisedLearning2",  cmd, false ),
		SupervisedXVal2      ( "", "SupervisedXVal2",      "Test SupervisedXVal2",      cmd, false ),
		SupervisedApply2     ( "", "SupervisedApply2",     "Test SupervisedApply2",     cmd, false ),
		SupervisedError2     ( "", "SupervisedError2",     "Test SupervisedError2",     cmd, false ),
		UnsupervisedLearning2( "", "UnsupervisedLearning2","Test UnsupervisedLearning2",cmd, false ),
		UnsupervisedXVal2    ( "", "UnsupervisedXVal2",    "Test UnsupervisedXVal2",    cmd, false ),
		UnsupervisedApply2   ( "", "UnsupervisedApply2",   "Test UnsupervisedApply2",   cmd, false ),
		SupervisedLearning3  ( "", "SupervisedLearning3",  "Test SupervisedLearning3",  cmd, false ),
		SupervisedXVal3      ( "", "SupervisedXVal3",      "Test SupervisedXVal3",      cmd, false ),
		SupervisedApply3     ( "", "SupervisedApply3",     "Test SupervisedApply3",     cmd, false ),
		SupervisedError3     ( "", "SupervisedError3",     "Test SupervisedError3",     cmd, false ),
		UnsupervisedLearning3( "", "UnsupervisedLearning3","Test UnsupervisedLearning3",cmd, false ),
		UnsupervisedXVal3    ( "", "UnsupervisedXVal3",    "Test UnsupervisedXVal3",    cmd, false ),
		UnsupervisedApply3   ( "", "UnsupervisedApply3",   "Test UnsupervisedApply3",   cmd, false ),
		Verbose              ( "", "Verbose",              "Verbose Mode",              cmd, false ),
		Brains               ( "B","Brains",               "Brains file",               false, "string", "string", cmd ),
		Clusters             ( "C","Clusters",             "Clusters file",             false, "string", "string", cmd ),
		GeneticFilename      ( "G","GeneticFilename",      "Genetic input filename",    false, "string", "string", cmd ),
		OutputFilename       ( "O","OutputFilename",       "Output filename",           false, "string", "string", cmd ),
		InputFilename        ( "I","InpuFilename",         "Input filename",            false, "string", "string", cmd ) {}
};                                                                                                                   
                                                                                                                     
CommandLineOptions options;                                                                                          
