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
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <assert.h>
#include <algorithm>
#include <string>
#include <vector>

#include <Statistics.h>
#include <Fourier.h>

#include "Parser.h"
#include "PreprocessorMacros.h"

#define FUNCTION_FORMAT_MACRO							\
for ( double * j_ptr = data; j_ptr != data + size; ++j_ptr )			\
{										\
	* j_ptr *= 2.0; --( * j_ptr );						\
}										\

#define FORMAT_MACRO									\
for ( double ** i_ptr = this->data_; i_ptr != this->data_ + this->rows_; ++i_ptr )	\
{											\
	for ( double * j_ptr = * i_ptr; j_ptr != ( * i_ptr ) + this->cols_; ++j_ptr )	\
	{										\
		* j_ptr *= 2.0; --( * j_ptr );						\
	}										\
}

namespace preprocessor
{

// normalize with respect to ALL values in a 2D array, results range between 0 and 1
inline void NormalizeAll_0( double ** data, const unsigned int & rows, const unsigned int & cols )
{
	Normalize1( data, rows, cols );
}

// normalize with respect to ALL values in a 2D array, results range between -1 and 1
inline void NormalizeAll_1( double ** data, const unsigned int & rows, const unsigned int & cols )
{
	assert( data );
	Normalize2( data, rows, cols );
}

// normalize from 0 to 1
inline void Normalize_0( double * data, const unsigned int & size )
{
	NormalizeByRow( & data, 1, size );
}

// normalize from -1 to 1
inline void Normalize_1( double * data, const unsigned int & size )
{
	NormalizeByRow( & data, 1, size );
	FUNCTION_FORMAT_MACRO;
}

// 1 if value is greater than previous, 0 else
inline void Increasing_0( double * data, const unsigned int & size )
{
	for ( double * d_ptr = data; d_ptr != data + ( size - 1 ); ++d_ptr )
	{
		* d_ptr = ( ( * d_ptr < * ( d_ptr + 1 ) ) ? 0.0 : 1.0 );
	} 
	* ( data + ( size - 1 ) ) = 1.0;
}

inline void Increasing_1( double * data, const unsigned int & size )
{
	for ( double * d_ptr = data; d_ptr != data + ( size - 1 ); ++d_ptr )
	{
		* d_ptr = ( ( * d_ptr < * ( d_ptr + 1 ) ) ? -1.0 : 1.0 );
	} 
	* ( data + ( size - 1 ) ) = 1.0;
}

// 0 if less than mean, 1 otherwise
inline void Mean_0( double * data, const unsigned int & size )
{
	double mean = 0.0;

	for ( double * d_ptr = data; d_ptr != data + size; ++d_ptr )
	{
		mean += * d_ptr;
	}
	mean /= size;

	for ( double * d_ptr = data; d_ptr != data + size; ++d_ptr )
	{
		* d_ptr = ( ( * d_ptr < mean ) ?  0.0 : 1.0 );
	}
}

inline void Mean_1( double * data, const unsigned int & size )
{
	double mean = 0.0;

	for ( double * d_ptr = data; d_ptr != data + size; ++d_ptr )
	{
		mean += * d_ptr;
	}
	mean /= size;

	for ( double * d_ptr = data; d_ptr != data + size; ++d_ptr )
	{
		* d_ptr = ( ( * d_ptr < mean ) ?  -1.0 : 1.0 );
	}
}

inline void StdDev_0( double * data, const unsigned int & size )
{
	double mean = 0.0;
	double std_dev = 0.0;

	for ( double * d_ptr = data; d_ptr != data + size; ++d_ptr )
	{
		mean += * d_ptr;
	}
	mean /= size;

	for ( double * d_ptr = data; d_ptr != data + size; ++d_ptr )
	{
		std_dev += ( * d_ptr - mean ) * ( * d_ptr - mean );
	}
	std_dev /= ( size - 1 );

	for ( double * d_ptr = data; d_ptr != data + size; ++d_ptr )
	{
		if ( * d_ptr < mean - std_dev )
		{
			* d_ptr = 0.0;
		}
		else if ( * d_ptr > mean + std_dev )
		{
			* d_ptr = 1.0;
		}
		else
		{
			* d_ptr = 0.5;
		}
	}
}

inline void StdDev_1( double * data, const unsigned int & size )
{
	double mean = 0.0;
	double std_dev = 0.0;

	for ( double * d_ptr = data; d_ptr != data + size; ++d_ptr )
	{
		mean += * d_ptr;
	}
	mean /= size;

	for ( double * d_ptr = data; d_ptr != data + size; ++d_ptr )
	{
		std_dev += ( * d_ptr - mean ) * ( * d_ptr - mean );
	}
	std_dev /= ( size - 1 );

	for ( double * d_ptr = data; d_ptr != data + size; ++d_ptr )
	{
		if ( * d_ptr < mean - std_dev )
		{
			* d_ptr = -1.0;
		}
		else if ( * d_ptr > mean + std_dev )
		{
			* d_ptr = 1.0;
		}
		else
		{
			* d_ptr = 0.0;
		}
	}
}

// PSD normalized from [0,1]
inline void Fourier_0( double * data, const unsigned int & size )
{
	MathLib::Fourier::pwr_spec_dns2( data, size );
	NormalizeByRow( & data, 1, size );
}

// PSD normalized from [-1,1]
inline void Fourier_1( double * data, const unsigned int & size )
{
	MathLib::Fourier::pwr_spec_dns2( data, size );
	NormalizeByRow( & data, 1, size );
	FUNCTION_FORMAT_MACRO;
}

inline void Sin_0( double * data, const unsigned int & size )
{
	for ( unsigned int j = 0; j < size; ++j )
		* ( data + j ) = sin( PI * * ( data + j ) );
}

inline void Sin_1( double * data, const unsigned int & size )
{
	for ( unsigned int j = 0; j < size; ++j )
		* ( data + j ) = sin( PI * * ( data + j ) );
}

inline void Cos_0( double * data, const unsigned int & size )
{
	for ( unsigned int j = 0; j < size; ++j )
		* ( data + j ) = cos( PI * ( * ( data + j ) - 0.5 ) );
}

inline void Cos_1( double * data, const unsigned int & size )
{
	for ( unsigned int j = 0; j < size; ++j )
		* ( data + j ) = cos( PI * * ( data + j ) );
}

inline void Bias( double * data, const unsigned int & size, 
	double * return_data, const unsigned int & size_return, const unsigned int & node_size )
{
	// accounts for how many times node_size divices cols
	unsigned int extra = size / node_size;

	// accounts for extra 1's needed to pad so that we are congruent
	// find extra needed to be congruent to node_size
	extra += ( node_size - ( extra + size ) % node_size );

	// processed rows and cols are equal to their unprocessed counterparts
	unsigned int processed_size = size + extra;

	// make sure we have enough space for the extra inserted one's
	assert( processed_size <= size_return);

	// do preprocessing
	unsigned int set_back = 0;
	for ( unsigned int j = 0; j < processed_size; ++j )
	{
		if ( ( j + 1 ) % node_size == 0 && j > 0 && ( j - set_back ) < size )
		{
			++set_back;
			return_data[ j ] = 1.0;
		}
		else if ( ( j - set_back ) >= size )
		{
			return_data[ j ] = 1.0;
		}
		else
		{
			return_data[ j ] = data[ j - set_back ];
		}
	}
}

class Preprocessor
{
	friend std::ostream & operator << ( std::ostream & strm, const Preprocessor & p )
	{
		for ( unsigned int i = 0; i < p.rows_; ++i )
			Output( & strm, p.data_[ i ], p.cols_ );
		return strm;
	}

