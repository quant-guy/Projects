#!/bin/bash
# if verbose mode wanted, add '--Verbose' at the end, ie ./run_neural_algorithms.sh --Verbose
PROGRAM_NAME=test_neural_network

./${PROGRAM_NAME} --SupervisedLearning1   -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --SupervisedXVal1       -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --SupervisedApply1      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --SupervisedError1      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --UnsupervisedLearning1 -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --UnsupervisedXVal1     -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --UnsupervisedApply1    -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" $1

./${PROGRAM_NAME} --SupervisedLearning2   -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --SupervisedXVal2       -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --SupervisedApply2      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --SupervisedError2      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --UnsupervisedLearning2 -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --UnsupervisedXVal2     -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --UnsupervisedApply2    -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" $1

./${PROGRAM_NAME} --SupervisedLearning3   -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --SupervisedXVal3       -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --SupervisedApply3      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --SupervisedError3      -I "Data/training_in.csv" -O "Data/training_out.csv" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --UnsupervisedLearning3 -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --UnsupervisedXVal3     -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" $1
./${PROGRAM_NAME} --UnsupervisedApply3    -I "Data/training_in.csv" -C "clusters.dat" -G "Genetics/Binary.txt" -B "brains.dat" $1
