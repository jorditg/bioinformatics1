l1=['C', 'G', 'S', 'H', 'U', 'B']
for i1 in l1:
	l2 = ['C', 'G', 'S', 'H', 'U', 'B']
	l2.remove(i1)
	for i2 in l2:
		l3 = ['C', 'G', 'S', 'H', 'U', 'B']
		l3.remove(i1)
		l3.remove(i2)
		for i3 in l3:
			l4 = ['C', 'G', 'S', 'H', 'U', 'B']
			l4.remove(i1)
			l4.remove(i2)
			l4.remove(i3)
			for i4 in l4:
				l5 = ['C', 'G', 'S', 'H', 'U', 'B']
				l5.remove(i1)
				l5.remove(i2)				
				l5.remove(i3)
				l5.remove(i4)
				for i5 in l5:
					l6 = ['C', 'G', 'S', 'H', 'U', 'B']
					l6.remove(i1)
					l6.remove(i2)
					l6.remove(i3)
					l6.remove(i4)					
					l6.remove(i5)
					for i6 in l6:
						val = i1+i2+i3+i4+i5+i6
						if val.index('U') > val.index('S') and val.index('B') > val.index('S') and val.index('H') > val.index('C'):
							print val
						