cmake_minimum_required( VERSION 2.6 )

project( utility )

include_directories( ${FOURIER}/Fourier/Source 
                     ${STATISTICS}/Statistics/Source )
                     

set( HEADERS Source/Iostream2.h   
             Source/Parser.h  
             Source/PreprocessorMacros.h
             Source/Preprocessor.hpp 
             Source/UtilityCallers.h
             ${FOURIER}/Fourier/Source/Fourier.h
             ${STATISTICS}/Statistics/Source/Statistics.h )

set( SOURCE  Source/Iostream2.cpp 
             Source/main.cpp
             Source/Parser.cpp 
             Source/UtilityCallers.cpp
             ${FOURIER}/Fourier/Source/Fourier.cpp
             ${STATISTICS}/Statistics/Source/Statistics.cpp )

add_library( ${PROJECT_NAME} SHARED ${HEADERS} ${SOURCE} )
