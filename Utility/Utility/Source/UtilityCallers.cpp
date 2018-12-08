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
#define WIN32_LEAN_AND_MEAN
#ifdef WIN32
#include <windows.h>
#endif // WIN32
#include "UtilityCallers.h"

// define "UTILITY_API_EXPORTS" from the command line in the project building this
// DLL.  DO NOT define it in the project that links to the DLL
#ifdef WIN32
        #ifdef UTILITY_API_EXPORTS
                #define UTILITY_API __declspec( dllexport )
                #define EXPORT_TEMPLATE
        #else
                #define UTILITY_API __declspec( dllimport )
                #define EXPORT_TEMPLATE extern
        #endif // UTILITY_API_EXPORTS
#else
        #define UTILITY_API_EXPORTS __attribute__( ( visibility( "default" ) ) )
        #define EXPORT_TEMPLATE
#endif // WIN32

//////////////////////////////////////////////////////////////////
// functionality to act on "naked" data, i.e. a double ** array
// with size information
//////////////////////////////////////////////////////////////////

// normalize with respect to ALL values in a 2D array, results range between 0 and 1
extern "C" UTILITY_API void PreprocessorNormalizeAll_0( double ** data, unsigned int rows, unsigned int cols )
{
	NormalizeAll_0( data, rows, cols );
}

// normalize with respect to ALL values in a 2D array, results range between -1 and 1
extern "C" UTILITY_API void PreprocessorNormalizeAll_1( double ** data, unsigned int rows, unsigned int cols )
{
	NormalizeAll_1( data, rows, cols );
}

// normalize from 0 to 1
extern "C" UTILITY_API void PreprocessorNormalizeByRow_0( double * data, unsigned int size )
{
	Normalize_0( data, size );
}

// normalize from -1 to 1
extern "C" UTILITY_API void PreprocessorNormalizeByRow_1( double * data, unsigned int size )
{
	Normalize_1( data, size );
}

// 1 if value is greater than previous, 0 else
extern "C" UTILITY_API void PreprocessorIncreasing_0( double * data, unsigned int size )
{
	Increasing_0( data, size );
}

extern "C" UTILITY_API void PreprocessorIncreasing_1( double * data, unsigned int size )
{
	Increasing_1( data, size );
}

// 0 if less than mean, 1 otherwise
extern "C" UTILITY_API void PreprocessorMean_0( double * data, unsigned int size )
{
	Mean_0( data, size );
}

extern "C" UTILITY_API void PreprocessorMean_1( double * data, unsigned int size )
{
	Mean_1( data, size );
}

extern "C" UTILITY_API void PreprocessorStdDev_0( double * data, unsigned int size )
{
	StdDev_0( data, size );
}

extern "C" UTILITY_API void PreprocessorStdDev_1( double * data, unsigned int size )
{
	StdDev_1( data, size );
}

// PSD normalized from [0,1]
extern "C" UTILITY_API void PreprocessorFourier_0( double * data, unsigned int size )
{
	Fourier_0( data, size );
}

// PSD normalized from [-1,1]
extern "C" UTILITY_API void PreprocessorFourier_1( double * data, unsigned int size )
{
	Fourier_1( data, size );
}

extern "C" UTILITY_API void PreprocessorSin_0( double * data, unsigned int size )
{
	Sin_0( data, size );
}

extern "C" UTILITY_API void PreprocessorSin_1( double * data, unsigned int size )
{
	Sin_1( data, size );
}

extern "C" UTILITY_API void PreprocessorCos_0( double * data, unsigned int size )
{
	Cos_0( data, size );
}

extern UTILITY_API "C" void PreprocessorCos_1( double * data, unsigned int size )
{
	Cos_1( data, size );
}

extern "C" UTILITY_API void PreprocessorBias( double * data, unsigned int size, double * return_data, unsigned int size_return, unsigned int node_size )
{
	Bias( data, size, return_data, size_return, node_size );
}

extern UTILITY_API void PreprocessorObjectBiasNode( Preprocessor * p_ptr, unsigned int node_size )
{
	p_ptr->Bias( node_size );
}

//////////////////////////////////////////////////////////////////
// Preprocessor function calls
//////////////////////////////////////////////////////////////////

extern "C" UTILITY_API Preprocessor * PreprocessorObjectConstructor( double ** data, unsigned int rows, unsigned int cols )
{
	return new Preprocessor( data, rows, cols );
}

extern "C" UTILITY_API Preprocessor * PreprocessorObjectFromDimensions( unsigned int rows, unsigned int cols )
{
	return new Preprocessor( rows, cols );
}

extern "C" UTILITY_API Preprocessor * PreprocessorObjectFromString( char * data, unsigned int rows, unsigned int cols )
{
	const int array_size = 8;
	char array[ array_size ];
	double ** double_data = new double * [ rows ];
	for ( unsigned int i = 0; i < rows; ++i )
	{
		* ( double_data + i ) = new double [ cols ];
	}

	int row_index = -1;
	for ( unsigned int i = 0; i < rows * cols; ++i )
	{
		array[ 0 ] = data[ array_size * i + 0 ];
		array[ 1 ] = data[ array_size * i + 1 ];
		array[ 2 ] = data[ array_size * i + 2 ];
		array[ 3 ] = data[ array_size * i + 3 ];
		array[ 4 ] = data[ array_size * i + 4 ];
		array[ 5 ] = data[ array_size * i + 5 ];
		array[ 6 ] = data[ array_size * i + 6 ];
		array[ 7 ] = data[ array_size * i + 7 ];
		if ( i % cols == 0 )
			++row_index;
		double_data[ row_index ][ i % cols ] = * ( double * ) ( char * ) array;
	}

	Preprocessor * return_value = new Preprocessor( double_data, rows, cols );

	for ( unsigned int i = 0; i < rows; ++i )
	{
		delete [] double_data[ i ];	
	}
	delete [] double_data;

	return return_value;
}

