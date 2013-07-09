#!/bin/sh
cd $(dirname $0)
cd bin
cp ../src/*.pas ./
for i in *.pas;
do
  fpc $i
done
rm *.pas
rm *.o
rm *.ppu
cd ..
