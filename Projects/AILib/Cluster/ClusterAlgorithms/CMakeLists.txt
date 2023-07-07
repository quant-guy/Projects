cmake_minimum_required(VERSION 2.6)

if( WIN32 )
	add_definitions( -DCLUSTER_ALGORITHM_API_EXPORTS )
endif( WIN32 )

project( cluster_algorithms )

include_directories( ${CLUSTER}/Cluster_2_0/Source
                     ${FOURIER}/Fourier/Source 
                     ${MATRIX}/Matrix/Source
                     ${METRICS}/Metrics/Source
                     ${RANDOM}/Random/Source
                     ${STATISTICS}/Statistics/Source
                     ${UTILITY}/Utility/Source )

set ( HEADERS ${CLUSTER}/Cluster_2_0/Source/Cluster.hpp
              ${CLUSTER}/Cluster_2_0/Source/ClusterLibCallers.h
              ${FOURIER}/Fourier/Source/Fourier.h 
              ${MATRIX}/Matrix/Source/Matrix.hpp
              ${METRICS}/Metrics/Source/Metrics.hpp
              ${RANDOM}/Random/Source/Random.hpp
              ${STATISTICS}/Statistics/Source/Statistics.h
              ${UTILITY}/Utility/Source/MemoryAllocationMacros.h
              ${UTILITY}/Utility/Source/Preprocessor.hpp
              Source/ClusterAlgorithmsCallers.h )

set ( SOURCE ${CLUSTER}/Cluster_2_0/Source/ClusterLibCallers.cpp
             Source/ClusterAlgorithmsCallers.cpp
             Source/main.cpp )

add_library ( ${PROJECT_NAME} SHARED ${SOURCE} ${HEADERS} )
