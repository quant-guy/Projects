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

cmake_minimum_required( VERSION 2.6 )

project( test_myproject )

include_directories( ${MYPROJECT}/MyProject/Source
	${TIMING} 
	${UTILITY}/Utility/Source )

set( HEADERS Source/CommandLineOptions.h
      ${MYPROJECT}/MyProject/Source/MyProject.hpp
      ${MYPROJECT}/MyProject/Source/MyProjectCallers.h
      ${TIMING}/Timing.h
      ${UTILITY}/Utility/Source/CommandLineParser.hpp
      ${UTILITY}/Utility/Source/Parser.h )

set( SOURCE  Source/main.cpp
	${UTILITY}/Utility/Source/Parser.cpp )

add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCE} )

target_link_libraries( ${PROJECT_NAME} myproject )

enable_testing()
add_test( test_Constructor1 ./${PROJECT_NAME} --Constructor1 )
add_test( test_Constructor2 ./${PROJECT_NAME} --Constructor2 )
add_test( test_Constructor3 ./${PROJECT_NAME} --Constructor3 )
add_test( test_Sanity       ./${PROJECT_NAME} --Sanity       )
add_test( test_Test1        ./${PROJECT_NAME} --Test1        )
