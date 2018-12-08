###################################################################################
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
# THIS SOFTWARE IS PROVIDED BY Kovach Technologies, LLC ''AS IS'' AND ANY
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
# AUTHOR: Daniel Kovach
# DATE: 10/01/2010
# COPYRIGHT 2014 Kovach Technologies, LLC
###################################################################################

cmake_minimum_required( VERSION 2.6 )

project( projects )

if ( WIN32 )
# pretty sure the PWD environment variable is the same in windows.
# if not, just hard code it
# set( CMAKE_HOME C:/Source_Code/Projects )
set( CMAKE_HOME $ENV{PWD}/Projects               )
set_property( DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
	_SCL_SECURE_NO_DEPRECATE
	_CRT_SECURE_NO_DEPRECATE )
endif ( WIN32 )

if ( UNIX )
set( CMAKE_HOME $ENV{PWD}/Projects               )
endif ( UNIX )

#############################################################################
# Main directories
#############################################################################
set( AI_LIB                      ${CMAKE_HOME}/AILib                         )
set( MATH_LIB                    ${CMAKE_HOME}/MathLib                       )
set( UTILITY                     ${CMAKE_HOME}/Utility                       )
set( MYPROJECT                   ${CMAKE_HOME}/MyProject                     )

#############################################################################
# AILib 
#############################################################################
set( CLUSTER                     ${AI_LIB}/Cluster                           )
set( GENETICS                    ${AI_LIB}/Genetics                          )
set( NEURAL_NETWORKS             ${AI_LIB}/NeuralNetworks                    )

#############################################################################
# AILib : Clusters
#############################################################################
set( CLUSTER_2_0                 ${CLUSTER}/Cluster_2_0                      )

#############################################################################
# AILib: Neural Networks 
#############################################################################
set( NEURAL_NETWORK              ${NEURAL_NETWORKS}/NeuralNetwork            )

#############################################################################
# AILib: Genetics 
#############################################################################
set( GENETICS_3_0                ${GENETICS}/Genetics_3_0                    )

#############################################################################
# MathLib
#############################################################################
set( ACTIVATION_FUNCTIONS        ${MATH_LIB}/ActivationFunctions             )
set( FOURIER                     ${MATH_LIB}/Fourier                         )
set( MATRIX                      ${MATH_LIB}/Matrix                          )
set( METRICS                     ${MATH_LIB}/Metrics                         )
set( RANDOM                      ${MATH_LIB}/Random                          )
set( STATISTICS                  ${MATH_LIB}/Statistics                      )

#############################################################################
# Utility
#############################################################################
set( TIMING                      ${UTILITY}/Timing                           )
 
add_subdirectory( ${CMAKE_HOME} )

enable_testing()