extern "C" UTILITY_API Preprocessor * PreprocessorObjectConstructorFromFile( const char * filename, const char * tokens )
{
	return new Preprocessor( filename, tokens );
}

extern "C" UTILITY_API Preprocessor * PreprocessorObjectFileConstructor( const char * filename )
{
	return new Preprocessor( filename, ",;:\t " );
}

extern "C" UTILITY_API void PreprocessorObjectDestructor( Preprocessor * p_ptr )
{
	delete p_ptr;
}

extern "C" UTILITY_API unsigned int PreprocessorObjectRows( Preprocessor * p_ptr )
{
	return p_ptr->GetRows();
}

extern "C" UTILITY_API unsigned int PreprocessorObjectCols( Preprocessor * p_ptr )
{
	return p_ptr->GetCols();
}

extern "C" UTILITY_API double ** PreprocessorObjectGetData( Preprocessor * p_ptr )
{
	return p_ptr->GetData();
}

extern "C" UTILITY_API void PreprocessorObjectPrint( Preprocessor * p_ptr )
{
	cout << * p_ptr;
}

//////////////////////////////////////////////////////////////////
// function wrappers for preprocessor class
//////////////////////////////////////////////////////////////////

extern "C" UTILITY_API void PreprocessorObjectNormalizeAll_0( Preprocessor * p_ptr )
{
	p_ptr->NormalizeAll_0();
}

extern "C" UTILITY_API void PreprocessorObjectNormalizeAll_1( Preprocessor * p_ptr )
{
	p_ptr->NormalizeAll_1();
}

extern "C" UTILITY_API void PreprocessorObjectNormalizeByRow_0( Preprocessor * p_ptr )
{
	p_ptr->NormalizeByRow_0();
}

extern "C" UTILITY_API void PreprocessorObjectNormalizeByRow_1( Preprocessor * p_ptr )
{
	p_ptr->NormalizeByRow_1();
}

extern "C" UTILITY_API void PreprocessorObjectNormalizeByCol_0( Preprocessor * p_ptr )
{
	p_ptr->NormalizeByColumn_0();
}

extern "C" UTILITY_API void PreprocessorObjectNormalizeByCol_1( Preprocessor * p_ptr )
{
	p_ptr->NormalizeByColumn_1();
}

extern "C" UTILITY_API void PreprocessorObjectIncreasing_0( Preprocessor * p_ptr )
{
	p_ptr->Increasing_0();
}

extern "C" UTILITY_API void PreprocessorObjectIncreasing_1( Preprocessor * p_ptr )
{
	p_ptr->Increasing_1();
}

extern "C" UTILITY_API void PreprocessorObjectMean_0( Preprocessor * p_ptr )
{
	p_ptr->Mean_0();
}

extern "C" UTILITY_API void PreprocessorObjectMean_1( Preprocessor * p_ptr )
{
	p_ptr->Mean_1();
}

extern "C" UTILITY_API void PreprocessorObjectStdDev_0( Preprocessor * p_ptr )
{
	p_ptr->StdDev_0();
}

extern "C" UTILITY_API void PreprocessorObjectStdDev_1( Preprocessor * p_ptr )
{
	p_ptr->StdDev_1();
}

extern "C" UTILITY_API void PreprocessorObjectFourier_0( Preprocessor * p_ptr )
{
	p_ptr->Fourier_0();
}

extern "C" UTILITY_API void PreprocessorObjectFourier_1( Preprocessor * p_ptr )
{
	p_ptr->Fourier_1();
}

extern "C" UTILITY_API void PreprocessorObjectBias( Preprocessor * p_ptr )
{
	p_ptr->Bias();
}

extern UTILITY_API void PreprocessorObjectSin_0( Preprocessor * p_ptr )
{
	p_ptr->Sin_0();
}

extern UTILITY_API void PreprocessorObjectSin_1( Preprocessor * p_ptr )
{
	p_ptr->Sin_1();
}

extern UTILITY_API void PreprocessorObjectCos_0( Preprocessor * p_ptr )
{
	p_ptr->Cos_0();
}

extern UTILITY_API void PreprocessorObjectCos_1( Preprocessor * p_ptr )
{
	p_ptr->Cos_1();
}

extern UTILITY_API void PreprocessorObjectPlusEq( Preprocessor * p_ptr1, Preprocessor * p_ptr2 )
{
	* p_ptr1 += * p_ptr2;
}

extern UTILITY_API void PreprocessorObjectFlatten( Preprocessor * p_ptr, double * data, unsigned int size )
{
	p_ptr->Flatten( data, size );
}

extern UTILITY_API void PreprocessorObjectFlattenPreprocessor( Preprocessor * p_ptr )
{
	p_ptr->Flatten();
}

extern UTILITY_API unsigned int PreprocessorObjectSize( Preprocessor * p_ptr )
{
	return p_ptr->Size();
}
