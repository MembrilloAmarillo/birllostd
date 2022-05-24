#!/bin/bash

gcc -o test.out test/main.c -Wall -Wextra -pedantic
gcc -o wm_test.out test/without_mira.c -Wall -Wextra -pedantic

@echo "=================================== WITH BRILLOSTD ==================================="  
valgrind --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes -s ./test.out
@echo "=================================== WITHOUT BRILLOSTD ===================================" 
valgrind --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes -s ./wm_test.out
