#!/usr/bin/env bash

mkdir -p bin
mkdir -p log

c++ -Wall -Werror -Wextra vector_test.cpp -o bin/std_vector
c++ -Wall -Werror -Wextra vector -D FT=1 vector_test.cpp -o bin/std_vector

c++ -Wall -Werror -Wextra vector_test.cpp -o bin/std_map
c++ -Wall -Werror -Wextra vector -D FT=1 vector_test.cpp -o bin/std_map

c++ -Wall -Werror -Wextra vector_test.cpp -o bin/std_stack
c++ -Wall -Werror -Wextra vector -D FT=1 vector_test.cpp -o bin/std_stack

c++ -Wall -Werror -Wextra vector_test.cpp -o bin/std_set
c++ -Wall -Werror -Wextra vector -D FT=1 vector_test.cpp -o bin/std_set

rm -f log/*

bin/std_vector >> log/std
bin/std_map >> log/std
bin/std_stack >> log/std
bin/std_set >> log/std

bin/ft_vector >> log/ft
bin/ft_map >> log/ft
bin/ft_stack >> log/ft
bin/ft_set >> log/ft

diff log/std log/ft

