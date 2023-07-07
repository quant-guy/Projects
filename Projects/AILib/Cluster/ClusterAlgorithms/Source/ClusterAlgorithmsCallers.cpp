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
#include "ClusterAlgorithmsCallers.h"

//////////////////////////////////////////////////////////////////////////////////////////
// KMeans 
//////////////////////////////////////////////////////////////////////////////////////////

extern "C" CLUSTER_ALGORITHMS_API void KMeansTrain( KMeans< double > * c_ptr, 
	const double ** data, const unsigned int & rows, const unsigned int & cols )
{
	assert( c_ptr );
	c_ptr->Initialize( data, rows, cols );
	c_ptr->Train( data, rows, cols );
}

extern "C" CLUSTER_ALGORITHMS_API double KMeansCrossValidate( KMeans< double > * c_ptr, const double ** data, 
	const unsigned int & rows1, const unsigned int & cols1, double ** xval, const unsigned int & rows2, const unsigned int & cols2, 
	const double & err )
{
	assert( c_ptr );
	return c_ptr->CrossValidate( data, rows1, cols1, xval, rows2, cols2, err );
}

extern "C" CLUSTER_ALGORITHMS_API void KMeansApply( KMeans< double > * c_ptr, const double ** data, 
	const unsigned int & rows1, const unsigned int & cols1, double ** app, const unsigned int & rows2, const unsigned int & cols2 )
{
	assert( c_ptr );
	c_ptr->Apply( data, rows1, cols1, app, rows2, cols2 );
}

extern "C" CLUSTER_ALGORITHMS_API double KMeansGetError( KMeans< double > * c_ptr, const double ** data, 
	const unsigned int & rows, const unsigned int & cols )
{
	assert( c_ptr );
	return c_ptr->GetError( data, rows, cols );
}

extern "C" CLUSTER_ALGORITHMS_API void KMeansTrainP( KMeans< double > * c_ptr, Preprocessor * p_ptr )
{
	assert( c_ptr );
	c_ptr->Initialize( ( const double ** ) p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols() );
	c_ptr->Train( ( const double ** ) p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API double KMeansCrossValidateP( KMeans< double > * c_ptr, 
	Preprocessor * p_ptr1, Preprocessor * p_ptr2, const double & err )
{
	assert( c_ptr );
	return c_ptr->CrossValidate( ( const double ** ) p_ptr1->GetData(), p_ptr1->GetRows(), p_ptr2->GetRows(), 
		p_ptr2->GetData(), p_ptr2->GetRows(), p_ptr2->GetCols(), err );
}

extern "C" CLUSTER_ALGORITHMS_API void KMeansApplyP( KMeans< double > * c_ptr, Preprocessor * p_ptr1, Preprocessor * p_ptr2 )
{
	assert( c_ptr );
	c_ptr->Apply( ( const double ** ) p_ptr1->GetData(), p_ptr1->GetRows(), p_ptr1->GetCols(), p_ptr2->GetData(), p_ptr2->GetRows(), p_ptr2->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API double KMeansGetErrorP( KMeans< double > * c_ptr, Preprocessor * p_ptr )
{
	assert( c_ptr );
	return c_ptr->GetError( ( const double ** ) p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API void KMeansTrainM( KMeans< double > * c_ptr, Matrix< double > * m_ptr )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr->GetRows() ];
	unsigned int rows = m_ptr->GetRows();
	unsigned int cols = m_ptr->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows, cols );
	m_ptr->Convert( data, rows, cols );
	c_ptr->Initialize( ( const double ** ) data, rows, cols );
	c_ptr->Train( ( const double ** ) data, rows, cols );
	DELETE_MEMORY_ONE_DATASET( data, cols );
}

extern "C" CLUSTER_ALGORITHMS_API double KMeansCrossValidateM( KMeans< double > * c_ptr, 
	Matrix< double > * m_ptr1, Matrix< double > * m_ptr2, const double & err )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr1->GetRows() ];
	double ** xval = new double * [ m_ptr2->GetRows() ];
	unsigned int rows1 = m_ptr1->GetRows();
	unsigned int cols1 = m_ptr1->GetColumns();
	unsigned int rows2 = m_ptr2->GetRows();
	unsigned int cols2 = m_ptr2->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows1, cols1 );
	ALLOCATE_MEMORY_ONE_DATASET( xval, rows2, cols2 );
	double return_value = c_ptr->CrossValidate( ( const double ** ) data, rows1, cols1, xval, rows2, cols2, err );
	m_ptr2->GetMatrix( ( const double ** ) xval, rows2, cols2 );
	DELETE_MEMORY_ONE_DATASET( data, rows1 );
	DELETE_MEMORY_ONE_DATASET( xval, rows2 );
	return return_value;
}

