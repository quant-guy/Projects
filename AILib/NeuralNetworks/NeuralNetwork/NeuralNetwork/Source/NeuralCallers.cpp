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
#include "NeuralCallers.h"

extern "C" NEURAL_API NeuralUnit< double >  *  NeuralUnitConstructor( void )
{
	return new NeuralUnit<double>();
}

extern "C" NEURAL_API NeuralUnit< double > *  NeuralUnitCopyConstructor( NeuralUnit< double > * n_ptr )
{
	assert( n_ptr );
	return new NeuralUnit< double >( * n_ptr );
}

extern "C" NEURAL_API NeuralUnit< double > *  NeuralUnitDimensionalConstructor( unsigned int rows, unsigned int cols )
{
	return new NeuralUnit< double >( rows, cols );
}

extern "C" NEURAL_API void NeuralUnitDestructor( NeuralUnit< double > * n_ptr )
{
	assert( n_ptr );
	delete n_ptr;
	n_ptr = NULL;

}

extern "C" NEURAL_API void SetLearningRateNeuralUnit( NeuralUnit< double > * n_ptr, double rho )
{
	assert( n_ptr );
	n_ptr->SetLearningRate( rho );
}

extern "C" NEURAL_API void SetSigmoidParameterNeuralUnit( NeuralUnit< double > * n_ptr, double sig )
{
	assert( n_ptr );
	n_ptr->SetSigmoidParameter( sig );
}

extern "C" NEURAL_API void SetNext( NeuralUnit< double > * n_ptr, NeuralUnit< double > * n_ptr2 )
{
	assert( n_ptr );
	assert( n_ptr2 );	
	n_ptr->SetNext( n_ptr2 );
}

extern "C" NEURAL_API void SetPrev( NeuralUnit< double > * n_ptr, NeuralUnit< double > * n_ptr2 )
{
	assert( n_ptr );
	assert( n_ptr2 );	
	n_ptr->SetPrev( n_ptr2 );
}

extern "C" NEURAL_API void SetInput( NeuralUnit< double > * n_ptr, double * input, unsigned int size )
{
	assert( n_ptr );
	n_ptr->SetInput( MathLib::Matrix::Matrix< double >( input, size, 1 )  );
}

extern "C" NEURAL_API void GetOutput( NeuralUnit< double > * n_ptr, double * output, unsigned int size )
{
	assert( n_ptr );
	MathLib::Matrix::Matrix< double > matrix_output = n_ptr->GetOutput( );
	assert( matrix_output.Size() == size );
	matrix_output.Convert( output, size );
}

extern "C" NEURAL_API void PutNeural( NeuralUnit< double > * n_ptr, std::ofstream * strm )
{
	assert( n_ptr );
	n_ptr->PutNeuralUnit( strm );
}

extern "C" NEURAL_API void GetNeural( NeuralUnit< double > * n_ptr, double * input, const unsigned int & size_input )
{
	assert( n_ptr );
	n_ptr->GetNeuralUnit( input, size_input );
}

extern "C" NEURAL_API void PropagateInput( NeuralUnit< double > * n_ptr, double * input, unsigned int size )
{
	assert( n_ptr );
	n_ptr->Propagate( MathLib::Matrix::Matrix< double >( input, size, 1 ) );
}

extern "C" NEURAL_API void PropagateNeuralUnit( NeuralUnit< double > * n_ptr )
{
	assert( n_ptr );
	n_ptr->Propagate();
}

extern "C" NEURAL_API void BackPropagateOutputNeuralUnit( NeuralUnit< double > * n_ptr, double * input, unsigned int size )
{
	assert( n_ptr );
	n_ptr->BackPropagate( MathLib::Matrix::Matrix< double >( input, size, 1 ) );
}

extern "C" NEURAL_API void BackPropagateNeuralUnit( NeuralUnit< double > * n_ptr )
{
	assert( n_ptr );
	n_ptr->BackPropagate();
}

extern "C" NEURAL_API double ErrorNeuralUnit( NeuralUnit< double > * n_ptr, double * output, unsigned int size_output )
{
	assert( n_ptr );
	return n_ptr->Error( MathLib::Matrix::Matrix< double >( output, size_output, 1 ) );
}

extern "C" NEURAL_API NeuralMacroStructure< double > *  NeuralMacroStructureConstructor( void )
{
	return new NeuralMacroStructure< double >();
}

extern "C" NEURAL_API NeuralMacroStructure< double > *  NeuralMacroStructureCopyConstructor( NeuralMacroStructure< double > * n_ptr )
{
	assert( n_ptr );
	return new NeuralMacroStructure< double >( * n_ptr );
}

extern "C" NEURAL_API NeuralMacroStructure< double > *  NeuralMacroStructureLayerConstructor( unsigned int _1, unsigned int _2, unsigned int _3 )
{
	return new NeuralMacroStructure< double >( _1, _2, _3 );
}

extern "C" NEURAL_API NeuralMacroStructure< double > *  NeuralMacroStructureFileConstructor( const char * f, unsigned int _1, double _2, double _3 )
{
	return new NeuralMacroStructure< double >( f, _1, _2, _3 );
}

extern "C" NEURAL_API NeuralMacroStructure< double > *  NeuralMacroStructureFileConstructor2( const char * f, unsigned int _1 )
{
	return new NeuralMacroStructure< double >( f, _1, 0.05, 1.0 );
}