	public :

		Preprocessor( void ) : 
			rows_( 0 ), cols_( 0 ), data_( 0 ) {}

		Preprocessor( const unsigned int & rows, const unsigned int & cols ) : 
			rows_( rows ), cols_( cols )
		{
			this->data_ = new double * [ rows ]; 
			for ( unsigned int i = 0; i < rows; ++i )
				this->data_[ i ] = new double [ cols ];

			for ( unsigned int i = 0; i < rows; ++i )
			{
				for ( unsigned int j = 0; j < cols; ++j )
				{
					this->data_[ i ][ j ] = 0.0;
				}
			}
		}

		Preprocessor( double ** data, const unsigned int & rows, const unsigned int & cols ) : 
			rows_( rows ), cols_( cols )
		{
			this->data_ = new double * [ rows ]; 
			for ( unsigned int i = 0; i < rows; ++i )
				this->data_[ i ] = new double [ cols ];

			for ( unsigned int i = 0; i < rows; ++i )
			{
				for ( unsigned int j = 0; j < cols; ++j )
				{
					this->data_[ i ][ j ] = data[ i ][ j ];
				}
			}
		}

		Preprocessor( const Preprocessor & p ) : 
			rows_( p.rows_ ), cols_( p.cols_ )
		{
			this->data_ = new double * [ p.rows_ ]; 
			for ( unsigned int i = 0; i < p.rows_; ++i )
				this->data_[ i ] = new double [ p.cols_ ];

			for ( unsigned int i = 0; i < p.rows_; ++i )
			{
				for ( unsigned int j = 0; j < p.cols_; ++j )
				{
					this->data_[ i ][ j ] = p.data_[ i ][ j ];
				}
			}
		}

		Preprocessor( std::string filename, const char * tokens )
		{
			/* assert nonempty filename */
			assert( ! filename.empty() );
															
			/* file objects and pointers */                                                                 
			ifstream data_file;                                                                             
			ifstream * d_ptr;  

			/* assign file pointers */                                                                      
			data_file.open( filename.c_str() );                                     
			d_ptr = & data_file;                                                                            
															
			/* get dimensions to instantiate 2D array */                                                    
			this->cols_ = count_fields( d_ptr, tokens );             
															
			/* count lines.  This is the number of input vectors in each data set resp. */                  
			this->rows_ = count_lines( d_ptr );                                                 
															
			/* instantiate 2D data array for the two data sets */                                           
			this->data_ = new double * [ this->rows_ ];                                                           
			for ( int i = 0; i < this->rows_; ++i )                                                                
			{                                                                                               
				this->data_[ i ] = new double [ this->cols_ ];                                                         
			}                                                                                               
															
			/* get the data */                                                                              
			parser( d_ptr, tokens, this->data_, this->rows_, this->cols_ );                           
															
			/* close data set file handles to conserve memory */                                            
			data_file.close();
		}

		Preprocessor( const char * filename, const char * tokens )
		{
			/* assert nonempty filename */
			assert( filename );
															
			/* file objects and pointers */                                                                 
			ifstream data_file;                                                                             
			ifstream * d_ptr;  

			/* assign file pointers */                                                                      
			data_file.open( filename );                                     
			d_ptr = & data_file;                                                                            
															
			/* get dimensions to instantiate 2D array */                                                    
			this->cols_ = count_fields( d_ptr, tokens );             
															
			/* count lines.  This is the number of input vectors in each data set resp. */                  
			this->rows_ = count_lines( d_ptr );                                                 
															
			/* instantiate 2D data array for the two data sets */                                           
			this->data_ = new double * [ this->rows_ ];                                                           
			for ( int i = 0; i < this->rows_; ++i )                                                                
			{                                                                                               
				this->data_[ i ] = new double [ this->cols_ ];                                                         
			}                                                                                               
															
			/* get the data */                                                                              
			parser( d_ptr, tokens, this->data_, this->rows_, this->cols_ );                           
															
			/* close data set file handles to conserve memory */                                            
			data_file.close();
		}

		Preprocessor( ifstream * d_ptr, const char * tokens )
		{
			/* assert nonempty filename */
			assert( d_ptr );
															
			/* get dimensions to instantiate 2D array */                                                    
			this->cols_ = count_fields( d_ptr, tokens );             
															
			/* count lines.  This is the number of input vectors in each data set resp. */                  
			this->rows_ = count_lines( d_ptr );                                                 
															
			/* instantiate 2D data array for the two data sets */                                           
			this->data_ = new double * [ this->rows_ ];                                                           
			for ( int i = 0; i < this->rows_; ++i )                                                                
			{                                                                                               
				this->data_[ i ] = new double [ this->cols_ ];                                                         
			}                                                                                               
															
			/* get the data */                                                                              
			parser( d_ptr, tokens, this->data_, this->rows_, this->cols_ );                           
		}

		inline void Flatten( double * data, const unsigned int & size )
		{
			assert( size == ( this->rows_ * this->cols_ ) );
			for ( unsigned int i = 0; i < this->rows_; ++i )
				for ( unsigned int j = 0; j < this->cols_; ++j )
					* ( data + i * ( this->cols_ ) + j ) = * ( * ( this->data_ + i ) + j );
		}

