#!/bin/bash

ROOT_ID="0"

if [ $UID != $ROOT_ID ]; then
	echo "You must be root!"
	exit 1
else
	if [ "$1" == "clean" ]; then
		rm -f /usr/local/bin/toh
	else
		gcc -g -o0 -Wall toh.c -o /usr/local/bin/toh -lm
	fi
fi
