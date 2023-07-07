cmake_minimum_required( VERSION 2.6 )

project( neural_algorithms )

if ( WIN32 )
	add_definitions( -DNEURAL_ALGORITHM_API_EXPORTS )
endif ( WIN32 )

include_directories( ${ACTIVATION_FUNCTIONS}/ActivationFunctions/Source
                     ${CLUSTER}/Cluster_2_0/Source
                     ${FOURIER}/Fourier/Source
                     ${GENETICS_3_0}/Genetics_3_0/Source
                     ${MATRIX}/Matrix/Source
                     ${METRICS}/Metrics/Source
                     ${NEURAL_NETWORK}/NeuralNetwork/Source
                     ${RANDOM}/Random/Source
                     ${STATISTICS}/Statistics/Source
                     ${UTILITY}/Utility/Source )

set( HEADERS ${ACTIVATION_FUNCTIONS}/ActivationFunctions/Source/ActivationFunctions.hpp
             ${CLUSTER}/Cluster_2_0/Source/Cluster.hpp
             ${FOURIER}/Fourier/Source/Fourier.h
             ${MATRIX}/Matrix/Source/Matrix.hpp
             ${GENETICS_3_0}/Genetics_3_0/Source/Genetics.hpp
             ${GENETICS_3_0}/Genetics_3_0/Source/GeneticPair.hpp
             ${METRICS}/Metrics/Source/Metrics.hpp
             ${NEURAL_NETWORK}/NeuralNetwork/Source/NeuralCallers.h
             ${NEURAL_NETWORK}/NeuralNetwork/Source/NeuralUnit.hpp 
             ${RANDOM}/Random/Source/Random.hpp
             ${STATISTICS}/Statistics/Source/Statistics.h
             ${UTILITY}/Utility/Source/Preprocessor.hpp
             Source/NeuralAlgorithmsCallers.h )

set( SOURCE ${FOURIER}/Fourier/Source/Fourier.cpp
            ${NEURAL_NETWORK}/NeuralNetwork/Source/NeuralCallers.cpp
            ${STATISTICS}/Statistics/Source/Statistics.cpp
            Source/NeuralAlgorithmsCallers.cpp
            Source/main.cpp )

add_library( ${PROJECT_NAME} SHARED ${HEADERS} ${SOURCE} )
