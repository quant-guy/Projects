#!/bin/bash
PROJECT_NAME=test_activation_functions
rm Results/Logistic_a.csv
./${PROJECT_NAME} --Logistic3          --OutputFilename Results/Logistic_a.csv
rm Results/Logistic_d.csv
./${PROJECT_NAME} --Logistic4          --OutputFilename Results/Logistic_d.csv
rm Results/InverseTangent_a.csv
./${PROJECT_NAME} --InverseTangent3    --OutputFilename Results/InverseTangent_a.csv
rm Results/InverseTangent_d.csv
./${PROJECT_NAME} --InverseTangent4    --OutputFilename Results/InverseTangent_d.csv
rm Results/HyperbolicTangent_a.csv
./${PROJECT_NAME} --HyperbolicTangent3 --OutputFilename Results/HyperbolicTangent_a.csv
rm Results/HyperbolicTangent_d.csv
./${PROJECT_NAME} --HyperbolicTangent4 --OutputFilename Results/HyperbolicTangent_d.csv
rm Results/Algebraic_a.csv
./${PROJECT_NAME} --Algebraic3         --OutputFilename Results/Algebraic_a.csv
rm Results/Algebraic_d.csv
./${PROJECT_NAME} --Algebraic4         --OutputFilename Results/Algebraic_d.csv
rm Results/Erf_a.csv
./${PROJECT_NAME} --Erf3               --OutputFilename Results/Erf_a.csv
rm Results/Erf_d.csv
./${PROJECT_NAME} --Erf4               --OutputFilename Results/Erf_d.csv
rm Results/Gompertz_a.csv
./${PROJECT_NAME} --Gompertz3          --OutputFilename Results/Gompertz_a.csv
rm Results/Gompertz_d.csv
./${PROJECT_NAME} --Gompertz4          --OutputFilename Results/Gompertz_d.csv
rm Results/Control_a.csv
./${PROJECT_NAME} --Control3           --OutputFilename Results/Control_a.csv
rm Results/Control_d.csv
./${PROJECT_NAME} --Control4           --OutputFilename Results/Control_d.csv