extern "C" CLUSTER_ALGORITHMS_API void KMeansApplyM( KMeans< double > * c_ptr, Matrix< double > * m_ptr1, Matrix< double > * m_ptr2 )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr1->GetRows() ];
	double ** appl = new double * [ m_ptr2->GetRows() ];
	unsigned int rows1 = m_ptr1->GetRows();
	unsigned int cols1 = m_ptr1->GetColumns();
	unsigned int rows2 = m_ptr2->GetRows();
	unsigned int cols2 = m_ptr2->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows1, cols1 );
	ALLOCATE_MEMORY_ONE_DATASET( appl, rows2, cols2 );
	c_ptr->Apply( ( const double ** ) data, rows1, cols1, appl, rows2, cols2 );
	m_ptr2->GetMatrix( ( const double ** ) appl, rows2, cols2 );
	DELETE_MEMORY_ONE_DATASET( data, rows1 );
	DELETE_MEMORY_ONE_DATASET( appl, rows2 );
}

extern "C" CLUSTER_ALGORITHMS_API double KMeansGetErrorM( KMeans< double > * c_ptr, Matrix< double > * m_ptr )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr->GetRows() ];
	unsigned int rows = m_ptr->GetRows();
	unsigned int cols = m_ptr->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows, cols );
	m_ptr->Convert( data, rows, cols );
	double return_value = c_ptr->GetError( ( const double ** ) data, rows, cols );
	DELETE_MEMORY_ONE_DATASET( data, rows );
	return return_value;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Self Organizing Map
//////////////////////////////////////////////////////////////////////////////////////////

extern "C" CLUSTER_ALGORITHMS_API void SelfOrganizingMapTrain( SelfOrganizingMap< double > * c_ptr, 
	const double ** data, const unsigned int & rows, const unsigned int & cols )
{
	assert( c_ptr );
	c_ptr->Initialize( cols );
	c_ptr->Train( data, rows, cols );
}

extern "C" CLUSTER_ALGORITHMS_API double SelfOrganizingMapCrossValidate( SelfOrganizingMap< double > * c_ptr, const double ** data, 
	const unsigned int & rows1, const unsigned int & cols1, double ** xval, const unsigned int & rows2, const unsigned int & cols2, 
	const double & err )
{
	assert( c_ptr );
	return c_ptr->CrossValidate( data, rows1, cols1, xval, rows2, cols2, err );
}

extern "C" CLUSTER_ALGORITHMS_API void SelfOrganizingMapApply( SelfOrganizingMap< double > * c_ptr, const double ** data, 
	const unsigned int & rows1, const unsigned int & cols1, double ** app, const unsigned int & rows2, const unsigned int & cols2 )
{
	assert( c_ptr );
	c_ptr->Apply( data, rows1, cols1, app, rows2, cols2 );
}

extern "C" CLUSTER_ALGORITHMS_API double SelfOrganizingMapGetError( SelfOrganizingMap< double > * c_ptr, const double ** data, 
	const unsigned int & rows, const unsigned int & cols )
{
	assert( c_ptr );
	return c_ptr->GetError( data, rows, cols );
}

