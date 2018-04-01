#!/usr/bin/env python
from random import randint

n = 500
print(n)
for i in range(n):
	for j in range(n):
		print(randint(1, 500))
q = 5000
print(q)
for i in range(q):
	type = randint(0, 1)
	if type == 0:
		x1 = randint(1, n)
		x2 = x1 + randint(0, n-x1)
		y1 = randint(1, n)
		y2 = y1 + randint(0, n-y1)
		print("q", x1, y1, x2, y2)
	else:
		x = randint(1, n)
		y = randint(1, n)
		print("c", x, y, randint(1, 500))
