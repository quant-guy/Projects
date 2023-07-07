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
#include "Parser.h"

/////////////////////////////////////////////////////////////////////////
// output double array 
/////////////////////////////////////////////////////////////////////////
void Output( ostream * output,                  // output file stream
	     double * array,                    // array of fields to output
	     unsigned int num_fields )          // number of fields
{
	if ( ! array )
	{
		* output << "Error: Invalid output" << endl;
		exit( 1 );
	}

	* output << * array;
	for ( double * ptr = array + 1;
	      ptr != array + num_fields;
	      ++ptr )
	{
		* output << "\t" << * ptr;
	}	
	* output << endl;
}


/////////////////////////////////////////////////////////////////////////
// output float array 
/////////////////////////////////////////////////////////////////////////
void Output( ostream * output,                  // output file stream
	     float * array,                     // array of fields to output
	     unsigned int num_fields )          // number of fields
{
	if ( ! array )
	{
		* output << "Error: Invalid output" << endl;
		exit( 1 );
	}

	* output << * array;
	for ( float * ptr = array + 1;
	      ptr != array + num_fields;
	      ++ptr )
	{
		* output << "\t" << * ptr;
	}	
	* output << endl;
}

/////////////////////////////////////////////////////////////////////////
// count number of fields in a string delimeted by char * delimeters
/////////////////////////////////////////////////////////////////////////
unsigned int count_fields( string string_line,        // filename string 
		           const char * delimeters )  // tokens that delimit data fields
{
	unsigned int num_fields = 0;
	char * token;
	char * line;
	double values;

	token = strtok( ( char * )string_line.c_str(), delimeters );

	// grab all tokens in between delimeters
	// set index i to 1 because first iteration was above
	unsigned int i = 1;
	while ( ( token = strtok( NULL, delimeters ) ) != NULL )
	{
		++i;
	}

	return i;
}

/////////////////////////////////////////////////////////////////////////
// count number of fields in a string delimeted by char * delimeters 
/////////////////////////////////////////////////////////////////////////
unsigned int count_fields( ifstream * input,          // filename string 
		           const char * delimeters )  // tokens that delimit data fields
{
	unsigned int num_fields = 0;
	char * token;
	string string_line;
	double values;

	getline( * input, string_line );

	if ( ! string_line.size() )
	{
		cerr << "Error: Unable to get data from file" << endl;
		exit( 1 );
	}

	token = strtok( ( char * ) string_line.c_str(), delimeters );

	// grab all tokens in between delimeters
	// set index i to 1 because first iteration was above
	unsigned int i = 1;
	while ( ( token = strtok( NULL, delimeters ) ) != NULL )
	{
		++i;
	}

	// need this function bc seekg won't work if already at eof!
	input->clear();

	// seek to the beginning of the file
	input->seekg( 0, ios::beg );

	return i;
}

/////////////////////////////////////////////////////////////////////////
// count number of lines in a file
/////////////////////////////////////////////////////////////////////////
unsigned int count_lines( ifstream * input )        // input file pointer 
{
	unsigned int result = 0;
	string line;
	
	while ( !input->eof() )
	{
		getline( * input, line );
		result++;
	}

	// need this function bc seekg won't work if already at eof!
	input->clear();

	// seek to the beginning of the file
	input->seekg( ios::beg );

	return result - 1;
}

/////////////////////////////////////////////////////////////////////////
// collect data fields parsed from string using specified delimeters 
/////////////////////////////////////////////////////////////////////////
void parser( string string_to_parse,            // string of data to parse
	     const char * delimeters,           // tokens that delimit data fields
	     double * data,                      // container to put delimited data
	     unsigned int size )                // size of data fields
{
	char * token;

	char * line = strdup( string_to_parse.c_str() );

	if ( string_to_parse.empty() )
	{
		data = 0;
		return;
	}

	// grab first token
	token = strtok( line, delimeters );
	* data = atof( token );

	// grab all tokens in between delimeters
	// set index i to 1 because first iteration was above
	unsigned int i = 1;
	while ( ( token = strtok( NULL, delimeters ) ) != NULL && i < size )
	{
		* ( data + i ) = atof( token );
		++i;
	}

	delete [] line;
}

