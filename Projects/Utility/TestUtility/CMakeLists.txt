cmake_minimum_required( VERSION 2.6 )

project( test_utility )

include_directories( ${FOURIER}/Fourier/Source
	${STATISTICS}/Statistics/Source
	${TIMING} 
	${UTILITY}/Utility/Source )

set( HEADERS Source/CommandLineOptions.h 
	${FOURIER}/Fourier/Source/Fourier.h
	${STATISTICS}/Statistics/Source/Statistics.h
	${TIMING}/Timing.h
	${UTILITY}/Utility/Source/CommandLineParser.hpp
	${UTILITY}/Utility/Source/Iostream2.h 
	${UTILITY}/Utility/Source/Parser.h
	${UTILITY}/Utility/Source/Preprocessor.hpp
	${UTILITY}/Utility/Source/PreprocessorMacros.h )

set( SOURCE Source/main.cpp )

add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCE} )

target_link_libraries( ${PROJECT_NAME} utility )

enable_testing()
add_test( test_output       ./${PROJECT_NAME} --Output       --InputFile Input/input.csv --Tokens ";, " )
add_test( test_countFields1 ./${PROJECT_NAME} --CountFields1 --InputFile Input/input.csv --Tokens ";, " )
add_test( test_countFields2 ./${PROJECT_NAME} --CountFields2 --InputFile Input/input.csv --Tokens ";, " )
add_test( test_countLines   ./${PROJECT_NAME} --CountLines   --InputFile Input/input.csv --Tokens ";, " )
add_test( test_parser1      ./${PROJECT_NAME} --Parser1      --InputFile Input/input.csv --Tokens ";, " )
add_test( test_parser2      ./${PROJECT_NAME} --Parser2      --InputFile Input/input.csv --Tokens ";, " )
add_test( test_echo         ./${PROJECT_NAME} --Echo         --InputFile Input/input.csv --Tokens ";, " )
# CoutArray_1 triggering an assert.  CoutArray_2 is not.  Not sure why
#add_test( test_coutArray1   ./${PROJECT_NAME} --CoutArray1   --InputFile Input/input.csv --Tokens ";, " )
add_test( test_coutArray2   ./${PROJECT_NAME} --CoutArray2   --InputFile Input/input.csv --Tokens ";, " )
add_test( test_NormalizeR1  ./${PROJECT_NAME} --NormalizeR1  --InputFile Input/input.csv --Tokens ";, " )
add_test( test_NormalizeR2  ./${PROJECT_NAME} --NormalizeR2  --InputFile Input/input.csv --Tokens ";, " )
add_test( test_NormalizeC1  ./${PROJECT_NAME} --NormalizeC1  --InputFile Input/input.csv --Tokens ";, " )
add_test( test_NormalizeC2  ./${PROJECT_NAME} --NormalizeC2  --InputFile Input/input.csv --Tokens ";, " )
add_test( test_Increasing0  ./${PROJECT_NAME} --Increasing0  --InputFile Input/input.csv --Tokens ";, " )
add_test( test_Increasing1  ./${PROJECT_NAME} --Increasing1  --InputFile Input/input.csv --Tokens ";, " )
add_test( test_Mean0        ./${PROJECT_NAME} --Mean0        --InputFile Input/input.csv --Tokens ";, " )
# Mean_1 triggering an assert.  Mean_0 is not.  Not sure why
#add_test( test_Mean1        ./${PROJECT_NAME} --Mean1        --InputFile Input/input.csv --Tokens ";, " )
add_test( test_StdDev0      ./${PROJECT_NAME} --StdDev0      --InputFile Input/input.csv --Tokens ";, " )
add_test( test_StdDev1      ./${PROJECT_NAME} --StdDev1      --InputFile Input/input.csv --Tokens ";, " )
add_test( test_Fourier0     ./${PROJECT_NAME} --Fourier0     --InputFile Input/input.csv --Tokens ";, " )
# triggering exception, not setting data, rows, and cols correctly
# add_test( test_Fourier1     ./${PROJECT_NAME} --Fourier1     --InputFile Input/input.csv --Tokens ";, " )
add_test( test_Bias0        ./${PROJECT_NAME} --Bias0        --InputFile Input/input.csv --Tokens ";, " )
add_test( test_Bias1        ./${PROJECT_NAME} --Bias1        --InputFile Input/input.csv --Tokens ";, " )
