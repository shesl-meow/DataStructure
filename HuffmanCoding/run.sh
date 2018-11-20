#!/bin/bash

make

python interact.py "`cat ./data/tree_build.txt`" "`cat ./data/text_for_decode.txt`" > ./data/summary_result.txt


awk -f ./split.awk ./data/summary_result.txt
rm ./data/0.txt
rm ./data/summary_result.txt

for f in $(seq 1 3); do
	# remove duplicate lines in the output file.
	awk 'NF > 0' ./data/${f}.txt > tmp.txt
	mv tmp.txt ./data/${f}.txt
done

mv ./data/1.txt ./data/tree_view.txt
echo "Tree View:"
cat ./data/tree_view.txt

mv ./data/2.txt ./data/table_view.txt
echo "Table View:"
cat ./data/table_view.txt

mv ./data/3.txt ./data/decode_result.txt
echo "Decode Result:"
cat ./data/decode_result.txt

