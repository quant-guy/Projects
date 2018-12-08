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
#include "Statistics.h"

/////////////////////////////////////////////////////////////////////////
// Calculate max values in a 2 d array.  The result will be an array
// of size "columns"
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void Max( double ** input, 
                                 double * max, 
                                 const unsigned int & rows, 
                                 const unsigned int & columns )
{ 	
	// temp vars: string for line, temp max, and values parsed from string
	double * temp = new double [ columns ]; 
	
	// intialize all values in the new'd arrays to zero
	for ( double * ptr = temp;
	      ptr != temp + columns;
	      ++ptr )
	{
		* ptr = 0;
	}

	// get a line, parse the values, store maxes in temp 
	for ( double ** outer_ptr = input;
              outer_ptr != input + rows;
              ++outer_ptr )
	{
		double * d_ptr = temp;
		for ( double * inner_ptr = * outer_ptr;
		      inner_ptr != ( * outer_ptr ) + columns;
		      ++inner_ptr,
		      ++d_ptr )
		{
			// store value into temp if value > temp
			if ( * d_ptr < * inner_ptr )
			{
				* d_ptr = * inner_ptr;
			}
		}
	}

	copy( temp, temp + columns, max );

	// clean up
	delete [] temp;
}

/////////////////////////////////////////////////////////////////////////
// Calculate min values in a 2 d array.  The result will be an array
// of size "columns"
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void Min( double ** input, 
                                 double * min, 
                                 const unsigned int & rows, 
                                 const unsigned int & columns )
{ 	
	// temp vars: string for line, temp max, and values parsed from string
	double * temp = new double [ columns ]; 
	
	// intialize all values in the new'd arrays to the fist values in the row
	double ** i_ptr = input;
	for ( double * ptr = temp;
	      ptr != temp + columns;
	      ++ptr,
              ++i_ptr )
	{
		* ptr = ** ( i_ptr );
	}

	// get a line, parse the values, store mins in temp 
	for ( double ** outer_ptr = input;
              outer_ptr != input + rows;
              ++outer_ptr )
	{
		double * d_ptr = temp;
		for ( double * inner_ptr = * outer_ptr;
		      inner_ptr != ( * outer_ptr ) + columns;
		      ++inner_ptr,
		      ++d_ptr )
		{
			// store value into temp if value < temp
			if ( * d_ptr > * inner_ptr )
			{
				* d_ptr = * inner_ptr;
			}
		}
	}

	// copy values into result array
	copy( temp, temp + columns, min );

	// clean up
	delete [] temp;
}

/////////////////////////////////////////////////////////////////////////
// Calculate mean values in a 2 d array.  The result will be an array
// of size "columns"
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void Mean( double ** input, 
                                  double * mean, 
                                  const unsigned int & rows, 
                                  const unsigned int & columns )
{ 	
	// temp vars: string for line, temp mean, and values parsed from string
	double * temp = new double [ columns ]; 

	// initialize variable for double version of rows for use in the mean later
	double double_rows = ( double ) rows;
	
	// intialize all values in the new'd arrays to zero
	for ( double * t_ptr = temp;
	      t_ptr != temp + columns;
	      ++t_ptr )
	{
		* t_ptr = 0;
	}

	// sum all the rows 
	for ( double ** outer_ptr = input;
              outer_ptr != input + rows;
              ++outer_ptr )
	{
		double * d_ptr = temp;
		for ( double * inner_ptr = * outer_ptr;
		      inner_ptr != ( * outer_ptr ) + columns;
		      ++inner_ptr,
		      ++d_ptr )
		{
			* d_ptr += * inner_ptr;
		}
	}

	// divide temp by number of lines, and store result in mean array
	for ( double * ptr = temp;
	      ptr != temp + columns;
	      ++ptr )
	{
		* ptr /= double_rows;
	}

	// copy result into output array
	copy( temp, temp + columns, mean );

	// clean up
	delete [] temp;
}

