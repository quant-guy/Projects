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
#include "NeuralAlgorithmsCallers.h"

///////////////////////////////////////////////////////////////////////
// Neural training algorithms.  This set uses matrices, which are
// the default data type in the neural training library.  This all
// operations will ultimately amount to matrices anyway
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// Supervised learning algorithm: use backpropagation against
// training set, stop when all elements are within desired error
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool SupervisedAlgorithmM( NeuralMacroStructure< double > * n_ptr,
	const Matrix< double > * m_ptr1, const Matrix< double > * m_ptr2, 
	unsigned int & index, const unsigned int & max_iterations, const double & desired_error )
{
	// check to make sure all data is valid
	assert( n_ptr ); assert( m_ptr1 ); assert( m_ptr2 );
	assert( ( * ( n_ptr->End() - 1 ) )->GetSizeOutput() == m_ptr2->GetColumns() );

	bool error = false;

	// backpropagation loop
	while ( index < max_iterations && ! error )
	{
		error = true;
		for ( unsigned int i = 0; i < m_ptr1->GetRows(); ++i )
		{
			n_ptr->Propagate( m_ptr1->GetRow( i ) );
			if ( n_ptr->Error( m_ptr2->GetRow( i ) ) > desired_error )
			{
				n_ptr->BackPropagate( m_ptr2->GetRow( i ) );
				error = false;
			}
		}
		++index;
	}

	return error;
}

///////////////////////////////////////////////////////////////////////
// Supervised learing cross validation: run trained network against
// trained data set, determine how many outliers, or if all were within
// desired error tolerance
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool SupervisedCrossValidationM( NeuralMacroStructure< double > * n_ptr,
	const Matrix< double > * m_ptr1, const Matrix< double > * m_ptr2, 
	const double & desired_error, double & rate )
{
	// check to make sure all data is valid
	assert( n_ptr ); assert( m_ptr1 ); assert( m_ptr2 );
	assert( ( * ( n_ptr->End() - 1 ) )->GetSizeOutput() == m_ptr2->GetColumns() );

	// backpropagation loop
	std::vector< unsigned int > within_desired_error;
	std::vector< unsigned int > outside_desired_error;
	bool error = true;
	for ( unsigned int i = 0; i < m_ptr1->GetRows(); ++i )
	{
		n_ptr->Propagate( m_ptr1->GetRow( i ) );
		if ( n_ptr->Error( m_ptr2->GetRow( i ) ) < desired_error )
		{
			within_desired_error.push_back( i );
		}
		else
		{
			outside_desired_error.push_back( i );
			error = false;
		}
	}

	// output stats
	rate = ( ( ( double ) outside_desired_error.size() ) / ( ( double ) m_ptr1->GetRows() ) );
	return error;
}

///////////////////////////////////////////////////////////////////////
// apply nn to input data set
// round to -1 or 1 respectively if rounding is set
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API void SupervisedApplyM( NeuralMacroStructure< double > * n_ptr,
	const Matrix< double > * m_ptr1, Matrix< double > * m_ptr2, bool rounding )
{
	// check to make sure all data is valid
	assert( n_ptr ); assert( m_ptr1 ); assert( m_ptr2 );
	assert( ( * ( n_ptr->End() - 1 ) )->GetSizeOutput() == m_ptr2->GetColumns() );

	// application loop: apply row by row
	for ( unsigned int i = 0; i < m_ptr1->GetRows(); ++i )
	{
		n_ptr->Propagate( m_ptr1->GetRow( i ) );
		m_ptr2->PutRow( n_ptr->GetOutput(), i );

		if ( rounding )
		{
			for ( unsigned int j = 0; j < m_ptr2->GetColumns(); ++j )
				m_ptr2->At( i, j ) = ( ( m_ptr2->At( i, j ) < 0 ) ? -1.0 : 1.0 );
		}
	}
}

extern "C" NEURAL_ALGORITHM_API double SupervisedGetErrorM( NeuralMacroStructure< double > * n_ptr, 
	const Matrix< double > * m_ptr1, const Matrix< double > * m_ptr2 )
{
	assert( n_ptr ); assert( m_ptr1 ); assert( m_ptr2 ); 
	assert( ( * ( n_ptr->End() - 1 ) )->GetSizeOutput() == m_ptr2->GetColumns() );

        double total_error = 0.0;
        for ( unsigned int i = 0; i < m_ptr1->GetRows(); ++i )
        {
		n_ptr->Propagate( m_ptr1->GetRow( i ) );
                total_error += n_ptr->Error( m_ptr2->GetRow( i ) );
        }
        return total_error;
}