/////////////////////////////////////////////////////////////////////////
// collect data fields parsed from string using specified delimeters 
/////////////////////////////////////////////////////////////////////////
void parser( string string_to_parse,            // string of data to parse
	     const char * delimeters,           // tokens that delimit data fields
	     float * data,                      // container to put delimited data
	     unsigned int size )                // size of data fields
{
	char * token;

	char * line = strdup( string_to_parse.c_str() );

	if ( string_to_parse.empty() )
	{
		data = 0;
		return;
	}

	// grab first token
	token = strtok( line, delimeters );
	* data = atof( token );

	// grab all tokens in between delimeters
	// set index i to 1 because first iteration was above
	unsigned int i = 1;
	while ( ( token = strtok( NULL, delimeters ) ) != NULL && i < size )
	{
		* ( data + i ) = atof( token );
		++i;
	}

	delete [] line;
}

/////////////////////////////////////////////////////////////////////////
// collect data into a matrix from a file 
// - allocate 2D data matrix first, using countlines and countfields
// - this will also give rows and columns
/////////////////////////////////////////////////////////////////////////
void parser( ifstream * i_ptr,                  // input file 
             const char * delimeters,           // delimeters
             double ** data,                     // 2d matrix for data assumed to be properly formatted using countlines/countfields
             unsigned int rows,                 // rows
             unsigned int columns )             // columns
{
	string line;
	unsigned int count = 0;

	double * data_from_line = new double [ columns ];

	// get a line, parse the values, store maxes in temp 
	while ( ! ( i_ptr->eof() || count == rows ) )
	{
		// grab a line from each input file
		getline( * i_ptr, line );

		// check to make sure we have valid data
		if ( line.empty() )
			break;

		// parse char line for numeric data, and copy it to the matrix
		parser( line, delimeters, data_from_line, columns );		

		// copy data properly into data
		for ( int i = 0; i < columns; ++i ) data[ count ][ i ] = data_from_line[ i ];

		++count;
	}

	// clean up
	i_ptr->close();
	delete [] data_from_line;
}

/////////////////////////////////////////////////////////////////////////
// collect data into a matrix from a file 
// - allocate 2D data matrix first, using countlines and countfields
// - this will also give rows and columns
/////////////////////////////////////////////////////////////////////////
void parser( ifstream * i_ptr,                  // input file 
             const char * delimeters,           // delimeters
             float ** data,                     // 2d matrix for data assumed to be properly formatted using countlines/countfields
             unsigned int rows,                 // rows
             unsigned int columns )             // columns
{
	string line;
	unsigned int count = 0;

	double * data_from_line = new double [ columns ];

	// get a line, parse the values, store maxes in temp 
	while ( ! ( i_ptr->eof() || count == rows ) )
	{
		// grab a line from each input file
		getline( * i_ptr, line );

		// check to make sure we have valid data
		if ( line.empty() )
			break;

		// parse char line for numeric data, and copy it to the matrix
		parser( line, delimeters, data_from_line, columns );		

		// copy data properly into data
		for ( int i = 0; i < columns; ++i ) data[ count ][ i ] = data_from_line[ i ];

		++count;
	}

	// clean up
	i_ptr->close();
	delete [] data_from_line;
}

/////////////////////////////////////////////////////////////////////////
// collect data fields parsed from string using specified delimeters 
/////////////////////////////////////////////////////////////////////////
void Echo( ifstream * input, const char * delimeters, unsigned int size )
{ 	
	// temp vars: string for line, temp max, and values parsed from string
	string line; 
	double * values = new double [ size ]; 
	
	// intialize all values in the new'd arrays to zero
	for ( double * ptr = values;
	      ptr != values + size;
	      ++ptr )
	{
		* ptr = 0;
	}

	// get a line, parse the values, store maxes in temp 
	while ( !input->eof() )
	{
		getline( * input, line );

		if ( line.empty() )
			break;

		parser( line, delimeters, values, size );		

		if ( !values )
			break;

		for ( double * ptr = values;
		      ptr != values+ size;
		      ++ptr )
		{
			cout << * ptr << "\t";
		}
		cout << endl;

	}

	// seek to beginning of file.  Use clear function bc if at EOF, seek won't work!!!
	input->clear();
	input->seekg( 0, ios::beg );

	// clean up
	delete [] values;
}
