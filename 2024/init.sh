#!/bin/sh

nn="$(printf '%02d' $1)"
mkdir -p $nn
sed "s/DAY/$nn/g" template.make > $nn/Makefile
cp template.cpp $nn/day${nn}a.cpp
cp template.cpp $nn/day${nn}b.cpp
