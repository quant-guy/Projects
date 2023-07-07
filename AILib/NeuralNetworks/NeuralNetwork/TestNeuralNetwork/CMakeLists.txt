cmake_minimum_required( VERSION 2.6 )

project( test_neural_network )

include_directories( ${ACTIVATION_FUNCTIONS}/ActivationFunctions/Source
	${CLUSTER}/Cluster_2_0/Source
	${FOURIER}/Fourier/Source
	${GENETICS_3_0}/Genetics_3_0/Source
	${MATRIX}/Matrix/Source
	${METRICS}/Metrics/Source
	${NEURAL_NETWORK}/NeuralNetwork/Source  
	${NEURAL_NETWORK}/NeuralAlgorithms/Source  
	${STATISTICS}/Statistics/Source
	${RANDOM}/Random/Source
	${TIMING}
	${UTILITY}/Utility/Source )

set( HEADERS ${ACTIVATION_FUNCTIONS}/ActivationFunctions/Source/ActivationFunctions.hpp
	${CLUSTER}/Cluster_2_0/Source/Cluster.hpp
	${FOURIER}/Fourier/Source/Fourier.h
	${GENETICS_3_0}/Genetics_3_0/Source/Genetics.hpp
	${MATRIX}/Matrix/Source/Matrix.hpp
	${METRICS}/Metrics/Source/Metrics.hpp
	${NEURAL_NETWORK}/NeuralNetwork/Source/NeuralCallers.h 
	${NEURAL_NETWORK}/NeuralAlgorithms/Source/NeuralAlgorithmsCallers.h 
	${NEURAL_NETWORK}/NeuralNetwork/Source/NeuralUnit.hpp 
	${RANDOM}/Random/Source/Random.hpp
	${STATISTICS}/Statistics/Source/Statistics.h
	${UTILITY}/Utility/Source/CommandLineParser.hpp
	${UTILITY}/Utility/Source/Preprocessor.hpp
	${UTILITY}/Utility/Source/Parser.h
	${UTILITY}/Utility/Source/MemoryAllocationMacros.h
	${TIMING}/Timing.h
	Source/CommandLineOptions.h )

set( SOURCE ${UTILITY}/Utility/Source/Parser.cpp
	Source/main.cpp )

add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCE} )

target_link_libraries( ${PROJECT_NAME} neural_network )
target_link_libraries( ${PROJECT_NAME} neural_algorithms )

