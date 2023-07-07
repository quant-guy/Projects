cmake_minimum_required(VERSION 2.6)

project( test_cluster )

include_directories( ${CLUSTER}/Cluster_2_0/Source
                     ${CLUSTER}/ClusterAlgorithms/Source
                     ${FOURIER}/Fourier/Source
                     ${MATRIX}/Matrix/Source
                     ${METRICS}/Metrics/Source
                     ${RANDOM}/Random/Source
                     ${STATISTICS}/Statistics/Source
                     ${TIMING}
                     ${UTILITY}/Utility/Source       )

set( HEADERS Source/CommandLineOptions.h            
             ${CLUSTER}/ClusterAlgorithms/Source/ClusterAlgorithmsCallers.h
             ${CLUSTER}/Cluster_2_0/Source/Cluster.hpp
             ${FOURIER}/Fourier/Source/Fourier.h
             ${METRICS}/Metrics/Source/Metrics.hpp
             ${MATRIX}/Matrix/Source/Matrix.hpp
             ${RANDOM}/Random/Source/Random.h
             ${STATISTICS}/Statistics/Source/Statistics.h
             ${TIMING}/Timing.h
             ${UTILITY}/Utility/Source/Iostream2.h
             ${UTILITY}/Utility/Source/MemoryAllocationMacros.h
             ${UTILITY}/Utility/Source/Parser.h
             ${UTILITY}/Utility/Source/CommandLineParser.hpp
             ${UTILITY}/Utility/Source/Preprocessor.hpp )

set( SOURCE Source/main.cpp
            ${UTILITY}/Utility/Source/Iostream2.cpp
            ${UTILITY}/Utility/Source/Parser.cpp )
     

add_executable( ${PROJECT_NAME} ${SOURCE} ${HEADERS} )

target_link_libraries( ${PROJECT_NAME} cluster_algorithms )