extern "C" CLUSTER_ALGORITHMS_API void SelfOrganizingMapTrainP( SelfOrganizingMap< double > * c_ptr, Preprocessor * p_ptr )
{
	assert( c_ptr );
	c_ptr->Initialize( p_ptr->GetCols() );
	c_ptr->Train( ( const double ** ) p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API double SelfOrganizingMapCrossValidateP( SelfOrganizingMap< double > * c_ptr, 
	Preprocessor * p_ptr1, Preprocessor * p_ptr2, const double & err )
{
	assert( c_ptr );
	return c_ptr->CrossValidate( ( const double ** ) p_ptr1->GetData(), p_ptr1->GetRows(), p_ptr2->GetRows(), 
		p_ptr2->GetData(), p_ptr2->GetRows(), p_ptr2->GetCols(), err );
}

extern "C" CLUSTER_ALGORITHMS_API void SelfOrganizingMapApplyP( SelfOrganizingMap< double > * c_ptr, Preprocessor * p_ptr1, Preprocessor * p_ptr2 )
{
	assert( c_ptr );
	c_ptr->Apply( ( const double ** ) p_ptr1->GetData(), p_ptr1->GetRows(), p_ptr1->GetCols(), p_ptr2->GetData(), p_ptr2->GetRows(), p_ptr2->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API double SelfOrganizingMapGetErrorP( SelfOrganizingMap< double > * c_ptr, Preprocessor * p_ptr )
{
	assert( c_ptr );
	return c_ptr->GetError( ( const double ** ) p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API void SelfOrganizingMapTrainM( SelfOrganizingMap< double > * c_ptr, Matrix< double > * m_ptr )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr->GetRows() ];
	unsigned int rows = m_ptr->GetRows();
	unsigned int cols = m_ptr->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows, cols );
	m_ptr->Convert( data, rows, cols );
	c_ptr->Initialize( cols );
	c_ptr->Train( ( const double ** ) data, rows, cols );
	DELETE_MEMORY_ONE_DATASET( data, rows );
}

extern "C" CLUSTER_ALGORITHMS_API double SelfOrganizingMapCrossValidateM( SelfOrganizingMap< double > * c_ptr, 
	Matrix< double > * m_ptr1, Matrix< double > * m_ptr2, const double & err )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr1->GetRows() ];
	double ** xval = new double * [ m_ptr2->GetRows() ];
	unsigned int rows1 = m_ptr1->GetRows();
	unsigned int cols1 = m_ptr1->GetColumns();
	unsigned int rows2 = m_ptr2->GetRows();
	unsigned int cols2 = m_ptr2->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows1, cols1 );
	ALLOCATE_MEMORY_ONE_DATASET( xval, rows2, cols2 );
	double return_value = c_ptr->CrossValidate( ( const double ** ) data, rows1, cols1, xval, rows2, cols2, err );
	m_ptr2->GetMatrix( ( const double ** ) xval, rows2, cols2 );
	DELETE_MEMORY_ONE_DATASET( data, rows1 );
	DELETE_MEMORY_ONE_DATASET( xval, rows2 );
	return return_value;
}

extern "C" CLUSTER_ALGORITHMS_API void SelfOrganizingMapApplyM( SelfOrganizingMap< double > * c_ptr, Matrix< double > * m_ptr1, Matrix< double > * m_ptr2 )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr1->GetRows() ];
	double ** appl = new double * [ m_ptr2->GetRows() ];
	unsigned int rows1 = m_ptr1->GetRows();
	unsigned int cols1 = m_ptr1->GetColumns();
	unsigned int rows2 = m_ptr2->GetRows();
	unsigned int cols2 = m_ptr2->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows1, cols1 );
	ALLOCATE_MEMORY_ONE_DATASET( appl, rows2, cols2 );
	c_ptr->Apply( ( const double ** ) data, rows1, cols1, appl, rows2, cols2 );
	m_ptr2->GetMatrix( ( const double ** ) appl, rows2, cols2 );
	DELETE_MEMORY_ONE_DATASET( data, rows1 );
	DELETE_MEMORY_ONE_DATASET( appl, rows2 );
}

extern "C" CLUSTER_ALGORITHMS_API double SelfOrganizingMapGetErrorM( SelfOrganizingMap< double > * c_ptr, Matrix< double > * m_ptr )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr->GetRows() ];
	unsigned int rows = m_ptr->GetRows();
	unsigned int cols = m_ptr->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows, cols );
	m_ptr->Convert( data, rows, cols );
	double return_value = c_ptr->GetError( ( const double ** ) data, rows, cols );
	DELETE_MEMORY_ONE_DATASET( data, rows );
	return return_value;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Topological