/////////////////////////////////////////////////////////////////////////
// Calculate standard deviation of values in a 2 d array.  The result 
// will be an array of size "columns"
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void StandardDeviation( double ** input, 
                                               double * std_dev, 
                                               const unsigned int & rows, 
                                               const unsigned int & columns )
{
	// temp vars: string for line, mean, temp stddev, and values parsed from string
	double * temp   = new double [ columns ]; 
	double * mean   = new double [ columns ]; 
	double divisor = ( double ) ( rows - 1 );
	
	// intialize all values in the new'd arrays to zero
	double * m_ptr = mean;
	for ( double * t_ptr = temp;
	      t_ptr != temp + columns;
	      ++t_ptr,
	      ++m_ptr )
	{
		* t_ptr = 0.0;
		* m_ptr = 0.0;
	}

	// calculate mean, we need this for the standard deviation calculation
	Mean( input, mean, rows, columns );

	// sum all the rows 
	for ( double ** outer_ptr = input;
              outer_ptr != input + rows;
              ++outer_ptr )
	{
		double * m_ptr = mean;
		double * t_ptr = temp;
		for ( double * inner_ptr = * outer_ptr;
		      inner_ptr != ( * outer_ptr ) + columns;
		      ++inner_ptr,
                      ++t_ptr,
		      ++m_ptr )
		{
			* t_ptr += ( * inner_ptr - * m_ptr ) * ( * inner_ptr - * m_ptr );
		}
	}

	double temp_value = 0;
	for ( double * t_ptr = temp; 
	      t_ptr != temp + columns;
	      ++t_ptr )
	{
		temp_value = ( * t_ptr / divisor );
		* t_ptr = pow( temp_value, 0.5 ) ;
	}

	copy( temp, temp + columns, std_dev );

	// clean up
	delete [] mean;
	delete [] temp;
}

/////////////////////////////////////////////////////////////////////////
// Calculate covariance of values in a file, take input file or stdin as input
// write output to an array of doubles
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void Covariance( double ** input,                 // input matrix, dimensions: rows by columns
                                        double ** covariance,            // covariance matrix, dimensions: columns by columns
                                        const unsigned int & rows,      // rows
                                        const unsigned int & columns )  // columns
{
	// temp vars: string for line, mean, temp stddev, and values parsed from string
	double * temp = new double [ columns ]; 
	double * mean = new double [ columns ]; 

	// number by which to divide covariance entry after after initial computation
	double divisor = ( ( double ) ( rows ) );

	// calculate mean, we need this for the standard deviation calculation
	Mean( input, mean, rows, columns );
	
	// intialize all values in the new'd arrays to zero
	for ( double * ptr = temp;
	      ptr != temp + columns;
	      ++ptr )
	{
		* ptr = 0;
	}

	double temp_value  = 0.0;
	double interchange = 0.0;
	for ( unsigned int i = 0; i < columns; ++i )
	{
		temp_value = 0.0;
		for ( unsigned int j = i; j < columns; ++j )
		{
			for ( int k = 0; k < rows; ++k )
			{
				temp_value += ( ( ( * ( * ( input + i ) + k ) ) - * ( mean + i ) ) *
                                                  ( * ( * ( input + j ) + k ) ) - * ( mean + j ) );
			}

			* ( * ( covariance + i ) + j ) = temp_value / divisor;

			* ( * ( covariance + j ) + i ) = * ( * ( covariance + i ) + j );
		}
	}

	// clean up
	delete [] mean;
	delete [] temp;
}

/////////////////////////////////////////////////////////////////////////
// Calculate covariance of values in a file, centered about the mean,
// take input file or stdin as input, write output to an array of doubles 
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void MeanCenteredCovariance( double ** input,                 // input matrix, dimensions: rows by columns
                                                    double ** covariance,            // covariance matrix, dimensions: columns by columns
                                                    const unsigned int & rows,      // rows
                                                    const unsigned int & columns )  // columns

