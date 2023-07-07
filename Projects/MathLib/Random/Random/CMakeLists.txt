cmake_minimum_required( VERSION 2.6 )

project( random )

#add_definitions( -DRANDOM_API_EXPORTS )

if( WIN32 )
	if( MSVC )
		set_property( DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
			      _SCL_SECURE_NO_DEPRECATE
			      _CRT_SECURE_NO_DEPRECATE )
	endif( MSVC )
	
endif( WIN32 )

set( HEADERS Source/RandomCallers.h Source/Random.hpp )

set( SOURCE Source/main.cpp Source/RandomCallers.cpp )

add_library( ${PROJECT_NAME} SHARED ${HEADERS} ${SOURCE} )

#install( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin ) 
