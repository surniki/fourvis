#!/usr/bin/env bash

NAME="fourvis"

if [[ $1 == debug ]]; then
    BUILDTYPE="-g" # for debugging
else
    BUILDTYPE="-O2" # for release
fi
    
CFLAGS="-std=c89 -Wall $BUILDTYPE -g"
SRC="f_main.c f_image.c f_physics.c"
LFLAGS="-lm"

gcc $CFLAGS -o $NAME $SRC $LFLAGS

if [[ $1 == run && $? ]]; then
    ./$NAME
fi
