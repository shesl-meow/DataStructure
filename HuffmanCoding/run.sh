#!/bin/bash

make

python interact.py "`cat ./data/tree_build.txt`" "`cat ./data/text_for_decode.txt`" > ./data/summary_result.txt


awk -f ./split.awk ./data/summary_result.txt
rm ./data/0.txt
rm ./data/summary_result.txt
mv ./data/1.txt ./data/tree_view.txt
mv ./data/2.txt ./data/table_view.txt
mv ./data/3.txt ./data/decode_result.txt
