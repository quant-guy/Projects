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
#include <Timing.h>
#include <Random.hpp>
#include "CommandLineOptions.h"

using namespace MathLib::Random;

int main( int argc, char ** argv )
{
	options.cmd.parse( argc, argv );

	unsigned int values = 1000;
	unsigned int seed = 0xA61d;
	if ( ! options.Values.isSet() && options.Verbose.isSet() )
	{
		cout << "Number values not set, setting number values to: " << values << endl;
	}
	else
	{
		values = options.Values.getValue();
	}

	if ( ! options.Seed.isSet() && options.Verbose.isSet() )
	{
		cout << "Seed not set, setting seed to: " << seed << endl;
	}
	else
	{
		seed = options.Seed.getValue();
	}

	MersenneTwister mt;
	CursoryRandomNumberGenerator crng;

	if ( options.RandomConstructor1.isSet() )
	{
	START;
		CursoryRandomNumberGenerator();
	STOP;
	}

	if ( options.RandomConstructor2.isSet() )
	{
	START;
		CursoryRandomNumberGenerator( seed );
	STOP;
	}

	if ( options.RandomConstructor3.isSet() )
	{
	START;
		MersenneTwister();
	STOP;
	}

	if ( options.RandomConstructor4.isSet() )
	{
	START;
		MersenneTwister( seed );
	STOP;
	}

	if ( options.TestSetSeed.isSet() )
	{
	START;
		crng.SetSeed( seed );
	STOP;
	}

	if ( options.TestGetSeed.isSet() )
	{
		crng.SetSeed( seed );
	START;
		crng.GetSeed();
	STOP;
		cout << "Seed value: " << crng.GetSeed() << endl;
	}

	if ( options.TestGenerate1.isSet() )
	{
	START;
		crng.Generate();
	STOP;
	}

	if ( options.TestGenerate2.isSet() )
	{
	START;
		mt.Generate();
	STOP;
	}

	if ( options.TestGenerate3.isSet() )
	{
	START;
		crng.Generate( ( unsigned int ) 3, ( unsigned int ) 10 );
	STOP;

	START;
		crng.Generate( 0.0, 1.0 );
	STOP;

		if ( options.Verbose.isSet() )
		{
			cout << crng.Generate( ( unsigned int ) 3, ( unsigned int ) 10 ) << endl;
			cout << crng.Generate( ( unsigned int ) 3, ( unsigned int ) 10 ) << endl;
			cout << crng.Generate( 0.0, 1.0 ) << endl;
			cout << crng.Generate( 0.0, 1.0 ) << endl;
		}
	}

	if ( options.TestGenerate4.isSet() )
	{
	START;
		mt.Generate( ( unsigned int ) 3, ( unsigned int ) 10 );
	STOP;

	START;
		mt.Generate( 0.0, 1.0 );
	STOP;
		if ( options.Verbose.isSet() )
		{
			cout << mt.Generate( ( unsigned int ) 3, ( unsigned int ) 10 ) << endl;
			cout << mt.Generate( ( unsigned int ) 3, ( unsigned int ) 10 ) << endl;
			cout << mt.Generate( 0.0, 1.0 ) << endl;
			cout << mt.Generate( 0.0, 1.0 ) << endl;
		}
	}

	if ( options.Generate.isSet() )
	{
	START;
		for ( unsigned int i = 0; i < values; ++i )
		{
			crng.Generate();
		}
	STOP;
	START;
		for ( unsigned int i = 0; i < values; ++i )
		{
			mt.Generate();
		}
	STOP;

		if ( options.Verbose.isSet() )
		{
			ostream * o_ptr = & std::cout;
			ofstream output;
			if ( options.OutputFilename.isSet() )
			{
				output.open( options.OutputFilename.getValue().c_str() );
				o_ptr = & output;
			}

			* o_ptr << "CRNG\tMT" << endl;
			for ( unsigned int i = 0; i < values; ++i )
			{
				* o_ptr << crng.Generate() << '\t' << mt.Generate() << endl;
			}

			if ( options.OutputFilename.isSet() )
			{
				output.close();
				o_ptr = 0;
			}
		}
	}

	return 0;
}
