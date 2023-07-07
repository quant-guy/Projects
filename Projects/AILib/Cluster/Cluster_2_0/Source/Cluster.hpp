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
#ifndef AILIB_CLUSTER_H
#define AILIB_CLUSTER_H
#include <Metrics.hpp>
#include <Preprocessor.hpp>
#include <Random.hpp>

namespace AILib
{

namespace Cluster
{

///////////////////////////////////////////////////////////////////////////////////////
// ParentCluster : parent object for cluster
//  - provides all the functionality for clustering algorithms, e.g. AddCluster, 
//  Constructors, GetDistance, GetIndex (get cluster centroid id), etc.
//  - provides virtual and purely virtual training methods.
//  -- Train : run the clustering algorithm against a data set
//  -- Apply : given a data set, run an (already trained) algorithm.  A value_type
//     array is returned containing the indices of the respective centroids, and
//     their distance to the sample
//  -- CrossValidate : same as apply, accept an error rate is returned
//  -- GetError : get total error from the data and centroids (sum of all distance from
//     centroids
///////////////////////////////////////////////////////////////////////////////////////

template< class T >
class ParentCluster
{
	friend ostream & operator << ( ostream & strm, const ParentCluster< T > & pc )
	{
		typename std::vector< std::vector< value_type > * >::const_iterator it = pc.clusters_.begin();
		typename std::vector< value_type >::const_iterator jt;
		for ( ; it != pc.clusters_.end(); ++it )
		{
			jt = ( * it )->begin(); 
			strm << * jt; ++jt;
			for ( ; jt != ( * it )->end(); ++jt )
			{
				strm << ", " << * jt;
			}
			strm << endl;
		}
		return strm;
	}

	public :

		typedef T value_type;

		ParentCluster( void ) : clusters_( 0 ) {}

		ParentCluster( const char * filename ) 
		{
			preprocessor::Preprocessor p( filename, ", " );
			
			const value_type ** v_ptr = ( const value_type ** ) p.GetData();
			for ( ; v_ptr != p.GetData() + p.GetRows(); ++v_ptr )
			{
				 
				this->clusters_.push_back( new std::vector< value_type >( ( * v_ptr ), ( * v_ptr ) + p.GetCols() ) );
			}
		}

		ParentCluster( const value_type ** clusters, const unsigned int & rows, const unsigned int & cols )
		{
			const value_type ** it = clusters;
			for ( ; it != clusters + rows; ++ it )
			{
				this->clusters_.push_back( new std::vector< value_type >( ( * it ), ( * it ) + cols ) );
			}
		}

		ParentCluster( preprocessor::Preprocessor * p )
		{
			const value_type ** clusters = ( const value_type ** ) p->GetData();
			const value_type ** it = clusters;
			const unsigned int rows = p->GetRows();
			const unsigned int cols = p->GetCols();
			for ( ; it != clusters + rows; ++ it )
			{
				this->clusters_.push_back( new std::vector< value_type >( ( * it ), ( * it ) + cols ) );
			}
		}

		virtual ~ParentCluster( void ) { this->DeleteAll(); }

		virtual inline void DeleteAll( void )
		{
			while ( ! this->clusters_.empty() )
			{
				delete this->clusters_.back(); this->clusters_.pop_back();
			}
		}

		virtual inline void GetCluster( const char * filename )
		{
			preprocessor::Preprocessor p( filename, ", " );
			
			this->DeleteAll();
			const value_type ** v_ptr = ( const value_type ** ) p.GetData();
			for ( ; v_ptr != p.GetData() + p.GetRows(); ++v_ptr )
			{
				this->clusters_.push_back( new std::vector< value_type > ( ( * v_ptr ), ( * v_ptr ) + p.GetCols() ) );
			}
		}

		virtual inline void AddCluster( const std::vector< value_type > & c ) 
		{ 	
			this->clusters_.push_back( new std::vector< value_type >( c.begin(), c.end() ) ); 
		}

		virtual inline void AddCluster( const value_type * c, const unsigned int & size_c ) 
		{ 	
			this->clusters_.push_back( new std::vector< value_type >( c, c + size_c ) ); 
		}

		virtual inline const value_type GetDistance( const std::vector< value_type > & sample ) const
		{
			if ( this->clusters_.empty() )
				return -1.0;
			typename std::vector< value_type > data( this->clusters_.size() );
			transform( this->clusters_.begin(), this->clusters_.end(), data.begin(), 
				MathLib::Metrics::Euclidean< value_type >( sample ) );
			return * min_element( data.begin(), data.end() );
		}

