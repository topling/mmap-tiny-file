#!/bin/sh
set -e
cc -Wextra -o a.out main.c
./a.out $@
