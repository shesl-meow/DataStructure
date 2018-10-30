#!/bin/sh

echo "Compile the c++ program."
echo "-----------------------------------------------"
make
echo "-----------------------------------------------"

echo "\n\nTest double coefficient for five times:"
echo "" > data/double_input.txt
echo "" > data/double_output.txt
for i in 1 2 3 4 5;
do
	echo "-----------------------------------------------"
	./main `python gnrdouble.py | tee -a data/double_input.txt` | tee -a data/double_output.txt
	echo "" >> data/double_output.txt
	echo "-----------------------------------------------"
done

echo "\n\nTest int coefficient for five times:"
echo "" > data/int_input.txt
echo "" > data/int_output.txt
for i in 1 2 3 4 5;
do
	echo "-----------------------------------------------"
	./main `python gnrint.py | tee -a data/int_input.txt` | tee -a data/int_output.txt
	echo "" >> data/int_output.txt
	echo "-----------------------------------------------"
done
typora data/int_output.txt &