		inline void Flatten( void )
		{
			// instantiate new temp variable for data
			double * temp_data = new double [ this->rows_ * this->cols_ ];
			unsigned int temp_columns = this->cols_;
			// copy data into temporary buffer
			for ( unsigned int i = 0; i < this->rows_; ++i )
				for ( unsigned int j = 0; j < this->cols_; ++j )
					* ( temp_data + i * ( this->cols_ ) + j ) = * ( * ( this->data_ + i ) + j );

			// delete rows
			for ( unsigned int i = 0; i < this->rows_; ++i )
				delete [] this->data_[ i ];
			delete [] this->data_;

			// copy temp_buffer into this->data 
			this->data_ = new double * [ 1 ];
			this->cols_ = this->rows_ * this->cols_;
			this->rows_ = 1;
			* this->data_ = new double [ this->cols_ ];

			assert( this->data_ );
			for ( unsigned int i = 0; i < this->rows_; ++i )
				for ( unsigned int j = 0; j < this->cols_; ++j )
					* ( * this->data_ + i * ( temp_columns ) + j ) = * ( temp_data + i * ( temp_columns ) + j );

			delete [] temp_data;
		}

		inline void Copy( double ** data, const unsigned int & rows, const unsigned int & cols )
		{
			for ( unsigned int i = 0; i < rows; ++i )
			{
				for ( unsigned int j = 0; j < cols; ++j )
				{
					this->data_[ i ][ j ] = data[ i ][ j ];
				}
			}
		}

		void Open( std::string filename, const char * tokens )
		{
			/* assert nonempty filename */
			assert( ! filename.empty() );
															
			/* file objects and pointers */                                                                 
			ifstream data_file;                                                                             
			ifstream * d_ptr;  

			/* assign file pointers */                                                                      
			data_file.open( filename.c_str() );                                     
			d_ptr = & data_file;                                                                            
															
			/* get dimensions to instantiate 2D array */                                                    
			this->cols_ = count_fields( d_ptr, tokens );             
															
			/* count lines.  This is the number of input vectors in each data set resp. */                  
			this->rows_ = count_lines( d_ptr );                                                 
															
			/* instantiate 2D data array for the two data sets */                                           
			this->data_ = new double * [ this->rows_ ];                                                           
			for ( int i = 0; i < this->rows_; ++i )                                                                
			{                                                                                               
				this->data_[ i ] = new double [ this->cols_ ];                                                         
			}                                                                                               
															
			/* get the data */                                                                              
			parser( d_ptr, tokens, this->data_, this->rows_, this->cols_ );                           
															
			/* close data set file handles to conserve memory */                                            
			data_file.close();
		}

		void Open( ifstream * d_ptr, const char * tokens )
		{
			/* assert nonempty filename */
			assert( d_ptr );
															
			/* get dimensions to instantiate 2D array */                                                    
			this->cols_ = count_fields( d_ptr, tokens );             
															
			/* count lines.  This is the number of input vectors in each data set resp. */                  
			this->rows_ = count_lines( d_ptr );                                                 
															
			/* instantiate 2D data array for the two data sets */                                           
			this->data_ = new double * [ this->rows_ ];                                                           
			for ( int i = 0; i < this->rows_; ++i )                                                                
			{                                                                                               
				this->data_[ i ] = new double [ this->cols_ ];                                                         
			}                                                                                               
															
			/* get the data */                                                                              
			parser( d_ptr, tokens, this->data_, this->rows_, this->cols_ );                           
		}

		inline bool Empty( void ) { return this->data_ == 0; }

		inline unsigned int GetRows( void ) { return this->rows_; }

		inline const unsigned int & GetRows( void ) const { return this->rows_; }

		inline unsigned int GetCols( void ) { return this->cols_; }

		inline const unsigned int & GetCols( void ) const { return this->cols_; }

		inline unsigned int Size( void ) { return ( this->cols_ * this->rows_ ); }

		inline void GetData( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			if ( d_ptr )
			{
				d_ptr = this->data_;
				rows = this->rows_;
				cols = this->cols_;
			}
		}

		inline double ** GetData( void ) { return this->data_; }

		inline const double ** GetData( void ) const 
		{
			const double ** temp = ( const double ** ) this->data_;
			return temp; 
		}

		// normalize with respect to ALL values in a 2D array, results range between 0 and 1
		inline void NormalizeAll_0( void )
		{
			Normalize1( this->data_, this->rows_, this->cols_ );
		}

		// normalize with respect to ALL values in a 2D array, results range between -1 and 1
		inline void NormalizeAll_1( void )
		{
			Normalize2( this->data_, this->rows_, this->cols_ );
		}

		// normalize from 0 to 1
		inline void NormalizeByRow_0( void )
		{
			NormalizeByRow( this->data_, this->rows_, this->cols_ );
		}

		// normalize from 0 to 1
		inline void NormalizeByRow_0( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			NormalizeByRow( this->data_, this->rows_, this->cols_ );
			this->GetData( d_ptr, rows, cols );
		}

		// normalize from -1 to 1
		inline void NormalizeByRow_1( void )
		{
			NormalizeByRow( this->data_, this->rows_, this->cols_ );
			FORMAT_MACRO;
		}

		// normalize from -1 to 1
		inline void NormalizeByRow_1( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			NormalizeByRow( this->data_, this->rows_, this->cols_ );
			FORMAT_MACRO;
			this->GetData( d_ptr, rows, cols );
		}

		// normalize from 0 to 1
		inline void NormalizeByColumn_0( void )
		{
			NormalizeByColumn( this->data_, this->rows_, this->cols_ );
		}

		// normalize from 0 to 1
		inline void NormalizeByColumn_0( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			NormalizeByColumn( this->data_, this->rows_, this->cols_ );
			this->GetData( d_ptr, rows, cols );
		}

		// normalize from -1 to 1
		inline void NormalizeByColumn_1( void )
		{
			NormalizeByColumn( this->data_, this->rows_, this->cols_ );
			FORMAT_MACRO;
		}

		// normalize from -1 to 1
		inline void NormalizeByColumn_1( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			NormalizeByColumn( this->data_, this->rows_, this->cols_ );
			FORMAT_MACRO;
			this->GetData( d_ptr, rows, cols );
		}

		// 1 if value is greater than previous, 0 else
		inline void Increasing_0( void )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			// processed rows and cols are equal to their unprocessed counterparts
			unsigned int processed_rows_ = this->rows_;
			unsigned int processed_cols_ = this->cols_ - 1;

			/* instantiate 2D data array for the two data sets */                                           
			double ** processed_data_ = new double * [ processed_rows_ ];                                                           
			for ( int i = 0; i < processed_rows_; ++i )                                                                
			{                                                                                               
				processed_data_[ i ] = new double [ processed_cols_ ];                                                         
			}                                                                                               