//////////////////////////////////////////////////////////////////////////////////////////

extern "C" CLUSTER_ALGORITHMS_API void TopologicalTrain( Topological< double > * c_ptr, 
	const double ** data, const unsigned int & rows, const unsigned int & cols )
{
	assert( c_ptr );
	c_ptr->Initialize( data, rows, cols );
	c_ptr->Train( data, rows, cols );
}

extern "C" CLUSTER_ALGORITHMS_API double TopologicalCrossValidate( Topological< double > * c_ptr, const double ** data, 
	const unsigned int & rows1, const unsigned int & cols1, double ** xval, const unsigned int & rows2, const unsigned int & cols2 )
{
	assert( c_ptr );
	return c_ptr->CrossValidate( data, rows1, cols1, xval, rows2, cols2 );
}

extern "C" CLUSTER_ALGORITHMS_API void TopologicalApply( Topological< double > * c_ptr, const double ** data, 
	const unsigned int & rows1, const unsigned int & cols1, double ** app, const unsigned int & rows2, const unsigned int & cols2 )
{
	assert( c_ptr );
	c_ptr->Apply( data, rows1, cols1, app, rows2, cols2 );
}

extern "C" CLUSTER_ALGORITHMS_API double TopologicalGetError( Topological< double > * c_ptr, const double ** data, 
	const unsigned int & rows, const unsigned int & cols )
{
	assert( c_ptr );
	return c_ptr->GetError( data, rows, cols );
}

extern "C" CLUSTER_ALGORITHMS_API void TopologicalTrainP( Topological< double > * c_ptr, Preprocessor * p_ptr )
{
	assert( c_ptr );
	c_ptr->Initialize( ( const double ** ) p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols() );
	c_ptr->Train( ( const double ** ) p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API double TopologicalCrossValidateP( Topological< double > * c_ptr, 
	Preprocessor * p_ptr1, Preprocessor * p_ptr2 )
{
	assert( c_ptr );
	return c_ptr->CrossValidate( ( const double ** ) p_ptr1->GetData(), p_ptr1->GetRows(), p_ptr2->GetRows(), 
		p_ptr2->GetData(), p_ptr2->GetRows(), p_ptr2->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API void TopologicalApplyP( Topological< double > * c_ptr, Preprocessor * p_ptr1, Preprocessor * p_ptr2 )
{
	assert( c_ptr );
	c_ptr->Apply( ( const double ** ) p_ptr1->GetData(), p_ptr1->GetRows(), p_ptr1->GetCols(), p_ptr2->GetData(), p_ptr2->GetRows(), p_ptr2->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API double TopologicalGetErrorP( Topological< double > * c_ptr, Preprocessor * p_ptr )
{
	assert( c_ptr );
	return c_ptr->GetError( ( const double ** ) p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API void TopologicalTrainM( Topological< double > * c_ptr, Matrix< double > * m_ptr )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr->GetRows() ];
	unsigned int rows = m_ptr->GetRows();
	unsigned int cols = m_ptr->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows, cols );
	m_ptr->Convert( data, rows, cols );
	c_ptr->Initialize( ( const double ** ) data, rows, cols );
	c_ptr->Train( ( const double ** ) data, rows, cols );
	DELETE_MEMORY_ONE_DATASET( data, cols );
}

extern "C" CLUSTER_ALGORITHMS_API double TopologicalCrossValidateM( Topological< double > * c_ptr, 
	Matrix< double > * m_ptr1, Matrix< double > * m_ptr2 )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr1->GetRows() ];
	double ** xval = new double * [ m_ptr2->GetRows() ];
	unsigned int rows1 = m_ptr1->GetRows();
	unsigned int cols1 = m_ptr1->GetColumns();
	unsigned int rows2 = m_ptr2->GetRows();
	unsigned int cols2 = m_ptr2->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows1, cols1 );
	ALLOCATE_MEMORY_ONE_DATASET( xval, rows2, cols2 );
	double return_value = c_ptr->CrossValidate( ( const double ** ) data, rows1, cols1, xval, rows2, cols2 );
	m_ptr2->GetMatrix( ( const double ** ) xval, rows2, cols2 );
	DELETE_MEMORY_ONE_DATASET( data, rows1 );
	DELETE_MEMORY_ONE_DATASET( xval, rows2 );
	return return_value;
}

extern "C" CLUSTER_ALGORITHMS_API void TopologicalApplyM( Topological< double > * c_ptr, Matrix< double > * m_ptr1, Matrix< double > * m_ptr2 )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr1->GetRows() ];
	double ** appl = new double * [ m_ptr2->GetRows() ];
	unsigned int rows1 = m_ptr1->GetRows();
	unsigned int cols1 = m_ptr1->GetColumns();
	unsigned int rows2 = m_ptr2->GetRows();
	unsigned int cols2 = m_ptr2->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows1, cols1 );
	ALLOCATE_MEMORY_ONE_DATASET( appl, rows2, cols2 );
	c_ptr->Apply( ( const double ** ) data, rows1, cols1, appl, rows2, cols2 );
	m_ptr2->GetMatrix( ( const double ** ) appl, rows2, cols2 );
	DELETE_MEMORY_ONE_DATASET( data, rows1 );
	DELETE_MEMORY_ONE_DATASET( appl, rows2 );
}

