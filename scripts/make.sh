#!/bin/zsh

mkdir build

cd build

cmake ..

make

cp SyntaxTreeGen ..

cd ..

./SyntaxTreeGen
