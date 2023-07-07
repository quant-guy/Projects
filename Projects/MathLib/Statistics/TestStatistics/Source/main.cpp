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
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>

#include <Statistics.h>
#include "CommandLineOptions.h"
#include "Parser.h"
#include "Timing.h"

void cout_array( double ** data, const unsigned int & rows, const unsigned int & columns )
{
	for ( double ** outer_ptr = data; outer_ptr < data + rows; ++outer_ptr )
	{
		for ( double * inner_ptr = * outer_ptr; inner_ptr < ( * outer_ptr ) + columns; ++inner_ptr )
		{
			cout << * inner_ptr << ' ';
		}
		cout << endl;
	}
}

void cout_array( double * data, const unsigned int & columns )
{
	for ( double * inner_ptr = data; inner_ptr < data + columns; ++inner_ptr )
	{
		cout << * inner_ptr << ' ';
	}
	cout << endl;
}

int main( int argc, char ** argv )
{
	options.cmd.parse( argc, argv );

	if ( ! options.Filename.isSet() )
	{
		cerr << "Error: please enter input filename" << endl;
		exit( 1 );
	}

	ifstream * input;
	ifstream file_input(options.Filename.getValue().c_str() );
	input = & file_input;

	const unsigned int rows = count_lines( input );
	const unsigned int columns = count_fields( input, options.Tokens.getValue().c_str() );

	// allocate memory for results
	double ** data =              new double * [ rows ];
	double ** covariance_result = new double * [ columns ];
	double *  row_result =        new double   [ columns ];

	// allocate memory for data
	for ( double ** outer_ptr = data; outer_ptr < data + rows; ++outer_ptr )
	{
		* outer_ptr = new double [ columns ];
	}

	// initialize data entries to zero
	for ( double ** outer_ptr = data; outer_ptr < data + rows; ++outer_ptr )
	{
		for ( double * inner_ptr = * outer_ptr; inner_ptr < ( * outer_ptr ) + columns; ++inner_ptr )
		{
			* inner_ptr = 0.0;
		}
	}

	// allocate memory for covariance result
	for ( double ** outer_ptr = covariance_result; outer_ptr < covariance_result + columns; ++outer_ptr )
	{
		* outer_ptr = new double [ columns ];
	}

	// initialize covariance matrix to zero
	for ( double ** outer_ptr = covariance_result; outer_ptr < covariance_result + columns; ++outer_ptr )
	{
		for ( double * inner_ptr = * outer_ptr; inner_ptr < ( * outer_ptr ) + columns; ++inner_ptr )
		{
			* inner_ptr = 0.0;
		}
	}

	parser( input, options.Tokens.getValue().c_str(), data, rows, columns );

	// run tests
	if ( options.Max.isSet() )
	{
START;
		Max( data, row_result, rows, columns );
STOP;
		if ( options.Verbose.isSet() ) cout_array( row_result, columns );
	}

	if ( options.Min.isSet() )
	{
START;
		Min( data, row_result, rows, columns );
STOP;
		if ( options.Verbose.isSet() ) cout_array( row_result, columns );
	}

	if ( options.Mean.isSet() )
	{
START;
		Mean( data, row_result, rows, columns );
STOP;
		if ( options.Verbose.isSet() ) cout_array( row_result, columns );
	}

	if ( options.StandardDeviation.isSet() )
	{
START;
		StandardDeviation( data, row_result, rows, columns );
STOP;
		if ( options.Verbose.isSet() ) cout_array( row_result, columns );
	}

	if ( options.Covariance.isSet() )
	{
START;
		Covariance( data, covariance_result, rows, columns );
STOP;
		if ( options.Verbose.isSet() ) cout_array( covariance_result, columns, columns );
	}

	if ( options.MeanCenteredCovariance.isSet() )
	{
START;
		MeanCenteredCovariance( data, covariance_result, rows, columns );
STOP;
		if ( options.Verbose.isSet() ) cout_array( covariance_result, columns, columns );
	}

	if ( options.Correlation.isSet() )
	{
START;
		Correlation( data, covariance_result, rows, columns );
STOP;
		if ( options.Verbose.isSet() ) cout_array( covariance_result, columns, columns );
	}

	if ( options.MeanCenteredCorrelation.isSet() )
	{
START;
		MeanCenteredCorrelation( data, covariance_result, rows, columns );
STOP;
		if ( options.Verbose.isSet() ) cout_array( covariance_result, columns, columns );
	}

	if ( options.NormalizeByColumn.isSet() )
	{
START;
		NormalizeByColumn( data, rows, columns );
STOP;
		if ( options.Verbose.isSet() ) cout_array( data, rows, columns );
	}

	if ( options.NormalizeByRow.isSet() )
	{
START;
		NormalizeByRow( data, rows, columns ); 
STOP;
		if ( options.Verbose.isSet() ) cout_array( data, rows, columns );
	}

	if ( options.NormalizeByColumn2.isSet() )
	{
START;
		NormalizeByColumn2( data, rows, columns );
STOP;
		if ( options.Verbose.isSet() ) cout_array( data, rows, columns );
	}

	if ( options.NormalizeByRow2.isSet() )
	{
START;
		NormalizeByRow2( data, rows, columns ); 
STOP;
		if ( options.Verbose.isSet() ) cout_array( data, rows, columns );
	}

	// close input file
	file_input.close();

	// clean up
	delete [] row_result;

	// delete memory for data
	for ( double ** outer_ptr = data; outer_ptr < data + rows; ++outer_ptr )
	{
		delete [] * outer_ptr;
	}

	// delete memory for covariance result
	for ( double ** outer_ptr = covariance_result; outer_ptr < covariance_result + columns; ++outer_ptr )
	{
		delete [] * outer_ptr;
	}

	return 0;
}
