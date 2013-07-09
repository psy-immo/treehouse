#!/bin/sh
BINDIR=$(dirname $0)/bin
CXT=${1%.cxt}
echo $CXT | $BINDIR/ferrers > "$CXT-ferrers.txt"
echo ${CXT}chains | $BINDIR/intentcover > "$CXT-intentcover.txt"
$BINDIR/makechain