extern "C" NEURAL_API void TimesEq( NeuralMacroStructure< double > * n_ptr, double constant )
{
	const double temp = constant;
	* n_ptr *= temp;
}

extern "C" NEURAL_API unsigned int Size( NeuralMacroStructure< double > * n_ptr  )
{
	assert( n_ptr );
	return n_ptr->Size();
}

extern "C" NEURAL_API unsigned int InputSize( NeuralMacroStructure< double > * n_ptr  )
{
	assert( n_ptr );
	return ( * n_ptr->Begin() )->GetSizeInput();
}

extern "C" NEURAL_API unsigned int OutputSize( NeuralMacroStructure< double > * n_ptr  )
{
	assert( n_ptr );
	return ( * ( n_ptr->End() - 1 ) )->GetSizeOutput();
}

extern "C" NEURAL_API unsigned int Nodes( NeuralMacroStructure< double > * n_ptr )
{
	assert( n_ptr );
	return n_ptr->Nodes();
}


extern "C" NEURAL_API void NeuralMacroStructureDestructor( NeuralMacroStructure< double > * n_ptr )
{
	assert( n_ptr );
	delete n_ptr;
	n_ptr = 0;
}

extern "C" NEURAL_API void PushBack( NeuralMacroStructure< double > * n_ptr, const NeuralUnit< double > * n_ptr2 )
{
	assert( n_ptr );
	assert( n_ptr2 );
	n_ptr->PushBack( * n_ptr2 );
}

extern "C" NEURAL_API void SetLearningRate( NeuralMacroStructure< double > * n_ptr, double rho )
{
	assert( n_ptr );
	n_ptr->SetLearningRate( rho );
}

extern "C" NEURAL_API void SetSigmoidParameter( NeuralMacroStructure< double > * n_ptr, double sig )
{
	assert( n_ptr );
	n_ptr->SetSigmoidParameter( sig );
}

extern "C" NEURAL_API double GetLearningRate( NeuralMacroStructure< double > * n_ptr )
{
	assert( n_ptr );
	return ( * n_ptr->Begin() )->GetLearningRate();
}

extern "C" NEURAL_API double GetSigmoidParameter( NeuralMacroStructure< double > * n_ptr )
{
	assert( n_ptr );
	return ( * n_ptr->Begin() )->GetSigmoidParameter();
}

extern "C" NEURAL_API void PutNeuralMacroStructure( NeuralMacroStructure< double > * n_ptr, const char * filename )
{
	assert( n_ptr );
	n_ptr->PutNeuralMacroStructure( filename );
}

extern "C" NEURAL_API void GetNeuralMacroStructure( NeuralMacroStructure< double > * n_ptr, const char * filename )
{
	assert( n_ptr );
	n_ptr->GetNeuralMacroStructure( filename );
}

extern "C" NEURAL_API void Propagate( NeuralMacroStructure< double > * n_ptr, double * input, unsigned int size_input )
{
	assert( n_ptr );
	n_ptr->Propagate( MathLib::Matrix::Matrix< double >( input, size_input, 1 ) );
}

extern "C" NEURAL_API void BackPropagate( NeuralMacroStructure< double > * n_ptr, double * output, unsigned int size_output )
{

	assert( n_ptr );
	n_ptr->BackPropagate( MathLib::Matrix::Matrix< double >( output, size_output, 1 ) );
}

extern "C" NEURAL_API void Output( NeuralMacroStructure< double > * n_ptr, double * output, unsigned int size_output )
{

	assert( n_ptr );
	( n_ptr->GetOutput() ).Convert( output, size_output );
}

extern "C" NEURAL_API double Error( NeuralMacroStructure< double > * n_ptr, double * output, unsigned int size_output )
{
	assert( n_ptr );
	return n_ptr->Error( MathLib::Matrix::Matrix< double >( output, size_output, 1 ) );
}

extern "C" NEURAL_API void PropagateM( NeuralMacroStructure< double > * n_ptr, Matrix< double > * m_ptr )
{
	assert( n_ptr );
	assert( m_ptr );
	n_ptr->Propagate( * m_ptr );
}

extern "C" NEURAL_API void BackPropagateM( NeuralMacroStructure< double > * n_ptr, Matrix< double > * m_ptr )
{

	assert( n_ptr );
	assert( m_ptr );
	n_ptr->BackPropagate( * m_ptr );
}

extern "C" NEURAL_API void OutputM( NeuralMacroStructure< double > * n_ptr, Matrix< double > * m_ptr )
{

	assert( n_ptr );
	assert( m_ptr );
	* m_ptr = n_ptr->GetOutput();
}

extern "C" NEURAL_API double ErrorM( NeuralMacroStructure< double > * n_ptr, Matrix< double > * m_ptr )
{
	assert( n_ptr );
	assert( m_ptr );
	return n_ptr->Error( * m_ptr );
}

extern "C" NEURAL_API void Print( NeuralMacroStructure< double > * n_ptr )
{
	assert( n_ptr );
	cout << * n_ptr;
	return;
}

extern "C" NEURAL_API void PrintWeights( NeuralMacroStructure< double > * n_ptr )
{
	assert( n_ptr );

	for ( NeuralMacroStructure<double>::neural_it it = n_ptr->Begin();
	      it != n_ptr->End();
	      ++it )
	{
		cout << ( ** it ) << endl;
	}

	return;
}
