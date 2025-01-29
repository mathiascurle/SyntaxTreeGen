#!/bin/bash

cd out

cmake ..

make

rm -r ~/Applications/SyntaxTreeGen.app

mkdir -p ~/Applications/SyntaxTreeGen.app/Contents/MacOS/

cp SyntaxTreeGen ~/Applications/SyntaxTreeGen.app/Contents/MacOS/SyntaxTreeGen

chmod +x ~/Applications/SyntaxTreeGen.app/Contents/MacOS/SyntaxTreeGen
