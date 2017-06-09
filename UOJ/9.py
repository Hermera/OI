import re

def idx(i):
	return int(re.sub('\D', '', i))
	
n = input()
a = []
for i in range(0, n):
	a.append(raw_input())
b = sorted(a, key = idx)

for i in b: print i



