# CMake generated Testfile for 
# Source directory: /home/daniel/Hypercomplete/Projects/Projects/MathLib/Statistics/TestStatistics
# Build directory: /home/daniel/Hypercomplete/Projects/Projects/MathLib/Statistics/TestStatistics
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(test_max "./test_statistics" "--Max" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_mean "./test_statistics" "--Mean" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_standard_deviation "./test_statistics" "--StandardDeviation" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_covariance "./test_statistics" "--Covariance" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_mean_centered_covariance "./test_statistics" "--MeanCenteredCovariance" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_normalize_by_column "./test_statistics" "--NormalizeByColumn" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_normalize_by_row "./test_statistics" "--NormalizeByRow" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