			// do preprocessing
			for ( unsigned int i = 0; i < processed_rows_; ++i )
			{
				for ( unsigned int j = 0; j < processed_cols_; ++j )
				{
					processed_data_[ i ][ j ] = 
						( ( this->data_[ i ][ j + 1 ] >= this->data_[ i ][ j ] ) ? 1.0 : 0.0 );
				}
			}

			// clean up data, we don't need it anymore
			for ( unsigned int i = 0; i < this->rows_; ++i )
				delete [] this->data_[ i ];

			// make this->data_ point at preprocessed data
			this->data_ = processed_data_;
			this->cols_ = processed_cols_;
			this->rows_ = processed_rows_;
		}		

		// 1 if value is greater than previous, 0 else
		inline void Increasing_0( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			// processed rows and cols are equal to their unprocessed counterparts
			unsigned int processed_rows_ = this->rows_;
			unsigned int processed_cols_ = this->cols_ - 1;

			/* instantiate 2D data array for the two data sets */                                           
			double ** processed_data_ = new double * [ processed_rows_ ];                                                           
			for ( int i = 0; i < processed_rows_; ++i )                                                                
			{                                                                                               
				processed_data_[ i ] = new double [ processed_cols_ ];                                                         
			}                                                                                               

			// do preprocessing
			for ( unsigned int i = 0; i < processed_rows_; ++i )
			{
				for ( unsigned int j = 0; j < processed_cols_; ++j )
				{
					processed_data_[ i ][ j ] = 
						( ( this->data_[ i ][ j + 1 ] >= this->data_[ i ][ j ] ) ? 1.0 : 0.0 );
				}
			}

			// clean up data, we don't need it anymore
			for ( unsigned int i = 0; i < this->rows_; ++i )
				delete [] this->data_[ i ];

			// make this->data_ point at preprocessed data
			this->data_ = processed_data_;
			this->cols_ = processed_cols_;
			this->rows_ = processed_rows_;

			// get user land pointer and parameters to point at this->data_
			this->GetData( d_ptr, rows, cols );
		}

		// 1 if value is greater than previous, -1 else
		inline void Increasing_1( void )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			// processed rows and cols are equal to their unprocessed counterparts
			unsigned int processed_rows_ = this->rows_;
			unsigned int processed_cols_ = this->cols_ - 1;

			/* instantiate 2D data array for the two data sets */                                           
			double ** processed_data_ = new double * [ processed_rows_ ];                                                           
			for ( int i = 0; i < processed_rows_; ++i )                                                                
			{                                                                                               
				processed_data_[ i ] = new double [ processed_cols_ ];                                                         
			}                                                                                               

			// do preprocessing
			for ( unsigned int i = 0; i < processed_rows_; ++i )
			{
				for ( unsigned int j = 0; j < processed_cols_; ++j )
				{
					processed_data_[ i ][ j ] = 
						( ( this->data_[ i ][ j + 1 ] >= this->data_[ i ][ j ] ) ? 1.0 : -1.0 );
				}
			}

			// clean up data, we don't need it anymore
			for ( unsigned int i = 0; i < this->rows_; ++i )
				delete [] this->data_[ i ];

