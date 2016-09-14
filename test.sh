#!/bin/sh

./corewar -dump $1 Arena/_.cor > out1
./42cor -d $1 Arena/_.cor > out2

diff out1 out2
