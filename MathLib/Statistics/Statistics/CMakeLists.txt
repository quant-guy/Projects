cmake_minimum_required( VERSION 2.6 )

project( statistics )

add_library( ${PROJECT_NAME} SHARED Source/Statistics.h Source/Statistics.cpp Source/main.cpp )