enable_testing()
add_test( KMeansTrain                          ./${PROJECT_NAME} --KMeans      --Train         --InputFilename "Input/input.csv" )
add_test( KMeansApply                          ./${PROJECT_NAME} --KMeans      --Apply         --InputFilename "Input/input.csv" )
add_test( KMeansCrossValidate                  ./${PROJECT_NAME} --KMeans      --CrossValidate --InputFilename "Input/input.csv" --XValFilename "Input/x.csv" )
add_test( KMeansGetError                       ./${PROJECT_NAME} --KMeans      --GetError      --InputFilename "Input/input.csv" )
add_test( KMeansTrainArray                     ./${PROJECT_NAME} --KMeans      --Train         --InputFilename "Input/input.csv" --Array )
add_test( KMeansApplyArray                     ./${PROJECT_NAME} --KMeans      --Apply         --InputFilename "Input/input.csv" --Array )
add_test( KMeansCrossValidateArray             ./${PROJECT_NAME} --KMeans      --CrossValidate --InputFilename "Input/input.csv" --Array --XValFilename "Input/x.csv" )
add_test( KMeansGetErrorArray                  ./${PROJECT_NAME} --KMeans      --GetError      --InputFilename "Input/input.csv" --Array )
add_test( KMeansTrainMatrix                    ./${PROJECT_NAME} --KMeans      --Train         --InputFilename "Input/input.csv" --Matrix )
add_test( KMeansApplyMatrix                    ./${PROJECT_NAME} --KMeans      --Apply         --InputFilename "Input/input.csv" --Matrix )
add_test( KMeansCrossValidateMatrix            ./${PROJECT_NAME} --KMeans      --CrossValidate --InputFilename "Input/input.csv" --Matrix --XValFilename "Input/x.csv" )
add_test( KMeansGetErrorMatrix                 ./${PROJECT_NAME} --KMeans      --GetError      --InputFilename "Input/input.csv" --Matrix )
add_test( KMeansTrainPreprocessor              ./${PROJECT_NAME} --KMeans      --Train         --InputFilename "Input/input.csv" --Preprocessor )
add_test( KMeansApplyPreprocessor              ./${PROJECT_NAME} --KMeans      --Apply         --InputFilename "Input/input.csv" --Preprocessor )
add_test( KMeansCrossValidatePreprocessor      ./${PROJECT_NAME} --KMeans      --CrossValidate --InputFilename "Input/input.csv" --Preprocessor --XValFilename "Input/x.csv" )
add_test( KMeansGetErrorPreprocessor           ./${PROJECT_NAME} --KMeans      --GetError      --InputFilename "Input/input.csv" --Preprocessor )
add_test( SOMTrain                             ./${PROJECT_NAME} --SOM         --Train         --InputFilename "Input/input.csv" )
add_test( SOMApply                             ./${PROJECT_NAME} --SOM         --Apply         --InputFilename "Input/input.csv" )
add_test( SOMCrossValidate                     ./${PROJECT_NAME} --SOM         --CrossValidate --InputFilename "Input/input.csv" --XValFilename "Input/x.csv" )
add_test( SOMGetError                          ./${PROJECT_NAME} --SOM         --GetError      --InputFilename "Input/input.csv" )
add_test( SOMTrainArray                        ./${PROJECT_NAME} --SOM         --Train         --InputFilename "Input/input.csv" --Array )
add_test( SOMApplyArray                        ./${PROJECT_NAME} --SOM         --Apply         --InputFilename "Input/input.csv" --Array )
add_test( SOMCrossValidateArray                ./${PROJECT_NAME} --SOM         --CrossValidate --InputFilename "Input/input.csv" --Array --XValFilename "Input/x.csv" )
add_test( SOMGetErrorArray                     ./${PROJECT_NAME} --SOM         --GetError      --InputFilename "Input/input.csv" --Array )
add_test( SOMTrainMatrix                       ./${PROJECT_NAME} --SOM         --Train         --InputFilename "Input/input.csv" --Matrix )
add_test( SOMApplyMatrix                       ./${PROJECT_NAME} --SOM         --Apply         --InputFilename "Input/input.csv" --Matrix )
add_test( SOMCrossValidateMatrix               ./${PROJECT_NAME} --SOM         --CrossValidate --InputFilename "Input/input.csv" --Matrix --XValFilename "Input/x.csv" )
add_test( SOMGetErrorMatrix                    ./${PROJECT_NAME} --SOM         --GetError      --InputFilename "Input/input.csv" --Matrix )
add_test( SOMTrainPreprocessor                 ./${PROJECT_NAME} --SOM         --Train         --InputFilename "Input/input.csv" --Preprocessor )
add_test( SOMApplyPreprocessor                 ./${PROJECT_NAME} --SOM         --Apply         --InputFilename "Input/input.csv" --Preprocessor )
add_test( SOMCrossValidatePreprocessor         ./${PROJECT_NAME} --SOM         --CrossValidate --InputFilename "Input/input.csv" --Preprocessor --XValFilename "Input/x.csv" )
add_test( SOMGetErrorPreprocessor              ./${PROJECT_NAME} --SOM         --GetError      --InputFilename "Input/input.csv" --Preprocessor )
add_test( TopologicalTrain                     ./${PROJECT_NAME} --Topological --Train         --InputFilename "Input/input.csv" )
add_test( TopologicalApply                     ./${PROJECT_NAME} --Topological --Apply         --InputFilename "Input/input.csv" )
add_test( TopologicalCrossValidate             ./${PROJECT_NAME} --Topological --CrossValidate --InputFilename "Input/input.csv" --XValFilename "Input/x.csv" )
add_test( TopologicalGetError                  ./${PROJECT_NAME} --Topological --GetError      --InputFilename "Input/input.csv" )
add_test( TopologicalTrainArray                ./${PROJECT_NAME} --Topological --Train         --InputFilename "Input/input.csv" --Array )
add_test( TopologicalApplyArray                ./${PROJECT_NAME} --Topological --Apply         --InputFilename "Input/input.csv" --Array )
add_test( TopologicalCrossValidateArray        ./${PROJECT_NAME} --Topological --CrossValidate --InputFilename "Input/input.csv" --Array --XValFilename "Input/x.csv" )
add_test( TopologicalGetErrorArray             ./${PROJECT_NAME} --Topological --GetError      --InputFilename "Input/input.csv" --Array )
add_test( TopologicalTrainMatrix               ./${PROJECT_NAME} --Topological --Train         --InputFilename "Input/input.csv" --Matrix )
add_test( TopologicalApplyMatrix               ./${PROJECT_NAME} --Topological --Apply         --InputFilename "Input/input.csv" --Matrix )
add_test( TopologicalCrossValidateMatrix       ./${PROJECT_NAME} --Topological --CrossValidate --InputFilename "Input/input.csv" --Matrix --XValFilename "Input/x.csv" )
add_test( TopologicalGetErrorMatrix            ./${PROJECT_NAME} --Topological --GetError      --InputFilename "Input/input.csv" --Matrix )
add_test( TopologicalTrainPreprocessor         ./${PROJECT_NAME} --Topological --Train         --InputFilename "Input/input.csv" --Preprocessor )
add_test( TopologicalApplyPreprocessor         ./${PROJECT_NAME} --Topological --Apply         --InputFilename "Input/input.csv" --Preprocessor )
add_test( TopologicalCrossValidatePreprocessor ./${PROJECT_NAME} --Topological --CrossValidate --InputFilename "Input/input.csv" --Preprocessor --XValFilename "Input/x.csv" )
add_test( TopologicalGetErrorPreprocessor      ./${PROJECT_NAME} --Topological --GetError      --InputFilename "Input/input.csv" --Preprocessor )
add_test( SimpleTrain                          ./${PROJECT_NAME} --Simple      --Train         --InputFilename "Input/input.csv" )
add_test( SimpleApply                          ./${PROJECT_NAME} --Simple      --Apply         --InputFilename "Input/input.csv" )
add_test( SimpleCrossValidate                  ./${PROJECT_NAME} --Simple      --CrossValidate --InputFilename "Input/input.csv" --XValFilename "Input/x.csv" )
add_test( SimpleGetError                       ./${PROJECT_NAME} --Simple      --GetError      --InputFilename "Input/input.csv" )
add_test( SimpleTrainArray                     ./${PROJECT_NAME} --Simple      --Train         --InputFilename "Input/input.csv" --Array )
add_test( SimpleApplyArray                     ./${PROJECT_NAME} --Simple      --Apply         --InputFilename "Input/input.csv" --Array )
add_test( SimpleCrossValidateArray             ./${PROJECT_NAME} --Simple      --CrossValidate --InputFilename "Input/input.csv" --Array --XValFilename "Input/x.csv" )
add_test( SimpleGetErrorArray                  ./${PROJECT_NAME} --Simple      --GetError      --InputFilename "Input/input.csv" --Array )
add_test( SimpleTrainMatrix                    ./${PROJECT_NAME} --Simple      --Train         --InputFilename "Input/input.csv" --Matrix )
add_test( SimpleApplyMatrix                    ./${PROJECT_NAME} --Simple      --Apply         --InputFilename "Input/input.csv" --Matrix )
add_test( SimpleCrossValidateMatrix            ./${PROJECT_NAME} --Simple      --CrossValidate --InputFilename "Input/input.csv" --Matrix --XValFilename "Input/x.csv" )
add_test( SimpleGetErrorMatrix                 ./${PROJECT_NAME} --Simple      --GetError      --InputFilename "Input/input.csv" --Matrix )
add_test( SimpleTrainPreprocessor              ./${PROJECT_NAME} --Simple      --Train         --InputFilename "Input/input.csv" --Preprocessor )
add_test( SimpleApplyPreprocessor              ./${PROJECT_NAME} --Simple      --Apply         --InputFilename "Input/input.csv" --Preprocessor )
add_test( SimpleCrossValidatePreprocessor      ./${PROJECT_NAME} --Simple      --CrossValidate --InputFilename "Input/input.csv" --Preprocessor --XValFilename "Input/x.csv" )
add_test( SimpleGetErrorPreprocessor           ./${PROJECT_NAME} --Simple      --GetError      --InputFilename "Input/input.csv" --Preprocessor )
