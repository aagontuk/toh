#!/bin/bash

if [ "$1" == "clean" ]; then
	rm -f /usr/bin/toh
else
	gcc -g -o0 -Wall toh.c -o toh -lm
	mv toh /usr/bin/toh
fi
