#!/bin/bash
./test_statistics --Tokens ";, " --InputFile Input/input.csv --Max
./test_statistics --Tokens ";, " --InputFile Input/input.csv --Min
./test_statistics --Tokens ";, " --InputFile Input/input.csv --Mean
./test_statistics --Tokens ";, " --InputFile Input/input.csv --StandardDeviation
./test_statistics --Tokens ";, " --InputFile Input/input.csv --Covariance
./test_statistics --Tokens ";, " --InputFile Input/input.csv --MeanCenteredCovariance
./test_statistics --Tokens ";, " --InputFile Input/input.csv --Correlation
./test_statistics --Tokens ";, " --InputFile Input/input.csv --MeanCenteredCorrelation
./test_statistics --Tokens ";, " --InputFile Input/input.csv --NormalizeByRow
./test_statistics --Tokens ";, " --InputFile Input/input.csv --NormalizeByColumn
./test_statistics --Tokens ";, " --InputFile Input/input.csv --NormalizeByRow2
./test_statistics --Tokens ";, " --InputFile Input/input.csv --NormalizeByColumn2
