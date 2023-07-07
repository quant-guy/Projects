cmake_minimum_required( VERSION 2.6 )

project( test_activation_functions )

include_directories( ${ACTIVATION_FUNCTIONS}/ActivationFunctions/Source 
	${TIMING}
	${UTILITY}/Utility/Source )

set( HEADERS Source/CommandLineOptions.h
	${ACTIVATION_FUNCTIONS}/ActivationFunctions/Source/ActivationFunctions.hpp
	${TIMING}/Timing.h
	${UTILITY}/Utility/Source/CommandLineParser.hpp )

set( SOURCE Source/main.cpp )

add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCE} )

enable_testing()
add_test( test_Logistic1          ./${PROJECT_NAME} --Logistic1          )
add_test( test_Logistic2          ./${PROJECT_NAME} --Logistic2          )
add_test( test_Logistic3          ./${PROJECT_NAME} --Logistic3          )
add_test( test_Logistic4          ./${PROJECT_NAME} --Logistic4          )
add_test( test_InverseTangent1    ./${PROJECT_NAME} --InverseTangent1    )
add_test( test_InverseTangent2    ./${PROJECT_NAME} --InverseTangent2    )
add_test( test_InverseTangent3    ./${PROJECT_NAME} --InverseTangent3    )
add_test( test_InverseTangent4    ./${PROJECT_NAME} --InverseTangent4    )
add_test( test_HyperbolicTangent1 ./${PROJECT_NAME} --HyperbolicTangent1 )
add_test( test_HyperbolicTangent2 ./${PROJECT_NAME} --HyperbolicTangent2 )
add_test( test_HyperbolicTangent3 ./${PROJECT_NAME} --HyperbolicTangent3 )
add_test( test_HyperbolicTangent4 ./${PROJECT_NAME} --HyperbolicTangent4 )
add_test( test_Algebraic1         ./${PROJECT_NAME} --Algebraic1         )
add_test( test_Algebraic2         ./${PROJECT_NAME} --Algebraic2         )
add_test( test_Algebraic3         ./${PROJECT_NAME} --Algebraic3         )
add_test( test_Algebraic4         ./${PROJECT_NAME} --Algebraic4         )
add_test( test_Erf1               ./${PROJECT_NAME} --Erf1               )
add_test( test_Erf2               ./${PROJECT_NAME} --Erf2               )
add_test( test_Erf3               ./${PROJECT_NAME} --Erf3               )
add_test( test_Erf4               ./${PROJECT_NAME} --Erf4               )
add_test( test_Gompertz1          ./${PROJECT_NAME} --Gompertz1          )
add_test( test_Gompertz2          ./${PROJECT_NAME} --Gompertz2          )
add_test( test_Gompertz3          ./${PROJECT_NAME} --Gompertz3          )
add_test( test_Gompertz4          ./${PROJECT_NAME} --Gompertz4          )
add_test( test_Control1           ./${PROJECT_NAME} --Control1           )
add_test( test_Control2           ./${PROJECT_NAME} --Control2           )
add_test( test_Control3           ./${PROJECT_NAME} --Control3           )
add_test( test_Control4           ./${PROJECT_NAME} --Control4           )