///////////////////////////////////////////////////////////////////////
// unsupervised learning algorithm using simple cluster library
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool UnsupervisedAlgorithmM( NeuralMacroStructure< double > * n_ptr, SimpleCluster< double > * c_ptr, 
	const Matrix< double > * m_ptr, unsigned int & index, const unsigned int & max_iterations, const double & desired_error, unsigned int & clusters )
{
	// check to make sure all data is valid
	assert( n_ptr ); assert( c_ptr ); assert( m_ptr );

	// parameters for training algorithm.
	// index - keeps track of iterations
	// error - boolean: true if all vectors yield less than desired error 
	const unsigned int size_cluster = ( ( * ( n_ptr->End() - 1 ) ) )->GetSizeOutput();
	std::vector< double > center_temp( size_cluster );
	bool error = false;
	double * cluster_data = new double [ size_cluster ];

	// unsupervised training loop
	while ( index < max_iterations && ! error )
	{
		error = true;
		for ( unsigned int i = 0; i < m_ptr->GetRows(); ++i )
		{
			// propagate and grab output
			n_ptr->Propagate( m_ptr->GetRow( i ) );
			n_ptr->GetOutput( cluster_data, size_cluster );

			// determine centers
			for ( unsigned int i = 0; i < size_cluster; ++i )
			{
				// determine center
				center_temp.at( i ) = ( ( cluster_data[ i ] >= 0 ) ? 1.0 : -1.0 );

				// determine center for use in backpropagation later
				cluster_data[ i ] = ( ( cluster_data[ i ] >= 0 ) ? 1.0 : -1.0 );
			}

			// check to see if it is in a cluster, if not add the new cluster
			if ( ( c_ptr->GetDistance( center_temp ) > 0.0 ) || ( c_ptr->GetDistance( center_temp ) == -1.0 ) )
				c_ptr->AddCluster( center_temp );
			
			// if distance between output and cluster center < desired error, move on 
			//	otherwise strengthen connections via backpropagation
			if ( n_ptr->Error( cluster_data, size_cluster ) > desired_error )
			{
				n_ptr->BackPropagate( cluster_data, size_cluster );
				error = false;
			}
		}
		++index;
	}

	clusters = c_ptr->Size();

	// clean up
	delete [] cluster_data;

	return error;
}

///////////////////////////////////////////////////////////////////////
// Unsupervised cross validation: apply trained nn to cross validation
// data.  Determine the number of outliers, ie, elements whos 
// mapping from the NN did fall into any of the clusters
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool UnsupervisedCrossValidationM( NeuralMacroStructure< double > * n_ptr, 
	SimpleCluster< double > * c_ptr, const Matrix< double > * m_ptr, const double & desired_error, double & rate )
{
	// check to make sure all data is valid
	assert( n_ptr ); assert( c_ptr ); assert( m_ptr );

	// parameters for training algorithm.
	// error - boolean: true if all vectors yield less than desired error 
	std::vector< unsigned int > within_desired_error;
	std::vector< unsigned int > outside_desired_error;
	unsigned int size_cluster = c_ptr->SizeCluster();
	double * cluster_data = new double [ size_cluster ];

	bool error = true;
	for ( unsigned int i = 0; i < m_ptr->GetRows(); ++i )
	{
		n_ptr->Propagate( m_ptr->GetRow( i ) );
		n_ptr->GetOutput( cluster_data, size_cluster );
		std::vector< double > cluster_temp( cluster_data, cluster_data + size_cluster );

		// find distance with respect to neural network distance function
		// this is: one half of the euclidean distance squared
		if ( c_ptr->GetDistance( cluster_temp ) < desired_error )
		{
			within_desired_error.push_back( i );
		}
		else
		{
			outside_desired_error.push_back( i );
			error = false;
		}
	}

	rate = ( ( ( double ) outside_desired_error.size() ) / ( ( double ) m_ptr->GetRows() ) );

	// clean up
	delete [] cluster_data;

	return error;
}

