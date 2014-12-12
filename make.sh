#!/bin/bash
gcc -c librdwr.c
ar rcs librdwr.a librdwr.o
gcc disp.c -o disp
gcc stat_wr.c -L. -lrdwr -o stat_wr
gcc stat_rd.c -L. -lrdwr -o stat_rd
