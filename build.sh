#!/bin/bash
ARGS="$1"
ROOTDIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
BUILDDIR=$ROOTDIR/build/
NUMCPUS=$(cat /proc/cpuinfo | grep processor | wc -l)

mkdir -p $BUILDDIR
cd $BUILDDIR

cmake -DCMAKE_BUILD_TYPE=release $ROOTDIR
make -j$NUMCPUS

test "$ARGS" = "install" && make install
cd "$ROOTDIR"
