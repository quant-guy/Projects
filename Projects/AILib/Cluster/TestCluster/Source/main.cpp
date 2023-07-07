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
#include <ClusterAlgorithmsCallers.h>
#include <Iostream2.h>
#include <Matrix.hpp>
#include <MemoryAllocationMacros.h>
#include <Preprocessor.hpp>
#include <Timing.h>

#include "CommandLineOptions.h"

using namespace AILib;

int main( int argc, char ** argv )
{
	options.cmd.parse( argc, argv );

	const double error = 0.1;
	const double tolerance = 0.1;
	const unsigned int clusters = 3;

	/////////////////////////////////////////////////////////////////////////////////
	// configure preprocessors
	/////////////////////////////////////////////////////////////////////////////////

	preprocessor::Preprocessor p_in;
	preprocessor::Preprocessor p_xval;

	if ( options.InputFilename.isSet() )
	{
		p_in.Open( options.InputFilename.getValue().c_str(), options.Tokens.getValue().c_str() );
	}
	else
	{
		std::cerr << "Error: Please specify input filename." << std::endl;
		return 1;
	}

	if ( options.XValFilename.isSet() )
	{
		p_xval.Open( options.XValFilename.getValue().c_str(), options.Tokens.getValue().c_str() );
	}

	preprocessor::Preprocessor p_app( p_in.GetRows(), 2 );

	/////////////////////////////////////////////////////////////////////////////////
	// configure matrices
	/////////////////////////////////////////////////////////////////////////////////

	MathLib::Matrix::Matrix< double > m_in( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
	MathLib::Matrix::Matrix< double > m_xval;
	MathLib::Matrix::Matrix< double > m_app( p_in.GetRows(), 2 );

	if ( options.XValFilename.isSet() )
	{
		m_xval.GetMatrix( ( const double ** ) p_xval.GetData(), p_in.GetRows(), p_in.GetCols() );
	}

	/////////////////////////////////////////////////////////////////////////////////
	// configure arrays
	/////////////////////////////////////////////////////////////////////////////////

	const unsigned int rows_in = p_in.GetRows();
	const unsigned int cols_in = p_in.GetCols();
	const unsigned int rows_app = p_in.GetRows();
	const unsigned int cols_app = 2;
	unsigned int rows_xval = 0;
	unsigned int cols_xval = 0;
	double ** a_in = new double * [ rows_in ];
	double ** a_app  = new double * [ rows_in ];
	double ** a_xval = 0;

	ALLOCATE_MEMORY_ONE_DATASET( a_app, rows_app, cols_app );
	ALLOCATE_MEMORY_ONE_DATASET( a_in, rows_in, cols_in );

	m_in.Convert( a_in, rows_in, cols_in );

	if ( options.XValFilename.isSet() )
	{
		a_xval = new double * [ p_xval.GetRows() ];
		rows_xval = p_xval.GetRows();
		cols_xval = p_xval.GetCols();
		ALLOCATE_MEMORY_ONE_DATASET( a_xval, p_xval.GetRows(), p_xval.GetCols() );
	}

	/////////////////////////////////////////////////////////////////////////////////
	// KMeans unit tests
	/////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	// - using preprocessors
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.KMeans.isSet() && options.Train.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
START;
		KMeansTrainP( c_ptr, & p_in );
STOP;
		KMeansDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
		}

		return 0;
	}

	if ( options.KMeans.isSet() && options.Apply.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
		KMeansTrainP( c_ptr, & p_in );
START;
		KMeansApplyP( c_ptr, & p_in, & p_app );
STOP;
		KMeansDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << p_app << endl;
		}

		return 0;
	}

	if ( options.KMeans.isSet() && options.CrossValidate.isSet() && options.Preprocessor.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
		KMeansTrainP( c_ptr, & p_in );
START;
		KMeansCrossValidateP( c_ptr, & p_in, & p_xval, error );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << p_xval << endl;
			cout << "Error: " << KMeansCrossValidateP( c_ptr, & p_in, & p_xval, error ) << endl;
		}

		KMeansDestructor( c_ptr );

		return 0;
	}

	if ( options.KMeans.isSet() && options.GetError.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
		KMeansTrainP( c_ptr, & p_in );
START;
		KMeansGetErrorP( c_ptr, & p_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << "Error: " << KMeansGetErrorP( c_ptr, & p_in ) << endl;
		}
		KMeansDestructor( c_ptr );

		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using matrices 
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.KMeans.isSet() && options.Train.isSet() && options.Matrix.isSet() )
	{
		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
START;
		KMeansTrainM( c_ptr, & m_in );
STOP;
		KMeansDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
		}

		return 0;
	}

	if ( options.KMeans.isSet() && options.Apply.isSet() && options.Matrix.isSet() )
	{
		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
		KMeansTrainM( c_ptr, & m_in );
START;
		KMeansApplyM( c_ptr, & m_in, & m_app );
STOP;
		KMeansDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << m_app << endl;
		}

		return 0;
	}

	if ( options.KMeans.isSet() && options.CrossValidate.isSet() && options.Matrix.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
		KMeansTrainM( c_ptr, & m_in );
START;
		KMeansCrossValidateM( c_ptr, & m_in, & m_xval, error );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << m_xval << endl;
			cout << "Error: " << KMeansCrossValidateM( c_ptr, & m_in, & m_xval, error ) << endl;
		}

		KMeansDestructor( c_ptr );

		return 0;
	}

	if ( options.KMeans.isSet() && options.GetError.isSet() && options.Matrix.isSet() )
	{
		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
		KMeansTrainM( c_ptr, & m_in );
START;
		KMeansGetErrorM( c_ptr, & m_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << "Error: " << KMeansGetErrorM( c_ptr, & m_in ) << endl;
		}
		KMeansDestructor( c_ptr );

		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using arrays 
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.KMeans.isSet() && options.Train.isSet() && options.Array.isSet() )
	{
		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
START;
		KMeansTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
STOP;
		KMeansDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
		}
		return 0;
	}

	if ( options.KMeans.isSet() && options.Apply.isSet() && options.Array.isSet() )
	{
		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
		KMeansTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
START;
		KMeansApply( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_app, rows_app, cols_app );
STOP;
		KMeansDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_app, rows_app, cols_app );
		}
		return 0;
	}

	if ( options.KMeans.isSet() && options.CrossValidate.isSet() && options.Array.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
		KMeansTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
START;
		KMeansCrossValidate( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_xval, rows_xval, cols_xval, error );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_xval, rows_xval, cols_xval );
			cout << "Error: " << 
				KMeansCrossValidate( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_xval, rows_xval, cols_xval, error ) << endl;
		}
		KMeansDestructor( c_ptr );

		return 0;
	}

	if ( options.KMeans.isSet() && options.GetError.isSet() && options.Array.isSet() )
	{
		Cluster::KMeans< double > * c_ptr = KMeansConstructor( clusters );
		KMeansTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
START;
		KMeansGetError( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			cout << "Error: " << 
				KMeansGetError( c_ptr, ( const double ** ) a_in, rows_in, cols_in ) << endl;
		}
		KMeansDestructor( c_ptr );
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using the methods directly
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.KMeans.isSet() && options.Train.isSet() )
	{
		Cluster::KMeans< double > km( clusters );
START;
		km.Initialize( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
		km.Train( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
		}
		return 0;
	}

	if ( options.KMeans.isSet() && options.Apply.isSet() )
	{
		Cluster::KMeans< double > km( clusters );
		km.Initialize( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
		km.Train( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
START;
		km.Apply( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_app, rows_app, cols_app );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			Utility::Iostream2::cout_array( a_app, rows_app, cols_app );
		}
		return 0;
	}

	if ( options.KMeans.isSet() && options.CrossValidate.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::KMeans< double > km( clusters );
		km.Initialize( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
		km.Train( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
START;
		km.CrossValidate( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_xval, rows_xval, cols_xval, 1.0 );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			Utility::Iostream2::cout_array( a_xval, rows_xval, cols_xval );
			cout << "Error: " << 
				km.CrossValidate( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_xval, rows_xval, cols_xval, 1.0 ) << endl;
		}
		return 0;
	}

	if ( options.KMeans.isSet() && options.GetError.isSet() )
	{

		Cluster::KMeans< double > km( clusters );
		km.Initialize( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
		km.Train( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
START;
		km.GetError( ( const double ** ) p_in.GetData(), rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << "Error: " << 
				km.GetError( ( const double ** ) p_in.GetData(), rows_in, cols_in ) << endl;
		}
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// Self Organizing Map unit tests
	/////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	// - using preprocessors
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.SOM.isSet() && options.Train.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
START;
		SelfOrganizingMapTrainP( c_ptr, & p_in );
STOP;
		SelfOrganizingMapDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
		}
		
		return 0;
	}

	if ( options.SOM.isSet() && options.Apply.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
		SelfOrganizingMapTrainP( c_ptr, & p_in );
START;
		SelfOrganizingMapApplyP( c_ptr, & p_in, & p_app );
STOP;
		SelfOrganizingMapDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << p_app << endl;
		}

		return 0;
	}

	if ( options.SOM.isSet() && options.CrossValidate.isSet() && options.Preprocessor.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
		SelfOrganizingMapTrainP( c_ptr, & p_in );
START;
		SelfOrganizingMapCrossValidateP( c_ptr, & p_in, & p_xval, error );
STOP;
		SelfOrganizingMapDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << p_app << endl;
			cout << "Error: " << 
				SelfOrganizingMapCrossValidateP( c_ptr, & p_in, & p_xval, error ) << endl;
		}

		return 0;
	}

	if ( options.SOM.isSet() && options.GetError.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
		SelfOrganizingMapTrainP( c_ptr, & p_in );
START;
		SelfOrganizingMapGetErrorP( c_ptr, & p_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << "Error: " << 
				SelfOrganizingMapGetErrorP( c_ptr, & p_in )
					<< endl;
		}

		SelfOrganizingMapDestructor( c_ptr );
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using matrices 
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.SOM.isSet() && options.Train.isSet() && options.Matrix.isSet() )
	{
		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
START;
		SelfOrganizingMapTrainM( c_ptr, & m_in );
STOP;
		SelfOrganizingMapDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
		}

		return 0;
	}

	if ( options.SOM.isSet() && options.Apply.isSet() && options.Matrix.isSet() )
	{
		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
		SelfOrganizingMapTrainM( c_ptr, & m_in );
START;
		SelfOrganizingMapApplyM( c_ptr, & m_in, & m_app );
STOP;
		SelfOrganizingMapDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << m_app << endl;
		}

		return 0;
	}

	if ( options.SOM.isSet() && options.CrossValidate.isSet() && options.Matrix.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
		SelfOrganizingMapTrainM( c_ptr, & m_in );
START;
		SelfOrganizingMapCrossValidateM( c_ptr, & m_in, & m_xval, error );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << m_xval << endl;
			cout << "Error: " << 
				SelfOrganizingMapCrossValidateM( c_ptr, & m_in, & m_xval, error ) 
					<< endl;
		}

		SelfOrganizingMapDestructor( c_ptr );
		return 0;
	}

	if ( options.SOM.isSet() && options.GetError.isSet() && options.Matrix.isSet() )
	{
		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
		SelfOrganizingMapTrainM( c_ptr, & m_in );
START;
		SelfOrganizingMapGetErrorM( c_ptr, & m_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << "Error: " << 
				SelfOrganizingMapGetErrorM( c_ptr, & m_in )
					<< endl;
		}

		SelfOrganizingMapDestructor( c_ptr );
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using arrays 
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.SOM.isSet() && options.Train.isSet() && options.Array.isSet() )
	{
		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
START;
		SelfOrganizingMapTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
STOP;
		SelfOrganizingMapDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
		}

		return 0;
	}

	if ( options.SOM.isSet() && options.Apply.isSet() && options.Array.isSet() )
	{
		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
		SelfOrganizingMapTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
START;
		SelfOrganizingMapApply( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_app, rows_app, cols_app );
STOP;
		SelfOrganizingMapDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_app, rows_app, cols_app );
		}

		return 0;
	}

	if ( options.SOM.isSet() && options.CrossValidate.isSet() && options.Array.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
		SelfOrganizingMapTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
START;
		SelfOrganizingMapCrossValidate( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_xval, rows_xval, cols_xval, error );
STOP;
		SelfOrganizingMapDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_xval, rows_xval, cols_xval );
			cout << "Error: " << 
				SelfOrganizingMapCrossValidate( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_xval, rows_xval, cols_xval, error ) 
					<< endl;
		}

		return 0;
	}

	if ( options.SOM.isSet() && options.GetError.isSet() && options.Array.isSet() )
	{
		Cluster::SelfOrganizingMap< double > * c_ptr = SelfOrganizingMapConstructor( clusters, tolerance, error );
		SelfOrganizingMapTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
START;
		SelfOrganizingMapGetError( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			cout << "Error: " << 
				SelfOrganizingMapGetError( c_ptr, ( const double ** ) a_in, rows_in, cols_in )
					<< endl;
		}

		SelfOrganizingMapDestructor( c_ptr );
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using the methods directly
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.SOM.isSet() && options.Train.isSet() )
	{
		Cluster::SelfOrganizingMap< double > som( clusters, tolerance, error );
START;
		som.Initialize( cols_in );
		som.Train( ( const double ** ) a_in, rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
		}

		return 0;
	}

	if ( options.SOM.isSet() && options.Apply.isSet() )
	{
		Cluster::SelfOrganizingMap< double > som( clusters, tolerance, error );
		som.Initialize( cols_in );
		som.Train( ( const double ** ) a_in, rows_in, cols_in );
START;
		som.Apply( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_app, rows_app, cols_app );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_app, rows_app, cols_app );
		}

		return 0;
	}

	if ( options.SOM.isSet() && options.CrossValidate.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::SelfOrganizingMap< double > som( clusters, tolerance, error );
		som.Initialize( cols_in );
		som.Train( ( const double ** ) a_in, rows_in, cols_in );
START;
		som.CrossValidate( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_xval, rows_xval, cols_xval, 1.0 );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_xval, rows_xval, cols_xval );
			cout << "Error: " << 
				som.CrossValidate( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_xval, rows_xval, cols_xval, 1.0 )
					<< endl;
		}

		return 0;
	}

	if ( options.SOM.isSet() && options.GetError.isSet() )
	{
		Cluster::SelfOrganizingMap< double > som( clusters, tolerance, error );
		som.Initialize( cols_in );
		som.Train( ( const double ** ) a_in, rows_in, cols_in );
START;
		som.GetError( ( const double ** ) p_in.GetData(), rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			cout << "Error: " << 
				som.GetError( ( const double ** ) p_in.GetData(), rows_in, cols_in )
					<< endl;
		}

		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// Topological cluster unit tests
	/////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	// - using preprocessors
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.Topological.isSet() && options.Train.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
START;
		TopologicalTrainP( c_ptr, & p_in );
STOP;
		TopologicalDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
		}

		return 0;
	}

	if ( options.Topological.isSet() && options.Apply.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
		TopologicalTrainP( c_ptr, & p_in );
START;
		TopologicalApplyP( c_ptr, & p_in, & p_app );
STOP;
		TopologicalDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << p_app << endl;
		}

		return 0;
	}

	if ( options.Topological.isSet() && options.CrossValidate.isSet() && options.Preprocessor.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
		TopologicalTrainP( c_ptr, & p_in );
START;
		TopologicalCrossValidateP( c_ptr, & p_in, & p_xval );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << p_xval << endl;
			cout << "Error: " << 
				TopologicalCrossValidateP( c_ptr, & p_in, & p_xval )
					<< endl;
		}

		TopologicalDestructor( c_ptr );
		return 0;
	}

	if ( options.Topological.isSet() && options.GetError.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
		TopologicalTrainP( c_ptr, & p_in );
START;
		TopologicalGetErrorP( c_ptr, & p_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << "Error: " << 
				TopologicalGetErrorP( c_ptr, & p_in )
					<< endl;
		}

		TopologicalDestructor( c_ptr );
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using matrices 
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.Topological.isSet() && options.Train.isSet() && options.Matrix.isSet() )
	{
		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
START;
		TopologicalTrainM( c_ptr, & m_in );
STOP;
		TopologicalDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
		}

		return 0;
	}

	if ( options.Topological.isSet() && options.Apply.isSet() && options.Matrix.isSet() )
	{
		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
		TopologicalTrainM( c_ptr, & m_in );
START;
		TopologicalApplyM( c_ptr, & m_in, & m_app );
STOP;
		TopologicalDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << m_app << endl;
		}

		return 0;
	}

	if ( options.Topological.isSet() && options.CrossValidate.isSet() && options.Matrix.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
		TopologicalTrainM( c_ptr, & m_in );
START;
		TopologicalCrossValidateM( c_ptr, & m_in, & m_xval );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << m_xval << endl;
			cout << "Error: " << 
				TopologicalCrossValidateM( c_ptr, & m_in, & m_xval )
					<< endl;
		}

		TopologicalDestructor( c_ptr );
		return 0;
	}

	if ( options.Topological.isSet() && options.GetError.isSet() && options.Matrix.isSet() )
	{
		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
		TopologicalTrainM( c_ptr, & m_in );
START;
		TopologicalGetErrorM( c_ptr, & m_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << "Error: " << 
				TopologicalGetErrorM( c_ptr, & m_in )
					<< endl;
		}

		TopologicalDestructor( c_ptr );
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using arrays 
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.Topological.isSet() && options.Train.isSet() && options.Array.isSet() )
	{
		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
START;
		TopologicalTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
STOP;
		TopologicalDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
		}

		return 0;
	}

	if ( options.Topological.isSet() && options.Apply.isSet() && options.Array.isSet() )
	{
		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
START;
		TopologicalApply( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_app, rows_app, cols_app );
STOP;
		TopologicalDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_app, rows_app, cols_app );
		}

		return 0;
	}

	if ( options.Topological.isSet() && options.CrossValidate.isSet() && options.Array.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
		TopologicalTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
START;
		TopologicalCrossValidate( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_xval, rows_xval, cols_xval );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_xval, rows_xval, cols_xval );
			cout << "Error: " << 
				TopologicalCrossValidate( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_xval, rows_xval, cols_xval )
					<< endl;
		}

		TopologicalDestructor( c_ptr );
		return 0;
	}

	if ( options.Topological.isSet() && options.GetError.isSet() && options.Array.isSet() )
	{
		Cluster::Topological< double > * c_ptr = TopologicalConstructor( tolerance );
		TopologicalTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
START;
		TopologicalGetError( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			cout << "Error: " << 
				TopologicalGetError( c_ptr, ( const double ** ) a_in, rows_in, cols_in )
					<< endl;
		}

		TopologicalDestructor( c_ptr );
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using the methods directly
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.Topological.isSet() && options.Train.isSet() )
	{
		Cluster::Topological< double > t;
START;
		t.Initialize( ( const double ** ) a_in, rows_in, cols_in );
		t.Train( ( const double ** ) a_in, rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
		}

		return 0;
	}

	if ( options.Topological.isSet() && options.Apply.isSet() )
	{
		Cluster::Topological< double > t;
		t.Initialize( ( const double ** ) a_in, rows_in, cols_in );
		t.Train( ( const double ** ) a_in, rows_in, cols_in );
START;
		t.Apply( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_app, rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_app, rows_app, cols_app );
		}

		return 0;
	}

	if ( options.Topological.isSet() && options.CrossValidate.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::Topological< double > t;
		t.Initialize( ( const double ** ) a_in, rows_in, cols_in );
		t.Train( ( const double ** ) a_in, rows_in, cols_in );
START;
		t.CrossValidate( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_xval, rows_xval, cols_xval );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_xval, rows_xval, cols_xval );
			cout << "Error: " << 
				t.CrossValidate( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_xval, rows_xval, cols_xval )
					<< endl;
		}

		return 0;
	}

	if ( options.Topological.isSet() && options.GetError.isSet() )
	{
		Cluster::Topological< double > t;
		t.Initialize( ( const double ** ) a_in, rows_in, cols_in );
		t.Train( ( const double ** ) a_in, rows_in, cols_in );
START;
		t.GetError( ( const double ** ) p_in.GetData(), rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << "Error: " << 
				t.GetError( ( const double ** ) p_in.GetData(), rows_in, cols_in )
					<< endl;
		}

		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// Simple cluster unit tests
	/////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	// - using preprocessors
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.Simple.isSet() && options.Train.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
START;
		SimpleClusterTrainP( c_ptr, & p_in );
STOP;
		SimpleClusterDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
		}

		return 0;
	}

	if ( options.Simple.isSet() && options.Apply.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
		SimpleClusterTrainP( c_ptr, & p_in );
START;
		SimpleClusterApplyP( c_ptr, & p_in, & p_app );
STOP;
		SimpleClusterDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << p_app << endl;
		}

		return 0;
	}

	if ( options.Simple.isSet() && options.CrossValidate.isSet() && options.Preprocessor.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
		SimpleClusterTrainP( c_ptr, & p_in );
START;
		SimpleClusterCrossValidateP( c_ptr, & p_in, & p_xval );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << p_xval << endl;
			cout << "Error: " << 
				SimpleClusterCrossValidateP( c_ptr, & p_in, & p_xval )
					<< endl;
		}

		SimpleClusterDestructor( c_ptr );
		return 0;
	}

	if ( options.Simple.isSet() && options.GetError.isSet() && options.Preprocessor.isSet() )
	{
		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
		SimpleClusterTrainP( c_ptr, & p_in );
START;
		SimpleClusterGetErrorP( c_ptr, & p_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << "Error: " << 
				SimpleClusterGetErrorP( c_ptr, & p_in )
					<< endl;
		}

		SimpleClusterDestructor( c_ptr );
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using matrices 
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.Simple.isSet() && options.Train.isSet() && options.Matrix.isSet() )
	{
		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
START;
		SimpleClusterTrainM( c_ptr, & m_in );
STOP;
		SimpleClusterDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
		}

		return 0;
	}

	if ( options.Simple.isSet() && options.Apply.isSet() && options.Matrix.isSet() )
	{
		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
		SimpleClusterTrainM( c_ptr, & m_in );
START;
		SimpleClusterApplyM( c_ptr, & m_in, & m_app );
STOP;
		SimpleClusterDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << m_app << endl;
		}

		return 0;
	}

	if ( options.Simple.isSet() && options.CrossValidate.isSet() && options.Matrix.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
		SimpleClusterTrainM( c_ptr, & m_in );
START;
		SimpleClusterCrossValidateM( c_ptr, & m_in, & m_xval );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << m_xval << endl;
			cout << "Error: " << 
				SimpleClusterCrossValidateM( c_ptr, & m_in, & m_xval )
					<< endl;
		}

		SimpleClusterDestructor( c_ptr );
		return 0;
	}

	if ( options.Simple.isSet() && options.GetError.isSet() && options.Matrix.isSet() )
	{
		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
		SimpleClusterTrainM( c_ptr, & m_in );
START;
		SimpleClusterGetErrorM( c_ptr, & m_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << m_in << endl;
			cout << "Error: " << 
				SimpleClusterGetErrorM( c_ptr, & m_in )
					<< endl;
		}

		SimpleClusterDestructor( c_ptr );
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using arrays 
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.Simple.isSet() && options.Train.isSet() && options.Array.isSet() )
	{
		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
START;
		SimpleClusterTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
STOP;
		SimpleClusterDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
		}

		return 0;
	}

	if ( options.Simple.isSet() && options.Apply.isSet() && options.Array.isSet() )
	{
		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
		SimpleClusterTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
START;
		SimpleClusterApply( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_app, rows_app, cols_app );
STOP;
		SimpleClusterDestructor( c_ptr );
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_app, rows_app, cols_app );
		}

		return 0;
	}

	if ( options.Simple.isSet() && options.CrossValidate.isSet() && options.Array.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
		SimpleClusterTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
START;
		SimpleClusterCrossValidate( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_xval, rows_xval, cols_xval );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_xval, rows_xval, cols_xval );
			cout << "Error: " << 
				SimpleClusterCrossValidate( c_ptr, ( const double ** ) a_in, rows_in, cols_in, a_xval, rows_xval, cols_xval )
					<< endl;
		}

		SimpleClusterDestructor( c_ptr );
		return 0;
	}

	if ( options.Simple.isSet() && options.GetError.isSet() && options.Array.isSet() )
	{
		Cluster::SimpleCluster< double > * c_ptr = SimpleClusterConstructor( tolerance );
		SimpleClusterTrain( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
START;
		SimpleClusterGetError( c_ptr, ( const double ** ) a_in, rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			cout << "Error: " << 
				SimpleClusterGetError( c_ptr, ( const double ** ) a_in, rows_in, cols_in )
					<< endl;
		}

		SimpleClusterDestructor( c_ptr );
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// - using the methods directly
	/////////////////////////////////////////////////////////////////////////////////
	if ( options.Simple.isSet() && options.Train.isSet() )
	{
		Cluster::SimpleCluster< double > s;
START;
		s.Train( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
		}

		return 0;
	}

	if ( options.Simple.isSet() && options.Apply.isSet() )
	{
		Cluster::SimpleCluster< double > s;
		s.Train( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
START;
		s.Apply( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_app, rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_app, rows_app, cols_app );
		}

		return 0;
	}

	if ( options.Simple.isSet() && options.CrossValidate.isSet() )
	{
		if ( ! options.XValFilename.isSet() )
		{
			std::cerr << "Error: Please specify cross validation filename." << std::endl;
			return 1;
		}

		Cluster::SimpleCluster< double > s;
		s.Train( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
START;
		s.CrossValidate( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_xval, rows_xval, cols_xval );
STOP;
		if ( options.Verbose.isSet() )
		{
			Utility::Iostream2::cout_array( a_in, rows_in, cols_in );
			Utility::Iostream2::cout_array( a_xval, rows_xval, cols_xval );
			cout << "Error: " << 
				s.CrossValidate( ( const double ** ) p_in.GetData(), rows_in, cols_in, a_xval, rows_xval, cols_xval )
					<< endl;
		}

		return 0;
	}

	if ( options.Simple.isSet() && options.GetError.isSet() )
	{
		Cluster::SimpleCluster< double > s;
		s.Train( ( const double ** ) p_in.GetData(), p_in.GetRows(), p_in.GetCols() );
START;
		s.GetError( ( const double ** ) p_in.GetData(), rows_in, cols_in );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << p_in << endl;
			cout << "Error: " << 
				s.GetError( ( const double ** ) p_in.GetData(), rows_in, cols_in )
					<< endl;
		}

		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////
	// clean up
	/////////////////////////////////////////////////////////////////////////////////

	DELETE_MEMORY_ONE_DATASET( a_in, rows_in );
	DELETE_MEMORY_ONE_DATASET( a_app, rows_in );
	if ( options.XValFilename.isSet() )
	{
		DELETE_MEMORY_ONE_DATASET( a_xval, p_xval.GetRows() );
	}

	return 0;
}
