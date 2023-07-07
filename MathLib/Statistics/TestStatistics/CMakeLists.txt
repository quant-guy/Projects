cmake_minimum_required( VERSION 2.6 )

project( test_statistics )

include_directories( ${STATISTICS}/Statistics/Source 
	${TIMING} 
	${UTILITY}/Utility/Source )

set( HEADERS Source/CommandLineOptions.h 
	${STATISTICS}/Statistics/Source/Statistics.h
	${TIMING}/Timing.h 
	${UTILITY}/Utility/Source/CommandLineParser.hpp
	${UTILITY}/Utility/Source/Parser.h )

set( SOURCE Source/main.cpp ${UTILITY}/Utility/Source/Parser.cpp )

add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCE} )

target_link_libraries( ${PROJECT_NAME} statistics )

enable_testing()
add_test( test_max                      ./${PROJECT_NAME} --Max                    --InputFile Input/input.csv --Tokens ";, " )
add_test( test_mean                     ./${PROJECT_NAME} --Mean                   --InputFile Input/input.csv --Tokens ";, " )
add_test( test_standard_deviation       ./${PROJECT_NAME} --StandardDeviation      --InputFile Input/input.csv --Tokens ";, " )
add_test( test_covariance               ./${PROJECT_NAME} --Covariance             --InputFile Input/input.csv --Tokens ";, " )
add_test( test_mean_centered_covariance ./${PROJECT_NAME} --MeanCenteredCovariance --InputFile Input/input.csv --Tokens ";, " )
add_test( test_normalize_by_column      ./${PROJECT_NAME} --NormalizeByColumn      --InputFile Input/input.csv --Tokens ";, " )
add_test( test_normalize_by_row         ./${PROJECT_NAME} --NormalizeByRow         --InputFile Input/input.csv --Tokens ";, " )
