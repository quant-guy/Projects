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
set term png
set output "Algebraic_a.png"
set yrange[ -1 : 1 ]
plot "Results/Algebraic_a.csv" using 1:2
set term png
set output "Algebraic_d.png"
set yrange[ 0 : 1.2 ]
plot "Results/Algebraic_d.csv" using 1:2
set term png
set output "Control_a.png"
set yrange[ -1 : 1 ]
plot "Results/Control_a.csv" using 1:2
set term png
set output "Control_d.png"
set yrange[ 0 : 0.6 ]
plot "Results/Control_d.csv" using 1:2
set term png
set output "Erf_a.png"
set yrange[ -1 : 1 ]
plot "Results/Erf_a.csv" using 1:2
set term png
set output "Erf_d.png"
set yrange[ 0 : 1.2 ]
plot "Results/Erf_d.csv" using 1:2
set term png
set output "Gompertz_a.png"
set yrange[ -1 : 1 ]
plot "Results/Gompertz_a.csv" using 1:2
set term png
set output "Gompertz_d.png"
set yrange[ 0 : 1.2 ]
plot "Results/Gompertz_d.csv" using 1:2
set term png
set output "HyperbolicTangent_a.png"
set yrange[ -1 : 1 ]
plot "Results/HyperbolicTangent_a.csv" using 1:2
set term png
set output "HyperbolicTangent_d.png"
set yrange[ 0 : 1.2 ]
plot "Results/HyperbolicTangent_d.csv" using 1:2
set term png
set output "InverseTangent_a.png"
set yrange[ -1 : 1 ]
plot "Results/InverseTangent_a.csv" using 1:2
set term png
set output "InverseTangent_d.png"
set yrange[ 0 : 1.2 ]
plot "Results/InverseTangent_d.csv" using 1:2
set term png
set output "Logistic_a.png"
set yrange[ -1 : 1 ]
plot "Results/Logistic_a.csv" using 1:2
set term png
set output "Logistic_d.png"
set yrange[ 0 : 0.6 ]
plot "Results/Logistic_d.csv" using 1:2
