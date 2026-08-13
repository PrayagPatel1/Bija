#!/bin/bash

set -xe 
gcc -Wall -Wextra property_based_tests/vec2df_pbt.c -o vec2df_pbt_test -lm 