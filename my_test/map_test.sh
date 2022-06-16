#!/usr/bin/env bash

c++ -Wall -Werror -Wextra -D FT=1 mains/map_test.cpp
./a.out > log/ft_map
c++ -Wall -Werror -Wextra -D STD=1 mains/map_test.cpp
./a.out > log/std_map

if [ $# -gt 0 ]
then
	if [ $1 == "-v" ]
	then
	cat log/ft_map
	fi
fi

if  diff log/ft_map log/std_map
then
	printf "map:\t✅\n"
else
	printf "map:\t❌\n"
fi
