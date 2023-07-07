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

#################################################################################
# simple progress bar tool
# - instantiate and use as in the example given in '__main__'
# - must update mod max iterations of whatever the task length is
#################################################################################
import time
import sys

class ProgressBar :
	progressbar_width = 40
	counter = 0
	mod_window = 0

	def __init__( self, pbw ) :
		self.progressbar_width = pbw
		self.counter = 0
		sys.stdout.write( "[%s]" % ( " " * self.progressbar_width ) )
		sys.stdout.flush()
		sys.stdout.write( "\b" * ( self.progressbar_width + 1 ) )

	def task_length( self, tl ) :
		try :
			self.mod_window = tl / self.progressbar_width
		except Exception as e :
			pass

	def update( self ) :
		self.counter += 1
		try :
			if self.counter % self.mod_window == 0 :
				sys.stdout.write( "-" )
				sys.stdout.flush()
		except Exception as e :
			pass
		
	def finish( self ) :
		sys.stdout.write( '\n' )

if __name__ == '__main__' :
	length = 50
	pb = ProgressBar( length )
	pb.task_length( length )
	for i in xrange( pb.progressbar_width ) :
		time.sleep( 0.1 )
		pb.update()
	pb.finish()

	length2 = 50
	mod_window = 500 * length
	pb2 = ProgressBar( length )
	pb2.task_length( mod_window )
	for i in range( mod_window ) :
		pb2.update()
	pb2.finish()
	
	
