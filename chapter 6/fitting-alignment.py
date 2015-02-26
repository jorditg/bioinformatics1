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
    INIT_VAL = -10000000
    sigma = 1
    m =len(v)
    n = len(w)
    
    s = [[0 for i in range(n+1)] for j in range(m+1)]
    backtrack = [['' for i in range(n+1)] for j in range(m+1)]
    
    for i in range(m+1):
        s[i][0] = 0
        backtrack[i][0] = ''
    for j in range(n+1):
        s[0][j] = 0 - j*sigma
        backtrack[0][j] = ''
    
    for i in range(1,m+1):
        for j in range(1,n+1):
            down = s[i-1][j]-sigma
            diagonal = s[i-1][j-1]+get_score(v[i-1],w[j-1])
            right = s[i][j-1]-sigma

            maximum = max(down,diagonal, right)
                
            if maximum == down: # first move has to be a diagonal move (matching or mismatching)
                # D equals down                
                backtrack[i][j] = 'D'
            elif maximum == right:
                backtrack[i][j] = 'R'
            else:
                # A equals diagonal                
                backtrack[i][j] = 'A'
            
            s[i][j] = maximum
                       

    #print_array(s)
    #print_array(backtrack)
        #print
    maximum = INIT_VAL
    imax = 0
    for i in range(m+1):
        if(s[i][n] > maximum):
            maximum = s[i][n]
            imax = i
    
  
    return s[imax][n], backtrack, imax

def print_array(A):
    print('\n'.join([''.join(['{:4}'.format(item) for item in row]) 
      for row in A]))

def output_strs(v,w, bt, imax):
    m = len(v)
    n = len(w)
    i=imax
    j=n
    str1=""
    str2=""
    while(j>0):
        if bt[i][j] == 'A':
            str1 = str1 + v[i-1]
            str2 = str2 + w[j-1]
            i = i - 1
            j = j - 1
        elif bt[i][j] == 'R':
            str1 = str1 + '-'
            str2 = str2 + w[j-1]
            j = j - 1
        elif bt[i][j] == 'D':
            str1 = str1 + v[i-1]
            str2 = str2 + '-'
            i = i - 1
        elif bt[i][j] == 'I':
            i = 0
            j = 0
            
    str1 = str1[::-1]
    str2 = str2[::-1]
    
    print str1
    print str2


v="ATACCTAGCGGCCCGACTTGAAGCCAGAGTAGTTCTCTCGCTAGCGTCTTGCTCGCACTGTTCTGTCCTCGGTACTTGAGCGCGGTGAGTTAGTGAATCGGTCTGTATCCCTCCTATGCAAATGATTTAAATGATGACGATACGGATTCCAATGAGGTGCCGCTATGTCCTACAGATAAGCGGAATAGAGGATACTACTAGGCGACCACCGAGCACTCTTGCGTGAATAGATTTAATAATATAAGACTACCTGACCATGGATTTAGCGCTCTTTCCCGGTGCTCGGTCACGATTTTTATACCAACGGTATCTTCCACAAGCCCTGTCGAGTCGCCGGTCGTATCCAACGGGTCCGGAGCATGCCCCACATCCATATCGTCCTGAGGCCTATGCTAGACACAGGGCTTTCACTACGGCTTACTTTAGCATACATCCGTGGAATTGAGATTGTGTAGCTCTACGTATGGAACGAAAGTTCACTGAGCGTCGACAGGGACTACTCCAATGGAGGAAATCCTCTAGCAAAAGACAATGGCTCTCCGCTCCAAGCCCCACGCTGCCTCCTAATACCAATTCTTCACTCTGCGCATCTCTATAGGGTACTGCGTGTTGACGCTGTTATGTCAAACCCGCTTGAGATCGAACATCTAACCAACGCGCCGGCATGTCAGCTTAAGTGGGCAATCAAAAACACGCACGCGTATCGCCATCTATTCAGACCGATAGCCTTCTTCGACTTGGATGTCGCATCATAACAGTGAAACGTCATGTCTGAACGCCATGGATACCTGGTATTCTGCCAAACGGTTATGTGTAGAGCACCGTTTGGCGCAGGCTGTACTTCCGTGTATTTCGGCAGACGGGTCCCTTTGCAGTCCAGTGCCCTGACAAGCTGAGTACGAACATGAGAGAATG"
w="TGCACAGCTGAACGAAATTCTTTATGCAAGACGGCCACGCTCCCAGCGTGAGCGCGCGTGTATCGGGGAGCGCTCGCTGAGCTAT"

#v="AAATTTAAA"
#w="TATA"

l, backtrack, imax= LCS(v,w)
print l
output_strs(v,w,backtrack, imax)