		virtual inline const unsigned int GetIndex( const std::vector< value_type > & sample ) const
		{
			if ( this->clusters_.empty() )
				return -1;
			typename std::vector< value_type > data( this->clusters_.size() );
			transform( this->clusters_.begin(), this->clusters_.end(), data.begin(), 
				MathLib::Metrics::Euclidean< value_type >( sample ) );
			return ( min_element( data.begin(), data.end() ) - data.begin() );
		}

		virtual inline const value_type GetDistance( const value_type * sample, const unsigned int & size_sample ) const
		{
			if ( this->clusters_.empty() )
				return -1.0;
			typename std::vector< value_type > data( this->clusters_.size() );
			transform( this->clusters_.begin(), this->clusters_.end(), data.begin(), 
				MathLib::Metrics::Euclidean< value_type >( sample, size_sample ) );
			return * min_element( data.begin(), data.end() );
		}

		virtual inline const unsigned int GetIndex( const value_type * sample, const unsigned int & size_sample ) const
		{
			if ( this->clusters_.empty() )
				return -1;
			typename std::vector< value_type > data( this->clusters_.size() );
			transform( this->clusters_.begin(), this->clusters_.end(), data.begin(), 
				MathLib::Metrics::Euclidean< value_type >( sample, size_sample ) );
			return ( min_element( data.begin(), data.end() ) - data.begin() );
		}

		virtual inline const unsigned int Size( void ) const { return this->clusters_.size(); }

		virtual inline const unsigned int SizeCluster( void ) const { return this->clusters_.at( 0 )->size(); }

		virtual inline void Train( const value_type ** data, const unsigned int & rows, const unsigned int & cols ) = 0; 

		virtual inline value_type CrossValidate( const value_type ** data, const unsigned int & rows, const unsigned int & cols, 
			 value_type ** indices, const unsigned int & rows_indices, const unsigned int & cols_indices, const value_type & tolerance )
		{
			assert( rows ); assert( cols_indices == 2 ); assert( rows_indices == rows );
			value_type ** jt = indices;
			unsigned int error = 0;
			for ( const value_type ** it = data; it != data + rows; ++it, ++jt )
			{
				( * jt )[ 0 ] = ( value_type ) this->GetIndex( * it, cols );
				( * jt )[ 1 ] = this->GetDistance( * it, cols );
				if ( ( * jt )[ 1 ] > tolerance )
					++error;
			}
			return ( ( value_type ) error ) / ( ( value_type ) rows );
		}

		virtual inline void Apply( const value_type ** data, const unsigned int & rows, const unsigned int & cols, 
			 value_type ** indices, const unsigned int & rows_indices, const unsigned int & cols_indices )
		{
			assert( cols_indices == 2 ); assert( rows_indices == rows );
			value_type ** jt = indices;

			for ( const value_type ** it = data; it != data + rows; ++it, ++jt )
			{
				( * jt )[ 0 ] = ( value_type ) this->GetIndex( * it, cols );
				( * jt )[ 1 ] = this->GetDistance( * it, cols );
			}
		}

		virtual inline value_type GetError( const value_type ** data, const unsigned int & rows, const unsigned int & cols )
		{
			value_type return_value = ( value_type ) 0;
			for ( const value_type ** it = data; it != data + rows; ++it )
			{
				return_value += this->GetDistance( * it, cols );
			}
			return return_value;
		}

	protected :

		std::vector< std::vector< value_type > * > clusters_;
};

template< class T >
class KMeans : protected ParentCluster< T >
{
	friend ostream & operator << ( ostream & strm, const KMeans< T > & k )
	{
		ParentCluster< T > * pc = dynamic_cast< ParentCluster< T > * >( ( KMeans< T > * ) & k );
		strm << * pc;
		return strm;
	}

	public :

		MathLib::Random::MersenneTwister mt;

		typedef T value_type;

		KMeans( void ) : ParentCluster< value_type>(), k_( 0 ) {}

		KMeans( const unsigned int & k ) : ParentCluster< value_type>(), k_( k ) {}

		void GetCluster( const char * filename ) { ParentCluster< value_type >::GetCluster( filename ); }

