cmake_minimum_required( VERSION 2.6 )

project( neural_network )

if ( WIN32 )
	add_definitions( -DNEURAL_API_EXPORTS )
endif ( WIN32 )

include_directories( ${ACTIVATION_FUNCTIONS}/ActivationFunctions/Source
                     ${GENETICS_3_0}/Genetics_3_0/Source
                     ${MATRIX}/Matrix/Source
                     ${RANDOM}/Random/Source )

set( HEADERS ${MATRIX}/Matrix/Source/Matrix.hpp
             ${GENETICS_3_0}/Genetics_3_0/Source/Genetics.hpp
             ${GENETICS_3_0}/Genetics_3_0/Source/GeneticPair.hpp
             ${RANDOM}/Random/Source/Random.hpp
             Source/NeuralUnit.hpp 
             Source/NeuralCallers.h )

set( SOURCE Source/main.cpp     
            Source/NeuralCallers.cpp )

add_library( ${PROJECT_NAME} SHARED ${HEADERS} ${SOURCE} )
