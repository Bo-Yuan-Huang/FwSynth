#!/usr/bin/bash

OBJ=obj

clang -c -emit-llvm -o $OBJ/ref.bc src/lmac_reference.c
clang -c -emit-llvm -o $OBJ/tem.bc src/lmac_template.c

saw scripts/prove.saw