{
	// allocate space for mean values
	double * mean = new double [ rows ];

	// instantiate new 2d array to hold mean centered input
	double ** mean_centered_input = new double * [ rows ];
	for ( double ** m_ptr = mean_centered_input;
              m_ptr < mean_centered_input + rows;
              ++m_ptr )
	{
		* m_ptr = new double [ columns ];
	}

	// determine mean values
	Mean( input, mean, rows, columns );

	// input about the mean and place those values into the mean_centered_input array
	double ** input_outer_ptr = input;
	for ( double ** outer_ptr = mean_centered_input;
              outer_ptr < mean_centered_input + rows;
              ++outer_ptr,
              ++input_outer_ptr )
	{
		double * input_inner_ptr = * input_outer_ptr;
		double * m_ptr = mean;
		for ( double * inner_ptr = * outer_ptr;
                      inner_ptr < ( * outer_ptr ) + columns;
                      ++inner_ptr,
                      ++input_inner_ptr,
                      ++m_ptr )
		{
			* inner_ptr = ( ( * input_inner_ptr ) - ( * ( m_ptr ) ) );
		}
	}

	// find mean centered covariance.  Use covariance function, but with mean_centered_covariance
	// array as input
	Covariance( mean_centered_input, covariance, rows, columns );

	// clean up
	delete [] mean;
	for ( double ** m_ptr = mean_centered_input;
              m_ptr < mean_centered_input + rows;
              ++m_ptr )
	{
		delete [] * m_ptr;
	}
}

/////////////////////////////////////////////////////////////////////////
// Calculate correlation of values in a file, take input file or stdin as input
// write output to an array of doubles
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void Correlation( double ** input,                 // input matrix, dimensions: rows by columns
                                         double ** correlation,           // correlation matrix, dimensions: columns by columns
                                         const unsigned int & rows,      // rows
                                         const unsigned int & columns )  // columns
{
	// temp vars: string for line, mean, temp stddev, and values parsed from string
	double * temp    = new double [ columns ]; 
	double * mean    = new double [ columns ]; 
	double * std_dev = new double [ columns ]; 

	// number by which to divide covariance entry after after initial computation
	double divisor = ( ( double ) ( rows ) );

	// calculate mean, we need this for the standard deviation calculation
	Mean( input, mean, rows, columns );

	// calculate standard deviation
	StandardDeviation( input, std_dev, rows, columns );
	
	// intialize all values in the new'd arrays to zero
	for ( double * ptr = temp;
	      ptr != temp + columns;
	      ++ptr )
	{
		* ptr = 0;
	}

	double temp_value  = 0.0;
	double interchange = 0.0;
	for ( unsigned int i = 0; i < columns; ++i )
	{
		temp_value = 0.0;
		for ( unsigned int j = i; j < columns; ++j )
		{
			for ( int k = 0; k < rows; ++k )
			{
				temp_value += ( ( ( * ( * ( input + i ) + k ) ) - * ( mean + i ) ) *
                                                  ( * ( * ( input + j ) + k ) ) - * ( mean + j ) );
			}

			* ( * ( correlation + i ) + j ) = temp_value / ( divisor * * ( std_dev + i ) * * ( std_dev + j ) );
			* ( * ( correlation + j ) + i ) = * ( * ( correlation + i ) + j );
		}
	}

	// clean up
	delete [] mean;
	delete [] temp;
	delete [] std_dev;
}

/////////////////////////////////////////////////////////////////////////
// Calculate correlation of values in a file, centered about the mean,
// take input file or stdin as input, write output to an array of doubles 
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void MeanCenteredCorrelation( double ** input,                 // input matrix, dimensions: rows by columns
                                                     double ** correlation,           // correlation matrix, dimensions: columns by columns
                                                     const unsigned int & rows,      // rows
                                                     const unsigned int & columns )  // columns

{
	// allocate space for mean values
	double * mean = new double [ rows ];

	// instantiate new 2d array to hold mean centered input
	double ** mean_centered_input = new double * [ rows ];
	for ( double ** m_ptr = mean_centered_input;
              m_ptr < mean_centered_input + rows;
              ++m_ptr )
	{
		* m_ptr = new double [ columns ];
	}

	// determine mean values
	Mean( input, mean, rows, columns );

	// input about the mean and place those values into the mean_centered_input array
	double ** input_outer_ptr = input;
	for ( double ** outer_ptr = mean_centered_input;
              outer_ptr < mean_centered_input + rows;
              ++outer_ptr,
              ++input_outer_ptr )
	{
		double * input_inner_ptr = * input_outer_ptr;
		double * m_ptr = mean;
		for ( double * inner_ptr = * outer_ptr;
                      inner_ptr < ( * outer_ptr ) + columns;
                      ++inner_ptr,
                      ++input_inner_ptr,
                      ++m_ptr )
		{
			* inner_ptr = ( ( * input_inner_ptr ) - ( * ( m_ptr ) ) );
		}
	}

	// find mean centered covariance.  Use covariance function, but with mean_centered_covariance
	// array as input
	Correlation( mean_centered_input, correlation, rows, columns );

	// clean up
	delete [] mean;
	for ( double ** m_ptr = mean_centered_input;
              m_ptr < mean_centered_input + rows;
              ++m_ptr )
	{
		delete [] * m_ptr;
	}
}

