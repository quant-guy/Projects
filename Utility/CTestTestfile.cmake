# CMake generated Testfile for 
# Source directory: /home/daniel/Hypercomplete/Projects/Projects/Utility
# Build directory: /home/daniel/Hypercomplete/Projects/Projects/Utility
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(test_progressbar "python" "ProgressBar/ProgressBar.py")
SUBDIRS(Utility)
SUBDIRS(TestUtility)