enable_testing()
add_test( N32_Ostream           ${PROJECT_NAME} --N32_Ostream                                          )
add_test( N32_CheckDim          ${PROJECT_NAME} --N32_CheckDim                                         )
add_test( N32_Constructor1      ${PROJECT_NAME} --N32_Constructor1                                     )
add_test( N32_Constructor2      ${PROJECT_NAME} --N32_Constructor2                                     )
add_test( N32_Constructor3      ${PROJECT_NAME} --N32_Constructor3                                     )
add_test( N32_GetRows           ${PROJECT_NAME} --N32_GetRows                                          )
add_test( N32_GetColumns        ${PROJECT_NAME} --N32_GetColumns                                       )
add_test( N32_SetNext           ${PROJECT_NAME} --N32_SetNext                                          )
add_test( N32_SetPrevious       ${PROJECT_NAME} --N32_SetPrevious                                      )
add_test( N32_SetLearningRate   ${PROJECT_NAME} --N32_SetLearningRate                                  )
add_test( N32_PutNeural         ${PROJECT_NAME} --N32_PutNeural                                        )
add_test( N32_Propagate1        ${PROJECT_NAME} --N32_Propagate1                                       )
add_test( N32_Propagate2        ${PROJECT_NAME} --N32_Propagate2                                       )
add_test( N32_BackPropagate1    ${PROJECT_NAME} --N32_BackPropagate1                                   )
add_test( N32_BackPropagate2    ${PROJECT_NAME} --N32_BackPropagate2                                   )
add_test( NMS_Ostream           ${PROJECT_NAME} --NMS_Ostream                                          )
add_test( NMS_Constructor1      ${PROJECT_NAME} --NMS_Constructor1                                     )
add_test( NMS_Constructor2      ${PROJECT_NAME} --NMS_Constructor2                                     )
add_test( NMS_PutNeural         ${PROJECT_NAME} --NMS_PutNeural                                        )
add_test( NMS_GetNeural         ${PROJECT_NAME} --NMS_GetNeural                                        )
add_test( NMS_SetLearningRate1  ${PROJECT_NAME} --NMS_SetLearningRate1                                 )
add_test( NMS_SetLearningRate2  ${PROJECT_NAME} --NMS_SetLearningRate2                                 )
add_test( NMS_Error             ${PROJECT_NAME} --NMS_Error                                            )
add_test( NMS_Propagate         ${PROJECT_NAME} --NMS_Propagate                                        )
add_test( NMS_BackPropagate     ${PROJECT_NAME} --NMS_BackPropagate                                    )
add_test( N32_Learning          ${PROJECT_NAME} --N32_Learning                                         )
add_test( N32_Learning2         ${PROJECT_NAME} --N32_Learning2                                        )
add_test( NMS_Learning          ${PROJECT_NAME} --NMS_Learning                                         )
add_test( NMS_Learning2         ${PROJECT_NAME} --NMS_Learning2                                        )
add_test( NMS_Pyramid           ${PROJECT_NAME} --NMS_Pyramid                                          )
add_test( NMS_Macros1           ${PROJECT_NAME} --NMS_Macros1                                          )
add_test( NMS_Macros2           ${PROJECT_NAME} --NMS_Macros2                                          )
add_test( NMS_Genetics          ${PROJECT_NAME} --NMS_Genetics --GeneticFilename Genetics/Ternary.txt  )
add_test( NMS_Mutate            ${PROJECT_NAME} --NMS_Mutate   --GeneticFilename Genetics/Ternary.txt  )
add_test( M_NU_ConstDest        ${PROJECT_NAME} --M_NU_ConstDest                                       )
add_test( M_NU_CopyConstDest    ${PROJECT_NAME} --M_NU_CopyConstDest                                   )
add_test( M_NU_DimConstDest     ${PROJECT_NAME} --M_NU_DimConstDest                                    )
add_test( M_NU_Rho              ${PROJECT_NAME} --M_NU_Rho                                             )
add_test( M_NU_Sig              ${PROJECT_NAME} --M_NU_Sig                                             )
add_test( M_NU_SetNext          ${PROJECT_NAME} --M_NU_SetNext                                         )
add_test( M_NU_SetPrev          ${PROJECT_NAME} --M_NU_SetPrev                                         )
add_test( M_NU_SetInput         ${PROJECT_NAME} --M_NU_SetInput                                        )
add_test( M_NU_GetOutput        ${PROJECT_NAME} --M_NU_GetOutput                                       )
add_test( M_NU_PutNeural        ${PROJECT_NAME} --M_NU_PutNeural                                       )
add_test( M_NU_GetNeural        ${PROJECT_NAME} --M_NU_GetNeural                                       )
add_test( M_NU_Propagate1       ${PROJECT_NAME} --M_NU_Propagate1                                      )
add_test( M_NU_Propagate2       ${PROJECT_NAME} --M_NU_Propagate2                                      )
add_test( M_NU_BackPropagate1   ${PROJECT_NAME} --M_NU_BackPropagate1                                  )
add_test( M_NU_BackPropagate2   ${PROJECT_NAME} --M_NU_BackPropagate2                                  )
add_test( M_NU_Error            ${PROJECT_NAME} --M_NU_Error                                           )
add_test( M_NMS_ConstDest       ${PROJECT_NAME} --M_NMS_ConstDest                                      )
add_test( M_NMS_CopyConstDest   ${PROJECT_NAME} --M_NMS_CopyConstDest                                  )
add_test( M_NMS_DimConstDest    ${PROJECT_NAME} --M_NMS_DimConstDest                                   )
add_test( M_NMS_PushBack        ${PROJECT_NAME} --M_NMS_PushBack                                       )
add_test( M_NMS_SetRho1         ${PROJECT_NAME} --M_NMS_SetRho1                                        )
add_test( M_NMS_SetRho2         ${PROJECT_NAME} --M_NMS_SetRho2                                        )
add_test( M_NMS_SetSig1         ${PROJECT_NAME} --M_NMS_SetSig1                                        )
add_test( M_NMS_SetSig2         ${PROJECT_NAME} --M_NMS_SetSig2                                        )
add_test( M_NMS_PutNeural       ${PROJECT_NAME} --M_NMS_PutNeural                                      )
add_test( M_NMS_Propagate       ${PROJECT_NAME} --M_NMS_Propagate                                      )
add_test( M_NMS_BackPropagate1  ${PROJECT_NAME} --M_NMS_BackPropagate1                                 )
add_test( M_NMS_BackPropagate2  ${PROJECT_NAME} --M_NMS_BackPropagate2                                 )
add_test( M_NMS_Error           ${PROJECT_NAME} --M_NMS_Error                                          )
add_test( SupervisedLearning1   ${PROJECT_NAME} --SupervisedLearning1   -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( SupervisedXVal1       ${PROJECT_NAME} --SupervisedXVal1       -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( SupervisedApply1      ${PROJECT_NAME} --SupervisedApply1      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( SupervisedError1      ${PROJECT_NAME} --SupervisedError1      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( UnsupervisedLearning1 ${PROJECT_NAME} --UnsupervisedLearning1 -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( UnsupervisedXVal1     ${PROJECT_NAME} --UnsupervisedXVal1     -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( UnsupervisedApply1    ${PROJECT_NAME} --UnsupervisedApply1    -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( SupervisedLearning2   ${PROJECT_NAME} --SupervisedLearning2   -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( SupervisedXVal2       ${PROJECT_NAME} --SupervisedXVal2       -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( SupervisedApply2      ${PROJECT_NAME} --SupervisedApply2      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( SupervisedError2      ${PROJECT_NAME} --SupervisedError2      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( UnsupervisedLearning2 ${PROJECT_NAME} --UnsupervisedLearning2 -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( UnsupervisedXVal2     ${PROJECT_NAME} --UnsupervisedXVal2     -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( UnsupervisedApply2    ${PROJECT_NAME} --UnsupervisedApply2    -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( SupervisedLearning3   ${PROJECT_NAME} --SupervisedLearning3   -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( SupervisedXVal3       ${PROJECT_NAME} --SupervisedXVal3       -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( SupervisedApply3      ${PROJECT_NAME} --SupervisedApply3      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( SupervisedError3      ${PROJECT_NAME} --SupervisedError3      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( UnsupervisedLearning3 ${PROJECT_NAME} --UnsupervisedLearning3 -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( UnsupervisedXVal3     ${PROJECT_NAME} --UnsupervisedXVal3     -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" )
add_test( UnsupervisedApply3    ${PROJECT_NAME} --UnsupervisedApply3    -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" )
