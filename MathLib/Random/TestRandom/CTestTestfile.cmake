# CMake generated Testfile for 
# Source directory: /home/daniel/Hypercomplete/Projects/Projects/MathLib/Random/TestRandom
# Build directory: /home/daniel/Hypercomplete/Projects/Projects/MathLib/Random/TestRandom
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(test_RandomConstructor1 "./test_random" "--RandomConstructor1")
ADD_TEST(test_RandomConstructor2 "./test_random" "--RandomConstructor2")
ADD_TEST(test_RandomConstructor3 "./test_random" "--RandomConstructor3")
ADD_TEST(test_RandomConstructor4 "./test_random" "--RandomConstructor4")
ADD_TEST(test_TestSetSeed "./test_random" "--TestSetSeed")
ADD_TEST(test_TestGetSeed "./test_random" "--TestGetSeed")
ADD_TEST(test_TestGenerate1 "./test_random" "--TestGenerate1")
ADD_TEST(test_TestGenerate2 "./test_random" "--TestGenerate2")
ADD_TEST(test_Generate "./test_random" "--Generate")
