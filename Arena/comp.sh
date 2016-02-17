#!/bin/bash
file="test"
if [ $# -eq 1 ] ; then
	file=$1
fi

if [ -f dump ] ; then
	rm dump
fi
if [ -f dump42 ] ; then
	rm dump42
fi

echo "./asm $file.s   && hex $file.cor > dump"
./asm "$file.s" &> /dev/null && hexdump -C "$file.cor" > dump

if [ $? -eq 0 ] ; then
	touch dump
fi
if [ -f "$file.cor" ] ; then
	rm "$file.cor"
fi

echo "./42asm $file.s && hex $file.cor > dump42"
./42asm "$file.s" &> /dev/null && hexdump -C "$file.cor" > dump42

if [ $? -eq 0 ] ; then
	touch dump42
fi
echo "diff dump dump42"
diff -s dump dump42
