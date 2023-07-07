cmake_minimum_required( VERSION 2.6 )

project( fourier )

add_library( ${PROJECT_NAME} SHARED Source/Fourier.h Source/Fourier.cpp )

enable_testing()
