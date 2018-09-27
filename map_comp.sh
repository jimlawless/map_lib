#!/bin/bash
gcc -c map_lib.c
gcc -c map_stuff.c
ld -o map_stuff map_stuff.o map_lib.o /usr/lib/crt1.o -lc
ls -l map_*.*
