cmake_minimum_required(VERSION 2.6)

if( WIN32 )
	add_definitions( -DCLUSTER_LIB_API_EXPORTS )
endif( WIN32 )

project( cluster_2_0 )

include_directories( ${FOURIER}/Fourier/Source 
                     ${MATRIX}/Matrix/Source
                     ${METRICS}/Metrics/Source
                     ${RANDOM}/Random/Source
                     ${STATISTICS}/Statistics/Source
                     ${UTILITY}/Utility/Source )

set ( HEADERS Source/ClusterLibCallers.h
              Source/Cluster.hpp
              ${FOURIER}/Fourier/Source/Fourier.h 
              ${MATRIX}/Matrix/Source/Matrix.hpp
              ${METRICS}/Metrics/Source/Metrics.hpp
              ${RANDOM}/Random/Source/Random.hpp
              ${STATISTICS}/Statistics/Source/Statistics.h
              ${UTILITY}/Utility/Source/MemoryAllocationMacros.h
              ${UTILITY}/Utility/Source/Preprocessor.hpp )

set ( SOURCE Source/ClusterLibCallers.cpp
             Source/main.cpp )

add_library ( ${PROJECT_NAME} SHARED ${SOURCE} ${HEADERS} )
