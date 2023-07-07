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
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>

namespace MathLib
{

namespace Metrics
{

/////////////////////////////////////////////////////////////////////////////////
// Distance Functions
/////////////////////////////////////////////////////////////////////////////////

template< class T >
class ParentDistance
{
	public :

		typedef T value_type;
		
		ParentDistance( const typename std::vector< value_type > & sample ) : sample_( sample ) {}

		ParentDistance( const value_type * sample, const unsigned int & size_sample ) : sample_( sample, sample + size_sample ) {}

		virtual ~ParentDistance(void ) {}

		virtual inline const value_type operator () ( const typename std::vector< value_type > * cluster ) = 0;
                                                         
		virtual inline const value_type operator () ( const value_type * cluster, const unsigned int & size_cluster ) = 0;

	protected :

		std::vector< value_type > sample_;
};

template< class T >
class Euclidean : protected ParentDistance< T >
{
	public :

		typedef T value_type;

		Euclidean( const typename std::vector< value_type > & sample ) : ParentDistance< double >( sample ) {}

		Euclidean( const value_type * sample, const unsigned int & size_sample ) : ParentDistance< double >( sample, size_sample ) {}

		inline const value_type operator () ( const typename std::vector< value_type > * cluster )
		{
			value_type return_value = 0.0;
			typename std::vector< value_type >::const_iterator it = this->sample_.begin();
			typename std::vector< value_type >::const_iterator jt = cluster->begin();
			for( ; jt != cluster->end(); ++jt, ++it )
			{
				return_value += ( ( * jt ) - ( * it ) ) * ( ( * jt ) - ( * it ) );
			}
			return pow( return_value, ( value_type ) 0.5 );
		}

		inline const value_type operator () ( const value_type * cluster, const unsigned int & size_cluster )
		{
			value_type return_value = 0.0;
			typename std::vector< value_type >::const_iterator it = this->sample_.begin();
			const value_type * jt = cluster;
			for( ; jt != cluster + size_cluster; ++jt, ++it )
			{
				return_value += ( ( * jt ) - ( * it ) ) * ( ( * jt ) - ( * it ) );
			}
			return pow( return_value, ( value_type ) 0.5 );
		}
};

template< class T >
class Manhattan : protected ParentDistance< T >
{
	public :

		typedef T value_type;
		
		Manhattan( const typename std::vector< value_type > & sample ) : ParentDistance< double >( sample ) {}

		Manhattan( const value_type * sample, const unsigned int & size_sample ) : ParentDistance< double >( sample, size_sample ) {}

		inline const value_type operator () ( const typename std::vector< value_type > * cluster )
		{
			value_type return_value = 0.0;
			typename std::vector< value_type >::const_iterator it = this->sample_.begin();
			typename std::vector< value_type >::const_iterator jt = cluster->begin();
			for( ; jt != cluster->end(); ++jt, ++it )
			{
				return_value += ( ( * jt ) - ( * it ) );
			}
			return return_value;
		}

		inline const value_type operator () ( const value_type * cluster, const unsigned int & size_cluster )
		{
			value_type return_value = 0.0;
			typename std::vector< value_type >::const_iterator it = this->sample_.begin();
			for( const value_type * jt = cluster; jt != cluster + size_cluster; ++jt, ++it )
			{
				return_value += ( ( * jt ) - ( * it ) );
			}
			return return_value;
		}
};

template< class T >
class Neural : protected ParentDistance< T >
{
	public :

		typedef T value_type;
		
		Neural( const typename std::vector< value_type > & sample ) : ParentDistance< double >( sample ) {}

		Neural( const value_type * sample, const unsigned int & size_sample ) : ParentDistance< double >( sample, size_sample ) {}

		inline const value_type operator () ( const typename std::vector< value_type > * cluster )
		{
			value_type return_value = 0.0;
			typename std::vector< value_type >::const_iterator it = this->sample_.begin();
			typename std::vector< value_type >::const_iterator jt = cluster->begin();
			for( ; jt != cluster->end(); ++jt, ++it )
			{
				return_value += ( ( * jt ) - ( * it ) ) * ( ( * jt ) - ( * it ) );
			}
			return 0.5 * return_value;
		}

		inline const value_type operator () ( const value_type * cluster, const unsigned int & size_cluster )
		{
			value_type return_value = 0.0;
			typename std::vector< value_type >::const_iterator it = this->sample_.begin();
			const value_type * jt = cluster;
			for( ; jt != cluster + size_cluster; ++jt, ++it )
			{
				return_value += ( ( * jt ) - ( * it ) ) * ( ( * jt ) - ( * it ) );
			}
			return 0.5 * return_value;
		}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gaussian distance function.  
// - Note that the standard deviation parameter here, is also called the 'squashing' parameter.  
//   It is included here as a private variable since it has many different meanings depending on the
//   application 
////////////////////////////////////////////////////////////////////////////////////////////////////////

template< class T >
class Gaussian : protected ParentDistance< T >
{
	public :

		typedef T value_type;

		Gaussian( const typename std::vector< value_type > & sample ) : 
			ParentDistance< double >( sample ), sigma_( ( value_type ) 1.0 ) {}

		Gaussian( const typename std::vector< value_type > & sample, const value_type & s ) : 
			ParentDistance< double >( sample ), sigma_( s ) {}
		
		Gaussian( const value_type * sample, const unsigned int & size_sample ) : 
			ParentDistance< double >( sample, size_sample ), sigma_( ( value_type ) 1.0 ) {}

		Gaussian( const value_type * sample, const unsigned int & size_sample , const value_type & s ) : 
			ParentDistance< double >( sample, size_sample ), sigma_( s ) {}
	
		inline const value_type operator () ( const typename std::vector< value_type > * cluster )
		{
			value_type return_value = 0.0;
			typename std::vector< value_type >::const_iterator it = this->sample_.begin();
			typename std::vector< value_type >::const_iterator jt = cluster->begin();

			for( ; jt != cluster->end(); ++jt, ++it )
			{
				return_value += ( ( * jt ) - ( * it ) );
			}
			return_value *= return_value;

			if ( this->sigma_ == 0.0 )
				return 1.0;
			return exp( -1.0 * ( return_value / ( 4 * this->sigma_ * this->sigma_ ) ) );
		}

		inline const value_type operator () ( const value_type * cluster, const unsigned int & size_cluster )
		{
			value_type return_value = 0.0;
			typename std::vector< value_type >::const_iterator it = this->sample_.begin();

			for( const value_type * jt = cluster; jt != cluster + size_cluster; ++jt, ++it )
			{
				return_value += ( ( * jt ) - ( * it ) );
			}
			return_value *= return_value;

			if ( this->sigma_ == 0.0 )
				return 1.0;
			return exp( -1.0 * ( return_value / ( 4 * this->sigma_ * this->sigma_ ) ) );
		}

	private :

		value_type sigma_;
};

} // Metrics

} // MathLib