extern "C" CLUSTER_ALGORITHMS_API double TopologicalGetErrorM( Topological< double > * c_ptr, Matrix< double > * m_ptr )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr->GetRows() ];
	unsigned int rows = m_ptr->GetRows();
	unsigned int cols = m_ptr->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows, cols );
	m_ptr->Convert( data, rows, cols );
	double return_value = c_ptr->GetError( ( const double ** ) data, rows, cols );
	DELETE_MEMORY_ONE_DATASET( data, rows );
	return return_value;
}

//////////////////////////////////////////////////////////////////////////////////////////
// SimpleCluster
//////////////////////////////////////////////////////////////////////////////////////////

extern "C" CLUSTER_ALGORITHMS_API void SimpleClusterTrain( SimpleCluster< double > * c_ptr, 
	const double ** data, const unsigned int & rows, const unsigned int & cols )
{
	assert( c_ptr );
	c_ptr->Initialize();
	c_ptr->Train( data, rows, cols );
}

extern "C" CLUSTER_ALGORITHMS_API double SimpleClusterCrossValidate( SimpleCluster< double > * c_ptr, const double ** data, 
	const unsigned int & rows1, const unsigned int & cols1, double ** xval, const unsigned int & rows2, const unsigned int & cols2 )
{
	assert( c_ptr );
	return c_ptr->CrossValidate( data, rows1, cols1, xval, rows2, cols2 );
}

extern "C" CLUSTER_ALGORITHMS_API void SimpleClusterApply( SimpleCluster< double > * c_ptr, const double ** data, 
	const unsigned int & rows1, const unsigned int & cols1, double ** app, const unsigned int & rows2, const unsigned int & cols2 )
{
	assert( c_ptr );
	c_ptr->Apply( data, rows1, cols1, app, rows2, cols2 );
}

extern "C" CLUSTER_ALGORITHMS_API double SimpleClusterGetError( SimpleCluster< double > * c_ptr, const double ** data, 
	const unsigned int & rows, const unsigned int & cols )
{
	assert( c_ptr );
	return c_ptr->GetError( data, rows, cols );
}