		inline void Initialize( const value_type ** data, const unsigned int & rows, const unsigned int & cols )
		{
			ParentCluster< value_type >::DeleteAll();

			value_type element_min = 0;
			value_type element_max = 0;
			typename std::vector< value_type > temp( cols, ( value_type ) 0.0 );
			typename std::vector< value_type > max_elements( cols, ( value_type ) 0.0 );
			typename std::vector< value_type > mean_elements( cols, ( value_type ) 0.0 );

			copy( * ( data + 0 ), ( * ( data + 0 ) ) + cols, max_elements.begin() );

			for ( unsigned int i = 0; i < rows; ++i )
			{
				for ( unsigned int j = 0; j < cols; ++j )
				{
					if ( * ( * ( data + i ) + j ) > max_elements.at( j ) )
						max_elements.at( j ) = * ( * ( data + i ) + j );
					mean_elements.at( j ) += * ( * ( data + i ) + j );
				}
			}

			if ( rows )
			{
				transform( mean_elements.begin(), mean_elements.end(), mean_elements.begin(), 
					bind2nd( std::divides< value_type >(), ( value_type ) rows ) );
			}

			for ( unsigned int i = 0; i < this->k_; ++i )
			{
				for ( unsigned int j = 0; j < cols; ++j )
				{
					element_min = mean_elements.at( j ) - max_elements.at( j );
					element_max = mean_elements.at( j ) + max_elements.at( j );
					temp.at( j ) = ( value_type ) mt( ( double ) element_min, ( double ) element_max );
				}
				this->AddCluster( temp );
			}
		}

		inline void Train( const value_type ** data, const unsigned int & rows, const unsigned int & cols ) 
		{
			unsigned int centers = 0;
			typename std::vector< value_type > center_temp( cols, ( value_type ) 0.0 );

			value_type ** temp = new value_type * [ rows ];
			for ( unsigned int i = 0; i < rows; ++i )
			{
				temp[ i ] = new value_type [ 2 ];
			}
			
			this->Apply( data, rows, cols, temp, rows, 2 );

			bool convergence = false;
			while ( ! convergence )
			{
				convergence = true;
				for ( unsigned int k = 0; k < this->k_; ++k )
				{
					centers = 0;
					std::fill( center_temp.begin(), center_temp.end(), ( value_type ) 0.0 );

					for ( unsigned int i = 0; i < rows; ++i )
					{
						if ( * ( * ( temp + i ) ) == k )
						{
							++centers;
							std::transform( center_temp.begin(), center_temp.end(), * ( data + i ), 
								center_temp.begin(), std::plus< value_type >() );
						}
					}

					if ( centers )
					{
						std::transform( center_temp.begin(), center_temp.end(), center_temp.begin(), 
							bind2nd( std::divides< value_type >(), ( value_type ) centers ) );
					}

					if( ! std::equal( center_temp.begin(), center_temp.end(), this->clusters_.at( k )->begin() ) )
					{
						convergence = false;
						std::copy( center_temp.begin(), center_temp.end(), this->clusters_.at( k )->begin()  );
					}
				}
			}

			for ( unsigned int i = 0; i < rows; ++i )
			{
				delete [] temp[ i ];
			}
			delete [] temp;
		}

		inline value_type CrossValidate( const value_type ** data, const unsigned int & rows, const unsigned int & cols, 
			 value_type ** indices, const unsigned int & rows_indices, const unsigned int & cols_indices, const value_type & tolerance )
		{
			return ParentCluster< value_type >::CrossValidate( data, rows, cols, indices, rows_indices, cols_indices, tolerance );
		}

		inline void Apply( const value_type ** data, const unsigned int & rows, const unsigned int & cols, 
			 value_type ** indices, const unsigned int & rows_indices, const unsigned int & cols_indices )
		{
			ParentCluster< value_type >::Apply( data, rows, cols, indices, rows_indices, cols_indices );
		}

		virtual inline value_type GetError( const value_type ** data, const unsigned int & rows, const unsigned int & cols )
		{
			return ParentCluster< value_type >::GetError( data, rows, cols );
		}

	private :

		unsigned int k_;
};

template< class T >
class SelfOrganizingMap : protected ParentCluster< T >
{
	friend ostream & operator << ( ostream & strm, const SelfOrganizingMap< T > & s )
	{
		ParentCluster< T > * pc = dynamic_cast< ParentCluster< T > * >( ( SelfOrganizingMap< T > * ) & s );
		strm << * pc;
		return strm;
	}

