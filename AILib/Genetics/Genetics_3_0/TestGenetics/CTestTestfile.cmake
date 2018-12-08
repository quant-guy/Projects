# CMake generated Testfile for 
# Source directory: /home/daniel/Hypercomplete/Projects/Projects/AILib/Genetics/Genetics_3_0/TestGenetics
# Build directory: /home/daniel/Hypercomplete/Projects/Projects/AILib/Genetics/Genetics_3_0/TestGenetics
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(test_GP_Constructor1 "./test_genetics" "--GP_Constructor1" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GP_Constructor2 "./test_genetics" "--GP_Constructor2" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GP_GetFirst "./test_genetics" "--GP_GetFirst" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GP_GetSecond "./test_genetics" "--GP_GetSecond" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GP_SetFirst "./test_genetics" "--GP_SetFirst" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GP_SetSecond "./test_genetics" "--GP_SetSecond" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GP_Swap "./test_genetics" "--GP_Swap" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GG_Constructor1 "./test_genetics" "--GG_Constructor1" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GG_Constructor2 "./test_genetics" "--GG_Constructor2" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GG_Constructor3 "./test_genetics" "--GG_Constructor3" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GG_PutGenetic "./test_genetics" "--GG_PutGenetic" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GG_Mutate1 "./test_genetics" "--GG_Mutate1" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GG_Mutate2 "./test_genetics" "--GG_Mutate2" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GG_Ostream "./test_genetics" "--GG_Ostream" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GG_OutputMutate "./test_genetics" "--GG_OutputMutate" "--GeneticFilename" "Structures/GeneticTemplate.txt")
ADD_TEST(test_GPA_Constructor1 "./test_genetics" "--GPA_Constructor1" "--GeneticFilename" "Structures/rnv.dat")
ADD_TEST(test_GPA_Constructor2 "./test_genetics" "--GPA_Constructor2" "--GeneticFilename" "Structures/rnv.dat")
ADD_TEST(test_GPA_Constructor3 "./test_genetics" "--GPA_Constructor3" "--GeneticFilename" "Structures/rnv.dat")
ADD_TEST(test_GPA_Constructor4 "./test_genetics" "--GPA_Constructor4" "--GeneticFilename" "Structures/rnv.dat")
ADD_TEST(test_GPA_Constructor5 "./test_genetics" "--GPA_Constructor5" "--GeneticFilename" "Structures/rnv.dat")
ADD_TEST(test_GPA_Assignment "./test_genetics" "--GPA_Assignment" "--GeneticFilename" "Structures/rnv.dat")
ADD_TEST(test_GPA_Perturb "./test_genetics" "--GPA_Perturb" "--GeneticFilename" "Structures/rnv.dat")
ADD_TEST(test_GPA_Copy "./test_genetics" "--GPA_Copy" "--GeneticFilename" "Structures/rnv.dat")
ADD_TEST(test_GPA_Plus "./test_genetics" "--GPA_Plus" "--GeneticFilename" "Structures/rnv.dat")
