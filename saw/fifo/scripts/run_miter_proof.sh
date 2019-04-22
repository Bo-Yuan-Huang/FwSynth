#!/usr/bin/bash

OBJ=obj
TARGET=tmp/tmp_verif.saw

F () {
  echo "Prove PKT_NUM = $1"
  echo "#define PKT_NUM $1" > src/verif_config.h
  clang -c -emit-llvm -o $OBJ/miter.bc src/miter.c

  more scripts/check.saw > $TARGET
  echo "Check {{ $1 : [PKT_WID] }};" >> $TARGET
  saw $TARGET
}

F 16
F 32
F 64
F 128
F 256
F 512
