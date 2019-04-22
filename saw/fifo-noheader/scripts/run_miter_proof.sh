#!/usr/bin/bash

SRC=src
OBJ=obj
SAW=scripts
TMP=tmp

F () {
  echo "Prove PKT_NUM = $1"
  echo "#define PKT_NUM $1" > $SRC/verif_config.h
  clang -c -emit-llvm -o $OBJ/miter.bc $SRC/miter.c

  more $SAW/check_miter.saw > $TMP/tmp_verif.saw
  echo "Check {{ $1 : [PKT_WID] }};" >> $TMP/tmp_verif.saw
  saw $TMP/tmp_verif.saw
}

F 16
F 32
F 64
F 128
F 256
F 512
