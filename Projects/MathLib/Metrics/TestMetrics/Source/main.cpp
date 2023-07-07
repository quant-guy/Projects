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
#include <iterator>

#include <Metrics.h>
#include <Metrics.hpp>
#include <Parser.h>
#include <Timing.h>

#include "CommandLineOptions.h"

using namespace std;
using namespace MathLib;

int main( int argc, char ** argv )
{
	options.cmd.parse( argc, argv );

	if ( options.CompD.isSet() )
	{
		if ( ! options.CompFiles.isSet() )
		{
			cerr << "Error: enter files for compression distance data" << endl;
			return 1;
		}

		string file_contents;
		ifstream file_data( options.CompFiles.getValue().at( 0 ).c_str() );

		copy( istream_iterator< char >( file_data ), istream_iterator< char >(), back_inserter( file_contents ) );

START;
		Metrics::CompressionDistance( file_contents.c_str(), file_contents.size() );
STOP;
		if ( options.Verbose.isSet() ) 
			cout << Metrics::CompressionDistance( file_contents.c_str(), file_contents.size() ) << endl;

		file_data.close();

		return 0;
	}

	if ( options.NormCompD.isSet() )
	{
		if ( ! options.CompFiles.isSet() )
		{
			cerr << "Error: enter files for compression distance data" << endl;
			return 1;

			if ( options.CompFiles.getValue().size() != 2 )
			{
				cerr << "Error: need two files for NCD" << endl;
				return 1;
			}
		}

		string file_contents1, file_contents2;
		ifstream file_data1( options.CompFiles.getValue().at( 0 ).c_str() );
		ifstream file_data2( options.CompFiles.getValue().at( 1 ).c_str() );

		copy( istream_iterator< char >( file_data1 ), istream_iterator< char >(), back_inserter( file_contents1 ) );
		copy( istream_iterator< char >( file_data2 ), istream_iterator< char >(), back_inserter( file_contents2 ) );

START;
		Metrics::NormalizedCompressionDistance( file_contents1.c_str(), file_contents1.size(), 
                                                        file_contents2.c_str(), file_contents2.size() );
STOP;
		if ( options.Verbose.isSet() ) 
			cout << Metrics::NormalizedCompressionDistance( file_contents1.c_str(), file_contents1.size(), 
                                                                        file_contents2.c_str(), file_contents2.size() ) << endl;
		file_data1.close();
		file_data2.close();

		return 0;
	}


	ifstream file;
	ifstream * f_ptr;

	// check to see that we have a dataset
	if ( ! options.Dataset.isSet() )
	{
		cerr << "Error: Enter a dataset" << endl;
		return 1;
	}

	file.open( options.Dataset.getValue().c_str() );
	f_ptr = & file;

        // get dimensions to instantiate 2D array
        const unsigned int rows = count_lines( f_ptr );
        const unsigned int cols = count_fields( f_ptr, options.Tokens.getValue().c_str() );

        // instantiate 2D data array for the data
        double ** data = new double * [ rows ];
        for ( int i = 0; i < rows; ++i )
        {
                data[ i ] = new double [ cols ];
        }

        parser( f_ptr, options.Tokens.getValue().c_str(), data, rows, cols );

	file.close();

	const unsigned int size_array = cols;

	vector< double > vector1;
	vector< double > vector2;

	copy( * ( data ), ( * ( data ) + size_array ), back_inserter( vector1 ) );
	copy( * ( data + 1 ), ( * ( data + 1 ) + size_array ), back_inserter( vector2 ) );

	if ( options.Euclidean.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << Metrics::EuclideanDistance< double >( * ( data ), * ( data + 1 ), size_array ) << endl;
START;
		Metrics::EuclideanDistance< double >( * ( data ), * ( data + 1 ), size_array );
STOP;
	}

	if ( options.Manhattan.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << Metrics::ManhattanDistance< double >( * ( data ), * ( data + 1 ), size_array ) << endl;
START;
		Metrics::ManhattanDistance< double >( * ( data ), * ( data + 1 ), size_array );
STOP;
	}
	  
	if ( options.EuclideanN.isSet() )
	{
		double normalization_value = 2.0;
		if ( options.Verbose.isSet() ) 
			cout << Metrics::EuclideanDistance< double >( * ( data ), * ( data + 1 ), size_array, normalization_value ) << endl;
START;
		Metrics::EuclideanDistance< double >( * ( data ), * ( data + 1 ), size_array, normalization_value );
STOP;
	}
	 
	if ( options.ManhattanN.isSet() )
	{
		double normalization_value = 2.0;
		if ( options.Verbose.isSet() ) 
			cout << Metrics::ManhattanDistance< double >( * ( data ), * ( data + 1 ), size_array, normalization_value ) << endl;
START;
		Metrics::ManhattanDistance< double >( * ( data ), * ( data + 1 ), size_array, normalization_value );
STOP;
	}
	 
	if ( options.EuclideanV.isSet() )
	{
		if ( options.Verbose.isSet() ) 
			cout << Metrics::EuclideanDistance< double >( vector1, vector2 ) << endl;
START;
		Metrics::EuclideanDistance< double >( vector1, vector2 );
STOP;
	}
	 
	if ( options.ManhattanV.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << Metrics::ManhattanDistance< double >( vector1, vector2 ) << endl;
START;
		Metrics::ManhattanDistance< double >( vector1, vector2 );
STOP;
	}
	 
	if ( options.EuclideanVN.isSet() )
	{
		double normalization_value = 2.0;
		if ( options.Verbose.isSet() ) 
			cout << Metrics::EuclideanDistance< double >( vector1, vector2, normalization_value ) << endl;
START;
		Metrics::EuclideanDistance< double >( vector1, vector2, normalization_value );
STOP;
	}
	 
	if ( options.ManhattanVN.isSet() )
	{
		double normalization_value = 2.0;
		if ( options.Verbose.isSet() ) 
			cout << Metrics::ManhattanDistance< double >( vector1, vector2, normalization_value ) << endl;
START;
		Metrics::ManhattanDistance< double >( vector1, vector2, normalization_value );
STOP;
	}
	 
	if ( options.GetNorm.isSet() )
	{
		double normalization_value = 0.0;
		if ( options.Verbose.isSet() ) 
			cout << Metrics::DetermineNormalizationValue< double >( ( const double ** ) data, rows, cols, & Metrics::EuclideanDistance ) << endl;
		if ( options.Verbose.isSet() ) 
			cout << Metrics::DetermineNormalizationValue< double >( ( const double ** ) data, rows, cols, & Metrics::ManhattanDistance ) << endl;
START;
		Metrics::DetermineNormalizationValue< double >( ( const double ** ) data, rows, cols, & Metrics::EuclideanDistance );
STOP;
START;
		Metrics::DetermineNormalizationValue< double >( ( const double ** ) data, rows, cols, & Metrics::ManhattanDistance );
STOP;
	}

	if ( options.EuclideanC.isSet() )
	{
		Metrics::Euclidean< double > m( vector1 );
START;
		m( & vector2 );
STOP;
	}

   	if ( options.ManhattanC.isSet() )
	{
		Metrics::Manhattan< double > m( vector1 );
START;
		m( & vector2 );
STOP;
	}

    	if ( options.NeuralC.isSet() )
	{
		Metrics::Neural< double > m( vector1 );
START;
		m( & vector2 );
STOP;
	}
    
    	if ( options.GaussianC.isSet() )
	{
		Metrics::Gaussian< double > m( vector1 );
START;
		m( & vector2 );
STOP;
	}
     
        for ( int i = 0; i < rows; ++i )
        {
                delete [] data[ i ];
        }

	return 0;
}
