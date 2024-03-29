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
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

/////////////////////////////////////////////////////////////////////////
// output array 
/////////////////////////////////////////////////////////////////////////
void Output( ostream *, double *, unsigned int );
void Output( ostream *, float *, unsigned int );

/////////////////////////////////////////////////////////////////////////
// count number of fields in a string delimeted by specified delimeters
/////////////////////////////////////////////////////////////////////////
unsigned int count_fields( string, const char * );

/////////////////////////////////////////////////////////////////////////
// count number of fields in a ifstream delimeted by specified delimeters
/////////////////////////////////////////////////////////////////////////
unsigned int count_fields( ifstream *, const char * );

/////////////////////////////////////////////////////////////////////////
// count number of lines in a file
/////////////////////////////////////////////////////////////////////////
unsigned int count_lines( ifstream * );

/////////////////////////////////////////////////////////////////////////
// collect data fields parsed from string using specified delimeters 
/////////////////////////////////////////////////////////////////////////
void parser( string, const char *, double *, unsigned int );
void parser( string, const char *, float *, unsigned int );

/////////////////////////////////////////////////////////////////////////
// collect data into a matrix from a file 
/////////////////////////////////////////////////////////////////////////
void parser( ifstream *, const char *, double **, unsigned int, unsigned int );
void parser( ifstream *, const char *, float **, unsigned int, unsigned int );

/////////////////////////////////////////////////////////////////////////
// collect data fields parsed from string using specified delimeters 
/////////////////////////////////////////////////////////////////////////
void Echo( ifstream *, const char *, unsigned int );
