# -*- coding: utf-8 -*-
"""
Created on Wed Dec 11 11:39:47 2013

@author: jordi
"""


def ManhattanTourist(n,m,down,right,s):
    s[0][0] = 0
    for i in range(1,n+1):
        s[i][0] = s[i-1][0] + down[i-1][0]
    for j in range(1,m+1):
        s[0][j] = s[0][j-1] + right[0][j-1]
    for i in range(1,n+1):
        for j in range(1,m+1):
            s[i][j] = max(s[i-1][j]+down[i-1][j], s[i][j-1] + right[i][j-1], s[i-1][j-1]+diag[i-1][j-1])

    return s[n][m]

down=[[1,0,2,4,3],
[4,6,5,2,1],
[4,4,5,2,1],
[5,6,8,5,3]]

right=[[3,2,4,0],
[3,2,4,2],
[0,7,3,3],
[3,3,0,2],
[1,3,2,2]]

diag=[[5,0,2,1],
[8,4,3,0],
[10,8,9,5],
[5,6,4,7]]

n = 4
m = 4

s = [[0 for i in range(m+1)] for j in range(n+1)]

print ManhattanTourist(n,m,down,right,s)