extern "C" CLUSTER_ALGORITHMS_API void SimpleClusterTrainP( SimpleCluster< double > * c_ptr, Preprocessor * p_ptr )
{
	assert( c_ptr );
	c_ptr->Initialize();
	c_ptr->Train( ( const double ** ) p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API double SimpleClusterCrossValidateP( SimpleCluster< double > * c_ptr, 
	Preprocessor * p_ptr1, Preprocessor * p_ptr2 )
{
	assert( c_ptr );
	return c_ptr->CrossValidate( ( const double ** ) p_ptr1->GetData(), p_ptr1->GetRows(), p_ptr2->GetRows(), 
		p_ptr2->GetData(), p_ptr2->GetRows(), p_ptr2->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API void SimpleClusterApplyP( SimpleCluster< double > * c_ptr, Preprocessor * p_ptr1, Preprocessor * p_ptr2 )
{
	assert( c_ptr );
	c_ptr->Apply( ( const double ** ) p_ptr1->GetData(), p_ptr1->GetRows(), p_ptr1->GetCols(), p_ptr2->GetData(), p_ptr2->GetRows(), p_ptr2->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API double SimpleClusterGetErrorP( SimpleCluster< double > * c_ptr, Preprocessor * p_ptr )
{
	assert( c_ptr );
	return c_ptr->GetError( ( const double ** ) p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols() );
}

extern "C" CLUSTER_ALGORITHMS_API void SimpleClusterTrainM( SimpleCluster< double > * c_ptr, Matrix< double > * m_ptr )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr->GetRows() ];
	unsigned int rows = m_ptr->GetRows();
	unsigned int cols = m_ptr->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows, cols );
	m_ptr->Convert( data, rows, cols );
	c_ptr->Initialize();
	c_ptr->Train( ( const double ** ) data, rows, cols );
	DELETE_MEMORY_ONE_DATASET( data, cols );
}

extern "C" CLUSTER_ALGORITHMS_API double SimpleClusterCrossValidateM( SimpleCluster< double > * c_ptr, 
	Matrix< double > * m_ptr1, Matrix< double > * m_ptr2 )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr1->GetRows() ];
	double ** xval = new double * [ m_ptr2->GetRows() ];
	unsigned int rows1 = m_ptr1->GetRows();
	unsigned int cols1 = m_ptr1->GetColumns();
	unsigned int rows2 = m_ptr2->GetRows();
	unsigned int cols2 = m_ptr2->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows1, cols1 );
	ALLOCATE_MEMORY_ONE_DATASET( xval, rows2, cols2 );
	double return_value = c_ptr->CrossValidate( ( const double ** ) data, rows1, cols1, xval, rows2, cols2 );
	m_ptr2->GetMatrix( ( const double ** ) xval, rows2, cols2 );
	DELETE_MEMORY_ONE_DATASET( data, rows1 );
	DELETE_MEMORY_ONE_DATASET( xval, rows2 );
	return return_value;
}

extern "C" CLUSTER_ALGORITHMS_API void SimpleClusterApplyM( SimpleCluster< double > * c_ptr, Matrix< double > * m_ptr1, Matrix< double > * m_ptr2 )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr1->GetRows() ];
	double ** appl = new double * [ m_ptr2->GetRows() ];
	unsigned int rows1 = m_ptr1->GetRows();
	unsigned int cols1 = m_ptr1->GetColumns();
	unsigned int rows2 = m_ptr2->GetRows();
	unsigned int cols2 = m_ptr2->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows1, cols1 );
	ALLOCATE_MEMORY_ONE_DATASET( appl, rows2, cols2 );
	c_ptr->Apply( ( const double ** ) data, rows1, cols1, appl, rows2, cols2 );
	m_ptr2->GetMatrix( ( const double ** ) appl, rows2, cols2 );
	DELETE_MEMORY_ONE_DATASET( data, rows1 );
	DELETE_MEMORY_ONE_DATASET( appl, rows2 );
}

extern "C" CLUSTER_ALGORITHMS_API double SimpleClusterGetErrorM( SimpleCluster< double > * c_ptr, Matrix< double > * m_ptr )
{
	assert( c_ptr );
	double ** data = new double * [ m_ptr->GetRows() ];
	unsigned int rows = m_ptr->GetRows();
	unsigned int cols = m_ptr->GetColumns();
	ALLOCATE_MEMORY_ONE_DATASET( data, rows, cols );
	m_ptr->Convert( data, rows, cols );
	double return_value = c_ptr->GetError( ( const double ** ) data, rows, cols );
	DELETE_MEMORY_ONE_DATASET( data, rows );
	return return_value;
}
