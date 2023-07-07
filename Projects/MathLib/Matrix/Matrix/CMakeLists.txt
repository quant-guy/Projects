cmake_minimum_required( VERSION 2.6 )

project( matrix )

#add_definitions( -DENTROPY_API_EXPORTS )

if( WIN32 )
	if( MSVC )
		set_property( DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
			      _SCL_SECURE_NO_DEPRECATE
			      _CRT_SECURE_NO_DEPRECATE )
	endif( MSVC )
	
endif( WIN32 )

include_directories( ${MATH_FUNCTORS}/MathFunctors/Source )

set( HEADERS Source/MatrixCallers.h 
	Source/Matrix.hpp 
	Source/MatrixFunctionality.hpp )

set( SOURCE Source/main.cpp Source/MatrixCallers.cpp )

add_library( ${PROJECT_NAME} SHARED ${HEADERS} ${SOURCE} )

#install( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin ) 
