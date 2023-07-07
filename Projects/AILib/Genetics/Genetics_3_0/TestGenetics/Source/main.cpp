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
#include <sstream>

#include <GeneticParameters.hpp>
#include <GeneticPair.hpp>
#include <Timing.h>

#include "CommandLineOptions.h"

using namespace std;
using namespace AILib::Genetics;
using namespace MathLib::Random;

int main( int argc, char ** argv )
{
	
	options.cmd.parse( argc, argv );

	if ( ! options.GeneticFilename.isSet() )
	{
		cerr << "Error: Please specify genetic input filename" << endl;
		exit( 1 );
	}

	// global genetic structure goes here
	GeneticPair  GP_Test( 1, 2 );
	GeneticGraph Test( options.GeneticFilename.getValue().c_str() );
	ParameterVector< double > genetic_parameters( 5, 0.1, -1.0, 1.0 );

	if ( options.GP_Constructor1.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing genetic pair constructor1" << endl;
		START;
			GeneticPair test;
		STOP;
	}

	if ( options.GP_Constructor2.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing genetic pair constructor2" << endl;
		START;
			GeneticPair test( 3, 4 );
		STOP;
		if ( options.Verbose.isSet() ) 
			cout << test << endl;
	}

	if ( options.GP_GetFirst.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing genetic pair get first" << endl;
		START;
			GP_Test.GetFirst();
		STOP;
		if ( options.Verbose.isSet() ) 
			cout << GP_Test.GetFirst() << endl;
	}

	if ( options.GP_GetSecond.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing genetic pair get second" << endl;
		START;
			GP_Test.GetSecond();
		STOP;
		if ( options.Verbose.isSet() ) 
			cout << GP_Test.GetSecond() << endl;
	}

	if ( options.GP_SetFirst.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing genetic pair set first" << endl;
		START;
			GP_Test.SetFirst( 8 );
		STOP;
		if ( options.Verbose.isSet() ) 
			cout << GP_Test.GetFirst() << endl;
	}

	if ( options.GP_SetSecond.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing genetic pair set second" << endl;
		START;
			GP_Test.SetSecond( 8 );
		STOP;
		if ( options.Verbose.isSet() ) 
			cout << GP_Test.GetSecond() << endl;
	}

	if ( options.GP_Swap.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing genetic pair swap" << endl;
		START;
			GP_Test.Swap();
		STOP;
		if ( options.Verbose.isSet() ) 
			cout << GP_Test << endl;
	}

	if ( options.GG_Constructor1.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing Constructor1" << endl;
		START;
			GeneticGraph gene;
		STOP;
	}

	if ( options.GG_Constructor2.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing Constructor2" << endl;
		START;
			GeneticGraph gene( Test );
		STOP;
	}

	if ( options.GG_Constructor3.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing Constructor3" << endl;
		START;
			GeneticGraph gene( options.GeneticFilename.getValue().c_str() );
		STOP;
	}

	if ( options.GG_PutGenetic.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing PutGenetic" << endl;
		START;
			Test.PutGenetic( "output_put_genetic.txt" );
		STOP;
	}

	if ( options.GG_Mutate1.isSet() )
	{
		if ( options.Verbose.isSet() ) 
		{
			cout << "Testing Mutate1" << endl;
			cout << Test << endl;
		}

		START;
			Test.Perturbation();
		STOP;

		if ( options.Verbose.isSet() ) 
			cout << Test << endl;
	}

	if ( options.GG_Mutate2.isSet() )
	{
		if ( options.Verbose.isSet() ) 
		{
			cout << "Testing Mutate2" << endl;
			cout << Test << endl;
		}

		START;
			Test.Perturbation( 5 );
		STOP;
		if ( options.Verbose.isSet() ) 
			cout << Test << endl;
	}

	if ( options.GG_Ostream.isSet() )
	{
		if ( options.Verbose.isSet() ) 
		{
			cout << "Testing Ostream" << endl;
		START;
			cout << Test << endl;
		STOP;
		}
	}

	if ( options.GG_OutputMutate.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Testing Mutate2" << endl;
		ostringstream output;
		output << time( 0 );
		Test.PutGenetic( string( output.str() + "_1.dot" ).c_str() );
		START;
			Test.Perturbation( 5 );
		STOP;
		Test.PutGenetic( string( output.str() + "_2.dot" ).c_str() );
	}

	if ( options.GPA_Constructor1.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Test GeneticParameter Constructor 1" << endl;
	START;
		ParameterVector< double > gp;
	STOP;
	}
 
	if ( options.GPA_Constructor2.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Test GeneticParameter Constructor 2" << endl;
	START;
		ParameterVector< double > gp( genetic_parameters );
	STOP;
		if ( options.Verbose.isSet() ) 
			cout << "Genetic parameter vector: " << gp << endl;
	}

	if ( options.GPA_Constructor3.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Test GeneticParameter Constructor 3" << endl;
	START;
		ParameterVector< double > gp( options.GeneticFilename.getValue().c_str(), 0.1, -1.0, 1.0 );
	STOP;
		if ( options.Verbose.isSet() ) 
			cout << "Genetic parameter vector: " << gp << endl;
	}

	if ( options.GPA_Constructor4.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Test GeneticParameter Constructor 4" << endl;
		vector< double > values( 5, 1.0 );
	START;
		ParameterVector< double > gp( values );
	STOP;
		if ( options.Verbose.isSet() ) 
			cout << "Genetic parameter vector: " << gp << endl;
	}

	if ( options.GPA_Constructor5.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Test GeneticParameter Constructor 5" << endl;
		double values[ 5 ];
		fill( values, values + 5, 1.0 );
	START;
		ParameterVector< double > gp( values, 5 );
	STOP;
		if ( options.Verbose.isSet() ) 
			cout << "Genetic parameter vector: " << gp << endl;
	}

	if ( options.GPA_Assignment.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << "Test assignment" << endl;
		
		ParameterVector< double > gp;
	START;
		gp = genetic_parameters;
	STOP;
	}

	if ( options.GPA_Perturb.isSet() )
	{
		if ( options.Verbose.isSet() ) 
		{	
			cout << "Test mutation operations\nStructure before mutation:" << endl;
			cout << genetic_parameters << endl;
		}
	START;
		genetic_parameters.Perturbation();
	STOP;
		if ( options.Verbose.isSet() ) 
		{	
			cout << "Structure after mutation" << endl;
			cout << genetic_parameters << endl;
		}
	}

	if ( options.GPA_Copy.isSet() )
	{
		ParameterVector< double > gp( options.GeneticFilename.getValue().c_str(), 0.1, -1.0, 1.0 );
		double * array = new double [ gp.Size() ];
		if ( options.Verbose.isSet() ) 
		{
			cout << "test copy" << endl;
			cout << "random numbers:" << endl << gp << endl;
		}
	START;
		gp.Copy( array, gp.Size() );
	STOP;
		if ( options.Verbose.isSet() ) 
		{
			cout << "copied array:" << endl;
			for ( unsigned int i = 0; i < gp.Size(); ++i )
				cout << array[ i ] << endl;
		}
		
	}

	if ( options.GPA_Plus.isSet() )
	{
		ParameterVector< double > genetic_parameters2( 5, 0.1, -1.0, 1.0 );
		if ( options.Verbose.isSet() ) 
		{
			cout << "test addition operator" << endl;
			cout << "random numbers:" << endl << genetic_parameters << endl;
			cout << "and:" << endl << genetic_parameters2 << endl;
		}
	START;
		genetic_parameters + genetic_parameters2;
	STOP;
		if ( options.Verbose.isSet() ) 
		{
			cout << "results:" << endl << genetic_parameters << endl;
			cout << "and:" << endl << genetic_parameters2 << endl;
		}
		
	}

	return 0;
}
