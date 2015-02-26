import sys

window = 100
i=0
min = 9999999999
for line in sys.stdin:    
	val = int(line)
	if val < min:
		min = val
	i = i + 1
	if i == window:
		print min
		i = 0
		min = 9999999999