/////////////////////////////////////////////////////////////////////////
// Normalize 2D array with respect to absolute max and min values
// in all the array.  Results should be in [0,1]
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void Normalize1( double ** input,
                                        const unsigned int & rows, 
                                        const unsigned int & columns )
{
	// instantiate new matrix for max values
	double max = 0;
	double min = 0;
	double * max_min = new double [ columns ];

	// find min of mins
	Min( input, max_min, rows, columns );
	min = * ( max_min + 0 );
	for ( unsigned int i = 0; i < columns; ++i )
	{
		if ( min > * ( max_min + i ) )
			min = * ( max_min + i );
	}

	// find max of maxs 
	Max( input, max_min, rows, columns );
	max = * ( max_min + 0 );
	for ( unsigned int i = 0; i < columns; ++i )
	{
		if ( max < * ( max_min + i ) )
			max = * ( max_min + i );
	}
	// do the normalization
	for ( double ** input_outer_ptr = input;
              input_outer_ptr < input + rows;
              ++input_outer_ptr )
	{
		for ( double * input_inner_ptr = * input_outer_ptr;
                      input_inner_ptr < ( * input_outer_ptr ) + columns;
                      ++input_inner_ptr )
		{
			* input_inner_ptr -= min;
			* input_inner_ptr /= ( max - min );
		}
	}
}
 
