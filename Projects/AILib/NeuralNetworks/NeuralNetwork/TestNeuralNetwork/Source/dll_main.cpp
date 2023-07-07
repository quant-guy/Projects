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
#include <Timing.h>
#include <NeuralUnit.hpp>
#include <NeuralCallers.h>

#include "CommandLineOptions.h"

int main( int argc, char ** argv )
{

	options.cmd.parse( argc, argv );

	if ( options.M_NU_ConstDest.isSet() )
	{
		NeuralUnit< float > * n_ptr = NeuralUnitConstructor();
		NeuralUnitDestructor( n_ptr );
	}

	if ( options.M_NU_ConstDest.isSet() )
	{
	}

	if ( options.M_NU_CopyConstDest.isSet() )
	{
	}

	if ( options.M_NU_DimConstDest.isSet() )
	{
	}

	if ( options.M_NU_Rho.isSet() )
	{
	}

	if ( options.M_NU_Sig.isSet() )
	{
	}

	if ( options.M_NU_SetNext.isSet() )
	{
	}

	if ( options.M_NU_SetPrev.isSet() )
	{
	}

	if ( options.M_NU_SetInput.isSet() )
	{
	}

	if ( options.M_NU_GetOutput.isSet() )
	{
	}

	if ( options.M_NU_PutNeural.isSet() )
	{
	}

	if ( options.M_NU_GetNeural.isSet() )
	{
	}

	if ( options.M_NU_Propagate1.isSet() )
	{
	}

	if ( options.M_NU_Propagate2.isSet() )
	{
	}

	if ( options.M_NU_BackPropagate1.isSet() )
	{
	}

	if ( options.M_NU_BackPropagate2.isSet() )
	{
	}

	if ( options.M_NU_Error.isSet() )
	{
	}

	if ( options.M_NMS_ConstDest.isSet() )
	{
	}

	if ( options.M_NMS_CopyConstDest.isSet() )
	{
	}

	if ( options.M_NMS_DimConstDest.isSet() )
	{
	}

	if ( options.M_NMS_PushBack.isSet() )
	{
	}

	if ( options.M_NMS_SetRho1.isSet() )
	{
	}

	if ( options.M_NMS_SetRho2.isSet() )
	{
	}

	if ( options.M_NMS_SetSig1.isSet() )
	{
	}

	if ( options.M_NMS_SetSig2.isSet() )
	{
	}

	if ( options.M_NMS_PutNeural.isSet() )
	{
	}

	if ( options.M_NMS_Propagate.isSet() )
	{
	}

	if ( options.M_NMS_BackPropagate1.isSet() )
	{
	}

	if ( options.M_NMS_BackPropagate2.isSet() )
	{
	}

	if ( options.M_NMS_Error.isSet() )
	{
	}

	return 0;
}
