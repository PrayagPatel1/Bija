#!/bin/bash

# ==== Script Description ====
# A master build script where the user supplies the argument and the script runs
# that part of the project.

# ==== OPTIONS / ARGUMENTS TYPES ==== 
# [help]
# [test]

# ANSI Escape Codes for Colored Log Output
ERROR_COL='\033[0;31m'
PASS_COL='\033[0;32m'
RESET='\033[0;0m'

ACTION=$1

if [[ "$ACTION" == "--help" ]]; then
   cat << EOF
   Usage: ./build.sh [OPTION] [ARGUMENT]

   Builds property based tests for Bija core types: Vec2D_f, Vec3D_f, Vec4D_f, Mat2_f, Mat3_f.

   OPTIONS:
        --help      Display this help section and exits.
   
   ARGUMENT:
        test        Runs the test build script to get a test_runner executable.
EOF
    exit 0

elif [[ "$ACTION" == "test" ]]; then
    echo -e "${PASS_COL}[INFO]${RESET} Building the test runner. You can find the runner in tests/."
    chmod +x ./tests/build_test.sh
    ./tests/build_test.sh

else
    echo -e "${ERROR_COL}[ERROR]${RESET}Argument: $ACTION is not supported. Run <./build.sh --help> to see all options avaliable."
    exit 1
fi 