/////////////////////////////////////////////////////////////////////////
// Normalize 2D array with respect to absolute max and min values
// in all the array.  Results should be in [-1,1]
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void Normalize2( double ** input,
                                        const unsigned int & rows, 
                                        const unsigned int & columns )
{
	// instantiate new matrix for max values
	double max = 0;
	double min = 0;
	double * max_min = new double [ columns ];

	// find min of mins
	Min( input, max_min, rows, columns );
	min = * ( max_min + 0 );
	for ( unsigned int i = 0; i < columns; ++i )
	{
		if ( min > * ( max_min + i ) )
			min = * ( max_min + i );
	}

	// find max of maxs 
	Max( input, max_min, rows, columns );
	max = * ( max_min + 0 );
	for ( unsigned int i = 0; i < columns; ++i )
	{
		if ( max < * ( max_min + i ) )
			max = * ( max_min + i );
	}

	// do the normalization
	for ( double ** input_outer_ptr = input;
              input_outer_ptr < input + rows;
              ++input_outer_ptr )
	{
		for ( double * input_inner_ptr = * input_outer_ptr;
                      input_inner_ptr < ( * input_outer_ptr ) + columns;
                      ++input_inner_ptr )
		{
			* input_inner_ptr -= min;
			* input_inner_ptr /= ( max - min );
			* input_inner_ptr = 2.0 * ( * input_inner_ptr ) - 1.0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////
// Normalize 2d array by maximum values in a *column*.  Scale values by
// min.
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void NormalizeByColumn( double ** input,
                                               const unsigned int & rows, 
                                               const unsigned int & columns )
{
	// instantiate new matrix for max values
	double * max_min = new double [ columns ];

	// find min values by *column*
	Min( input, max_min, rows, columns );

	// scale all values by mins
	for ( double ** input_outer_ptr = input;
              input_outer_ptr < input + rows;
              ++input_outer_ptr )
	{
		double * m_ptr = max_min;
		for ( double * input_inner_ptr = * input_outer_ptr;
                      input_inner_ptr < ( * input_outer_ptr ) + columns;
                      ++input_inner_ptr,
                      ++m_ptr )
		{
			* input_inner_ptr -= * m_ptr;
		}
	}

	// find max values by *column*
	Max( input, max_min, rows, columns );

	// adjust element by its respective max
	for ( double ** input_outer_ptr = input;
              input_outer_ptr < input + rows;
              ++input_outer_ptr )
	{
		double * m_ptr = max_min;
			for ( double * input_inner_ptr = * input_outer_ptr;
			      input_inner_ptr < ( * input_outer_ptr ) + columns;
			      ++input_inner_ptr,
			      ++m_ptr )
			{
				if ( * m_ptr != 0.0f )
				{
					* input_inner_ptr /= * m_ptr;
				}
			}
	}

	// clean up
	delete [] max_min;
}

/////////////////////////////////////////////////////////////////////////
// Normalize 2d array by maximum values in a *row*.  Scale values by min.
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void NormalizeByRow( double ** input, 
                                            const unsigned int & rows, 
                                            const unsigned int & columns )
{
	// variable for max value
	double max_min = 0;

	// adjust element by its respective max, after scaling by min
	for ( double ** input_outer_ptr = input;
              input_outer_ptr < input + rows;
              ++input_outer_ptr )
	{
		// find minimum value in row
		max_min = ** input_outer_ptr;
		for ( double * input_inner_ptr = ( * input_outer_ptr ) + 1;
                      input_inner_ptr < ( * input_outer_ptr ) + columns;
                      ++input_inner_ptr )
		{
			if ( * input_inner_ptr < max_min )
			{
				max_min = * input_inner_ptr;
			}
		}		

		// translate row by minimum value
		if ( max_min != 0.0f )
		{
			for ( double * input_inner_ptr = * input_outer_ptr;
			      input_inner_ptr < ( * input_outer_ptr ) + columns;
			      ++input_inner_ptr )
			{
				* input_inner_ptr -= max_min;
			}
		}

		// find maximum value in row
		max_min = ** input_outer_ptr;
		for ( double * input_inner_ptr = ( * input_outer_ptr ) + 1;
                      input_inner_ptr < ( * input_outer_ptr ) + columns;
                      ++input_inner_ptr )
		{
			if ( * input_inner_ptr > max_min )
			{
				max_min = * input_inner_ptr;
			}
		}

		// normalize row by max value in row
		if ( max_min != 0.0f )
		{
			for ( double * input_inner_ptr = * input_outer_ptr;
			      input_inner_ptr < ( * input_outer_ptr ) + columns;
			      ++input_inner_ptr )
			{
				
				* input_inner_ptr /= max_min;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////
// Normalize 2d array by maximum values in a *column*.  Do not scale
// values.
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void NormalizeByColumn2( double ** input,
                                                const unsigned int & rows, 
                                                const unsigned int & columns )
{
	// instantiate new matrix for max values
	double * max = new double [ columns ];

	// find max values by *column*
	Max( input, max, rows, columns );

	// adjust element by its respective max
	for ( double ** input_outer_ptr = input;
              input_outer_ptr < input + rows;
              ++input_outer_ptr )
	{
		double * m_ptr = max;
		for ( double * input_inner_ptr = * input_outer_ptr;
                      input_inner_ptr < ( * input_outer_ptr ) + columns;
                      ++input_inner_ptr,
                      ++m_ptr )
		{
			* input_inner_ptr /= * m_ptr;
		}
	}

	// clean up
	delete [] max;
}

/////////////////////////////////////////////////////////////////////////
// Normalize 2d array by maximum values in a *row*.  Do not scale values.
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API  void NormalizeByRow2( double ** input, 
                                             const unsigned int & rows, 
                                             const unsigned int & columns )
{
	// variable for max value
	double max = 0;

	// adjust element by its respective max
	for ( double ** input_outer_ptr = input;
              input_outer_ptr < input + rows;
              ++input_outer_ptr )
	{
		max = ** input_outer_ptr;
		for ( double * input_inner_ptr = ( * input_outer_ptr ) + 1;
                      input_inner_ptr < ( * input_outer_ptr ) + columns;
                      ++input_inner_ptr )
		{
			if ( * input_inner_ptr > max )
			{
				max = * input_inner_ptr;
			}
		}

		for ( double * input_inner_ptr = * input_outer_ptr;
                      input_inner_ptr < ( * input_outer_ptr ) + columns;
                      ++input_inner_ptr )
		{
			* input_inner_ptr /= max;
		}
	}
}
