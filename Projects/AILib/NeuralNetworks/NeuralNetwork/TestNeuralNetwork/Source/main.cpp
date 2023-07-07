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
#include <Timing.h>
#include <Matrix.hpp>
#include <MemoryAllocationMacros.h>
#include <NeuralUnit.hpp>
#include <NeuralCallers.h>
#include <NeuralAlgorithmsCallers.h>
#include <Preprocessor.hpp>

#include "CommandLineOptions.h"

using namespace MathLib::Matrix;
using namespace preprocessor;

int main( int argc, char ** argv )
{

	options.cmd.parse( argc, argv );

	unsigned int i = 0;
	unsigned int max_it = 100000;
	unsigned int clusters = 0;
	double desired_error = 0.1;
	double rate = 0.0;

	NeuralUnit< double > TestNeural( 3, 3 );
	NeuralUnit< double > TestNeural2( 3, 3 );

	double array_in4[ 4 ]; array_in4[ 0 ] = -1.0; array_in4[ 1 ] = 1.0; array_in4[ 2 ] = -1.0; array_in4[ 3 ] = 1.0;
	double array_in2[ 2 ]; array_in2[ 0 ] = -1.0; array_in2[ 1 ] = 1.0;
	double array_out2[ 2 ] = { 0 };

	vector< double > in4( 4 );
	in4.at( 0 ) = -1.0;
	in4.at( 1 ) =  1.0;
	in4.at( 2 ) = -1.0;
	in4.at( 3 ) =  1.0;
	Matrix< double > input4( in4.begin(), 4, 1 );

	vector< double > in( 3 );
	in.at( 0 ) = -1.0;
	in.at( 1 ) =  1.0;
	in.at( 2 ) = -1.0;
	Matrix< double > input( in.begin(), 3, 1 );

	vector< double > in2( 2 );
	in2.at( 0 ) = -1.0;
	in2.at( 1 ) =  1.0;
	Matrix< double > input_2( in2.begin(), 2, 1 );

	vector< double > out2( 2 );

	NeuralUnit< double > sample( 3, 3 );
	
	if ( options.N32_Ostream.isSet() )
	{
		START;
			cout << sample << endl;
		STOP;
	}
		      
	if ( options.N32_CheckDim.isSet() )
	{
		START;
			sample.GetRows();
		STOP;
		START;
			sample.GetCols();
		STOP;
	}
		     
	if ( options.N32_Constructor1.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test N32_Constructor1" << endl;
		START;
			NeuralUnit< double > Test;
		STOP;
	}
		 
	if ( options.N32_Constructor2.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test N32_Constructor2" << endl;
		START;
			NeuralUnit< double > Test( 3, 3 );
		STOP;
	}
		 
	if ( options.N32_Constructor3.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test copy constructor" << endl;
		NeuralUnit< double > Test( 3, 3 );
		START;
			NeuralUnit< double > Test2( TestNeural );
		STOP;
	}
		 
	if ( options.N32_GetRows.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test N32_GetRows" << endl;
		START;
			cout << TestNeural.GetRows() << endl;
		STOP;
	}
		      
	if ( options.N32_GetColumns.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test N32_GetColumns" << endl;
		START;
			cout << TestNeural.GetCols() << endl;
		STOP;
	}
		   
	if ( options.N32_SetNext.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test N32_SetNext" << endl;
		START;
			TestNeural.SetNext( & TestNeural2 );
		STOP;
	}
		      
	if ( options.N32_SetPrevious.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test N32_SetPrevious" << endl;
		START;
			TestNeural.SetPrev( & TestNeural2 );
		STOP;
	}
		  
	if ( options.N32_SetLearningRate.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test N32_SetLearningRate" << endl;
		START;
			TestNeural.SetLearningRate( ( double ) 0.0101 );
		STOP;
	}
	      
	if ( options.N32_PutNeural.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test N32_PutNeural" << endl;
		ofstream output( "test.dat" );
		START;
			TestNeural.PutNeuralUnit( & output );	
		STOP;
		output.close();	
	}
		    
	if ( options.N32_GetNeural.isSet() )
	{
		START;
		STOP;
	}
		    
	if ( options.N32_BackPropagate1.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test BackPropagation1" << endl;
		START;
			sample.BackPropagate( in );
		STOP;
	}
	 
	if ( options.N32_BackPropagate2.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test BackPropagation2" << endl;
		START;
			sample.BackPropagate( input );
		STOP;
	}
	       
	if ( options.N32_Propagate1.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test N32_Propagate1" << endl;
		START;
			TestNeural.Propagate( input );
		STOP;

		if ( options.Verbose.isSet() )
			cout << TestNeural.GetOutput() << endl;
	}

	if ( options.N32_Propagate2.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test N32_Propagate2" << endl;
		START;
			sample.Propagate( in );
		STOP;

		if ( options.Verbose.isSet() )
			cout << TestNeural.GetOutput() << endl;
	}		      

	   
	if ( options.NMS_Ostream.isSet() )
	{
		START;
			cout << sample << endl;
		STOP;
	}
		      
	if ( options.NMS_SetLearningRate1.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Set learning rate 1" << endl;
	}

	if ( options.NMS_SetLearningRate2.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Set learning rate 2" << endl;
	}

	if ( options.NMS_Constructor1.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test NMS_Constructor1" << endl;
		START;
			NeuralMacroStructure<double> nms;
		STOP;
	}
		 
	if ( options.NMS_Constructor2.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test NMS_Constructor2" << endl;
	}
	 
	if ( options.NMS_PutNeural.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test NMS_PutNeural" << endl;
		NeuralMacroStructure< double > nms( 4, 3, 2 );
		
		START;
			nms.PutNeuralMacroStructure( "test.dat" );
		STOP;
	}
		    
	if ( options.NMS_GetNeural.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test NMS_GetNeural" << endl;
		NeuralMacroStructure< double > nms( 4, 3, 2 );
		
		START;
			nms.GetNeuralMacroStructure( "test.dat" );
		STOP;
	}
		    
	if ( options.NMS_Error.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test NMS_Error" << endl;
	}
		 
	if ( options.NMS_Propagate.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test NMS_Propagate" << endl;
		NeuralMacroStructure< double > Test( 2, 2, 2 );
		Test.SetLearningRate( 0.5 );
		Matrix< double > input2( in2.begin(), 2, 1 );
		
		START;
			Test.Propagate( input2 );
		STOP;

		if ( options.Verbose.isSet() )
			cout << Test.Propagate( input2 ) << endl;
	}

	if ( options.NMS_BackPropagate.isSet() )
	{
		if ( options.Verbose.isSet() )
		cout << "Test NMS_BackPropagate" << endl;

		NeuralMacroStructure< double > Test( 2, 2, 2 );
		Test.SetLearningRate( 0.5 );
		Matrix< double > input2( in2.begin(), 2, 1 );

		Test.Propagate( input2 );
		if ( options.Verbose.isSet() )
		{
			cout << "Input:" << endl;
			cout << input2 << endl;
			cout << "After first propagation:" << endl;
			cout << Test.GetOutput() << endl;
		}

		START;
			Test.BackPropagate( input2 );
		STOP;

		Test.Propagate( input2 );
		if ( options.Verbose.isSet() )
		{
			cout << "After first training epoch:" << endl;
			cout << Test.GetOutput() << endl;
		}
	}


	// very simple learning algorithm that maps in2 to itself
	if ( options.N32_Learning.isSet() )
	{
		NeuralUnit< double > Test( 2, 2 );
		Test.SetLearningRate( 0.05 );
		Matrix< double > input2( in2.begin(), 2, 1 );

		int i = 0; double err = 0;
		Test.Propagate( input2 );

		if ( options.Verbose.isSet() )
		{
			cout << "Input:\n" << input2 << endl;
			cout << "Output:\n" << Test.GetOutput() << endl;
		}

		START;
			do
			{
				Test.BackPropagate( input2 );
				Test.Propagate( input2 );
				err = Test.Error( input2 );
				++i;
			} while ( i < 10000 && err > 0.01 );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Output:\n" << Test.GetOutput() << endl;
			cout << "Iterations:\n" << i << endl;
			cout << "Error:\n" << err << endl;
		}
			
	}

	if ( options.N32_Learning2.isSet() )
	{
		NeuralUnit< double > Test1( 3, 4 );
		NeuralUnit< double > Test2( 2, 3 );
		Test1.SetLearningRate( 0.5 );
		Test2.SetLearningRate( 0.5 );

		Matrix< double > output( in2.begin(), 2, 1 );

		Test1.SetNext( & Test2 );
		Test2.SetPrev( & Test1 );

		Test1.Propagate( input4 );
		Test2.Propagate();

		if ( options.Verbose.isSet() )
		{
			cout << "Input:\n" << input4 << endl;
			cout << "Output:\n" << Test2.GetOutput() << endl;
		}

		int i = 0;
		double err = 0;
		START;
			do
			{
				Test2.BackPropagate( output );
				Test1.BackPropagate();
				Test1.Propagate( input4 );
				Test2.Propagate();

				err = Test2.Error( output );
				++i;
			} while ( i < 100000 && err > 0.01 );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Output:\n" << Test2.GetOutput() << endl;
			cout << "Iterations:\n" << i << endl;
			cout << "Error:\n" << err << endl;
		}
			
	}

	if ( options.NMS_Learning.isSet() )
	{
		NeuralMacroStructure< double > nms( 4, 3, 2 );
		Matrix< double > output( in2.begin(), 2, 1 );

		nms.Propagate( input4 );

		if ( options.Verbose.isSet() )
		{
			cout << "Input:\n" << input4 << endl;
			cout << "Output:\n" << nms.GetOutput() << endl;
		}

		int i = 0;
		double err = 0;
		START;
			do
			{
				nms.BackPropagate( output );
				nms.Propagate( input4 );
				err = nms.Error( output );
				++i;
			} while ( i < 100000 && err > 0.01 );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Output:\n" << nms.GetOutput() << endl;
			cout << "Iterations:\n" << i << endl;
			cout << "Error:\n" << err << endl;
		}
	}

	if ( options.NMS_Learning2.isSet() )
	{
		NeuralUnit< double > Test1( 2, 2 );
		NeuralUnit< double > Test2( 2, 2 );
		NeuralUnit< double > Test3( 2, 2 );
		Matrix< double > input2( in2.begin(), 2, 1 );

		// 1 -> 3
		// 2 -> 3
		Test1.SetNext( & Test3 );
		Test2.SetNext( & Test3 );
		Test3.SetPrev( & Test1 );
		Test3.SetPrev( & Test2 );

		int i = 0; double err = 0;
		Test1.Propagate( input2 );
		Test2.Propagate( input2 );
		Test3.Propagate();

		if ( options.Verbose.isSet() )
		{
			cout << "Input:\n" << input2 << endl;
			cout << "Output:\n" << Test3.GetOutput() << endl;
		}

		START;
			do
			{
				Test3.BackPropagate( input2 );
				Test2.BackPropagate();
				Test1.BackPropagate();

				Test1.Propagate( input2 );
				Test2.Propagate( input2 );
				Test3.Propagate();

				err = Test3.Error( input2 ); ++i;
			} while ( i < 10000 && err > 0.01 );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Output:\n" << Test3.GetOutput() << endl;
			cout << "Iterations:\n" << i << endl;
			cout << "Error:\n" << err << endl;
		}
	}

	if ( options.NMS_Learning3.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: Please supply genetic filename." << endl;
			exit( 1 );
		}

		NeuralMacroStructure< double > nms( options.GeneticFilename.getValue().c_str(), 2, 0.05, 1.0 );

		if ( options.Verbose.isSet() )
		{
			cout << nms << endl;
		}

		// propagate first time
		nms.Propagate( in4, 4 );
		std::vector< double > nms_out;

		// output results if necessary
		if ( options.Verbose.isSet() )
		{
			cout << "Input:\n" << input4 << endl;
			cout << "Output:\n";
			nms.GetOutput( nms_out, 2 );
			copy( nms_out.begin(), nms_out.end(), ostream_iterator< double >( cout, "\t" ) );
			cout << "\nDesired Output:\n";
			copy( in2.begin(), in2.end(), ostream_iterator< double >( cout, "\t" ) );
			cout << endl;
		}

		int i = 0; double err = 0.0;
		START;
			do
			{
				nms.BackPropagate( in2, 2 );
				nms.Propagate( in4, 4 );
				err = nms.Error( in2, 2 );
				++i;
			} while ( i < 100000 && err > 0.01 );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Output:\n";
			nms.GetOutput( out2, 2 );
			copy( out2.begin(), out2.end(), ostream_iterator< double >( cout, "\t" ) );
			cout << "\nIterations:\t" << i << endl;
			cout << "Error:\t\t" << err << endl;
		}
	}

	if ( options.NMS_Learning4.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: Please supply genetic filename." << endl;
			exit( 1 );
		}

		NeuralMacroStructure< double > nms( options.GeneticFilename.getValue().c_str(), 2, 0.05, 1.0 );

		if ( options.Verbose.isSet() )
		{
			cout << nms << endl;
		}

		// propagate first time
		nms.Propagate( array_in4, 4 );
		double nms_out[ 2 ] = { 0.0 };

		// output results if necessary
		if ( options.Verbose.isSet() )
		{
			cout << "Input:\n";
			copy( array_in4, array_in4 + 4, ostream_iterator< double >( cout, "\t" ) );
			cout << "\nOutput:\n";
			nms.GetOutput( nms_out, 2 );
			copy( nms_out, nms_out + 2, ostream_iterator< double >( cout, "\t" ) );
			cout << "\nDesired Output:\n";
			copy( array_in2, array_in2 + 2, ostream_iterator< double >( cout, "\t" ) );
			cout << endl;
		}

		int i = 0; double err = 0;
		START;
			do
			{
				nms.BackPropagate( array_in2, 2 );
				nms.Propagate( array_in4, 4 );
				err = nms.Error( array_in2, 2 );
				++i;
			} while ( i < 100000 && err > 0.01 );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Output:\n";
			nms.GetOutput( array_out2, 2 );
			copy( array_out2, array_out2 + 2, ostream_iterator< double >( cout, "\t" ) );
			cout << "\nIterations:\t" << i << endl;
			cout << "Error:\t\t" << err << endl;
		}
	}

	if ( options.NMS_Pyramid.isSet() )
	{
	}

	// use macros for training ONLY ONE set of input vectors
	if ( options.NMS_Macros1.isSet() )
	{
	}

	if ( options.NMS_Macros2.isSet() )
	{
	}

	if ( options.NMS_Genetics.isSet() )
	{
	}

	if ( options.NMS_Mutate.isSet() )
	{
		NeuralMacroStructure< double > nms( options.GeneticFilename.getValue().c_str(), 2, 0.05, 1.0 );
START;
		nms.Mutate();
STOP;
		ofstream output_file( "output_from_mutation.txt" );
		output_file << nms << endl;
		output_file.close();
	}

	//////////////////////////////////////////////////////////////////
	// Dll tests
	//////////////////////////////////////////////////////////////////
	if ( options.M_NU_ConstDest.isSet() )
	{
		NeuralUnit< double > * n_ptr = NeuralUnitConstructor();
		NeuralUnitDestructor( n_ptr );
	}

	if ( options.M_NU_ConstDest.isSet() )
	{
	}

	if ( options.M_NU_CopyConstDest.isSet() )
	{
	}

	if ( options.M_NU_DimConstDest.isSet() )
	{
	}

	if ( options.M_NU_Rho.isSet() )
	{
	}

	if ( options.M_NU_Sig.isSet() )
	{
	}

	if ( options.M_NU_SetNext.isSet() )
	{ }

	if ( options.M_NU_SetPrev.isSet() )
	{
	}

	if ( options.M_NU_SetInput.isSet() )
	{
	}

	if ( options.M_NU_GetOutput.isSet() )
	{
	}

	if ( options.M_NU_PutNeural.isSet() )
	{
	}

	if ( options.M_NU_GetNeural.isSet() )
	{
	}

	if ( options.M_NU_Propagate1.isSet() )
	{
	}

	if ( options.M_NU_Propagate2.isSet() )
	{
	}

	if ( options.M_NU_BackPropagate1.isSet() )
	{
	}

	if ( options.M_NU_BackPropagate2.isSet() )
	{
	}

	if ( options.M_NU_Error.isSet() )
	{
	}

	if ( options.M_NMS_ConstDest.isSet() )
	{
	}

	if ( options.M_NMS_CopyConstDest.isSet() )
	{
	}

	if ( options.M_NMS_DimConstDest.isSet() )
	{
	}

	if ( options.M_NMS_PushBack.isSet() )
	{
	}

	if ( options.M_NMS_SetRho1.isSet() )
	{
	}

	if ( options.M_NMS_SetRho2.isSet() )
	{
	}

	if ( options.M_NMS_SetSig1.isSet() )
	{
	}

	if ( options.M_NMS_SetSig2.isSet() )
	{
	}

	if ( options.M_NMS_PutNeural.isSet() )
	{
	}

	if ( options.M_NMS_Propagate.isSet() )
	{
	}

	if ( options.M_NMS_BackPropagate1.isSet() )
	{
	}

	if ( options.M_NMS_BackPropagate2.isSet() )
	{
	}

	if ( options.M_NMS_Error.isSet() )
	{
	}

	//////////////////////////////////////////////////////////////////////
	// Test neural algorithms
	//////////////////////////////////////////////////////////////////////

	if ( options.SupervisedLearning1.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		Matrix<double> m1( ( const double ** ) p1.GetData(), p1.GetRows(), p1.GetCols() );
		Matrix<double> m2( ( const double ** ) p2.GetData(), p2.GetRows(), p2.GetCols() );

		if ( options.Verbose.isSet() )
		{
			cout << m1 << endl;
			cout << m2 << endl;
		}

		START;
			SupervisedAlgorithmM( & nn, & m1, & m2, i, max_it, desired_error );
		STOP;

		if ( options.Brains.isSet() )
		{
			if ( options.Verbose.isSet() )
				cout << "Outputting NN to brains file: " << options.Brains.getValue() << endl;
			nn.PutNeuralMacroStructure( options.Brains.getValue().c_str() );
		}

		if ( options.Verbose.isSet() )
		{
			cout << "Total Iterations: " << i << endl;
			cout << "Max Iterations:   " << max_it << endl;
			cout << "Desired Error:    " << desired_error << endl;
		}
	}
  
	if ( options.SupervisedXVal1.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		nn.GetNeuralMacroStructure( options.Brains.getValue().c_str() );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		Matrix<double> m1( ( const double ** ) p1.GetData(), p1.GetRows(), p1.GetCols() );
		Matrix<double> m2( ( const double ** ) p2.GetData(), p2.GetRows(), p2.GetCols() );

		START;
			SupervisedCrossValidationM( & nn, & m1, & m2, desired_error, rate );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Error rate: " << rate << endl;
		}
	}
      
	if ( options.SupervisedApply1.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );

		if ( options.Brains.isSet() )
		{
			if ( options.Verbose.isSet() )
				cout << "Loading brains file: " << options.Brains.getValue() << endl;
			nn.GetNeuralMacroStructure( options.Brains.getValue().c_str() );
		}

		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		Matrix<double> m1( ( const double ** ) p1.GetData(), p1.GetRows(), p1.GetCols() );
		Matrix<double> m2( ( const double ** ) p2.GetData(), p2.GetRows(), p2.GetCols() );

		START;
			SupervisedApplyM( & nn, & m1, & m2, true );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << m1 << endl << m2 << endl;
		}	
	}
     
	if ( options.SupervisedError1.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		nn.GetNeuralMacroStructure( options.Brains.getValue().c_str() );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		Matrix<double> m1( ( const double ** ) p1.GetData(), p1.GetRows(), p1.GetCols() );
		Matrix<double> m2( ( const double ** ) p2.GetData(), p2.GetRows(), p2.GetCols() );

		START;
			SupervisedGetErrorM( & nn, & m1, & m2 );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Total NN error: " << SupervisedGetErrorM( & nn, & m1, & m2 ) << endl;
		}	
	}
     
	if ( options.UnsupervisedLearning1.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		SimpleCluster<double> s;

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
		}

		Matrix<double> m1( ( const double ** ) p1.GetData(), p1.GetRows(), p1.GetCols() );

		if ( options.Verbose.isSet() )
		{
			cout << m1 << endl;
		}

		START;
			UnsupervisedAlgorithmM( & nn, & s, & m1, i, max_it, desired_error, clusters );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Clusters:         " << s << endl;
			cout << "Total iterations: " << i << endl;
			cout << "Max iterations:   " << max_it << endl;
			cout << "Desired error:    " << desired_error << endl;
			cout << "Clusters:         " << clusters << endl;
		}

		if ( options.Brains.isSet() )
		{
			nn.PutNeuralMacroStructure( options.Brains.getValue().c_str() );
		}

		if ( options.Clusters.isSet() )
		{
			ofstream cluster_output_file( options.Clusters.getValue().c_str() );
			cluster_output_file << s << endl;
			cluster_output_file.close();
		}
	}

	if ( options.UnsupervisedXVal1.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		if ( ! options.Clusters.isSet() )
		{
			cerr << "Error: need cluster filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		SimpleCluster<double> s( options.Clusters.getValue().c_str() );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
		}

		Matrix<double> m1( ( const double ** ) p1.GetData(), p1.GetRows(), p1.GetCols() );

		START;
			UnsupervisedCrossValidationM( & nn, & s, & m1, desired_error, rate );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Desired error:    " << desired_error << endl;
			cout << "Error Rate:       " << rate << endl;
		}
	}
    
	if ( options.UnsupervisedApply1.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		if ( ! options.Clusters.isSet() )
		{
			cerr << "Error: need cluster filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		SimpleCluster<double> s( options.Clusters.getValue().c_str() );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
		}

		Matrix<double> m1( ( const double ** ) p1.GetData(), p1.GetRows(), p1.GetCols() );
		int * indices = new int [ p1.GetRows() ];

		if ( ! indices )
		{
			cerr << "Error: error allocating data for clusters" << endl;
			return 1;
		}

		START;
			UnsupervisedApplyM( & nn, & s, & m1, indices );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Sample Classifications:" << endl;
			for ( unsigned int i = 0; i < p1.GetRows(); ++i )
			{
				cout << i << ", " << indices[ i ] << endl;
			}
		}

		delete [] indices;
	}
   
	if ( options.SupervisedLearning2.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		START;
			SupervisedAlgorithmP( & nn, & p1, & p2, i, max_it, desired_error );
		STOP;

		if ( options.Brains.isSet() )
		{
			if ( options.Verbose.isSet() )
				cout << "Outputting NN to brains file: " << options.Brains.getValue() << endl;
			nn.PutNeuralMacroStructure( options.Brains.getValue().c_str() );
		}

		if ( options.Verbose.isSet() )
		{
			cout << "Total Iterations: " << i << endl;
			cout << "Max Iterations:   " << max_it << endl;
			cout << "Desired Error:    " << desired_error << endl;
		}
	}
  
	if ( options.SupervisedXVal2.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		nn.GetNeuralMacroStructure( options.Brains.getValue().c_str() );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		START;
			SupervisedCrossValidationP( & nn, & p1, & p2, desired_error, rate );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Error rate: " << rate << endl;
		}
	}
      
	if ( options.SupervisedApply2.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );

		if ( options.Brains.isSet() )
		{
			if ( options.Verbose.isSet() )
				cout << "Loading brains file: " << options.Brains.getValue() << endl;
			nn.GetNeuralMacroStructure( options.Brains.getValue().c_str() );
		}

		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		START;
			SupervisedApplyP( & nn, & p1, & p2, true );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl << p2 << endl;
		}	
	}
     
	if ( options.SupervisedError2.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		nn.GetNeuralMacroStructure( options.Brains.getValue().c_str() );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		START;
			SupervisedGetErrorP( & nn, & p1, & p2 );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Total NN error: " << SupervisedGetErrorP( & nn, & p1, & p2 ) << endl;
		}	
	}
     
	if ( options.UnsupervisedLearning2.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		SimpleCluster<double> s;

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
		}

		START;
			UnsupervisedAlgorithmP( & nn, & s, & p1, i, max_it, desired_error, clusters );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Clusters:         " << s << endl;
			cout << "Total iterations: " << i << endl;
			cout << "Max iterations:   " << max_it << endl;
			cout << "Desired error:    " << desired_error << endl;
			cout << "Clusters:         " << clusters << endl;
		}

		if ( options.Brains.isSet() )
		{
			nn.PutNeuralMacroStructure( options.Brains.getValue().c_str() );
		}

		if ( options.Clusters.isSet() )
		{
			ofstream cluster_output_file( options.Clusters.getValue().c_str() );
			cluster_output_file << s << endl;
			cluster_output_file.close();
		}
	}

	if ( options.UnsupervisedXVal2.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		if ( ! options.Clusters.isSet() )
		{
			cerr << "Error: need cluster filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		SimpleCluster<double> s( options.Clusters.getValue().c_str() );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
		}

		START;
			UnsupervisedCrossValidationP( & nn, & s, & p1, desired_error, rate );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Desired error:    " << desired_error << endl;
			cout << "Error Rate:       " << rate << endl;
		}
	}
    
	if ( options.UnsupervisedApply2.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		if ( ! options.Clusters.isSet() )
		{
			cerr << "Error: need cluster filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		SimpleCluster<double> s( options.Clusters.getValue().c_str() );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
		}

		int * indices = new int [ p1.GetRows() ];

		if ( ! indices )
		{
			cerr << "Error: error allocating data for clusters" << endl;
			return 1;
		}

		START;
			UnsupervisedApplyP( & nn, & s, & p1, indices );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Sample Classifications:" << endl;
			for ( unsigned int i = 0; i < p1.GetRows(); ++i )
			{
				cout << i << ", " << indices[ i ] << endl;
			}
		}

		delete [] indices;
	}
   
	if ( options.SupervisedLearning3.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		const double ** data1 = ( const double ** ) p1.GetData();
		const double ** data2 = ( const double ** ) p2.GetData();
		const unsigned int rows = p1.GetRows();
		const unsigned int cols1 = p1.GetCols();
		const unsigned int cols2 = p2.GetCols();

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		if ( options.Verbose.isSet() )
		{
			for ( unsigned int i = 0; i < rows; ++i )
			{
				cout << data1[ i ][ 0 ];
				for ( unsigned int j = 1; j < cols1; ++j )
				{
					cout << ", " << data1[ i ][ j ];
				}
				cout << endl;
			}

			for ( unsigned int i = 0; i < rows; ++i )
			{
				cout << data2[ i ][ 0 ];
				for ( unsigned int j = 1; j < cols1; ++j )
				{
					cout << ", " << data2[ i ][ j ];
				}
				cout << endl;
			}
		}

		START;
			SupervisedAlgorithm( & nn, data1, data2, rows, cols1, cols2, i, max_it, desired_error );
		STOP;

		if ( options.Brains.isSet() )
		{
			if ( options.Verbose.isSet() )
				cout << "Outputting NN to brains file: " << options.Brains.getValue() << endl;
			nn.PutNeuralMacroStructure( options.Brains.getValue().c_str() );
		}

		if ( options.Verbose.isSet() )
		{
			cout << "Total Iterations: " << i << endl;
			cout << "Max Iterations:   " << max_it << endl;
			cout << "Desired Error:    " << desired_error << endl;
		}
	}
  
	if ( options.SupervisedXVal3.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		nn.GetNeuralMacroStructure( options.Brains.getValue().c_str() );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		const double ** data1 = ( const double ** ) p1.GetData();
		const double ** data2 = ( const double ** ) p2.GetData();
		const unsigned int rows = p1.GetRows();
		const unsigned int cols1 = p1.GetCols();
		const unsigned int cols2 = p2.GetCols();

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		if ( options.Verbose.isSet() )
		{
			for ( unsigned int i = 0; i < rows; ++i )
			{
				cout << data1[ i ][ 0 ];
				for ( unsigned int j = 1; j < cols1; ++j )
				{
					cout << ", " << data1[ i ][ j ];
				}
				cout << endl;
			}

			for ( unsigned int i = 0; i < rows; ++i )
			{
				cout << data2[ i ][ 0 ];
				for ( unsigned int j = 1; j < cols1; ++j )
				{
					cout << ", " << data2[ i ][ j ];
				}
				cout << endl;
			}
		}

		START;
			SupervisedCrossValidation( & nn, data1, data2, rows, cols1, cols2, desired_error, rate );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Error rate: " << rate << endl;
		}
	}
      
	if ( options.SupervisedApply3.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );

		if ( options.Brains.isSet() )
		{
			if ( options.Verbose.isSet() )
				cout << "Loading brains file: " << options.Brains.getValue() << endl;
			nn.GetNeuralMacroStructure( options.Brains.getValue().c_str() );
		}

		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		const double ** data1 = ( const double ** ) p1.GetData();
		double ** data2 = p2.GetData();
		const unsigned int rows = p1.GetRows();
		const unsigned int cols1 = p1.GetCols();
		const unsigned int cols2 = p2.GetCols();

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		START;
			SupervisedApply( & nn, data1, data2, rows, cols1, cols2, true );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl << p2 << endl;
		}	
	}
     
	if ( options.SupervisedError3.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.OutputFilename.isSet() )
		{
			cerr << "Error: need output filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		nn.GetNeuralMacroStructure( options.Brains.getValue().c_str() );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		Preprocessor p2( options.OutputFilename.getValue().c_str(), ", " );

		const double ** data1 = ( const double ** ) p1.GetData();
		const double ** data2 = ( const double ** ) p2.GetData();
		const unsigned int rows = p1.GetRows();
		const unsigned int cols1 = p1.GetCols();
		const unsigned int cols2 = p2.GetCols();

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
			cout << p2 << endl;
		}

		START;
			SupervisedGetError( & nn, data1, data2, rows, cols1, cols2 );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Total NN error: " << SupervisedGetError( & nn, data1, data2, rows, cols1, cols2 ) << endl;
		}	
	}
     
	if ( options.UnsupervisedLearning3.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		SimpleCluster<double> s;

		const double ** data1 = ( const double ** ) p1.GetData();
		const unsigned int rows = p1.GetRows();
		const unsigned int cols1 = p1.GetCols();

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
		}

		START;
			UnsupervisedAlgorithm( & nn, & s, data1, rows, cols1, i, max_it, desired_error, clusters );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Clusters:         " << s << endl;
			cout << "Total iterations: " << i << endl;
			cout << "Max iterations:   " << max_it << endl;
			cout << "Desired error:    " << desired_error << endl;
			cout << "Clusters:         " << clusters << endl;
		}

		if ( options.Brains.isSet() )
		{
			nn.PutNeuralMacroStructure( options.Brains.getValue().c_str() );
		}

		if ( options.Clusters.isSet() )
		{
			ofstream cluster_output_file( options.Clusters.getValue().c_str() );
			cluster_output_file << s << endl;
			cluster_output_file.close();
		}
	}

	if ( options.UnsupervisedXVal3.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		if ( ! options.Clusters.isSet() )
		{
			cerr << "Error: need cluster filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		SimpleCluster<double> s( options.Clusters.getValue().c_str() );

		const double ** data1 = ( const double ** ) p1.GetData();
		const unsigned int rows = p1.GetRows();
		const unsigned int cols1 = p1.GetCols();

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
		}

		START;
			UnsupervisedCrossValidation( & nn, & s, data1, rows, cols1, desired_error, rate );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Desired error:    " << desired_error << endl;
			cout << "Error Rate:       " << rate << endl;
		}
	}
    
	if ( options.UnsupervisedApply3.isSet() )
	{
		if ( ! options.GeneticFilename.isSet() )
		{
			cerr << "Error: need genetic filename" << endl;
			return 1;
		}

		if ( ! options.InputFilename.isSet() )
		{
			cerr << "Error: need input filename" << endl;
			return 1;
		}

		if ( ! options.Brains.isSet() )
		{
			cerr << "Error: need brains!!" << endl;
			return 1;
		}

		if ( ! options.Clusters.isSet() )
		{
			cerr << "Error: need cluster filename" << endl;
			return 1;
		}

		NeuralMacroStructure<double> nn( options.GeneticFilename.getValue().c_str(), 4, 0.05, 1.0 );
		Preprocessor p1( options.InputFilename.getValue().c_str(), ", " );
		SimpleCluster<double> s( options.Clusters.getValue().c_str() );

		const double ** data1 = ( const double ** ) p1.GetData();
		const unsigned int rows = p1.GetRows();
		const unsigned int cols1 = p1.GetCols();

		if ( options.Verbose.isSet() )
		{
			cout << p1 << endl;
		}

		int * indices = new int [ p1.GetRows() ];

		if ( ! indices )
		{
			cerr << "Error: error allocating data for clusters" << endl;
			return 1;
		}

		START;
			UnsupervisedApply( & nn, & s, data1, rows, cols1, indices );
		STOP;

		if ( options.Verbose.isSet() )
		{
			cout << "Sample Classifications:" << endl;
			for ( unsigned int i = 0; i < p1.GetRows(); ++i )
			{
				cout << i << ", " << indices[ i ] << endl;
			}
		}

		delete [] indices;
	}
   
	return 0;
}
