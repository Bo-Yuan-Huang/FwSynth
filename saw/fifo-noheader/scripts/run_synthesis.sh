#!/usr/bin/bash

CORE=archive
SAW=scripts
TMP=tmp 
TARGET=$TMP/tmp_synth.saw

F () {
  let SIZE=$1*4
  let SYM=$1-2
  echo "Synthesizing w/ PKT_SIZE = $SIZE"
  echo "pkt_arr <- fresh_symbolic \"pkt_arr\" {| [$SYM][32] |};" > $TARGET
  echo "syn_arr <- fresh_symbolic \"syn_arr\" {| [32] |};" >> $TARGET
  echo "" >> $TARGET
  echo "reference_term <- read_core \"$CORE/ref_$SIZE.core\";" >> $TARGET
  echo "template_term <- read_core \"$CORE/syn_$SIZE.core\";" >> $TARGET
  more $SAW/synthesis_post.saw >> $TARGET
  saw $TARGET
}

F 16
F 32
F 64
F 128
F 256
F 512
