# CMake generated Testfile for 
# Source directory: /home/daniel/Hypercomplete/Projects/Projects/MathLib/Metrics
# Build directory: /home/daniel/Hypercomplete/Projects/Projects/MathLib/Metrics
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(test_levenshtein "python" "Levenshtein/Levenshtein.py")
SUBDIRS(Metrics)
SUBDIRS(TestMetrics)