	public :

		MathLib::Random::MersenneTwister mt;

		typedef T value_type;

		SelfOrganizingMap( void ) : 
			ParentCluster< value_type>(), n_( 0 ), r_( ( value_type ) 0.0 ), error_( ( value_type ) 0.0 ) {}

		SelfOrganizingMap( const unsigned int & n, const value_type & r, const value_type & e ) : 
			ParentCluster< value_type>(), n_( n ), r_( r ), error_( e ) {}

		void GetCluster( const char * filename ) { ParentCluster< value_type >::GetCluster( filename ); }

		inline void Initialize( const unsigned int & size_vectors )
		{
			ParentCluster< value_type >::DeleteAll();

			typename std::vector< value_type > temp( size_vectors, ( value_type ) 0.0 );

			for ( unsigned int i = 0; i < this->n_; ++i )
			{
				for ( unsigned int j = 0; j < size_vectors; ++j )
				{
					temp.at( j ) = ( value_type ) mt( -1.0, 1.0 );
				}
				this->AddCluster( temp );
			}
		}

		inline void Train( const value_type ** data, const unsigned int & rows, const unsigned int & cols ) 
		{
			assert( this->clusters_.at( 0 )->size() == cols );
			value_type * temp = new value_type [ this->n_ ];
			value_type * temp_addition = new value_type [ cols ];
			std::fill( temp, temp + this->n_, ( value_type ) 0.0 );
			value_type norm_i = ( value_type ) 0.0;
			value_type norm_v = ( value_type ) 0.0;
			unsigned int index_winner = 0;

			bool convergence = false;
			while ( ! convergence )
			{
				convergence = true;
				for ( unsigned int i = 0; i < rows; ++i )
				{
					norm_i = sqrt( std::inner_product( * ( data + i ), * ( data + i ) + cols, 
						* ( data + i ), ( value_type ) 0.0 ) );

					for ( unsigned int j = 0; j < this->n_; ++j )
					{
						temp[ j ] = std::inner_product( * ( data + i ), * ( data + i ) + cols, 
							this->clusters_.at( j )->begin(), ( value_type ) 0.0 );
						norm_v = sqrt( std::inner_product( this->clusters_.at( j )->begin(), this->clusters_.at( j )->end(), 
							this->clusters_.at( j )->begin(), ( value_type ) 0.0 ) );
						temp[ j ] /= norm_i * norm_v;
					}

					if ( 1.0 - ( * max_element( temp, temp + this->n_ ) ) > this->error_ )
					{
						convergence = false;
						index_winner = ( max_element( temp, temp + this->n_ ) - temp );

						transform( * ( data + i ), * ( data + i ) + cols, this->clusters_.at( index_winner )->begin(), temp_addition, 
							minus< value_type >() );
						transform( temp_addition, temp_addition + cols, temp_addition, 
							std::bind2nd( multiplies< value_type >(), this->r_ ) );
						transform( temp_addition, temp_addition + cols, this->clusters_.at( index_winner )->begin(),
							this->clusters_.at( index_winner )->begin(), plus< value_type >() );
					}
				}
			}
			
			delete [] temp;
			delete [] temp_addition;
		}

		inline value_type CrossValidate( const value_type ** data, const unsigned int & rows, const unsigned int & cols, 
			 value_type ** indices, const unsigned int & rows_indices, const unsigned int & cols_indices, const value_type & tolerance )
		{
			assert( cols_indices == 2 ); assert( rows_indices == rows ); assert( this->n_ == this->clusters_.size() );
			value_type * temp = new value_type [ this->n_ ];
			value_type norm_i = ( value_type ) 0.0;
			value_type norm_v = ( value_type ) 0.0;
			unsigned int errors = 0;

			for ( unsigned int i = 0; i < rows; ++i )
			{
				norm_i = sqrt( std::inner_product( * ( data + i ), * ( data + i ) + cols, 
					* ( data + i ), ( value_type ) 0.0 ) );

				for ( unsigned int j = 0; j < this->n_; ++j )
				{
						temp[ j ] = std::inner_product( * ( data + i ), * ( data + i ) + cols, 
							this->clusters_.at( j )->begin(), ( value_type ) 0.0 );
						norm_v = sqrt( std::inner_product( this->clusters_.at( j )->begin(), this->clusters_.at( j )->end(), 
							this->clusters_.at( j )->begin(), ( value_type ) 0.0 ) );
						temp[ j ] /= norm_i * norm_v;
				}
				* ( * ( indices + i ) + 0 ) = ( value_type ) * ( min_element( temp, temp + this->n_ ) - this->n_ );
				* ( * ( indices + i ) + 1 ) = ( value_type ) 1.0 - * max_element( temp, temp + this->n_ );
				if ( * ( * ( indices + i ) + 1 ) > tolerance )
					++errors;
			}
			delete [] temp;
			return ( ( value_type ) errors / rows );
		}

