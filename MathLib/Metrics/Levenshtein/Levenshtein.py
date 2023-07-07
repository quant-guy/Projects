###################################################################################
# COPYRIGHT 2015 KovachTechnologies LLC
# Redistribution and use in source and binary forms, with or without 
# modification, are permitted provided that the following conditions are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#    This product includes software developed by the Kovach Technologies, LLC.
# 4. Neither the name of the Kovach Technologies, LLC nor the
#    names of its contributors may be used to endorse or promote products
#    derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY Kovach Technologies, LLC AS IS AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL Kovach Technologies, LLC BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# AUTHOR : Daniel Kovach
# DATE : 2015-12-30 10:19:06.739857
# All rights reserved.
###################################################################################
#!/usr/bin/python

# implementation of the Levenshtein distance
def distance( s1, s2 ) :
	# if either string is length zero return the other one
	if len( s1 ) == 0 :
		return len( s2 )
	
	if len( s2 ) == 0 :
		return len( s1 )

	# test if the last characters match
	indicator = 1
	if s1[ len( s1 ) - 1 ] == s2[ len( s2 ) - 1 ] :
		indicator = 0

	a = distance( s1[ 0 : len( s1 ) - 1 ], s2[ 0 : len( s2 ) ] ) + 1
	b = distance( s1[ 0 : len( s1 ) ], s2[ 0 : len( s2 ) - 1 ] ) + 1
	c = distance( s1[ 0 : len( s1 ) - 1 ], s2[ 0 : len( s2 ) - 1 ] ) + indicator
	
	return min( a, b, c )

if __name__ == "__main__" :
	s1 = 'aaaaaa'
	s2 = 'aaaaaa'
	print "distance between %s, and %s: %u" % ( s1, s2, distance( s1, s2 ) )

	s1 = 'orange'
	s2 = 'storage'
	print "distance between %s, and %s: %u" % ( s1, s2, distance( s1, s2 ) )

