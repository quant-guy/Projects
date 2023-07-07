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
#ifndef CLUSTER_ALGORITHMS_CALLERS_H
#define CLUSTER_ALGORITHMS_CALLERS_H

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // WIN32

#include <ClusterLibCallers.h>
#include <Matrix.hpp>
#include <MemoryAllocationMacros.h>

#ifndef WIN32
#define CLUSTER_ALGORITHMS_API
#endif // WIN32

using namespace preprocessor;
using namespace AILib::Cluster;
using namespace MathLib::Matrix;

// define "CLUSTER_ALGORITHMS_API_EXPORTS" from the command line in the project building this
// DLL.  DO NOT define it in the project that links to the DLL
#ifdef WIN32
        #ifdef CLUSTER_ALGORITHMS_API_EXPORTS
                #define CLUSTER_ALGORITHMS_API __declspec( dllexport )
                #define EXPORT_TEMPLATE
        #else
                #define CLUSTER_ALGORITHMS_API __declspec( dllimport )
                #define EXPORT_TEMPLATE extern
        #endif // CLUSTER_ALGORITHMS_API_EXPORTS
#else
        #define CLUSTER_ALGORITHMS_API_EXPORTS __attribute__( ( visibility( "default" ) ) )
        #define EXPORT_TEMPLATE
#endif // WIN32


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////////////////////
// KMeans 
//////////////////////////////////////////////////////////////////////////////////////////

extern CLUSTER_ALGORITHMS_API void KMeansTrain( KMeans< double > *, const double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API double KMeansCrossValidate( KMeans< double > *, const double **, 
	const unsigned int &, const unsigned int &, double **, const unsigned int &, const unsigned int &, const double & );

extern CLUSTER_ALGORITHMS_API void KMeansApply( KMeans< double > *, const double **, 
	const unsigned int &, const unsigned int &, double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API double KMeansGetError( KMeans< double > *, const double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API void KMeansTrainP( KMeans< double > *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API double KMeansCrossValidateP( KMeans< double > *, 
	Preprocessor *, Preprocessor *, const double & );

extern CLUSTER_ALGORITHMS_API void KMeansApplyP( KMeans< double > *, Preprocessor *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API double KMeansGetErrorP( KMeans< double > *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API void KMeansTrainM( KMeans< double > *, Matrix< double > * );

extern CLUSTER_ALGORITHMS_API double KMeansCrossValidateM( KMeans< double > *, 
	Matrix< double > *, Matrix< double > *, const double & );

extern CLUSTER_ALGORITHMS_API void KMeansApplyM( KMeans< double > *, Matrix< double > *, Matrix< double > * );

extern CLUSTER_ALGORITHMS_API double KMeansGetErrorM( KMeans< double > *, Matrix< double > * );

//////////////////////////////////////////////////////////////////////////////////////////
// Self Organizing Map
//////////////////////////////////////////////////////////////////////////////////////////

extern CLUSTER_ALGORITHMS_API void SelfOrganizingMapTrain( SelfOrganizingMap< double > *, 
	const double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API double SelfOrganizingMapCrossValidate( SelfOrganizingMap< double > *, const double **, 
	const unsigned int &, const unsigned int &, double **, const unsigned int &, const unsigned int &, const double & );

extern CLUSTER_ALGORITHMS_API void SelfOrganizingMapApply( SelfOrganizingMap< double > *, const double **, 
	const unsigned int &, const unsigned int &, double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API double SelfOrganizingMapGetError( SelfOrganizingMap< double > *, 
	const double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API void SelfOrganizingMapTrainP( SelfOrganizingMap< double > *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API double SelfOrganizingMapCrossValidateP( SelfOrganizingMap< double > *, 
	Preprocessor *, Preprocessor *, const double & );

extern CLUSTER_ALGORITHMS_API void SelfOrganizingMapApplyP( SelfOrganizingMap< double > *, Preprocessor *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API double SelfOrganizingMapGetErrorP( SelfOrganizingMap< double > *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API void SelfOrganizingMapTrainM( SelfOrganizingMap< double > *, Matrix< double > * );

extern CLUSTER_ALGORITHMS_API double SelfOrganizingMapCrossValidateM( SelfOrganizingMap< double > *, 
	Matrix< double > *, Matrix< double > *, const double & );

extern CLUSTER_ALGORITHMS_API void SelfOrganizingMapApplyM( SelfOrganizingMap< double > *, Matrix< double > *, Matrix< double > * );

extern CLUSTER_ALGORITHMS_API double SelfOrganizingMapGetErrorM( SelfOrganizingMap< double > *, Matrix< double > * );

//////////////////////////////////////////////////////////////////////////////////////////
// Topological
//////////////////////////////////////////////////////////////////////////////////////////

extern CLUSTER_ALGORITHMS_API void TopologicalTrain( Topological< double > *, 
	const double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API double TopologicalCrossValidate( Topological< double > *, const double **, 
	const unsigned int &, const unsigned int &, double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API void TopologicalApply( Topological< double > *, const double **, 
	const unsigned int &, const unsigned int &, double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API double TopologicalGetError( Topological< double > *, 
	const double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API void TopologicalTrainP( Topological< double > *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API double TopologicalCrossValidateP( Topological< double > *, 
	Preprocessor *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API void TopologicalApplyP( Topological< double > *, Preprocessor *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API double TopologicalGetErrorP( Topological< double > *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API void TopologicalTrainM( Topological< double > *, Matrix< double > * );

extern CLUSTER_ALGORITHMS_API double TopologicalCrossValidateM( Topological< double > *, 
	Matrix< double > *, Matrix< double > * );

extern CLUSTER_ALGORITHMS_API void TopologicalApplyM( Topological< double > *, Matrix< double > *, Matrix< double > * );

extern CLUSTER_ALGORITHMS_API double TopologicalGetErrorM( Topological< double > *, Matrix< double > * );

//////////////////////////////////////////////////////////////////////////////////////////
// SimpleCluster
//////////////////////////////////////////////////////////////////////////////////////////

extern CLUSTER_ALGORITHMS_API void SimpleClusterTrain( SimpleCluster< double > *, 
	const double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API double SimpleClusterCrossValidate( SimpleCluster< double > *, const double **, 
	const unsigned int &, const unsigned int &, double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API void SimpleClusterApply( SimpleCluster< double > *, const double **, 
	const unsigned int &, const unsigned int &, double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API double SimpleClusterGetError( SimpleCluster< double > *, 
	const double **, const unsigned int &, const unsigned int & );

extern CLUSTER_ALGORITHMS_API void SimpleClusterTrainP( SimpleCluster< double > *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API double SimpleClusterCrossValidateP( SimpleCluster< double > *, 
	Preprocessor *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API void SimpleClusterApplyP( SimpleCluster< double > *, Preprocessor *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API double SimpleClusterGetErrorP( SimpleCluster< double > *, Preprocessor * );

extern CLUSTER_ALGORITHMS_API void SimpleClusterTrainM( SimpleCluster< double > *, Matrix< double > * );

extern CLUSTER_ALGORITHMS_API double SimpleClusterCrossValidateM( SimpleCluster< double > *, 
	Matrix< double > *, Matrix< double > * );

extern CLUSTER_ALGORITHMS_API void SimpleClusterApplyM( SimpleCluster< double > *, Matrix< double > *, Matrix< double > * );

extern CLUSTER_ALGORITHMS_API double SimpleClusterGetErrorM( SimpleCluster< double > *, Matrix< double > * );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CLUSTER_ALGORITHMS_CALLERS_H
