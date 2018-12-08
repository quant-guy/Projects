#!/bin/bash
PROJECT_NAME=test_metrics
./${PROJECT_NAME} --Dataset Data/data.csv --Euclidean   $1
./${PROJECT_NAME} --Dataset Data/data.csv --Manhattan   $1
./${PROJECT_NAME} --Dataset Data/data.csv --EuclideanN  $1
./${PROJECT_NAME} --Dataset Data/data.csv --ManhattanN  $1
./${PROJECT_NAME} --Dataset Data/data.csv --EuclideanV  $1
./${PROJECT_NAME} --Dataset Data/data.csv --ManhattanV  $1
./${PROJECT_NAME} --Dataset Data/data.csv --EuclideanVN $1
./${PROJECT_NAME} --Dataset Data/data.csv --ManhattanVN $1
./${PROJECT_NAME} --Dataset Data/data.csv --GetNorm     $1
./${PROJECT_NAME} --Dataset Data/data.csv --ManhattanC  $1
./${PROJECT_NAME} --Dataset Data/data.csv --EuclideanC  $1
./${PROJECT_NAME} --Dataset Data/data.csv --NeuralC     $1
./${PROJECT_NAME} --Dataset Data/data.csv --GaussianC   $1
./${PROJECT_NAME} --CompFiles Data/entropy_test1.txt --CompD $1
./${PROJECT_NAME} --CompFiles Data/entropy_test1.txt --CompFiles Data/entropy_test2.txt --NormCompD $1
