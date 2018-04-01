#!/bin/bash
while true; do
	./gen.py > in.txt
	./2DSegTree < in.txt > o1.txt
	./Brute2D < in.txt > o2.txt
	diff o1.txt o2.txt
	if [ $? -ne 0 ]; then
		echo "WA"
		exit
	fi
	echo "AC"
done
