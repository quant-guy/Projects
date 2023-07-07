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
#ifndef NEURAL_ALGORITHM_CALLERS_H
#define NEURAL_ALGORITHM_CALLERS_H

#include <Cluster.hpp>
#include <NeuralCallers.h>
#include <NeuralUnit.hpp>
#include <Preprocessor.hpp>

using namespace AILib::Cluster;
using namespace AILib::NeuralNetwork;
using namespace preprocessor;

#define WIN32_LEAN_AND_MEAN
#ifdef WIN32
#include <windows.h>
#endif // WIN32

#ifndef WIN32
#define NEURAL_ALGORITHM_API
#endif // WIN32

// define "NEURAL_ALGORITHM_API_EXPORTS" from the command line in the project building this
// DLL.  DO NOT define it in the project that links to the DLL
#ifdef WIN32
        #ifdef NEURAL_ALGORITHM_API_EXPORTS
                #define NEURAL_ALGORITHM_API __declspec( dllexport )
                #define EXPORT_TEMPLATE
        #else
                #define NEURAL_ALGORITHM_API __declspec( dllimport )
                #define EXPORT_TEMPLATE extern
        #endif // NEURAL_ALGORITHM_API_EXPORTS
#else
        #define NEURAL_ALGORITHM_API_EXPORTS __attribute__( ( visibility( "default" ) ) )
        #define EXPORT_TEMPLATE
#endif // WIN32

#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus

///////////////////////////////////////////////////////////////////////
// Neural algorithms using matrices
///////////////////////////////////////////////////////////////////////
extern NEURAL_ALGORITHM_API bool SupervisedAlgorithmM( NeuralMacroStructure< double > *,
	const Matrix< double > *, const Matrix< double > *, unsigned int &, const unsigned int &, const double & );

extern NEURAL_ALGORITHM_API bool SupervisedCrossValidationM( NeuralMacroStructure< double > *, 
	const Matrix< double > *, const Matrix< double > *, const double &, double & );

extern NEURAL_ALGORITHM_API void SupervisedApplyM( NeuralMacroStructure< double > *, 
	const Matrix< double > *, Matrix< double > *, bool );

extern NEURAL_ALGORITHM_API double SupervisedGetErrorM( NeuralMacroStructure< double > *, 
	const Matrix< double > *, const Matrix< double > * );

extern NEURAL_ALGORITHM_API bool UnsupervisedAlgorithmM( NeuralMacroStructure< double > *, 
	SimpleCluster< double > *, const Matrix< double > *, unsigned int &, const unsigned int &, const double &, unsigned int & );

extern NEURAL_ALGORITHM_API bool UnsupervisedCrossValidationM( NeuralMacroStructure< double > *, 
	SimpleCluster< double > *, const Matrix< double > *, const double &, double & );

extern NEURAL_ALGORITHM_API void UnsupervisedApplyM( NeuralMacroStructure< double > *,
	SimpleCluster< double > *, const Matrix< double > *, int * );

///////////////////////////////////////////////////////////////////////
// Neural algorithms using double arrays
///////////////////////////////////////////////////////////////////////
extern NEURAL_ALGORITHM_API bool SupervisedAlgorithm( NeuralMacroStructure< double > *,
	const double **, const double **, const unsigned int &, const unsigned int &, const unsigned int &, 
	unsigned int &, const unsigned int &, const double & );

extern NEURAL_ALGORITHM_API bool SupervisedCrossValidation( NeuralMacroStructure< double > *, 
	const double **, const double **, const unsigned int &, const unsigned int &, const unsigned int &, const double &, double & );

extern NEURAL_ALGORITHM_API void SupervisedApply( NeuralMacroStructure< double > *,
	const double **, double **, const unsigned int &, const unsigned int &, const unsigned int &, bool );

extern NEURAL_ALGORITHM_API double SupervisedGetError( NeuralMacroStructure< double > *,
	const double **, const double **, const unsigned int &, const unsigned int &, const unsigned int & );

extern NEURAL_ALGORITHM_API bool UnsupervisedAlgorithm( NeuralMacroStructure< double > *,
	SimpleCluster< double > *, const double **, const unsigned int &, const unsigned int &, unsigned int &, 
	const unsigned int &, const double &, unsigned int & );

extern NEURAL_ALGORITHM_API bool UnsupervisedCrossValidation( NeuralMacroStructure< double > *,
	SimpleCluster< double > *, const double **, const unsigned int &, const unsigned int &, const double &, double & );

extern NEURAL_ALGORITHM_API void UnsupervisedApply( NeuralMacroStructure< double > *,
	SimpleCluster< double > *, const double **, const unsigned int &, const unsigned int &, int * );

///////////////////////////////////////////////////////////////////////////////
// Neural algorithms using preprocessors
///////////////////////////////////////////////////////////////////////////////

extern NEURAL_ALGORITHM_API bool SupervisedAlgorithmP( NeuralMacroStructure< double > *,
	const Preprocessor *, const Preprocessor *, unsigned int &, const unsigned int &, const double & );

extern NEURAL_ALGORITHM_API bool SupervisedCrossValidationP( NeuralMacroStructure< double > *, 
	const Preprocessor *, const Preprocessor *, const double &, double & );

extern NEURAL_ALGORITHM_API void SupervisedApplyP( NeuralMacroStructure< double > *,
	const Preprocessor *, Preprocessor *, bool );

extern NEURAL_ALGORITHM_API double SupervisedGetErrorP( NeuralMacroStructure< double > *, const Preprocessor *, const Preprocessor *);

extern NEURAL_ALGORITHM_API bool UnsupervisedAlgorithmP( NeuralMacroStructure< double > *,
	SimpleCluster< double > *, const Preprocessor *, unsigned int &, const unsigned int &, const double &, unsigned int & );

extern NEURAL_ALGORITHM_API bool UnsupervisedCrossValidationP( NeuralMacroStructure< double > *,
	SimpleCluster< double > *, const Preprocessor *, const double &, double & );

extern NEURAL_ALGORITHM_API void UnsupervisedApplyP( NeuralMacroStructure< double > *,
	SimpleCluster< double > *, const Preprocessor *, int * );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // NEURAL_ALGORITHM_CALLERS_H
