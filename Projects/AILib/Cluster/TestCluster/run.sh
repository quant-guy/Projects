#!/bin/bash
PROJECT_NAME=test_cluster

./${PROJECT_NAME} --KMeans      --Train         --InputFilename "Input/input.csv"
./${PROJECT_NAME} --KMeans      --Apply         --InputFilename "Input/input.csv"
./${PROJECT_NAME} --KMeans      --CrossValidate --InputFilename "Input/input.csv" --XValFilename "Input/x.csv"
./${PROJECT_NAME} --KMeans      --GetError      --InputFilename "Input/input.csv" 
   
./${PROJECT_NAME} --KMeans      --Train         --InputFilename "Input/input.csv" --Array
./${PROJECT_NAME} --KMeans      --Apply         --InputFilename "Input/input.csv" --Array
./${PROJECT_NAME} --KMeans      --CrossValidate --InputFilename "Input/input.csv" --Array --XValFilename "Input/x.csv"
./${PROJECT_NAME} --KMeans      --GetError      --InputFilename "Input/input.csv" --Array
   
./${PROJECT_NAME} --KMeans      --Train         --InputFilename "Input/input.csv" --Matrix
./${PROJECT_NAME} --KMeans      --Apply         --InputFilename "Input/input.csv" --Matrix
./${PROJECT_NAME} --KMeans      --CrossValidate --InputFilename "Input/input.csv" --Matrix --XValFilename "Input/x.csv"
./${PROJECT_NAME} --KMeans      --GetError      --InputFilename "Input/input.csv" --Matrix
   
./${PROJECT_NAME} --KMeans      --Train         --InputFilename "Input/input.csv" --Preprocessor
./${PROJECT_NAME} --KMeans      --Apply         --InputFilename "Input/input.csv" --Preprocessor
./${PROJECT_NAME} --KMeans      --CrossValidate --InputFilename "Input/input.csv" --Preprocessor --XValFilename "Input/x.csv"
./${PROJECT_NAME} --KMeans      --GetError      --InputFilename "Input/input.csv" --Preprocessor
   
./${PROJECT_NAME} --SOM         --Train         --InputFilename "Input/input.csv"
./${PROJECT_NAME} --SOM         --Apply         --InputFilename "Input/input.csv"
./${PROJECT_NAME} --SOM         --CrossValidate --InputFilename "Input/input.csv"  --XValFilename "Input/x.csv"
./${PROJECT_NAME} --SOM         --GetError      --InputFilename "Input/input.csv" 
   
./${PROJECT_NAME} --SOM         --Train         --InputFilename "Input/input.csv" --Array
./${PROJECT_NAME} --SOM         --Apply         --InputFilename "Input/input.csv" --Array
./${PROJECT_NAME} --SOM         --CrossValidate --InputFilename "Input/input.csv" --Array --XValFilename "Input/x.csv"
./${PROJECT_NAME} --SOM         --GetError      --InputFilename "Input/input.csv" --Array
                               
./${PROJECT_NAME} --SOM         --Train         --InputFilename "Input/input.csv" --Matrix
./${PROJECT_NAME} --SOM         --Apply         --InputFilename "Input/input.csv" --Matrix
./${PROJECT_NAME} --SOM         --CrossValidate --InputFilename "Input/input.csv" --Matrix --XValFilename "Input/x.csv"
./${PROJECT_NAME} --SOM         --GetError      --InputFilename "Input/input.csv" --Matrix
                               
./${PROJECT_NAME} --SOM         --Train         --InputFilename "Input/input.csv" --Preprocessor
./${PROJECT_NAME} --SOM         --Apply         --InputFilename "Input/input.csv" --Preprocessor
./${PROJECT_NAME} --SOM         --CrossValidate --InputFilename "Input/input.csv" --Preprocessor --XValFilename "Input/x.csv"
./${PROJECT_NAME} --SOM         --GetError      --InputFilename "Input/input.csv" --Preprocessor
   
./${PROJECT_NAME} --Topological --Train         --InputFilename "Input/input.csv"
./${PROJECT_NAME} --Topological --Apply         --InputFilename "Input/input.csv"
./${PROJECT_NAME} --Topological --CrossValidate --InputFilename "Input/input.csv"  --XValFilename "Input/x.csv"
./${PROJECT_NAME} --Topological --GetError      --InputFilename "Input/input.csv" 
   
./${PROJECT_NAME} --Topological --Train         --InputFilename "Input/input.csv" --Array
./${PROJECT_NAME} --Topological --Apply         --InputFilename "Input/input.csv" --Array
./${PROJECT_NAME} --Topological --CrossValidate --InputFilename "Input/input.csv" --Array --XValFilename "Input/x.csv"
./${PROJECT_NAME} --Topological --GetError      --InputFilename "Input/input.csv" --Array
   
./${PROJECT_NAME} --Topological --Train         --InputFilename "Input/input.csv" --Matrix
./${PROJECT_NAME} --Topological --Apply         --InputFilename "Input/input.csv" --Matrix
./${PROJECT_NAME} --Topological --CrossValidate --InputFilename "Input/input.csv" --Matrix --XValFilename "Input/x.csv"
./${PROJECT_NAME} --Topological --GetError      --InputFilename "Input/input.csv" --Matrix
   
./${PROJECT_NAME} --Topological --Train         --InputFilename "Input/input.csv" --Preprocessor
./${PROJECT_NAME} --Topological --Apply         --InputFilename "Input/input.csv" --Preprocessor
./${PROJECT_NAME} --Topological --CrossValidate --InputFilename "Input/input.csv" --Preprocessor --XValFilename "Input/x.csv"
./${PROJECT_NAME} --Topological --GetError      --InputFilename "Input/input.csv" --Preprocessor
   
./${PROJECT_NAME} --Simple      --Train         --InputFilename "Input/input.csv"
./${PROJECT_NAME} --Simple      --Apply         --InputFilename "Input/input.csv"
./${PROJECT_NAME} --Simple      --CrossValidate --InputFilename "Input/input.csv"  --XValFilename "Input/x.csv"
./${PROJECT_NAME} --Simple      --GetError      --InputFilename "Input/input.csv" 
   
./${PROJECT_NAME} --Simple      --Train         --InputFilename "Input/input.csv" --Array
./${PROJECT_NAME} --Simple      --Apply         --InputFilename "Input/input.csv" --Array
./${PROJECT_NAME} --Simple      --CrossValidate --InputFilename "Input/input.csv" --Array --XValFilename "Input/x.csv"
./${PROJECT_NAME} --Simple      --GetError      --InputFilename "Input/input.csv" --Array
   
./${PROJECT_NAME} --Simple      --Train         --InputFilename "Input/input.csv" --Matrix
./${PROJECT_NAME} --Simple      --Apply         --InputFilename "Input/input.csv" --Matrix
./${PROJECT_NAME} --Simple      --CrossValidate --InputFilename "Input/input.csv" --Matrix --XValFilename "Input/x.csv"
./${PROJECT_NAME} --Simple      --GetError      --InputFilename "Input/input.csv" --Matrix
   
./${PROJECT_NAME} --Simple      --Train         --InputFilename "Input/input.csv" --Preprocessor
./${PROJECT_NAME} --Simple      --Apply         --InputFilename "Input/input.csv" --Preprocessor
./${PROJECT_NAME} --Simple      --CrossValidate --InputFilename "Input/input.csv" --Preprocessor --XValFilename "Input/x.csv"
./${PROJECT_NAME} --Simple      --GetError      --InputFilename "Input/input.csv" --Preprocessor
