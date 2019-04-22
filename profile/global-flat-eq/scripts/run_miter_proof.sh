#!/usr/bin/bash

F () {
  echo "Prove PKT_NUM = $1"
  echo "#define PKT_NUM $1" > src/verif_config.h
  clang -c -emit-llvm -o miter.bc src/miter.c

  more scripts/check.saw > tmp_verif.saw
  echo "Check {{ $1 : [PKT_WID] }};" >> tmp_verif.saw
  saw tmp_verif.saw
}

F 16
F 32
F 64
F 128
F 256
F 512
