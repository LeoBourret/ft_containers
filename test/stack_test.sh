#!/usr/bin/env bash

c++ -Wall -Werror -Wextra -D FT=1 mains/stack_test.cpp
./a.out > log/ft_stack
c++ -Wall -Werror -Wextra -D STD=1 mains/stack_test.cpp
./a.out > log/std_stack

if [ $# -gt 0 ]
then
	if [ $1 != "-m" ]
	then
		cat log/ft_stack
	fi
else
	cat log/ft_stack
fi


if  diff log/ft_stack log/std_stack
then
	printf "stack:\t✅\n"
else
	printf "stack:\t❌\n"
fi

