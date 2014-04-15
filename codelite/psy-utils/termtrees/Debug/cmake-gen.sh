#!/bin/sh

cd $(dirname $0)
cmake -DCMAKE_BUILD_TYPE=Debug ..