		inline void Apply( const value_type ** data, const unsigned int & rows, const unsigned int & cols, 
			 value_type ** indices, const unsigned int & rows_indices, const unsigned int & cols_indices )
		{
			assert( cols_indices == 2 ); assert( rows_indices == rows ); assert( this->n_ == this->clusters_.size() );
			value_type * temp = new value_type [ this->n_ ];
			value_type norm_i = ( value_type ) 0.0;
			value_type norm_v = ( value_type ) 0.0;

			for ( unsigned int i = 0; i < rows; ++i )
			{
				norm_i = sqrt( std::inner_product( * ( data + i ), * ( data + i ) + cols, 
					* ( data + i ), ( value_type ) 0.0 ) );

				for ( unsigned int j = 0; j < this->n_; ++j )
				{
					temp[ j ] = std::inner_product( * ( data + i ), * ( data + i ) + cols, 
						this->clusters_.at( j )->begin(), ( value_type ) 0.0 );
					norm_v = sqrt( std::inner_product( this->clusters_.at( j )->begin(), this->clusters_.at( j )->end(), 
						this->clusters_.at( j )->begin(), ( value_type ) 0.0 ) );
					temp[ j ] /= norm_i * norm_v;
				}
				* ( * ( indices + i ) + 0 ) = ( value_type ) * ( min_element( temp, temp + this->n_ ) - this->n_ );
				* ( * ( indices + i ) + 1 ) = ( value_type ) 1.0 - * max_element( temp, temp + this->n_ );
			}
			delete [] temp;
		}

		inline value_type GetError( const value_type ** data, const unsigned int & rows, const unsigned int & cols )
		{
			assert( this->n_ == this->clusters_.size() );
			value_type return_value = ( value_type ) 0.0;
			value_type temp_return_value = ( value_type ) 0.0;
			value_type norm_i = ( value_type ) 0.0;
			value_type norm_v = ( value_type ) 0.0;

			for ( unsigned int i = 0; i < rows; ++i )
			{
				norm_i = sqrt( std::inner_product( * ( data + i ), * ( data + i ) + cols, 
					* ( data + i ), ( value_type ) 0.0 ) );

				for ( unsigned int j = 0; j < this->n_; ++j )
				{
					temp_return_value = std::inner_product( * ( data + i ), * ( data + i ) + cols, 
						this->clusters_.at( j )->begin(), ( value_type ) 0.0 );
					norm_v = sqrt( std::inner_product( this->clusters_.at( j )->begin(), this->clusters_.at( j )->end(), 
						this->clusters_.at( j )->begin(), ( value_type ) 0.0 ) );
					temp_return_value /= norm_i * norm_v;
					return_value += ( 1.0 - temp_return_value );
				}
			}
		}

	private :

		unsigned int n_;

		value_type r_, error_;
};

// -- TODO --
template< class T >
class Topological : protected ParentCluster< T >
{
	friend ostream & operator << ( ostream & strm, const Topological< T > & t )
	{
		ParentCluster< T > * pc = dynamic_cast< ParentCluster< T > * >( ( Topological< T > * ) & t );
		strm << * pc;
		return strm;
	}

	public :

		typedef T value_type;

		Topological( void ) : ParentCluster< value_type>(), radius_( 0 ) {}

		Topological( const value_type & t ) : ParentCluster< value_type>(), radius_( t ) {}

		void GetCluster( const char * filename ) { ParentCluster< value_type >::GetCluster( filename ); }

		inline void Initialize( const value_type ** data, const unsigned int & rows, const unsigned int & cols ) 
		{
			ParentCluster< value_type >::DeleteAll();
			typename std::vector< value_type > temp( * data, * data + cols );
			this->AddCluster( temp );
		}

		inline void Train( const value_type ** data, const unsigned int & rows, const unsigned int & cols ) 
		{
			return;
		}

