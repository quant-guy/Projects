cmake_minimum_required( VERSION 2.6 )

project( test_metrics )

include_directories( ${METRICS}/Metrics/Source 
	${TIMING} 
	${UTILITY}/Utility/Source )

set( HEADERS Source/CommandLineOptions.h
	${METRICS}/Metrics/Source/Metrics.h
	${METRICS}/Metrics/Source/Metrics.hpp
	${TIMING}/Timing.h
	${UTILITY}/Utility/Source/CommandLineParser.hpp
	${UTILITY}/Utility/Source/Parser.h )

set( SOURCE  Source/main.cpp
	${UTILITY}/Utility/Source/Parser.cpp )

add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCE} )

target_link_libraries( ${PROJECT_NAME} metrics )

enable_testing()
add_test( test_Euclidean   ./${PROJECT_NAME} --Dataset Data/data.csv --Euclidean   )
add_test( test_Manhattan   ./${PROJECT_NAME} --Dataset Data/data.csv --Manhattan   )
add_test( test_EuclideanN  ./${PROJECT_NAME} --Dataset Data/data.csv --EuclideanN  )
add_test( test_ManhattanN  ./${PROJECT_NAME} --Dataset Data/data.csv --ManhattanN  )
add_test( test_EuclideanV  ./${PROJECT_NAME} --Dataset Data/data.csv --EuclideanV  )
add_test( test_ManhattanV  ./${PROJECT_NAME} --Dataset Data/data.csv --ManhattanV  )
add_test( test_EuclideanVN ./${PROJECT_NAME} --Dataset Data/data.csv --EuclideanVN )
add_test( test_ManhattanVN ./${PROJECT_NAME} --Dataset Data/data.csv --ManhattanVN )
add_test( test_GetNorm     ./${PROJECT_NAME} --Dataset Data/data.csv --GetNorm     )
add_test( test_EuclideanC  ./${PROJECT_NAME} --Dataset Data/data.csv --EuclideanC  )
add_test( test_ManhattanC  ./${PROJECT_NAME} --Dataset Data/data.csv --ManhattanC  )
add_test( test_NeuralC     ./${PROJECT_NAME} --Dataset Data/data.csv --NeuralC     )
add_test( test_GaussianC   ./${PROJECT_NAME} --Dataset Data/data.csv --GaussianC   )
add_test( test_CompD       ./${PROJECT_NAME} --CompFiles Data/entropy_test1.csv --CompD )
add_test( test_NormCompD   ./${PROJECT_NAME} --CompFiles Data/entropy_test1.csv --CompFiles Data/entropy_test2.csv --NormCompD )
