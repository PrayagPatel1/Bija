#!/bin/bash

set -xe 

gcc -Wall -Wextra -g -fsanitize=address property_based_tests/vec2df_pbt.c -o test_runner -lm 
