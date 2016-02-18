#!/bin/bash

echo -e "\t\tStarting Tournament\n\n" > championship_result

i=0
n=0
t=0

champ=*.s
for f in $champ
do
	echo -en "Testing $f:"
	echo "Testing $f" >> championship_result
	./comp.sh "${f%.*}" &> /dev/null
	res=$?
	if [ $res -eq 0 ] ; then
		echo "ok"
		echo -e "\tfile are identical!" >> championship_result
		i=$(( i + 1 ))
	else
		echo "failed"
		echo -e "\tfile mismatched..." >> championship_result
		if [ -f dump ] ; then
			diff dump dump42 >> championship_result
		else
			echo -e "\t./asm no outpout"
			n=$(( n + 1 ))
		fi
	fi
	t=$((t + 1 ))
done

rm *.cor

echo "$i / $t" >> championship_result
echo "$i / $t"
echo "no output on $n" >> championship_result
echo "no output on $n"

echo "End of Tournament!!!" >> championship_result