			// make this->data_ point at preprocessed data
			this->data_ = processed_data_;
			this->cols_ = processed_cols_;
			this->rows_ = processed_rows_;
		}

		// 1 if value is greater than previous, -1 else
		inline void Increasing_1( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			// processed rows and cols are equal to their unprocessed counterparts
			unsigned int processed_rows_ = this->rows_;
			unsigned int processed_cols_ = this->cols_ - 1;

			/* instantiate 2D data array for the two data sets */                                           
			double ** processed_data_ = new double * [ processed_rows_ ];                                                           
			for ( int i = 0; i < processed_rows_; ++i )                                                                
			{                                                                                               
				processed_data_[ i ] = new double [ processed_cols_ ];                                                         
			}                                                                                               

			// do preprocessing
			for ( unsigned int i = 0; i < processed_rows_; ++i )
			{
				for ( unsigned int j = 0; j < processed_cols_; ++j )
				{
					processed_data_[ i ][ j ] = 
						( ( this->data_[ i ][ j + 1 ] >= this->data_[ i ][ j ] ) ? 1.0 : -1.0 );
				}
			}

			// clean up data, we don't need it anymore
			for ( unsigned int i = 0; i < this->rows_; ++i )
				delete [] this->data_[ i ];

			// make this->data_ point at preprocessed data
			this->data_ = processed_data_;
			this->cols_ = processed_cols_;
			this->rows_ = processed_rows_;

			// get user land pointer and parameters to point at this->data_
			this->GetData( d_ptr, rows, cols );
		}

		// 0 if less than mean, 1 otherwise
		inline void Mean_0( void )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			double * means = new double [ this->rows_ ];

			for ( unsigned int i = 0; i < this->rows_; ++i )
				means[ i ] = 0.0;

			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					means[ i ] += this->data_[ i ][ j ];
				}
				means[ i ] /= this->cols_;
			}

			double * m_ptr = means;
			for ( double ** i_ptr = this->data_; i_ptr != this->data_ + this->rows_; ++i_ptr, ++m_ptr )	
			{											
				for ( double * j_ptr = * i_ptr; j_ptr != ( * i_ptr ) + this->cols_; ++j_ptr )	
				{										
					if ( * j_ptr < * m_ptr )
					{
						* j_ptr = 0.0;
					}
					else
					{
						* j_ptr = 1.0;
					}
				}										
			}			

			delete [] means;
		}

		// 0 if less than mean, 1 otherwise
		inline void Mean_0( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			double * means = new double [ this->rows_ ];

			for ( unsigned int i = 0; i < this->rows_; ++i )
				means[ i ] = 0.0;

			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					means[ i ] += this->data_[ i ][ j ];
				}
				means[ i ] /= this->cols_;
			}

			double * m_ptr = means;
			for ( double ** i_ptr = this->data_; i_ptr != this->data_ + this->rows_; ++i_ptr, ++m_ptr )	
			{											
				for ( double * j_ptr = * i_ptr; j_ptr != ( * i_ptr ) + this->cols_; ++j_ptr )	
				{										
					if ( * j_ptr < * m_ptr )
					{
						* j_ptr = 0.0;
					}
					else
					{
						* j_ptr = 1.0;
					}
				}										
			}			

			delete [] means;

			this->GetData( d_ptr, rows, cols );
		}

		// -1 if less than mean, 1 otherwise
		inline void Mean_1( void )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			double * means = new double [ this->rows_ ];
			for ( unsigned int i = 0; i < this->rows_; ++i )
				means[ i ] = 0.0;

			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					means[ i ] += this->data_[ i ][ j ];
				}
				means[ i ] /= this->cols_;
			}

			double * m_ptr = means;
			for ( double ** i_ptr = this->data_; i_ptr != this->data_ + this->rows_; ++i_ptr, ++m_ptr )	
			{											
				for ( double * j_ptr = * i_ptr; j_ptr != ( * i_ptr ) + this->cols_; ++j_ptr )	
				{										
					if ( * j_ptr < * m_ptr )
					{
						* j_ptr = -1.0;
					}
					else
					{
						* j_ptr = 1.0;
					}
				}										
			}			

			delete [] means;
		}

		// -1 if less than mean, 1 otherwise
		inline void Mean_1( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			double * means = new double [ this->rows_ ];
			for ( unsigned int i = 0; i < this->rows_; ++i )
				means[ i ] = 0.0;

			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					means[ i ] += this->data_[ i ][ j ];
				}
				means[ i ] /= this->cols_;
			}

			double * m_ptr = means;
			for ( double ** i_ptr = this->data_; i_ptr != this->data_ + this->rows_; ++i_ptr, ++m_ptr )	
			{											
				for ( double * j_ptr = * i_ptr; j_ptr != ( * i_ptr ) + this->cols_; ++j_ptr )	
				{										
					if ( * j_ptr < * m_ptr )
					{
						* j_ptr = -1.0;
					}
					else
					{
						* j_ptr = 1.0;
					}
				}										
			}			

			delete [] means;

			this->GetData( d_ptr, rows, cols );
		}

		// 0 if less than mean - std dev, 1 if mean + std ev, 0.5 otherwise
		// WARNING: this causes make test to crash, but does not crash under
		// normal program execution
		inline void StdDev_0( void ) 
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			double * means = new double [ this->rows_ ];
			double * std_devs = new double [ this->rows_ ];

			// initialize means and std_devs
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				means[ i ] = 0.0;
				std_devs[ i ] = 0.0;
			}

			// calculate means
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					means[ i ] += this->data_[ i ][ j ];
				}
				means[ i ] /= this->cols_;
			}

			// calculate std dev's 
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					std_devs[ i ] += ( this->data_[ i ][ j ] - means[ i ] ) * ( this->data_[ i ][ j ] - means[ i ] );
				}
				std_devs[ i ] /= ( this->cols_ - 1 );
				pow( std_devs[ i ], 0.5 );
			}			

			double * m_ptr = means;
			double * s_ptr = std_devs;
			for ( double ** i_ptr = this->data_; i_ptr != this->data_ + this->rows_; ++i_ptr, ++m_ptr, ++s_ptr )	
			{											
				for ( double * j_ptr = * i_ptr; j_ptr != ( * i_ptr ) + this->cols_; ++j_ptr )	
				{										
					if ( * j_ptr < * m_ptr - * s_ptr )
					{
						* j_ptr = 0.0;
					}
					else if ( * j_ptr > * m_ptr + * s_ptr )
					{
						* j_ptr = 1.0;
					}
					else
					{
						* j_ptr = 0.5;
					}
				}										
			}			

			delete [] means;
			delete [] std_devs;
			m_ptr = 0;
			s_ptr = 0;
		}

		// 0 if less than mean - std dev, 1 if mean + std ev, 0.5 otherwise
		// WARNING: this causes make test to crash, but does not crash under
		// normal program execution
		inline void StdDev_0( double ** d_ptr, unsigned int & rows, unsigned int & cols ) 
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			double * means = new double [ this->rows_ ];
			double * std_devs = new double [ this->rows_ ];

			// initialize means and std_devs
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				means[ i ] = 0.0;
				std_devs[ i ] = 0.0;
			}

			// calculate means
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					means[ i ] += this->data_[ i ][ j ];
				}
				means[ i ] /= this->cols_;
			}

			// calculate std dev's 
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					std_devs[ i ] += ( this->data_[ i ][ j ] - means[ i ] ) * ( this->data_[ i ][ j ] - means[ i ] );
				}
				std_devs[ i ] /= ( this->cols_ - 1 );
				pow( std_devs[ i ], 0.5 );
			}			

			double * m_ptr = means;
			double * s_ptr = std_devs;
			for ( double ** i_ptr = this->data_; i_ptr != this->data_ + this->rows_; ++i_ptr, ++m_ptr, ++s_ptr )	
			{											
				for ( double * j_ptr = * i_ptr; j_ptr != ( * i_ptr ) + this->cols_; ++j_ptr )	
				{										
					if ( * j_ptr < * m_ptr - * s_ptr )
					{
						* j_ptr = 0.0;
					}
					else if ( * j_ptr > * m_ptr + * s_ptr )
					{
						* j_ptr = 1.0;
					}
					else
					{
						* j_ptr = 0.5;
					}
				}										
			}			

			delete [] means;
			delete [] std_devs;

			m_ptr = 0;
			s_ptr = 0;

			this->GetData( d_ptr, rows, cols );
		}

		// -1 if less than mean - std dev, 1 if mean + std ev, 0 otherwise
		// WARNING: this causes make test to crash, but does not crash under
		// normal program execution
		inline void StdDev_1( void ) 
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			double * means = new double [ this->rows_ ];
			double * std_devs = new double [ this->rows_ ];

			// initialize means and std_devs
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				means[ i ] = 0.0;
				std_devs[ i ] = 0.0;
			}

			// calculate means
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					means[ i ] += this->data_[ i ][ j ];
				}
				means[ i ] /= this->cols_;
			}

			// calculate std dev's 
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					std_devs[ i ] += ( this->data_[ i ][ j ] - means[ i ] ) * ( this->data_[ i ][ j ] - means[ i ] );
				}
				std_devs[ i ] /= ( this->cols_ - 1 );
				pow( std_devs[ i ], 0.5 );
			}

			double * m_ptr = means;
			double * s_ptr = std_devs;
			for ( double ** i_ptr = this->data_; i_ptr != this->data_ + this->rows_; ++i_ptr, ++m_ptr, ++s_ptr )	
			{											
				for ( double * j_ptr = * i_ptr; j_ptr != ( * i_ptr ) + this->cols_; ++j_ptr )	
				{										
					if ( * j_ptr < * m_ptr - * s_ptr )
					{
						* j_ptr = -1.0;
					}
					else if ( * j_ptr > * m_ptr + * s_ptr )
					{
						* j_ptr = 1.0;
					}
					else
					{
						* j_ptr = 0.0;
					}
				}										
			}			

			delete [] means;
			delete [] std_devs;

			m_ptr = 0;
			s_ptr = 0;
		}

		// -1 if less than mean - std dev, 1 if mean + std ev, 0 otherwise
		// WARNING: this causes make test to crash, but does not crash under
		// normal program execution
		inline void StdDev_1( double ** d_ptr, unsigned int & rows, unsigned int & cols ) 
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			double * means = new double [ this->rows_ ];
			double * std_devs = new double [ this->rows_ ];

			// initialize means and std_devs
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				means[ i ] = 0.0;
				std_devs[ i ] = 0.0;
			}

			// calculate means
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					means[ i ] += this->data_[ i ][ j ];
				}
				means[ i ] /= this->cols_;
			}

			// calculate std dev's 
			for ( unsigned int i = 0; i < this->rows_; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					std_devs[ i ] += ( this->data_[ i ][ j ] - means[ i ] ) * ( this->data_[ i ][ j ] - means[ i ] );
				}
				std_devs[ i ] /= ( this->cols_ - 1 );
				pow( std_devs[ i ], 0.5 );
			}

			double * m_ptr = means;
			double * s_ptr = std_devs;
			for ( double ** i_ptr = this->data_; i_ptr != this->data_ + this->rows_; ++i_ptr, ++m_ptr, ++s_ptr )	
			{											
				for ( double * j_ptr = * i_ptr; j_ptr != ( * i_ptr ) + this->cols_; ++j_ptr )	
				{										
					if ( * j_ptr < * m_ptr - * s_ptr )
					{
						* j_ptr = -1.0;
					}
					else if ( * j_ptr > * m_ptr + * s_ptr )
					{
						* j_ptr = 1.0;
					}
					else
					{
						* j_ptr = 0.0;
					}
				}										
			}			

			delete [] means;
			delete [] std_devs;

			m_ptr = 0;
			s_ptr = 0;

			this->GetData( d_ptr, rows, cols );
		}

		// PSD normalized from [0,1]
		inline void Fourier_0( void )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				MathLib::Fourier::pwr_spec_dns2( this->data_[ i ], this->cols_ );
			NormalizeByRow( this->data_, this->rows_, this->cols_ );
		}

		// PSD normalized from [0,1]
		inline void Fourier_0( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				MathLib::Fourier::pwr_spec_dns2( this->data_[ i ], this->cols_ );
			NormalizeByRow( this->data_, this->rows_, this->cols_ );
			this->GetData( d_ptr, rows, cols );
		}

		// PSD normalized from [-1,1]
		inline void Fourier_1( void )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				MathLib::Fourier::pwr_spec_dns2( this->data_[ i ], this->cols_ );
			NormalizeByRow( this->data_, this->rows_, this->cols_ );
			FORMAT_MACRO;
		}

		// PSD normalized from [-1,1]
		inline void Fourier_1( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				MathLib::Fourier::pwr_spec_dns2( this->data_[ i ], this->cols_ );
			NormalizeByRow( this->data_, this->rows_, this->cols_ );
			FORMAT_MACRO;
			this->GetData( d_ptr, rows, cols );
		}

		// add a bias at the end of the data
		inline void Bias( void )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			// processed rows and cols are equal to their unprocessed counterparts
			unsigned int processed_rows_ = this->rows_;
			unsigned int processed_cols_ = this->cols_ + 1;

			/* instantiate 2D data array for the two data sets */                                           
			double ** processed_data_ = new double * [ processed_rows_ ];                                                           
			for ( int i = 0; i < processed_rows_; ++i )                                                                
			{                                                                                               
				processed_data_[ i ] = new double [ processed_cols_ ];                                                         
			}                                                                                               

			// do preprocessing
			for ( unsigned int i = 0; i < processed_rows_; ++i )
			{
				for ( unsigned int j = 0; j < processed_cols_ - 1; ++j )
				{
					processed_data_[ i ][ j ] = this->data_[ i ][ j ];
				}
				processed_data_[ i ][ processed_cols_ - 1 ] = 1.0;
			}

			// clean up data, we don't need it anymore
			for ( unsigned int i = 0; i < this->rows_; ++i )
				delete [] this->data_[ i ];

			// make this->data_ point at preprocessed data
			this->data_ = processed_data_;
			this->cols_ = processed_cols_;
			this->rows_ = processed_rows_;
		}

		// add a bias at the end of the data
		inline void Bias( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			// processed rows and cols are equal to their unprocessed counterparts
			unsigned int processed_rows_ = this->rows_;
			unsigned int processed_cols_ = this->cols_ + 1;

			/* instantiate 2D data array for the two data sets */                                           
			double ** processed_data_ = new double * [ processed_rows_ ];                                                           
			for ( int i = 0; i < processed_rows_; ++i )                                                                
			{                                                                                               
				processed_data_[ i ] = new double [ processed_cols_ ];                                                         
			}                                                                                               

			// do preprocessing
			for ( unsigned int i = 0; i < processed_rows_; ++i )
			{
				for ( unsigned int j = 0; j < processed_cols_ - 1; ++j )
				{
					processed_data_[ i ][ j ] = this->data_[ i ][ j ];
				}
				processed_data_[ i ][ processed_cols_ - 1 ] = 1.0;
			}

			// clean up data, we don't need it anymore
			for ( unsigned int i = 0; i < this->rows_; ++i )
				delete [] this->data_[ i ];

			// make this->data_ point at preprocessed data
			this->data_ = processed_data_;
			this->cols_ = processed_cols_;
			this->rows_ = processed_rows_;

			// get user land pointer and parameters to point at this->data_
			this->GetData( d_ptr, rows, cols );
		}

		// add a bias to each node and pad the extra data with 1's so the data
		// is congruent mod node_size 
		inline void Bias( const unsigned int & node_size )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			// accounts for how many times node_size divices cols
			unsigned int extra = this->cols_ / node_size;

			// accounts for extra 1's needed to pad so that we are congruent
			// find extra needed to be congruent to node_size
			extra += ( node_size - ( extra + this->cols_ ) % node_size );

			// processed rows and cols are equal to their unprocessed counterparts
			unsigned int processed_rows_ = this->rows_;
			unsigned int processed_cols_ = this->cols_ + extra;

			/* instantiate 2D data array for the two data sets */                                           
			double ** processed_data_ = new double * [ processed_rows_ ];                                                           
			for ( int i = 0; i < processed_rows_; ++i )                                                                
			{                                                                                               
				processed_data_[ i ] = new double [ processed_cols_ ];                                                         
			}                                                                                               

			// do preprocessing
			for ( unsigned int i = 0; i < processed_rows_; ++i )
			{
				unsigned int set_back = 0;
				for ( unsigned int j = 0; j < processed_cols_; ++j )
				{
					if ( ( j + 1 ) % node_size == 0 && j > 0 && ( j - set_back ) < this->cols_ )
					{
						++set_back;
						processed_data_[ i ][ j ] = 1.0;
					}
					else if ( ( j - set_back ) >= this->cols_ )
					{
						processed_data_[ i ][ j ] = 1.0;
					}
					else
					{
						processed_data_[ i ][ j ] = this->data_[ i ][ j - set_back ];
					}
				}
			}

			// clean up data, we don't need it anymore
			for ( unsigned int i = 0; i < this->rows_; ++i )
				delete [] this->data_[ i ];

			// make this->data_ point at preprocessed data
			this->data_ = processed_data_;
			this->cols_ = processed_cols_;
			this->rows_ = processed_rows_;
		}

		// add a bias to each node and pad the extra data with 1's so the data
		// is congruent mod node_size 
		inline void Bias( double ** d_ptr, unsigned int & rows, unsigned int & cols, const unsigned int & node_size )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			// accounts for how many times node_size divices cols
			unsigned int extra = this->cols_ / node_size;

			// accounts for extra 1's needed to pad so that we are congruent
			// find extra needed to be congruent to node_size
			extra += ( node_size - ( extra + this->cols_ ) % node_size );

			// processed rows and cols are equal to their unprocessed counterparts
			unsigned int processed_rows_ = this->rows_;
			unsigned int processed_cols_ = this->cols_ + extra;

			/* instantiate 2D data array for the two data sets */                                           
			double ** processed_data_ = new double * [ processed_rows_ ];                                                           
			for ( int i = 0; i < processed_rows_; ++i )                                                                
			{                                                                                               
				processed_data_[ i ] = new double [ processed_cols_ ];                                                         
			}                                                                                               

			// do preprocessing
			for ( unsigned int i = 0; i < processed_rows_; ++i )
			{
				unsigned int set_back = 0;
				for ( unsigned int j = 0; j < processed_cols_; ++j )
				{
					if ( ( j + 1 ) % node_size == 0 && j > 0 && ( j - set_back ) < this->cols_ )
					{
						++set_back;
						processed_data_[ i ][ j ] = 1.0;
					}
					else if ( ( j - set_back ) >= this->cols_ )
					{
						processed_data_[ i ][ j ] = 1.0;
					}
					else
					{
						processed_data_[ i ][ j ] = this->data_[ i ][ j - set_back ];
					}
				}
			}

			// clean up data, we don't need it anymore
			for ( unsigned int i = 0; i < this->rows_; ++i )
				delete [] this->data_[ i ];

			// make this->data_ point at preprocessed data
			this->data_ = processed_data_;
			this->cols_ = processed_cols_;
			this->rows_ = processed_rows_;

			// get user land pointer and parameters to point at this->data_
			this->GetData( d_ptr, rows, cols );
		}

		// sin of the values scaled by pi, still in the interval [0,1]
		// since sin : [0, pi] in R+
		inline void Sin_0( void )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				for ( unsigned int j = 0; j < this->cols_; ++j )
					* ( * ( this->data_ + i ) + j ) = sin( PI * * ( * ( this->data_ + i ) + j ) );
		}

		// sin of the values scaled by pi, still in the interval [0,1]
		// since sin : [0, pi] in R+
		inline void Sin_0( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				for ( unsigned int j = 0; j < this->cols_; ++j )
					* ( * ( this->data_ + i ) + j ) = sin( PI * * ( * ( this->data_ + i ) + j ) );

			// get user land pointer and parameters to point at this->data_
			this->GetData( d_ptr, rows, cols );
		}

		
		// sin of the values scaled by pi, still in the interval [-1,1]
		// since sin : [-pi, pi] in [-1,1] 
		inline void Sin_1( void )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				for ( unsigned int j = 0; j < this->cols_; ++j )
					* ( * ( this->data_ + i ) + j ) = sin( PI * * ( * ( this->data_ + i ) + j ) );
		}

		// sin of the values scaled by pi, still in the interval [-1,1]
		// since sin : [-pi, pi] in [-1,1] 
		inline void Sin_1( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				for ( unsigned int j = 0; j < this->cols_; ++j )
					* ( * ( this->data_ + i ) + j ) = sin( PI * * ( * ( this->data_ + i ) + j ) );

			// get user land pointer and parameters to point at this->data_
			this->GetData( d_ptr, rows, cols );
		}

		// sin of the values scaled by pi, still in the interval [0,1]
		// since cos : [-pi/2, pi/2] in R+
		inline void Cos_0( void )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				for ( unsigned int j = 0; j < this->cols_; ++j )
					* ( * ( this->data_ + i ) + j ) = cos( PI * ( * ( * ( this->data_ + i ) + j ) - 0.5 ) );
		}

		// sin of the values scaled by pi and shifted by -pi/2, still in the interval [0,1]
		// since cos : [-pi/2, pi/2] in R+
		inline void Cos_0( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				for ( unsigned int j = 0; j < this->cols_; ++j )
					* ( * ( this->data_ + i ) + j ) = cos( PI * ( * ( * ( this->data_ + i ) + j ) - 0.5 ) );

			// get user land pointer and parameters to point at this->data_
			this->GetData( d_ptr, rows, cols );
		}

		
		// sin of the values scaled by pi, still in the interval [-1,1]
		// since sin : [-pi, pi] in [-1,1] 
		inline void Cos_1( void )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				for ( unsigned int j = 0; j < this->cols_; ++j )
					* ( * ( this->data_ + i ) + j ) = cos( PI * * ( * ( this->data_ + i ) + j ) );
		}

		// sin of the values scaled by pi, still in the interval [-1,1]
		// since sin : [-pi, pi] in [-1,1] 
		inline void Cos_1( double ** d_ptr, unsigned int & rows, unsigned int & cols )
		{
			// allocate preprocessed data and set rows and cols
			// assert rows and cols have been allocated
			assert( this->rows_ && this->cols_ );

			for ( unsigned int i = 0; i < this->rows_; ++i )
				for ( unsigned int j = 0; j < this->cols_; ++j )
					* ( * ( this->data_ + i ) + j ) = cos( PI * * ( * ( this->data_ + i ) + j ) );

			// get user land pointer and parameters to point at this->data_
			this->GetData( d_ptr, rows, cols );
		}

		// clean up data
		inline void CleanUpData( void )
		{
			if ( this->rows_ != 0 && this->cols_ != 0 && this->data_ != 0 )
			{
				for ( unsigned int i = 0; i < this->rows_; ++i )
					delete [] this->data_[ i ];
				delete [] this->data_;

				this->rows_ = 0;
				this->cols_ = 0;
				this->data_ = 0;
			}
		}

		~Preprocessor( void )
		{
			this->CleanUpData();
		}

		// concatenates preprocessors
		Preprocessor operator + ( const Preprocessor & p ) const
		{
			// determine rows, columns
			unsigned int rows = ( ( p.rows_ < this->rows_ ) ? p.rows_ : this->rows_ );
			unsigned int columns = p.cols_ + this->cols_;

			// allocate temporary memory
			double ** temp_data = new double * [ rows ]; 
			for ( unsigned int i = 0; i < rows; ++i )
				this->data_[ i ] = new double [ columns ];

			// copy data into memory
			for ( unsigned int i = 0; i < rows; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					temp_data[ i ][ j ] = this->data_[ i ][ j ];
				}

				for ( unsigned int j = this->cols_; j < columns; ++j )
				{
					temp_data[ i ][ j ] = p.data_[ i ][ j ];
				}
			}

			// create return value
			Preprocessor return_value( temp_data, rows, columns );

			// clean up temporary data
			for ( unsigned int i = 0; i < rows; ++i )
				delete [] temp_data[ i ];
			delete [] temp_data;

			return return_value;
		}

		Preprocessor operator += ( const Preprocessor & p )
		{
			// determine rows, columns
			unsigned int rows = ( ( p.rows_ < this->rows_ ) ? p.rows_ : this->rows_ );
			unsigned int columns = p.cols_ + this->cols_;

			// allocate temporary memory
			double ** temp_data = new double * [ rows ]; 
			for ( unsigned int i = 0; i < rows; ++i )
				temp_data[ i ] = new double [ columns ];

			// copy data into memory
			for ( unsigned int i = 0; i < rows; ++i )
			{
				for ( unsigned int j = 0; j < this->cols_; ++j )
				{
					temp_data[ i ][ j ] = this->data_[ i ][ j ];
				}

				for ( unsigned int j = this->cols_; j < columns; ++j )
				{
					temp_data[ i ][ j ] = p.data_[ i ][ j - this->cols_ ];
				}
			}

			// clean up temporary data
			for ( unsigned int i = 0; i < this->rows_; ++i )
				delete [] this->data_[ i ];
			delete [] this->data_;

			this->data_ = temp_data;
			this->rows_ = rows;
			this->cols_ = columns;

			return * this;
		}

	private :

		unsigned int rows_, cols_;

		double ** data_;
};

