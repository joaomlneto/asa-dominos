#!/bin/bash

for file_in in tests/*.in
do
	file_out=${file_in//.in/.out}
	file_expected=${file_in//.in/.expected}
	file_diff=${file_in//.in/.diff}

	testname=${file_in//.in/}
	testname=${testname//test/}

	echo -e "\nRunning test $testname... "
	time ./dominos < $file_in > $file_out

	if diff $file_out $file_expected > $file_diff; then
		echo "Success!"
		rm $file_diff
		rm $file_out
	else
		echo "XXX FAILED XXX"
		mv $file_diff .
		mv $file_out .
	fi

done

