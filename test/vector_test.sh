#!/usr/bin/env bash

c++ -Wall -Werror -Wextra -D FT=1 mains/vector_test.cpp
./a.out > log/ft_vector
c++ -Wall -Werror -Wextra -D STD=1 mains/vector_test.cpp
./a.out > log/std_vector

if [ $# -gt 0 ]
	then
	if [ $1 != "-m" ]
	then
		cat log/ft_vector
	fi
else
	cat log/ft_vector
fi


if  diff log/ft_vector log/std_vector
then
	printf "vector: ✅\n"
else
	printf "vector: ❌\n"
fi

