# CMake generated Testfile for 
# Source directory: /home/daniel/Hypercomplete/Projects/Projects/Utility/TestUtility
# Build directory: /home/daniel/Hypercomplete/Projects/Projects/Utility/TestUtility
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(test_output "./test_utility" "--Output" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_countFields1 "./test_utility" "--CountFields1" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_countFields2 "./test_utility" "--CountFields2" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_countLines "./test_utility" "--CountLines" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_parser1 "./test_utility" "--Parser1" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_parser2 "./test_utility" "--Parser2" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_echo "./test_utility" "--Echo" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_coutArray2 "./test_utility" "--CoutArray2" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_NormalizeR1 "./test_utility" "--NormalizeR1" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_NormalizeR2 "./test_utility" "--NormalizeR2" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_NormalizeC1 "./test_utility" "--NormalizeC1" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_NormalizeC2 "./test_utility" "--NormalizeC2" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_Increasing0 "./test_utility" "--Increasing0" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_Increasing1 "./test_utility" "--Increasing1" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_Mean0 "./test_utility" "--Mean0" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_StdDev0 "./test_utility" "--StdDev0" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_StdDev1 "./test_utility" "--StdDev1" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_Fourier0 "./test_utility" "--Fourier0" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_Bias0 "./test_utility" "--Bias0" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
ADD_TEST(test_Bias1 "./test_utility" "--Bias1" "--InputFile" "Input/input.csv" "--Tokens" ";, ")
