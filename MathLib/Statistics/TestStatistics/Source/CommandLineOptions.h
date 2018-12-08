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
	CmdLine cmd;

	SwitchArg	Max;
	SwitchArg	Min;
	SwitchArg	Mean;
	SwitchArg	StandardDeviation;
	SwitchArg	Covariance;
	SwitchArg	MeanCenteredCovariance;
	SwitchArg	Correlation;
	SwitchArg	MeanCenteredCorrelation;
	SwitchArg	NormalizeByColumn;
	SwitchArg	NormalizeByRow;
	SwitchArg	NormalizeByColumn2;
	SwitchArg	NormalizeByRow2;

	SwitchArg	Verbose;
	
	ValueArg<string> Filename;
	ValueArg<string> Tokens;

	CommandLineOptions( void ) :
		cmd                    ( "test_statistics", ' ', "0.0" ),
		Max                    ( "", "Max",                     "Max",                     cmd, false ),
		Min                    ( "", "Min",                     "Min",                     cmd, false ),
		Mean                   ( "", "Mean",                    "Mean",                    cmd, false ),
		StandardDeviation      ( "", "StandardDeviation",       "StandardDeviation",       cmd, false ),
		Covariance             ( "", "Covariance",              "Covariance",              cmd, false ),
		MeanCenteredCovariance ( "", "MeanCenteredCovariance",  "MeanCenteredCovariance",  cmd, false ),
		Correlation            ( "", "Correlation",             "Correlation",             cmd, false ),
		MeanCenteredCorrelation( "", "MeanCenteredCorrelation", "MeanCenteredCorrelation", cmd, false ),
		NormalizeByColumn      ( "", "NormalizeByColumn",       "NormalizeByColumn",       cmd, false ),
		NormalizeByRow         ( "", "NormalizeByRow",          "NormalizeByRow",          cmd, false ),
		NormalizeByColumn2     ( "", "NormalizeByColumn2",      "NormalizeByColumn2",      cmd, false ),
		NormalizeByRow2        ( "", "NormalizeByRow2",         "NormalizeByRow2",         cmd, false ),
		Verbose                ( "", "Verbose",                 "Verbose output",          cmd, false ),
		Filename               ( "", "InputFile",               "Input file for training/ trading", false, "", "string", cmd ),
		Tokens                 ( "", "Tokens",                  "Delimeters used in parsing",       false, "", "string", cmd ) {}
};

CommandLineOptions options;