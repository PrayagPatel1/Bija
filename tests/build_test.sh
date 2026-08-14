#!/bin/bash

set -xe 

gcc -Wall -Wextra -g -fsanitize=address -o test_runner property_based_tests/vec2df_pbt.c property_based_tests/vec3df_pdt.c property_based_tests/pbt_runner.c -lm 
