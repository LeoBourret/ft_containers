#!/usr/bin/env bash
if [ $# -gt 0 ] && [ $1 == "-v" ]
then
	./vector_test.sh
	./stack_test.sh
	./map_test.sh
	./set_test.sh
else
	./vector_test.sh -m
	./stack_test.sh -m
	./map_test.sh -m
	./set_test.sh -m
fi
