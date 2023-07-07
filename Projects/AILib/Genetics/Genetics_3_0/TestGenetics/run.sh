#!/bin/bash
PROJECT_NAME=test_genetics
./${PROJECT_NAME} --GP_Constructor1 --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GP_Constructor2 --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GP_GetFirst     --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GP_GetSecond    --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GP_SetFirst     --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GP_SetSecond    --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GP_Swap         --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GG_Constructor1 --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GG_Constructor2 --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GG_Constructor3 --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GG_PutGenetic   --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GG_Mutate1      --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GG_Mutate2      --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GG_Ostream      --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GG_OutputMutate --GeneticFilename Structures/GeneticTemplate.txt $1
./${PROJECT_NAME} --GPA_Constructor1 --GeneticFilename Structures/rnv.dat             $1
./${PROJECT_NAME} --GPA_Constructor2 --GeneticFilename Structures/rnv.dat             $1
./${PROJECT_NAME} --GPA_Constructor3 --GeneticFilename Structures/rnv.dat             $1
./${PROJECT_NAME} --GPA_Constructor4 --GeneticFilename Structures/rnv.dat             $1
./${PROJECT_NAME} --GPA_Constructor5 --GeneticFilename Structures/rnv.dat             $1
./${PROJECT_NAME} --GPA_Assignment   --GeneticFilename Structures/rnv.dat             $1
./${PROJECT_NAME} --GPA_Perturb      --GeneticFilename Structures/rnv.dat             $1
./${PROJECT_NAME} --GPA_Copy         --GeneticFilename Structures/rnv.dat             $1
./${PROJECT_NAME} --GPA_Plus         --GeneticFilename Structures/rnv.dat             $1
