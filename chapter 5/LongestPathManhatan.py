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
            s[i][j] = max(s[i-1][j]+down[i-1][j], s[i][j-1] + right[i][j-1])

    return s[n][m]

down=[[4,2,1,1,1,3,1,0,1],
[3,2,1,1,4,3,0,0,3],
[2,3,4,1,4,1,4,3,2],
[4,1,3,0,1,4,2,1,4],
[3,0,1,1,2,0,2,1,4]]

right=[[4,0,4,0,2,4,4,0],
[3,0,1,0,3,2,3,4],
[0,0,3,1,2,4,0,3],
[4,2,0,2,3,0,0,4],
[3,3,0,4,2,1,2,0],
[3,0,4,1,2,2,2,2]]

n = 5
m = 8

s = [[0 for i in range(m+1)] for j in range(n+1)]

print ManhattanTourist(n,m,down,right,s)
