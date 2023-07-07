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
#include "ClusterLibCallers.h"

//////////////////////////////////////////////////////////////////////////////////////////
// KMeans 
//////////////////////////////////////////////////////////////////////////////////////////

extern "C" CLUSTER_LIB_API KMeans< double > * KMeansConstructor( const unsigned int & k )
{
	return new KMeans< double >( k );
}

extern "C" CLUSTER_LIB_API void KMeansDestructor( KMeans< double > * c_ptr )
{
	assert( c_ptr );
	delete c_ptr;
}

extern "C" CLUSTER_LIB_API void KMeansGetCluster( KMeans< double > * c_ptr, const char * filename )
{
	assert( c_ptr );
	c_ptr->GetCluster( filename );
}

extern "C" CLUSTER_LIB_API void KMeansPutCluster( KMeans< double > * c_ptr, const char * filename )
{
	assert( c_ptr );
	ofstream output( filename );
	output << * c_ptr;
	c_ptr->GetCluster( filename );
}

//////////////////////////////////////////////////////////////////////////////////////////
// Self Organizing Map
//////////////////////////////////////////////////////////////////////////////////////////

extern "C" CLUSTER_LIB_API SelfOrganizingMap< double > * SelfOrganizingMapConstructor( const unsigned int & k, 
	const double & r, const double & e )
{
	return new SelfOrganizingMap< double >( k, r, e );
}

extern "C" CLUSTER_LIB_API void SelfOrganizingMapDestructor( SelfOrganizingMap< double > * c_ptr )
{
	assert( c_ptr );
	delete c_ptr;
}

extern "C" CLUSTER_LIB_API void SelfOrganizingMapGetCluster( SelfOrganizingMap< double > * c_ptr, const char * filename )
{
	assert( c_ptr );
	c_ptr->GetCluster( filename );
}

extern "C" CLUSTER_LIB_API void SelfOrganizingMapPutCluster( SelfOrganizingMap< double > * c_ptr, const char * filename )
{
	assert( c_ptr );
	ofstream output( filename );
	output << * c_ptr;
	c_ptr->GetCluster( filename );
}

//////////////////////////////////////////////////////////////////////////////////////////
// Topological
//////////////////////////////////////////////////////////////////////////////////////////

extern "C" CLUSTER_LIB_API Topological< double > * TopologicalConstructor( const double & k )
{
	return new Topological< double >( k );
}

extern "C" CLUSTER_LIB_API void TopologicalDestructor( Topological< double > * c_ptr )
{
	assert( c_ptr );
	delete c_ptr;
}

extern "C" CLUSTER_LIB_API void TopologicalGetCluster( Topological< double > * c_ptr, const char * filename )
{
	assert( c_ptr );
	c_ptr->GetCluster( filename );
}

extern "C" CLUSTER_LIB_API void TopologicalPutCluster( Topological< double > * c_ptr, const char * filename )
{
	assert( c_ptr );
	ofstream output( filename );
	output << * c_ptr;
	c_ptr->GetCluster( filename );
}

//////////////////////////////////////////////////////////////////////////////////////////
// SimpleCluster
//////////////////////////////////////////////////////////////////////////////////////////

extern "C" CLUSTER_LIB_API SimpleCluster< double > * SimpleClusterConstructor( const double & k )
{
	return new SimpleCluster< double >( k );
}

extern "C" CLUSTER_LIB_API void SimpleClusterDestructor( SimpleCluster< double > * c_ptr )
{
	assert( c_ptr );
	delete c_ptr;
}

extern "C" CLUSTER_LIB_API void SimpleClusterGetCluster( SimpleCluster< double > * c_ptr, const char * filename )
{
	assert( c_ptr );
	c_ptr->GetCluster( filename );
}

extern "C" CLUSTER_LIB_API void SimpleClusterPutCluster( SimpleCluster< double > * c_ptr, const char * filename )
{
	assert( c_ptr );
	ofstream output( filename );
	output << * c_ptr;
	c_ptr->GetCluster( filename );
}