		inline value_type CrossValidate( const value_type ** data, const unsigned int & rows, const unsigned int & cols, 
			 value_type ** indices, const unsigned int & rows_indices, const unsigned int & cols_indices )
		{
			return ( value_type ) 0.0;
//			return ParentCluster< value_type >::CrossValidate( data, rows, cols, indices, rows_indices, cols_indices, this->radius_ );
		}

		virtual inline void Apply( const value_type ** data, const unsigned int & rows, const unsigned int & cols, 
			 value_type ** indices, const unsigned int & rows_indices, const unsigned int & cols_indices )
		{
			return;
//			ParentCluster< value_type >::Apply( data, rows, cols, indices, rows_indices, cols_indices );
		}

		virtual inline value_type GetError( const value_type ** data, const unsigned int & rows, const unsigned int & cols )
		{
			return ( value_type ) 0.0;
//			return ParentCluster< value_type >::GetError( data, rows, cols );
		}

	private :

		value_type radius_;
};

template< class T >
class SimpleCluster : protected ParentCluster< T >
{
	friend ostream & operator << ( ostream & strm, const SimpleCluster< T > & s )
	{
		ParentCluster< T > * pc = dynamic_cast< ParentCluster< T > * >( ( SimpleCluster< T > * ) & s );
		strm << * pc;
		return strm;
	}

	public :

		typedef T value_type;

		SimpleCluster( void ) : ParentCluster< value_type>(), tolerance_( ( value_type ) 0.0 ) {}

		SimpleCluster( const value_type & t ) : ParentCluster< value_type>(), tolerance_( t ) {}

		SimpleCluster( const char * filename ) : ParentCluster< value_type>(), tolerance_( ( value_type ) 0.0 )
		{ 
			ParentCluster< value_type >::GetCluster( filename ); 
		}

		void GetCluster( const char * filename ) { ParentCluster< value_type >::GetCluster( filename ); }

		inline const value_type GetDistance( const std::vector< value_type > & sample ) const
		{
			return ParentCluster< value_type >::GetDistance( sample );
		}

		inline const unsigned int GetIndex( const std::vector< value_type > & sample ) const
		{
			return ParentCluster< value_type >::GetIndex( sample );
		}

		inline const value_type GetDistance( const value_type * sample, const unsigned int & size_sample ) const
		{
			return ParentCluster< value_type >::GetDistance( sample, size_sample );
		}

		inline const unsigned int GetIndex( const value_type * sample, const unsigned int & size_sample ) const
		{
			return ParentCluster< value_type >::GetIndex( sample, size_sample );
		}

		inline void AddCluster( const std::vector< value_type > & c ) 
		{
			ParentCluster< value_type >::AddCluster( c );
		}

		inline void AddCluster( const value_type * c, const unsigned int & size_c )
		{
			ParentCluster< value_type >::AddCluster( c, size_c );
		}

		inline const unsigned int Size( void ) const { return ParentCluster< value_type >::Size(); }

		inline const unsigned int SizeCluster( void ) const { return ParentCluster< value_type >::SizeCluster(); }

		inline void Initialize( void )
		{
			ParentCluster< value_type >::DeleteAll();
		}

		inline void Train( const value_type ** data, const unsigned int & rows, const unsigned int & cols ) 
		{
			for ( const value_type ** it = data; it != data + rows; ++it )
			{
				if ( this->GetDistance( * it, cols ) > this->tolerance_ )
				{
					this->AddCluster( * it, cols );
				}
			}
		}

		inline value_type CrossValidate( const value_type ** data, const unsigned int & rows, const unsigned int & cols, 
			 value_type ** indices, const unsigned int & rows_indices, const unsigned int & cols_indices )
		{
			return ParentCluster< value_type >::CrossValidate( data, rows, cols, indices, rows_indices, cols_indices, this->tolerance_ );
		}

		virtual inline void Apply( const value_type ** data, const unsigned int & rows, const unsigned int & cols, 
			 value_type ** indices, const unsigned int & rows_indices, const unsigned int & cols_indices )
		{
			ParentCluster< value_type >::Apply( data, rows, cols, indices, rows_indices, cols_indices );
		}

		virtual inline value_type GetError( const value_type ** data, const unsigned int & rows, const unsigned int & cols )
		{
			return ParentCluster< value_type >::GetError( data, rows, cols );
		}

	private :

		value_type tolerance_;
};

} // Cluster

} // AILib

#endif // AILIB_CLUSTER_H
