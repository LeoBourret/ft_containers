#!/usr/bin/env bash

c++ -Wall -Werror -Wextra -D FT=1 mains/set_test.cpp
./a.out > log/ft_set
c++ -Wall -Werror -Wextra -D STD=1 mains/set_test.cpp
./a.out > log/std_set

if [ $# -gt 0 ]
then
	if [ $1 == "-v" ]
	then
	cat log/ft_set
	fi
fi

if  diff log/ft_set log/std_set
then
	printf "set:\t✅\n"
else
	printf "set:\t❌\n"
fi