///////////////////////////////////////////////////////////////////////
// apply neural network to unsupervised data set
// record the cluster centroid index into centers array
// not that indices array must be the same length as data1 has rows
// - if data is not in a cluster, then record index as -1
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API void UnsupervisedApplyM( NeuralMacroStructure< double > * n_ptr,
	SimpleCluster< double > * c_ptr,
	const Matrix< double > * m_ptr, int * indices )
{
	// check to make sure all data is valid
	assert( n_ptr ); assert( c_ptr ); assert( m_ptr );

	unsigned int size_column = c_ptr->SizeCluster();
	double * cluster_data = new double [ size_column ];
	for ( unsigned int i = 0; i < m_ptr->GetRows(); ++i )
	{
		n_ptr->Propagate( m_ptr->GetRow( i ) );
		n_ptr->GetOutput( cluster_data, size_column );
		std::vector< double > cluster_temp( cluster_data, cluster_data + size_column );
		* ( indices + i ) =  c_ptr->GetIndex( cluster_temp );
	}

	// clean up
	delete [] cluster_data;
}

///////////////////////////////////////////////////////////////////////
// Neural algorithms assuming double array input
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool SupervisedAlgorithm( NeuralMacroStructure< double > * n_ptr,
	const double ** data1, const double ** data2,
	const unsigned int & rows, const unsigned int & columns1, const unsigned int & columns2,
	unsigned int & index, const unsigned int & max_iterations, const double & desired_error )
{
	// check to make sure all data is valid
	assert( n_ptr ); assert( data1 ); assert( data2 ); 
	const Matrix< double > m1( data1, rows, columns1 ); const Matrix< double > m2( data2, rows, columns2 );
	return SupervisedAlgorithmM( n_ptr, & m1, & m2, index, max_iterations, desired_error);
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool SupervisedCrossValidation( NeuralMacroStructure< double > * n_ptr,
	const double ** data1, const double ** data2,
	const unsigned int & rows, const unsigned int & columns1, const unsigned int & columns2,
	const double & desired_error, double & rate )
{
	// check to make sure all data is valid
	assert( n_ptr ); assert( data1 ); assert( data2 ); 
	assert( ( * ( n_ptr->End() - 1 ) )->GetSizeOutput() == columns2 );
	const Matrix< double > m1( data1, rows, columns1 ); const Matrix< double > m2( data2, rows, columns2 );
	return SupervisedCrossValidationM( n_ptr, & m1, & m2, desired_error, rate );
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API void SupervisedApply( NeuralMacroStructure< double > * n_ptr,
	const double ** data1, double ** data2, const unsigned int & rows1, const unsigned int & columns1, const unsigned int & columns2, bool rounding )
{
	// check to make sure all data is valid
	assert( n_ptr ); assert( data1 ); assert( data2 );
	assert( ( * ( n_ptr->End() - 1 ) )->GetSizeOutput() == columns2 );

	// matrix representation of data2
	const Matrix< double > m1( data1, rows1, columns1 ); Matrix< double > m2( ( const double ** ) data2, rows1, columns2 );
	SupervisedApplyM( n_ptr, & m1, & m2, rounding );

	// copy data to output array
	m2.Convert( data2, rows1, columns2 );
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API double SupervisedGetError( NeuralMacroStructure< double > * n_ptr,
	const double ** data1, const double ** data2, const unsigned int & rows, const unsigned int & columns1, const unsigned int & columns2 )
{
	assert( data1 ); assert( data2 );
	assert( ( * ( n_ptr->End() - 1 ) )->GetSizeOutput() == columns2 );
	const Matrix< double > m1( data1, rows, columns1 ); const Matrix< double > m2( data2, rows, columns2 );
	return SupervisedGetErrorM( n_ptr, & m1, & m2 );
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool UnsupervisedAlgorithm( NeuralMacroStructure< double > * n_ptr,
	SimpleCluster< double > * c_ptr, 
	const double ** data1, const unsigned int & rows1, const unsigned int & columns1,
	unsigned int & index, const unsigned int & max_iterations, const double & desired_error, unsigned int & clusters )
{
	// check to make sure all data is valid
	assert( n_ptr ); assert( c_ptr ); assert( data1 );
	const Matrix< double > m1( data1, rows1, columns1 );
	return UnsupervisedAlgorithmM( n_ptr, c_ptr, & m1, index, max_iterations, desired_error, clusters );
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool UnsupervisedCrossValidation( NeuralMacroStructure< double > * n_ptr,
	SimpleCluster< double > * c_ptr,
	const double ** data1, const unsigned int & rows1, const unsigned int & columns1, 
	const double & desired_error, double & rate )
{
	// check to make sure all data is valid
	assert( n_ptr ); assert( c_ptr ); assert( data1 ); 
	const Matrix< double > m1( data1, rows1, columns1 );
	return UnsupervisedCrossValidationM( n_ptr, c_ptr, & m1, desired_error, rate );
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API void UnsupervisedApply( NeuralMacroStructure< double > * n_ptr,
	SimpleCluster< double > * c_ptr,
	const double ** data1, const unsigned int & rows1, const unsigned int & columns1, int * indices )
{
	assert( n_ptr ); assert( c_ptr ); assert( data1 ); 
	const Matrix< double > m1( data1, rows1, columns1 );
	UnsupervisedApplyM( n_ptr, c_ptr, & m1, indices );
}

///////////////////////////////////////////////////////////////////////
// Neural algorithms assuming preprocessor input
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool SupervisedAlgorithmP( NeuralMacroStructure< double > * n_ptr,
	const Preprocessor * p_ptr1, const Preprocessor * p_ptr2, unsigned int & index, 
	const unsigned int & max_iterations, const double & desired_error )
{
	assert( p_ptr1 ); assert( p_ptr2 );
	return SupervisedAlgorithm( n_ptr, p_ptr1->GetData(), p_ptr2->GetData(), p_ptr1->GetRows(), 
		p_ptr1->GetCols(), p_ptr2->GetCols(), index, max_iterations, desired_error );
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool SupervisedCrossValidationP( NeuralMacroStructure< double > * n_ptr, 
	const Preprocessor * p_ptr1, const Preprocessor * p_ptr2, const double & desired_error, double & rate )
{
	assert( p_ptr1 ); assert( p_ptr2 );
	return SupervisedCrossValidation( n_ptr, p_ptr1->GetData(), p_ptr2->GetData(), p_ptr1->GetRows(), 
		p_ptr1->GetCols(), p_ptr2->GetCols(), desired_error, rate );
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API void SupervisedApplyP( NeuralMacroStructure< double > * n_ptr,
	const Preprocessor * p_ptr1, Preprocessor * p_ptr2, bool rounding )
{
	assert( p_ptr1 ); assert( p_ptr2 );
	SupervisedApply( n_ptr, p_ptr1->GetData(), p_ptr2->GetData(), p_ptr1->GetRows(), 
		p_ptr1->GetCols(), p_ptr2->GetCols(), rounding );
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API double SupervisedGetErrorP( NeuralMacroStructure< double > * n_ptr,
	const Preprocessor * p_ptr1, const Preprocessor * p_ptr2 )
{
	assert( p_ptr1 ); assert( p_ptr2 );
	return SupervisedGetError( n_ptr,
		p_ptr1->GetData(), p_ptr2->GetData(), p_ptr1->GetRows(), p_ptr1->GetCols(), p_ptr2->GetCols() );
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool UnsupervisedAlgorithmP( NeuralMacroStructure< double > * n_ptr,
	SimpleCluster< double > * c_ptr, const Preprocessor * p_ptr, unsigned int & index, 
	const unsigned int & max_iterations, const double & desired_error, unsigned int & clusters )
{
	assert( p_ptr ); assert( c_ptr );
	return UnsupervisedAlgorithm( n_ptr, c_ptr, p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols(), index, max_iterations, desired_error, clusters );
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API bool UnsupervisedCrossValidationP( NeuralMacroStructure< double > * n_ptr,
	SimpleCluster< double > * c_ptr, const Preprocessor * p_ptr, const double & desired_error, double & rate )
{
	assert( p_ptr ); assert( c_ptr );
	return UnsupervisedCrossValidation( n_ptr, c_ptr, p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols(), desired_error, rate );
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
extern "C" NEURAL_ALGORITHM_API void UnsupervisedApplyP( NeuralMacroStructure< double > * n_ptr,
	SimpleCluster< double > * c_ptr, const Preprocessor * p_ptr, int * clusters )
{
	assert( p_ptr ); assert( c_ptr );
	UnsupervisedApply( n_ptr, c_ptr, p_ptr->GetData(), p_ptr->GetRows(), p_ptr->GetCols(), clusters );
}
