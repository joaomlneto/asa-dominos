#!/bin/bash

testpattern="testXXX"
outfile="results.txt"
outfile_tmp="results.txt.tmp"
exec="~/dominos/dominos"

rm $outfile

i=100
while [ $i -le 100000 ]
do

	testname=${testpattern//XXX/$i}
	echo $testname

	# generate the test
	./testgen $i > $testname
	# run the tests
	j=0
	while [ $j -lt 1 ]
	do
		#/usr/bin/time -ao $outfile ~/dominos/dominos < $testname
		/usr/bin/time -a -o $outfile -p ~/dominos/dominos < $testname > /dev/null
		head -n -2 $outfile > $outfile_tmp
		mv $outfile_tmp $outfile

		j=$(($j+1));
	done
	rm $testname

	i=$(($i+100))

done

cat $outfile | sed 's/^.....//' > $outfile_tmp
mv $outfile_tmp $outfile

