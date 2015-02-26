# -*- coding: utf-8 -*-
"""
Created on Wed Dec 11 11:39:47 2013

@author: jordi
"""
#import sys 

def get_score(f, t):
    if f == t:
        return 1
    else:
        return -1

def LCS(v,w):
    sigma = 1
    
    m =len(v)
    n = len(w)
    
    s = [[0 for i in range(n+1)] for j in range(m+1)]
    backtrack = [['' for i in range(n+1)] for j in range(m+1)]
    
    for i in range(m+1):
        s[i][0] = 0     # zero initialization, because we are looking for a tail
        backtrack[i][0] = 'D'
    for j in range(n+1):
        s[0][j] = 0 - sigma*j   # we penalize going out from head
        backtrack[0][j] = 'R'
    
    for i in range(1,m+1):
        for j in range(1,n+1):
            right = s[i][j-1]-sigma
            down = s[i-1][j]-sigma
            diagonal = s[i-1][j-1]+get_score(v[i-1],w[j-1])

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
    # we get the maximum of the last row (we are truncating with an edge from every point of the final of v to final edge    
    maximum = -1000000
    for j in range(1,n+1):
        if s[m][j] > maximum:
            maximum = s[m][j]
            jmax = j
    
    return s[m][jmax], backtrack, jmax


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

v = ""
w = ""

l, backtrack, jmax = LCS(v,w)
print l
#OutputLCS(backtrack, v, len(v), len(w))
output_strs(v,w,backtrack, jmax)


