#!/bin/sh

echo "Compile the c++ program."
echo "-----------------------------------------------"
make
echo "-----------------------------------------------"

echo -e "\n\nTest double coefficient for five times:"
for i in {1..5}; do
    echo "-----------------------------------------------"
    ./main.exe `python gnrdouble.py`
    echo "-----------------------------------------------"
done

echo -e "\n\nTest integer coefficient for five times:"
for i in {1..5}; do
    echo "-----------------------------------------------"
    ./main.exe `python gnrint.py`
    echo "-----------------------------------------------"
done