class PreprocessorVector
{
	public :

		PreprocessorVector( void ) : node_size_( 0 ) {}

		PreprocessorVector( const std::vector< std::string > & v, const char * tokens ) 
			: node_size_( 0 )
		{
			for ( std::vector< std::string >::const_iterator it = v.begin();
                              it != v.end();
                              ++it )
			{
				this->preprocessors_.push_back( new Preprocessor( * it, tokens ) );
			}
		}

		PreprocessorVector( const std::vector< std::ifstream * > & v, const char * tokens ) 
			: node_size_( 0 )
		{
			for ( std::vector< std::ifstream * >::const_iterator it = v.begin();
                              it != v.end();
                              ++it )
			{
				this->preprocessors_.push_back( new Preprocessor( * it, tokens ) );
			}
		}

		~PreprocessorVector( void ) 
		{
			for ( unsigned int i = 0; i < this->preprocessors_.size(); ++i )
			{
				delete this->preprocessors_[ i ];
			}
		}

		void SetNodes( const unsigned int & node_size ) { this->node_size_ = node_size; }

		unsigned int Size( void ) { return this->preprocessors_.size(); }

		const Preprocessor * operator () ( const unsigned int & index ) const 
			{ return this->preprocessors_.at( index ); }

		double ** GetData( const unsigned int & index )
			{ return this->preprocessors_.at( index )->GetData(); }

