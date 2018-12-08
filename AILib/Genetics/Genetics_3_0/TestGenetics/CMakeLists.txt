cmake_minimum_required( VERSION 2.6 )

project( test_genetics )

include_directories( ${GENETICS}/Genetics_3_0/Genetics_3_0/Source
	${RANDOM}/Random/Source
	${TIMING}
	${UTILITY}/Utility/Source )

set( HEADERS Source/CommandLineOptions.h
	${GENETICS}/Genetics_3_0/Genetics_3_0/Source/Genetics.hpp 
	${GENETICS}/Genetics_3_0/Genetics_3_0/Source/GeneticPair.hpp 
	${GENETICS}/Genetics_3_0/Genetics_3_0/Source/GeneticParameters.hpp 
	${RANDOM}/Random/Source/Random.hpp
	${TIMING}/Timing.h
	${UTILITY}/Utility/Source/CommandLineParser.hpp )

set( SOURCE Source/main.cpp )

add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCE} )

enable_testing()
add_test( test_GP_Constructor1  ./${PROJECT_NAME} --GP_Constructor1  --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GP_Constructor2  ./${PROJECT_NAME} --GP_Constructor2  --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GP_GetFirst      ./${PROJECT_NAME} --GP_GetFirst      --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GP_GetSecond     ./${PROJECT_NAME} --GP_GetSecond     --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GP_SetFirst      ./${PROJECT_NAME} --GP_SetFirst      --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GP_SetSecond     ./${PROJECT_NAME} --GP_SetSecond     --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GP_Swap          ./${PROJECT_NAME} --GP_Swap          --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GG_Constructor1  ./${PROJECT_NAME} --GG_Constructor1  --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GG_Constructor2  ./${PROJECT_NAME} --GG_Constructor2  --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GG_Constructor3  ./${PROJECT_NAME} --GG_Constructor3  --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GG_PutGenetic    ./${PROJECT_NAME} --GG_PutGenetic    --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GG_Mutate1       ./${PROJECT_NAME} --GG_Mutate1       --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GG_Mutate2       ./${PROJECT_NAME} --GG_Mutate2       --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GG_Ostream       ./${PROJECT_NAME} --GG_Ostream       --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GG_OutputMutate  ./${PROJECT_NAME} --GG_OutputMutate  --GeneticFilename Structures/GeneticTemplate.txt )
add_test( test_GPA_Constructor1 ./${PROJECT_NAME} --GPA_Constructor1 --GeneticFilename Structures/rnv.dat             )
add_test( test_GPA_Constructor2 ./${PROJECT_NAME} --GPA_Constructor2 --GeneticFilename Structures/rnv.dat             )
add_test( test_GPA_Constructor3 ./${PROJECT_NAME} --GPA_Constructor3 --GeneticFilename Structures/rnv.dat             )
add_test( test_GPA_Constructor4 ./${PROJECT_NAME} --GPA_Constructor4 --GeneticFilename Structures/rnv.dat             )
add_test( test_GPA_Constructor5 ./${PROJECT_NAME} --GPA_Constructor5 --GeneticFilename Structures/rnv.dat             )
add_test( test_GPA_Assignment   ./${PROJECT_NAME} --GPA_Assignment   --GeneticFilename Structures/rnv.dat             )
add_test( test_GPA_Perturb      ./${PROJECT_NAME} --GPA_Perturb      --GeneticFilename Structures/rnv.dat             )
add_test( test_GPA_Copy         ./${PROJECT_NAME} --GPA_Copy         --GeneticFilename Structures/rnv.dat             )
add_test( test_GPA_Plus         ./${PROJECT_NAME} --GPA_Plus         --GeneticFilename Structures/rnv.dat             )
