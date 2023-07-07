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
#include <Matrix.hpp>
#include <MatrixFunctionality.hpp>
#include <Timing.h>
#include "CommandLineOptions.h"

int main( int argc, char ** argv )
{

	options.cmd.parse( argc, argv );

	double array[ 4 ] = { 0.0, 1.0, 2.0, 3.0 };
	MathLib::Matrix::Matrix< double > m1( 4, 4 );
	MathLib::Matrix::Matrix< double > m2( 4, 4 );
	MathLib::Matrix::Matrix< double > M( array, 2, 2 );

	Fill( m1, 1.0 );
	Fill( m2, 2.0 );

	if ( options.MulConstMatrix.isSet() )
	{
START;
		5.0 * M;
STOP;
		if ( options.Verbose.isSet() )
			cout << 5.0 * M << endl;
	}

	if ( options.Ostream.isSet() )
	{
		cout << M << endl;
	}
		      
	if ( options.Transpose.isSet() )
	{
START;
		Transpose( M );
STOP;
		if ( options.Verbose.isSet() )
		{
			cout << M << endl;
			cout << "After transpose operator" << endl;
			cout << Transpose( M ) << endl;
		}
	}

	if ( options.Sigmoid.isSet() )
	{ 
		if ( options.Verbose.isSet() )
		{
			cout << "Sigmoid" << endl;
			cout << M << endl;
		}
START;
		SIG( M, 1.0 );
STOP;
		if ( options.Verbose.isSet() )
			cout << SIG( M, 1.0 ) << endl;
	}
		    		      
	if ( options.DSigmoid.isSet() )
	{
		if ( options.Verbose.isSet() )
		{
			cout << "Derivative sigmoid" << endl;
			cout << M << endl;
		}
START;
		DSIG( M, 1.0 );
STOP;
		if ( options.Verbose.isSet() )
			cout << SIG( M, 1.0 ) << endl;
	}
		     
	if ( options.Err.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Error" << endl;
START;
		ERR( m1, m2 );
STOP;
		if ( options.Verbose.isSet() )
			cout << ERR( m1, m2 ) << endl;
	}
		  
	if ( options.Comp.isSet() )
	{
		if ( options.Verbose.isSet() )
		{
			cout << "Componentwise mult" << endl;
			cout << "M1:\n" << m1 << endl << "M2:\n" << m2 << endl;
		}
START;
		COMP( m1, m2 );
STOP;
		if ( options.Verbose.isSet() )
			cout << COMP( m1, m2 ) << endl;
	}
			  
	if ( options.Dot.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Dot product" << endl;
START;
		DOT( m1, m2 );
STOP;
		if ( options.Verbose.isSet() )
			cout << DOT( m1, m2 ) << endl;
	}
			  
	if ( options.Sum.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Sum all elements" << endl;
START;
		SUM( m1 );
STOP;
		if ( options.Verbose.isSet() )
			cout << SUM( m1 ) << endl;
	}
			  
	if ( options.Constructor1.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Constructor1" << endl;
START;
		MathLib::Matrix::Matrix< double > m3;
STOP;
	}
		 
	if ( options.Constructor2.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Constructor2" << endl;
START;
		MathLib::Matrix::Matrix< double > m3( 4, 4 );
STOP;
	}
		 
	if ( options.Constructor3.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Constructor3" << endl;
START;
		MathLib::Matrix::Matrix< double > m3( m1 );
STOP;
	}
		 
	if ( options.PutMatrix.isSet() )
	{
START;
//		m1.PutMatrix( "matrix.csv" );
STOP;
	}
		    
	if ( options.GetMatrix.isSet() )
	{
	}

	if ( options.GetRows.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Get rows" << endl;
START;
		m1.GetRows();
STOP;
		if ( options.Verbose.isSet() )
			cout << m1.GetRows() << endl;
	}
		      
	if ( options.GetColumns.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Get columns" << endl;
START;
		m1.GetColumns();
STOP;
		if ( options.Verbose.isSet() )
			cout << m1.GetColumns() << endl;
	}
		      
	if ( options.Size.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Size" << endl;
START;
		m1.Size();
STOP;
		if ( options.Verbose.isSet() )
			cout << m1.Size() << endl;
	}

	if ( options.At.isSet() )
	{
START;
		m1.At( 0 );
STOP;
		if ( options.Verbose.isSet() )
			cout << m1.At( 0 ) << endl;
	}
			   
		     
	if ( options.Addition.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Addition" << endl;
START;
		m1 + m2;
STOP;
		if ( options.Verbose.isSet() )
			cout << m1 + m2 << endl;
	}

	if ( options.Subtraction.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Subtraction" << endl;
START;
		m1 - m2;
STOP;
		if ( options.Verbose.isSet() )
			cout << m1 - m2 << endl;
	}
		  
	if ( options.Multiplication.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Multiplication" << endl;
START;
		m1 * m2;
STOP;
		if ( options.Verbose.isSet() )
			cout << M * M << endl;
	}
	       
	if ( options.Assignment.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Assignment, first = second" << endl;
START;
		m1 = m2;
STOP;
	}
		   
	if ( options.AdditionAssignment.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Addition Assignment, first += second" << endl;
START;
		m1 += m2;
STOP;
	}

	if ( options.SubtractionAssignment.isSet() )
	{
		if ( options.Verbose.isSet() )
			cout << "Addition Assignment, first -= second" << endl;
START;
		m1 -= m2;
STOP;
	}
	   
	return 0;
}