		double * GetData( const unsigned int & index_i, const unsigned int & index_j )
			{ return * ( this->preprocessors_.at( index_i )->GetData() + index_j ); }

		unsigned int GetCols( const unsigned int & index )
			{ return this->preprocessors_.at( index )->GetCols(); }

		unsigned int GetRows( const unsigned int & index )
			{ return this->preprocessors_.at( index )->GetRows(); }

		// apply index-th preprocessor to all elements
		void ApplyPreprocessor( const unsigned int & index )
		{
			switch ( index )
			{
			case INDEX_NORMALIZE_BY_ROW_0		:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->NormalizeByRow_0();
				}
				break;
			case INDEX_NORMALIZE_BY_ROW_1		:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->NormalizeByRow_1();
				}
				break;
			case INDEX_NORMALIZE_BY_COL_0		:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->NormalizeByColumn_0();
				}
				break;
			case INDEX_NORMALIZE_BY_COL_1		:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->NormalizeByColumn_1();
				}
				break;
			case INDEX_INCREASING_PREPROCESSOR_0	:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->Increasing_0();
				}
				break;
			case INDEX_INCREASING_PREPROCESSOR_1	:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->Increasing_1();
				}
				break;
			case INDEX_MEAN_PREPROCESSOR_0		:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->Mean_0();
				}
				break;
			case INDEX_MEAN_PREPROCESSOR_1		:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->Mean_1();
				}
				break;
			case INDEX_STD_DEV_PREPROCESSOR_0	:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->StdDev_0();
				}
				break;
			case INDEX_STD_DEV_PREPROCESSOR_1	:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->StdDev_1();
				}
				break;
			case INDEX_FOURIER_PREPROCESSOR_0	:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->Fourier_0();
				}
				break;
			case INDEX_FOURIER_PREPROCESSOR_1	:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->Fourier_1();
				}
				break;
			case INDEX_BIAS				:
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->Bias();
				}
				break;
			case INDEX_NODE_BIAS			:
				assert( this->node_size_ != 0 );
				for ( std::vector< Preprocessor * >::iterator it = this->preprocessors_.begin();
				      it != this->preprocessors_.end();
				      ++it )
				{
					( * it )->Bias( this->node_size_ );
				}
				break;
			default 				:
				break;
			}
		}

		void ApplyPreprocessor( const std::vector<unsigned int> & values )
		{
			for ( std::vector<unsigned int>::const_iterator it = values.begin();
                              it != values.end();
                              ++it )
			{
				this->ApplyPreprocessor( * it );
			}
		}

	private :

		unsigned int node_size_;

		std::vector< Preprocessor * > preprocessors_;
};

}

#endif  // PREPROCESSOR_H
