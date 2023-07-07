#!/bin/bash
PROJECT_NAME=test_utility
./${PROJECT_NAME} --Output       --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --CountFields1 --InputFile Input/input2.csv --Tokens ";, " --Verbose
./${PROJECT_NAME} --CountFields2 --InputFile Input/input2.csv --Tokens ";, " --Verbose   
./${PROJECT_NAME} --CountLines   --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --Parser1      --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --Parser2      --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --Echo         --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --CoutArray1   --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --CoutArray2   --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --NormalizeR1  --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --NormalizeR2  --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --NormalizeC1  --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --NormalizeC2  --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --Increasing0  --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --Increasing1  --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --Mean0        --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --Mean1        --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --StdDev0      --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --StdDev1      --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --Fourier0     --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --Fourier1     --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --Bias0        --InputFile Input/input2.csv --Tokens ";, " --Verbose 
./${PROJECT_NAME} --Bias1        --InputFile Input/input2.csv --Tokens ";, " --Verbose 
