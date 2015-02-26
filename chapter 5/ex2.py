#How many different paths are there from source to sink in a 16 x 12 rectangular grid?

m = 17
n = 13
node = [[0 for i in range(n)] for j in range(m)]

for i in range(n):
    node[m-1][i] = 1
for j in range(m):
    node[j][n-1] = 1

for i in range(m-2,-1,-1):
    for j in range(n-2,-1,-1):
        node[i][j] = node[i+1][j] + node[i][j+1]

print node[0][0]
    
