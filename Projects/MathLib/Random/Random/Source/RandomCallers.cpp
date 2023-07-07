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
#include "RandomCallers.h"

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern "C" RANDOM_API MathLib::Random::CursoryRandomNumberGenerator * CRNGConstructor( void )
{
	return new MathLib::Random::CursoryRandomNumberGenerator();
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern "C" RANDOM_API void CRNGDestructor( MathLib::Random::CursoryRandomNumberGenerator * c_ptr )
{
	assert( c_ptr );
	delete c_ptr;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern "C" RANDOM_API unsigned int CRNGGenerateUint( MathLib::Random::CursoryRandomNumberGenerator * c_ptr )
{
	assert( c_ptr );
	return c_ptr->Generate();
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern "C" RANDOM_API unsigned int CRNGGenerateUintBounded( MathLib::Random::CursoryRandomNumberGenerator * c_ptr,
	unsigned int rng_min, unsigned int rng_max )
{
	assert( c_ptr );
	return c_ptr->Generate( rng_min, rng_max );
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern "C" RANDOM_API double CRNGGenerateDoubleBounded( MathLib::Random::CursoryRandomNumberGenerator * c_ptr,
	double rng_min, double rng_max )
{
	assert( c_ptr );
	return c_ptr->Generate( rng_min, rng_max );
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern "C" RANDOM_API MathLib::Random::MersenneTwister * MTConstructor( void )
{
	return new MathLib::Random::MersenneTwister();
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern "C" RANDOM_API MathLib::Random::MersenneTwister * MTSeedConstructor( unsigned int seed )
{
	return new MathLib::Random::MersenneTwister( seed );
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern "C" RANDOM_API void MTDestructor( MathLib::Random::MersenneTwister * m_ptr )
{
	assert( m_ptr );
	delete m_ptr;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern "C" RANDOM_API unsigned int MTGenerateUint( MathLib::Random::MersenneTwister * m_ptr )
{
	assert( m_ptr );
	return m_ptr->Generate();
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern "C" RANDOM_API unsigned int MTGenerateUintBounded( MathLib::Random::MersenneTwister * m_ptr, 
	unsigned int rng_min, unsigned int rng_max )
{
	assert( m_ptr );
	return m_ptr->Generate( rng_min, rng_max );
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
extern "C" RANDOM_API double MTGenerateDoubleBounded( MathLib::Random::MersenneTwister * m_ptr, 
	double rng_min, double rng_max )
{
	assert( m_ptr );
	return m_ptr->Generate( rng_min, rng_max );
}
