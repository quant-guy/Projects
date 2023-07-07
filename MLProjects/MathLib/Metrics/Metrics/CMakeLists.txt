cmake_minimum_required( VERSION 2.6 )

project( metrics )

set( HEADERS Source/Metrics.h )

set( SOURCE Source/Metrics.cpp )

add_library( ${PROJECT_NAME} SHARED ${HEADERS} ${SOURCE} )

enable_testing()

