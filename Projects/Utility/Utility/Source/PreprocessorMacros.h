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
// macros to facilitate preprocessing

#ifndef __PREPROCESSOR_MACROS__
#define __PREPROCESSOR_MACROS__

/////////////////////////////////////////////////////////////////////////////////////////
// indices of preprocessors 
/////////////////////////////////////////////////////////////////////////////////////////
#define INDEX_NORMALIZE_BY_ROW_0		0
#define INDEX_NORMALIZE_BY_ROW_1		1
#define INDEX_NORMALIZE_BY_COL_0		2
#define INDEX_NORMALIZE_BY_COL_1		3
#define INDEX_INCREASING_PREPROCESSOR_0		4
#define INDEX_INCREASING_PREPROCESSOR_1		5
#define INDEX_MEAN_PREPROCESSOR_0		6
#define INDEX_MEAN_PREPROCESSOR_1		7
#define INDEX_STD_DEV_PREPROCESSOR_0		8
#define INDEX_STD_DEV_PREPROCESSOR_1		9
#define INDEX_FOURIER_PREPROCESSOR_0		10
#define INDEX_FOURIER_PREPROCESSOR_1		11
#define INDEX_BIAS				12
#define INDEX_NODE_BIAS				13

/////////////////////////////////////////////////////////////////////////////////////////
// get raw data 
/////////////////////////////////////////////////////////////////////////////////////////
#define GET_DATA(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)				\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.GetData( _DATA_, _ROWS_, _COLS_ );							\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

/////////////////////////////////////////////////////////////////////////////////////////
// normalize data by rows
/////////////////////////////////////////////////////////////////////////////////////////
#define NORMALIZE_BY_ROW_0(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)			\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.NormalizeByRow_0( _DATA_, _ROWS_, _COLS_ );						\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

#define NORMALIZE_BY_ROW_1(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)			\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.NormalizeByRow_1( _DATA_, _ROWS_, _COLS_ );						\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

/////////////////////////////////////////////////////////////////////////////////////////
// normalize data by columns 
/////////////////////////////////////////////////////////////////////////////////////////
#define NORMALIZE_BY_COL_0(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)			\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.NormalizeByColumn_0( _DATA_, _ROWS_, _COLS_ );					\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

#define NORMALIZE_BY_COL_1(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)			\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.NormalizeByColumn_1( _DATA_, _ROWS_, _COLS_ );					\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

/////////////////////////////////////////////////////////////////////////////////////////
// increasing
/////////////////////////////////////////////////////////////////////////////////////////
#define INCREASING_PREPROCESSOR_0(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)		\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.Increasing_0( _DATA_, _ROWS_, _COLS_ );						\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

#define INCREASING_PREPROCESSOR_1(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)		\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.Increasing_1( _DATA_, _ROWS_, _COLS_ );						\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

/////////////////////////////////////////////////////////////////////////////////////////
// mean
/////////////////////////////////////////////////////////////////////////////////////////
#define MEAN_PREPROCESSOR_0(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)			\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.Mean_0( _DATA_, _ROWS_, _COLS_ );							\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

#define MEAN_PREPROCESSOR_1(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)			\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.Mean_1( _DATA_, _ROWS_, _COLS_ );							\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

/////////////////////////////////////////////////////////////////////////////////////////
// std dev
/////////////////////////////////////////////////////////////////////////////////////////
#define STD_DEV_PREPROCESSOR_0(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)		\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.StdDev_0( _DATA_, _ROWS_, _COLS_ );							\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

#define STD_DEV_PREPROCESSOR_1(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)		\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.StdDev_1( _DATA_, _ROWS_, _COLS_ );							\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

/////////////////////////////////////////////////////////////////////////////////////////
// fourier
/////////////////////////////////////////////////////////////////////////////////////////
#define FOURIER_PREPROCESSOR_0(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)		\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.Fourier_0( _DATA_, _ROWS_, _COLS_ );							\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

#define FOURIER_PREPROCESSOR_1(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)		\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.Fourier_1( _DATA_, _ROWS_, _COLS_ );							\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

/////////////////////////////////////////////////////////////////////////////////////////
// Bias 
/////////////////////////////////////////////////////////////////////////////////////////
#define BIAS(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_)					\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.Bias( _DATA_, _ROWS_, _COLS_ );							\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );

#define NODE_BIAS(_FILENAME_,_TOKENS_,_DATA_,_ROWS_,_COLS_,_N_)				\
double ** _DATA_;									\
unsigned int _ROWS_ = 0;								\
unsigned int _COLS_ = 0;								\
preprocessor::Preprocessor p( _FILENAME_, _TOKENS_ );					\
p.Bias( _DATA_, _ROWS_, _COLS_, _N_ );							\
assert( _DATA_ != 0 );									\
assert( _ROWS_ != 0 );									\
assert( _COLS_ != 0 );


#define DEFAULT_GET_DATA(_FILENAME_,_TOKENS_)                  GET_DATA(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_NORMALIZE_BY_ROW_0(_FILENAME_,_TOKENS_)        NORMALIZE_BY_ROW_0(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_NORMALIZE_BY_ROW_1(_FILENAME_,_TOKENS_)        NORMALIZE_BY_ROW_1(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_NORMALIZE_BY_COL_0(_FILENAME_,_TOKENS_)        NORMALIZE_BY_COL_0(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_NORMALIZE_BY_COL_1(_FILENAME_,_TOKENS_)        NORMALIZE_BY_COL_1(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_INCREASING_PREPROCESSOR_0(_FILENAME_,_TOKENS_) INCREASING_PREPROCESSOR_0(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_INCREASING_PREPROCESSOR_1(_FILENAME_,_TOKENS_) INCREASING_PREPROCESSOR_1(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_MEAN_PREPROCESSOR_0(_FILENAME_,_TOKENS_)       MEAN_PREPROCESSOR_0(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_MEAN_PREPROCESSOR_1(_FILENAME_,_TOKENS_)       MEAN_PREPROCESSOR_1(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_STD_DEV_PREPROCESSOR_0(_FILENAME_,_TOKENS_)    STD_DEV_PREPROCESSOR_0(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_STD_DEV_PREPROCESSOR_1(_FILENAME_,_TOKENS_)    STD_DEV_PREPROCESSOR_1(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_FOURIER_PREPROCESSOR_0(_FILENAME_,_TOKENS_)    FOURIER_PREPROCESSOR_0(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_FOURIER_PREPROCESSOR_1(_FILENAME_,_TOKENS_)    FOURIER_PREPROCESSOR_1(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_BIAS(_FILENAME_,_TOKENS_)                      BIAS(_FILENAME_,_TOKENS_,data,rows,cols)
#define DEFAULT_NODE_BIAS(_FILENAME_,_TOKENS_,_N_)             NODE_BIAS(_FILENAME_,_TOKENS_,data,rows,cols,_N_)
#define DEFAULT_OUTPUT_MACRO                                   std::cout << p << std::endl;	

#endif // __PREPROCESSOR_MACROS__
