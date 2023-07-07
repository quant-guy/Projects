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
#ifndef NEURAL_CALLERS_H
#define NEURAL_CALLERS_H

#define WIN32_LEAN_AND_MEAN
#ifdef WIN32
#include <windows.h>
#endif // WIN32

#include "NeuralUnit.hpp"

// define "NEURAL_API_EXPORTS" from the command line in the project building this
// DLL.  DO NOT define it in the project that links to the DLL
#ifdef WIN32
        #ifdef NEURAL_API_EXPORTS
                #define NEURAL_API __declspec( dllexport )
                #define EXPORT_TEMPLATE
        #else
                #define NEURAL_API __declspec( dllimport )
                #define EXPORT_TEMPLATE extern
        #endif // NEURAL_API_EXPORTS
#else
        #define NEURAL_API_EXPORTS __attribute__( ( visibility( "default" ) ) )
        #define EXPORT_TEMPLATE
#endif // WIN32

using namespace AILib::NeuralNetwork;
using namespace MathLib::Matrix;

#ifndef WIN32
#define NEURAL_API
#endif // WIN32

#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus

///////////////////////////////////////////////////////////////////////////////
// Neural Unit 
///////////////////////////////////////////////////////////////////////////////

extern NEURAL_API NeuralUnit< double > *  NeuralUnitConstructor( void );

extern NEURAL_API NeuralUnit< double > *  NeuralUnitCopyConstructor( NeuralUnit< double > * );

extern NEURAL_API NeuralUnit< double > *  NeuralUnitDimensionalConstructor( unsigned int, unsigned int );

extern NEURAL_API void NeuralUnitDestructor( NeuralUnit< double > * );

extern NEURAL_API void SetLearningRateNeuralUnit( NeuralUnit< double > *, double );

extern NEURAL_API double GetLearningRateNeuralUnit( NeuralUnit< double > * );

extern NEURAL_API void SetSigmoidParameterNeuralUnit( NeuralUnit< double > *, double ); 

extern NEURAL_API double GetSigmoidParameterNeuralUnit( NeuralUnit< double > * ); 

extern NEURAL_API void SetNext( NeuralUnit< double > *, NeuralUnit< double > * );

extern NEURAL_API void SetPrev( NeuralUnit< double > *, NeuralUnit< double > * );

extern NEURAL_API void SetInput( NeuralUnit< double > *, double *, unsigned int );

extern NEURAL_API void GetOutput( NeuralUnit< double > *, double *, unsigned int );

extern NEURAL_API void PutNeural( NeuralUnit< double > *, std::ofstream * );

extern NEURAL_API void GetNeural( NeuralUnit< double > *, double * input, const unsigned int & size_input );

extern NEURAL_API void PropagateInput( NeuralUnit< double > *, double *, unsigned int );

extern NEURAL_API void PropagateNeuralUnit( NeuralUnit< double > * );

extern NEURAL_API void BackPropagateOutputNeuralUnit( NeuralUnit< double > *, double *, unsigned int );

extern NEURAL_API void BackPropagateNeuralUnit( NeuralUnit< double > * );

extern NEURAL_API double ErrorNeuralUnit( NeuralUnit< double > *, double *, unsigned int );

///////////////////////////////////////////////////////////////////////////////
// Neural Macro Structure
///////////////////////////////////////////////////////////////////////////////

extern NEURAL_API NeuralMacroStructure< double > *  NeuralMacroStructureConstructor( void );

extern NEURAL_API NeuralMacroStructure< double > *  NeuralMacroStructureCopyConstructor( NeuralMacroStructure< double > * );

extern NEURAL_API NeuralMacroStructure< double > *  NeuralMacroStructureLayerConstructor( unsigned int, unsigned int, unsigned int );

extern NEURAL_API NeuralMacroStructure< double > *  NeuralMacroStructureFileConstructor( const char *, unsigned int, double, double );

extern NEURAL_API NeuralMacroStructure< double > *  NeuralMacroStructureFileConstructor2( const char *, unsigned int );

extern NEURAL_API void TimesEq( NeuralMacroStructure< double > *, double );

extern NEURAL_API void NeuralMacroStructureDestructor( NeuralMacroStructure< double > * );

extern NEURAL_API unsigned int Size( NeuralMacroStructure< double > * );

extern NEURAL_API unsigned int InputSize( NeuralMacroStructure< double > * );

extern NEURAL_API unsigned int OutputSize( NeuralMacroStructure< double > * );

extern NEURAL_API unsigned int Nodes( NeuralMacroStructure< double > * );

extern NEURAL_API void PushBack( NeuralMacroStructure< double > *, const NeuralUnit< double > * );

extern NEURAL_API void SetLearningRate( NeuralMacroStructure< double > *, double );

extern NEURAL_API double GetLearningRate( NeuralMacroStructure< double > * );

extern NEURAL_API void SetSigmoidParameter( NeuralMacroStructure< double > *, double );

extern NEURAL_API double GetSigmoidParameter( NeuralMacroStructure< double > * );

extern NEURAL_API void PutNeuralMacroStructure( NeuralMacroStructure< double > *, const char * );

extern NEURAL_API void GetNeuralMacroStructure( NeuralMacroStructure< double > *, const char * );

extern NEURAL_API void Propagate( NeuralMacroStructure< double > *, double *, unsigned int );

extern NEURAL_API void BackPropagate( NeuralMacroStructure< double > *, double *, unsigned int );

extern NEURAL_API void Output( NeuralMacroStructure< double > *, double *, unsigned int );

extern NEURAL_API double Error( NeuralMacroStructure< double > *, double *, unsigned int );

extern NEURAL_API void PropagateM( NeuralMacroStructure< double > *, Matrix< double > * );

extern NEURAL_API void BackPropagateM( NeuralMacroStructure< double > *, Matrix< double > * );

extern NEURAL_API void OutputM( NeuralMacroStructure< double > *, Matrix< double > * );

extern NEURAL_API double ErrorM( NeuralMacroStructure< double > *, Matrix< double > * );

extern NEURAL_API void Print( NeuralMacroStructure< double > * );

extern NEURAL_API void PrintWeights( NeuralMacroStructure< double > * );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // NEURAL_CALLERS_H
