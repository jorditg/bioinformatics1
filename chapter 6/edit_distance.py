# -*- coding: utf-8 -*-
"""
Created on Wed Dec 11 11:39:47 2013

@author: jordi
"""
#import sys 

def LCS(v,w):
    sigma = 1
    
    m =len(v)
    n = len(w)
    
    s = [[0 for i in range(n+1)] for j in range(m+1)]
    backtrack = [['' for i in range(n+1)] for j in range(m+1)]
   
    for i in range(m+1):
        s[i][0] = 0 - sigma*i
        backtrack[i][0] = 'D'
    for j in range(n+1):
		s[0][j] = 0 - sigma*j
		backtrack[0][j] = 'R'
    
    for i in range(1,m+1):
        for j in range(1,n+1):
            right = s[i][j-1]-sigma
            down = s[i-1][j]-sigma
            if v[i-1] == w[j-1]:
                score = 0
            else:
                score = -1
            diagonal = s[i-1][j-1]+score

            maximum = max(right,down,diagonal)
                
            if maximum == down:
                # D equals down                
                backtrack[i][j] = 'D'
            elif maximum == right:
                # R equals right
                backtrack[i][j] = 'R'
            else:
                # A equals diagonal                
                backtrack[i][j] = 'A'
            
            s[i][j] = maximum

            #print backtrack[i][j],
        #print
    return s[m][n], backtrack


def OutputLCS(backtrack, v, i, j):
    if i == 0 or j == 0:
        return
    if backtrack[i][j] == 'D': # backtrack == down
        OutputLCS(backtrack,v,i-1,j)
    elif backtrack[i][j] == 'R': # backtrack == right
        OutputLCS(backtrack,v,i,j-1)
    else:
        OutputLCS(backtrack,v,i-1,j-1)        
        #print v[i-1],

def output_strs(v,w,backtrack):
    m =len(v)
    n = len(w) 
    i=m
    j=n
    str1=""
    str2=""
    while(i>0 or j>0):
        if backtrack[i][j] == 'A':
            str1 = str1 + v[i-1]
            str2 = str2 + w[j-1]
            i = i - 1
            j = j - 1
        elif backtrack[i][j] == 'R':
            str1 = str1 + '-'
            str2 = str2 + w[j-1]
            j = j - 1
        elif backtrack[i][j] == 'D':
            str1 = str1 + v[i-1]
            str2 = str2 + '-'
            i = i - 1
            
    str1 = str1[::-1]
    str2 = str2[::-1]
    
    print str1
    print str2

#sys.setrecursionlimit(2000)

f = "GTAGGCTTAAGGTTA"
t = "TAGATA"

l, backtrack = LCS(f,t)
print l
#OutputLCS(backtrack, v, len(v), len(w))
output_strs(f,t,backtrack)


