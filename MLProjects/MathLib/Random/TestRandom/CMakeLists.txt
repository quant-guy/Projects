cmake_minimum_required( VERSION 2.6 )

project( test_random )

include_directories( ${RANDOM}/Random/Source
	${TIMING}
	${UTILITY}/Utility/Source )

set( HEADERS Source/CommandLineOptions.h
	${RANDOM}/Random/Source/Random.hpp
	${TIMING}/Timing.h
	${UTILITY}/Utility/Source/CommandLineParser.hpp )

set( SOURCE Source/main.cpp )

add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCE} )

enable_testing()
add_test( test_RandomConstructor1 ./${PROJECT_NAME} --RandomConstructor1 )
add_test( test_RandomConstructor2 ./${PROJECT_NAME} --RandomConstructor2 )
add_test( test_RandomConstructor3 ./${PROJECT_NAME} --RandomConstructor3 )
add_test( test_RandomConstructor4 ./${PROJECT_NAME} --RandomConstructor4 )
add_test( test_TestSetSeed        ./${PROJECT_NAME} --TestSetSeed        )
add_test( test_TestGetSeed        ./${PROJECT_NAME} --TestGetSeed        )
add_test( test_TestGenerate1      ./${PROJECT_NAME} --TestGenerate1      )
add_test( test_TestGenerate2      ./${PROJECT_NAME} --TestGenerate2      )
add_test( test_Generate           ./${PROJECT_NAME} --Generate           )
