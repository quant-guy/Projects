cmake_minimum_required( VERSION 2.6 )

project( test_matrix )

include_directories( ${MATRIX}/Matrix/Source
	${TIMING}
	${UTILITY}/Utility/Source )


set( HEADERS Source/CommandLineOptions.h      
	${MATRIX}/Matrix/Source/Matrix.hpp
	${MATRIX}/Matrix/Source/MatrixFunctionality.hpp
	${TIMING}/Timing.h
	${UTILITY}/Utility/Source/CommandLineParser.hpp )

set( SOURCE Source/main.cpp )

add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCE} )

enable_testing()
add_test( matrix_mul_const  ${PROJECT_NAME} --MulConstMatrix        )
add_test( matrix_ostream    ${PROJECT_NAME} --Ostream               ) 
add_test( matrix_transpose  ${PROJECT_NAME} --Transpose             )
add_test( matrix_sig        ${PROJECT_NAME} --Sigmoid               )
add_test( matrix_dsig       ${PROJECT_NAME} --DSigmoid              )
add_test( matrix_err        ${PROJECT_NAME} --Err                   )
add_test( matrix_comp       ${PROJECT_NAME} --Comp                  )
add_test( matrix_kro        ${PROJECT_NAME} --Kro                   )
add_test( matrix_dot        ${PROJECT_NAME} --Dot                   )
add_test( matrix_sum        ${PROJECT_NAME} --Sum                   )
add_test( matrix_con_1      ${PROJECT_NAME} --Constructor1          )
add_test( matrix_con_2      ${PROJECT_NAME} --Constructor2          )
add_test( matrix_con_3      ${PROJECT_NAME} --Constructor3          )
add_test( matrix_fil_1      ${PROJECT_NAME} --Fill1                 )
add_test( matrix_fil_2      ${PROJECT_NAME} --Fill2                 )
add_test( matrix_fil_3      ${PROJECT_NAME} --Fill3                 )
add_test( matrix_put_m      ${PROJECT_NAME} --PutMatrix             )
add_test( matrix_get_m      ${PROJECT_NAME} --GetMatrix             )
add_test( matrix_get_r      ${PROJECT_NAME} --GetRows               )
add_test( matrix_get_c      ${PROJECT_NAME} --GetColumns            )
add_test( matrix_size       ${PROJECT_NAME} --Size                  )
add_test( matrix_at         ${PROJECT_NAME} --At                    )
add_test( matrix_add        ${PROJECT_NAME} --Addition              )
add_test( matrix_sub        ${PROJECT_NAME} --Subtraction           )
add_test( matrix_mul        ${PROJECT_NAME} --Multiplication        )
add_test( matrix_assn       ${PROJECT_NAME} --Assignment            )
add_test( matrix_add_a      ${PROJECT_NAME} --AdditionAssignment    )
add_test( matrix_sub_a      ${PROJECT_NAME} --SubtractionAssignment )
