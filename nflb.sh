#!/bin/env bash

# Wrapper for leaving no files behind

DIR=$(dirname "$(readlink -f "$0")")
LIB=${DIR}/nflb.so

if [ ! -x $LIB ]; then
    echo $0: Check $LIB
    exit 1
fi

export NFLB_FILE=$(mktemp)
OLD_LD_PRELOAD=$LD_PRELOAD
export LD_PRELOAD=$LIB:$LD_PRELOAD
"$@"
export LD_PRELOAD=$OLD_LD_PRELOAD

for f in $(cat $NFLB_FILE)
do
    echo Cleaning up $f
    rm -f $f
done

rm -f $NFLB_FILE

# EOF
