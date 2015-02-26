#!/usr/bin/python

def func(c, N):
	out = [c]
	for pos in range(N):
		#primero por delante
		if pos > 0:
			for i in range(0,pos):
				temp = out
				out = [] 
				for t in temp:
					if t[:1] == '0':
						s1 = '1' + t
						s2 = '0' + t
						out.append(s1)
						out.append(s2)
					elif t[:1] == '1':
						s = '1' + t
						out.append(s)

		#despues por detras
		if pos < N-1:
			for i in range(pos,N-1):
				temp = out
				out = [] 
				for t in temp:
					if t[-1:] == '1':
						s1 = t + '1'
						s2 = t + '0'
						out.append(s1)
						out.append(s2)
					elif t[-1:] == '0':
						s = t + '0'
						out.append(s)

		for o in out:
			print o
		out = [c]

if __name__ == "__main__":
	func('0', 25)
	func('1', 25)