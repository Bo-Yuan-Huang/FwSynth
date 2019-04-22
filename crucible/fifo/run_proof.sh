#!/usr/bin/bash

F () {
  echo "Prove PKT_NUM = $1"
  echo "#define PKT_NUM $1" > pkt_num.h
  clang -c -emit-llvm -o miter.bc miter.c
  python3 genscript.py $1 prove_$1.saw
  saw prove_$1.saw
}

F 8
F 16
F 32
F 64
F 128
F 256
F 512
