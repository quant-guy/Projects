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
#ifndef MYPROJECT_CALLERS_H
#define MYPROJECT_CALLERS_H

#define WIN32_LEAN_AND_MEAN
#ifdef WIN32
#include <windows.h>
#endif // WIN32

#ifndef WIN32
#define MYPROJECT_API
#endif // WIN32

// define "MYPROJECT_API_EXPORTS" from the command line in the project building this
// DLL.  DO NOT define it in the project that links to the DLL
#ifdef WIN32
        #ifdef MYPROJECT_API_EXPORTS
                #define MYPROJECT_API __declspec( dllexport )
                #define EXPORT_TEMPLATE
        #else
                #define MYPROJECT_API __declspec( dllimport )
                #define EXPORT_TEMPLATE extern
        #endif // MYPROJECT_API_EXPORTS
#else
        #define MYPROJECT_API_EXPORTS __attribute__( ( visibility( "default" ) ) )
        #define EXPORT_TEMPLATE
#endif // WIN32

#include <assert.h>

#include "MyProject.hpp"

#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus

extern MYPROJECT_API Sample::MyProject::MyProject * MyProjectConstructor( void );

extern MYPROJECT_API void MyProjectDestructor( Sample::MyProject::MyProject * );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MYPROJECT_CALLERS_H
