#!/bin/sh
BINDIR=$(dirname $0)/bin
CXT=${1%.cxt}
echo $CXT | $BINDIR/ferrers > "$CXT-ferrers.txt"
echo ${CXT}chains | $BINDIR/intentcover > "$CXT-intentcover.txt"
rm "$CXT-chains.txt"
for nbr in `cat "$CXT-intentcover.txt" | grep \#CHAIN | sed 's/.CHAIN.//'`;
do
  cnbr=$(cat "$CXT-ferrers.txt" | head -n $(($nbr+3)) | tail -n 1 | sed 's/^.*MAKECHAIN *//')
  echo "" >> "$CXT-chains.txt"
  echo "Ferrers chain $nbr a.k.a. maximal chain $cnbr" >> "$CXT-chains.txt"
  echo "${CXT}\n${cnbr}\n" | $BINDIR/makechain >> "$CXT-chains.txt"
  mv Ferrers.cxt "$CXT-ferrers-$nbr.cxt"
done

