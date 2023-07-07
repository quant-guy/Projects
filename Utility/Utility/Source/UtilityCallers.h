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
#ifndef UTILITY_CALLERS_H
#define UTILITY_CALLERS_H

#include "Preprocessor.hpp"

#ifndef WIN32
#define UTILITY_API
#endif // WIN32

#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus

using namespace preprocessor;

//////////////////////////////////////////////////////////////////
// verify data set is 'sane'
//////////////////////////////////////////////////////////////////

extern UTILITY_API void CheckData( const char * );

//////////////////////////////////////////////////////////////////
// functionality to act on "naked" data, i.e. a double ** array
// with size information
//////////////////////////////////////////////////////////////////

extern UTILITY_API void PreprocessorNormalizeAll_0( double **, unsigned int, unsigned int );

extern UTILITY_API void PreprocessorNormalizeAll_1( double **, unsigned int, unsigned int );

extern UTILITY_API void PreprocessorNormalizeByRow_0( double *, unsigned int );

extern UTILITY_API void PreprocessorNormalizeByRow_1( double *, unsigned int );

extern UTILITY_API void PreprocessorIncreasing_0( double *, unsigned int );

extern UTILITY_API void PreprocessorIncreasing_1( double *, unsigned int );

extern UTILITY_API void PreprocessorMean_0( double *, unsigned int );

extern UTILITY_API void PreprocessorMean_1( double *, unsigned int );

extern UTILITY_API void PreprocessorStdDev_0( double *, unsigned int );

extern UTILITY_API void PreprocessorStdDev_1( double *, unsigned int );

extern UTILITY_API void PreprocessorFourier_0( double *, unsigned int );

extern UTILITY_API void PreprocessorFourier_1( double *, unsigned int );

extern UTILITY_API void PreprocessorSin_0( double *, unsigned int );

extern UTILITY_API void PreprocessorSin_1( double *, unsigned int );

extern UTILITY_API void PreprocessorCos_0( double *, unsigned int );

extern UTILITY_API void PreprocessorCos_1( double *, unsigned int );

extern UTILITY_API void PreprocessorBias( double *, unsigned int, double *, unsigned int, unsigned int );

//////////////////////////////////////////////////////////////////
// Preprocessor function calls
//////////////////////////////////////////////////////////////////

extern UTILITY_API Preprocessor * PreprocessorObjectConstructor( double **, unsigned int, unsigned int );

extern UTILITY_API Preprocessor * PreprocessorObjectFromDimensions( unsigned int, unsigned int );

extern UTILITY_API Preprocessor * PreprocessorObjectFromString( char *, unsigned int , unsigned int );

extern UTILITY_API Preprocessor * PreprocessorObjectConstructorFromFile( const char *, const char * );

extern UTILITY_API Preprocessor * PreprocessorObjectFileConstructor( const char * );

extern UTILITY_API void PreprocessorObjectDestructor( Preprocessor * );

extern UTILITY_API unsigned int PreprocessorObjectRows( Preprocessor * );

extern UTILITY_API unsigned int PreprocessorObjectCols( Preprocessor * );

extern UTILITY_API double ** PreprocessorObjectGetData( Preprocessor * );

extern UTILITY_API void PreprocessorObjectPrint( Preprocessor * );

//////////////////////////////////////////////////////////////////
// function wrappers for preprocessor class
//////////////////////////////////////////////////////////////////

extern UTILITY_API void PreprocessorObjectNormalizeAll_0( Preprocessor * );

extern UTILITY_API void PreprocessorObjectNormalizeAll_1( Preprocessor * );

extern UTILITY_API void PreprocessorObjectNormalizeByRow_0( Preprocessor * );

extern UTILITY_API void PreprocessorObjectNormalizeByRow_1( Preprocessor * );

extern UTILITY_API void PreprocessorObjectNormalizeByCol_0( Preprocessor * );

extern UTILITY_API void PreprocessorObjectNormalizeyCol_1( Preprocessor * );

extern UTILITY_API void PreprocessorObjectIncreasing_0( Preprocessor * );

extern UTILITY_API void PreprocessorObjectIncreasing_1( Preprocessor * );

extern UTILITY_API void PreprocessorObjectMean_0( Preprocessor * );

extern UTILITY_API void PreprocessorObjectMean_1( Preprocessor * );

extern UTILITY_API void PreprocessorObjectStdDev_0( Preprocessor * );

extern UTILITY_API void PreprocessorObjectStdDev_1( Preprocessor * );

extern UTILITY_API void PreprocessorObjectFourier_0( Preprocessor * );

extern UTILITY_API void PreprocessorObjectFourier_1( Preprocessor * );

extern UTILITY_API void PreprocessorObjectSin_0( Preprocessor * );

extern UTILITY_API void PreprocessorObjectSin_1( Preprocessor * );

extern UTILITY_API void PreprocessorObjectCos_0( Preprocessor * );

extern UTILITY_API void PreprocessorObjectCos_1( Preprocessor * );

extern UTILITY_API void PreprocessorObjectPlusEq( Preprocessor *, Preprocessor * );

extern UTILITY_API void PreprocessorObjectBias( Preprocessor * );

extern UTILITY_API void PreprocessorObjectBiasNode( Preprocessor *, unsigned int );

extern UTILITY_API void PreprocessorObjectFlatten( Preprocessor *, double *, unsigned int );

extern UTILITY_API void PreprocessorObjectFlattenPreprocessor( Preprocessor * );

extern UTILITY_API unsigned int PreprocessorObjectSize( Preprocessor * );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UTILITY_CALLERS_H
