cmake_minimum_required( VERSION 2.6 )

project( test_fourier )

include_directories( ${FOURIER}/Fourier/Source 
	${TIMING}
	${UTILITY}/Utility/Source  )

set( HEADERS Source/CommandLineOptions.h
	${FOURIER}/Fourier/Source/Fourier.h
	${TIMING}/Timing.h
	${UTILITY}/Utility/Source/CommandLineParser.hpp
	${UTILITY}/Utility/Source/Parser.h )

set( SOURCE Source/main.cpp ${UTILITY}/Utility/Source/Parser.cpp )

add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCE} )

target_link_libraries( ${PROJECT_NAME} fourier )

enable_testing()
