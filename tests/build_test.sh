#!/bin/bash

# ==== Script Description ====
# Builds Bija's property based test runner. 

# Log Output Specific SHELL Variables
ERROR_COL='\033[0;31m'
PASS_COL='\033[0;32m'
RESET='\033[0;0m'

# Compiler Specific SHELL Variables
CC="gcc"
FLAGS="-fsanitize=address,undefined -g -Wall -Wextra"

# Directory / Output Executable Specific SHELL Variables
TARGET_DIR="tests/property_based_tests"
OUTPUT_EXE="pbt_runner"

cd ./tests/property_based_tests

if compgen -G "*.c" > /dev/null; then
    echo -e "${PASS_COL}[INFO]${RESET} Found .c files. Compilling..."

    ${CC} ${FLAGS} *.c -o ${OUTPUT_EXE} -lm

    if [ $? -eq 0 ] ; then
        echo -e "${PASS_COL}[INFO]${RESET} Complete Compilation: $TARGET_DIR/$OUTPUT_EXE."
    else
        echo -e "${ERROR_COL}[ERROR]${RESET} Incomplete Compilation."
    fi
else
    echo -e "${ERROR_COL}[ERROR]${RESET} No .c files were found in $TARGET_DIR."
fi
 
