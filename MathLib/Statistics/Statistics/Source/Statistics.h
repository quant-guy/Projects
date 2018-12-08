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
#ifndef STATISTICS_H
#define STATISTICS_H

#ifdef WIN32
#include <windows.h>
#else
#define STATISTICS_API
#endif // WIN32

#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>

// define "STATISTICS_API_EXPORTS" from the command line in the project building this
// DLL.  DO NOT define it in the project that links to the DLL
#ifdef WIN32
	#ifdef STATISTICS_API_EXPORTS
		#define STATISTICS_API __declspec( dllexport )
		#define EXPORT_TEMPLATE
	#else
		#define STATISTICS_API __declspec( dllimport )
		#define EXPORT_TEMPLATE extern
	#endif // STATISTICS_API_EXPORTS
#else
	#define STATISTICS_API_EXPORTS __attribute__( ( visibility( "default" ) ) )
	#define EXPORT_TEMPLATE
#endif // WIN32

#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus

using namespace std;

/////////////////////////////////////////////////////////////////////////
// Calculate max values in a 2 d array.  The result will be an array
// of size "columns"
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void Max( double **,                                 // input values
                                double * ,                                 // container for results
                                const unsigned int &,                     // rows
                                const unsigned int & );                   // columns

/////////////////////////////////////////////////////////////////////////
// Calculate min values in a 2 d array.  The result will be an array
// of size "columns"
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void Min( double **,                                 // input values
                                double *,                                  // container for results
                                const unsigned int &,                     // rows
                                const unsigned int & );                   // columns

/////////////////////////////////////////////////////////////////////////
// Calculate mean values in a 2 d array.  The result will be an array
// of size "columns"
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void Mean( double **,                                // input values
                                 double *,                                 // container for results
                                 const unsigned int &,                    // rows
                                 const unsigned int &);                   // columns

/////////////////////////////////////////////////////////////////////////
// Calculate standard deviation of values in a 2 d array.  The result 
// will be an array of size "columns"
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void StandardDeviation( double **,                   // input values          
                                              double *,                    // container for results
                                              const unsigned int &,       // rows
                                              const unsigned int & );     // columns

/////////////////////////////////////////////////////////////////////////
// Find covariance of a 2D array.  Array dimensions are rows by columns,
// covariance dimensions are columns by columns
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void Covariance( double **,                          // input matrix, dimensions: rows by columns
                                       double **,                          // covariance matrix, dimensions: columns by columns
                                       const unsigned int &,              // rows
                                       const unsigned int & );            // columns

/////////////////////////////////////////////////////////////////////////
// Find mean centered covariance of a 2D array.  Array dimensions are 
// rows by columns, covariance dimensions are columns by columns.
// - center the input first, then call the covariance function
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void MeanCenteredCovariance( double **,              // input matrix, dimensions: rows by columns
                                                   double **,              // covariance matrix, dimensions: columns by columns
                                                   const unsigned int &,  // rows
                                                   const unsigned int & );// columns

/////////////////////////////////////////////////////////////////////////
// Find correlation of a 2D array.  Array dimensions are rows by columns,
// correlation dimensions are columns by columns
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void Correlation( double **,                          // input matrix, dimensions: rows by columns
                                        double **,                          // correlation matrix, dimensions: columns by columns
                                        const unsigned int &,              // rows
                                        const unsigned int & );            // columns

/////////////////////////////////////////////////////////////////////////
// Find mean centered correlation of a 2D array.  Array dimensions are 
// rows by columns, correlation dimensions are columns by columns.
// - center the input first, then call the correlation function
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void MeanCenteredCorrelation( double **,              // input matrix, dimensions: rows by columns
                                                    double **,              // correlation matrix, dimensions: columns by columns
                                                    const unsigned int &,  // rows
                                                    const unsigned int & );// columns

/////////////////////////////////////////////////////////////////////////
// Normalize 2D array with respect to absolute max and min values
// in all the array
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void Normalize1( double **, const unsigned int &, const unsigned int & );

/////////////////////////////////////////////////////////////////////////
// Normalize 2D array with respect to absolute max and min values
// in all the array
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void Normalize2( double **, const unsigned int &, const unsigned int & );

/////////////////////////////////////////////////////////////////////////
// Normalize 2d array by maximum values in a *column*.  Scale values by
// min
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void NormalizeByColumn( double **, const unsigned int &, const unsigned int & );

/////////////////////////////////////////////////////////////////////////
// Normalize 2d array by maximum values in a *row*.  Scale values by min
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void NormalizeByRow( double **, const unsigned int &, const unsigned int & );

/////////////////////////////////////////////////////////////////////////
// Normalize 2d array by maximum values in a *column*.  Do not scale.
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void NormalizeByColumn2( double **, const unsigned int &, const unsigned int & );

/////////////////////////////////////////////////////////////////////////
// Normalize 2d array by maximum values in a *row*.  Do not scale.
/////////////////////////////////////////////////////////////////////////
extern STATISTICS_API void NormalizeByRow2( double **, const unsigned int &, const unsigned int & );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // STATISTICS_H
