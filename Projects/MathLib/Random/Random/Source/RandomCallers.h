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
#ifndef MATHLIB_LIBRANDOM_H
#define MATHLIB_LIBRANDOM_H

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#define RANDOM_API
#endif // WIN32

#include "Random.hpp"

// define "RANDOM_API_EXPORTS" from the command line in the project building this
// DLL.  DO NOT define it in the project that links to the DLL
#ifdef WIN32
        #ifdef RANDOM_API_EXPORTS
                #define RANDOM_API __declspec( dllexport )
                #define EXPORT_TEMPLATE
        #else
                #define RANDOM_API __declspec( dllimport )
                #define EXPORT_TEMPLATE extern
        #endif // RANDOM_API_EXPORTS
#pragma warning( disable:4251 )
#else
        #define RANDOM_API_EXPORTS __attribute__( ( visibility( "default" ) ) )
        #define EXPORT_TEMPLATE
#endif // WIN32

#ifdef __cplusplus

extern "C" 
{
#endif // __cplusplus

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern RANDOM_API MathLib::Random::CursoryRandomNumberGenerator * CRNGConstructor( void );

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern RANDOM_API void CRNGDestructor( MathLib::Random::CursoryRandomNumberGenerator * );

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern RANDOM_API unsigned int CRNGGenerateUint( MathLib::Random::CursoryRandomNumberGenerator * );

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern RANDOM_API unsigned int CRNGGenerateUintBounded( MathLib::Random::CursoryRandomNumberGenerator *, unsigned int, unsigned int );

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern RANDOM_API double CRNGGenerateDoubleBounded( MathLib::Random::CursoryRandomNumberGenerator *, double, double );

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern RANDOM_API MathLib::Random::MersenneTwister * MTConstructor( void );

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern RANDOM_API MathLib::Random::MersenneTwister * MTSeedConstructor( unsigned int );

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern RANDOM_API void MTDestructor( MathLib::Random::MersenneTwister * );

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern RANDOM_API unsigned int MTGenerateUint( MathLib::Random::MersenneTwister * );

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern RANDOM_API unsigned int MTGenerateUintBounded( MathLib::Random::MersenneTwister *, unsigned int, unsigned int );

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern RANDOM_API double MTGenerateDoubleBounded( MathLib::Random::MersenneTwister *, double, double );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MATHLIB_LIBRANDOM_H
