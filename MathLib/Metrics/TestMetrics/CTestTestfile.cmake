# CMake generated Testfile for 
# Source directory: /home/daniel/Hypercomplete/Projects/Projects/MathLib/Metrics/TestMetrics
# Build directory: /home/daniel/Hypercomplete/Projects/Projects/MathLib/Metrics/TestMetrics
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(test_Euclidean "./test_metrics" "--Dataset" "Data/data.csv" "--Euclidean")
ADD_TEST(test_Manhattan "./test_metrics" "--Dataset" "Data/data.csv" "--Manhattan")
ADD_TEST(test_EuclideanN "./test_metrics" "--Dataset" "Data/data.csv" "--EuclideanN")
ADD_TEST(test_ManhattanN "./test_metrics" "--Dataset" "Data/data.csv" "--ManhattanN")
ADD_TEST(test_EuclideanV "./test_metrics" "--Dataset" "Data/data.csv" "--EuclideanV")
ADD_TEST(test_ManhattanV "./test_metrics" "--Dataset" "Data/data.csv" "--ManhattanV")
ADD_TEST(test_EuclideanVN "./test_metrics" "--Dataset" "Data/data.csv" "--EuclideanVN")
ADD_TEST(test_ManhattanVN "./test_metrics" "--Dataset" "Data/data.csv" "--ManhattanVN")
ADD_TEST(test_GetNorm "./test_metrics" "--Dataset" "Data/data.csv" "--GetNorm")
ADD_TEST(test_EuclideanC "./test_metrics" "--Dataset" "Data/data.csv" "--EuclideanC")
ADD_TEST(test_ManhattanC "./test_metrics" "--Dataset" "Data/data.csv" "--ManhattanC")
ADD_TEST(test_NeuralC "./test_metrics" "--Dataset" "Data/data.csv" "--NeuralC")
ADD_TEST(test_GaussianC "./test_metrics" "--Dataset" "Data/data.csv" "--GaussianC")
ADD_TEST(test_CompD "./test_metrics" "--CompFiles" "Data/entropy_test1.csv" "--CompD")
ADD_TEST(test_NormCompD "./test_metrics" "--CompFiles" "Data/entropy_test1.csv" "--CompFiles" "Data/entropy_test2.csv" "--NormCompD")
