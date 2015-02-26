# -*- coding: utf-8 -*-
"""
Created on Wed Dec 11 11:39:47 2013

@author: jordi
"""
#import sys 

def get_score(amino_from, amino_to):
    aminoacid = "ACDEFGHIKLMNPQRSTVWY"
    score=  [
            [4,0,-2,-1,-2,0,-2,-1,-1,-1,-1,-2,-1,-1,-1,1,0,0,-3,-2],
            [0,9,-3,-4,-2,-3,-3,-1,-3,-1,-1,-3,-3,-3,-3,-1,-1,-1,-2,-2],
            [-2,-3,6,2,-3,-1,-1,-3,-1,-4,-3,1,-1,0,-2,0,-1,-3,-4,-3],
            [-1,-4,2,5,-3,-2,0,-3,1,-3,-2,0,-1,2,0,0,-1,-2,-3,-2],
            [-2,-2,-3,-3,6,-3,-1,0,-3,0,0,-3,-4,-3,-3,-2,-2,-1,1,3],
            [0,-3,-1,-2,-3,6,-2,-4,-2,-4,-3,0,-2,-2,-2,0,-2,-3,-2,-3],
            [-2,-3,-1,0,-1,-2,8,-3,-1,-3,-2,1,-2,0,0,-1,-2,-3,-2,2],
            [-1,-1,-3,-3,0,-4,-3,4,-3,2,1,-3,-3,-3,-3,-2,-1,3,-3,-1],
            [-1,-3,-1,1,-3,-2,-1,-3,5,-2,-1,0,-1,1,2,0,-1,-2,-3,-2],
            [-1,-1,-4,-3,0,-4,-3,2,-2,4,2,-3,-3,-2,-2,-2,-1,1,-2,-1],
            [-1,-1,-3,-2,0,-3,-2,1,-1,2,5,-2,-2,0,-1,-1,-1,1,-1,-1],
            [-2,-3,1,0,-3,0,1,-3,0,-3,-2,6,-2,0,0,1,0,-3,-4,-2],
            [-1,-3,-1,-1,-4,-2,-2,-3,-1,-3,-2,-2,7,-1,-2,-1,-1,-2,-4,-3],
            [-1,-3,0,2,-3,-2,0,-3,1,-2,0,0,-1,5,1,0,-1,-2,-2,-1],
            [-1,-3,-2,0,-3,-2,0,-3,2,-2,-1,0,-2,1,5,-1,-1,-3,-3,-2],
            [1,-1,0,0,-2,0,-1,-2,0,-2,-1,1,-1,0,-1,4,1,-2,-3,-2],
            [0,-1,-1,-1,-2,-2,-2,-1,-1,-1,-1,0,-1,-1,-1,1,5,0,-2,-2],
            [0,-1,-3,-2,-1,-3,-3,3,-2,1,1,-3,-2,-2,-3,-2,0,4,-3,-1],
            [-3,-2,-4,-3,1,-2,-2,-3,-3,-2,-1,-4,-4,-2,-3,-3,-2,-3,11,2],
            [-2,-2,-3,-2,3,-3,2,-1,-2,-1,-1,-2,-3,-1,-2,-2,-2,-1,2,7]
            ]
    i = aminoacid.index(amino_from)
    j = aminoacid.index(amino_to)
    
    return score[i][j]

def LCS(v,w):
    sigma = 5
    
    m =len(v)
    n = len(w)
    
    s = [[0 for i in range(n+1)] for j in range(m+1)]
    backtrack = [['' for i in range(n+1)] for j in range(m+1)]
    
    for i in range(m+1):
        s[i][0] = 0 - sigma*i
        backtrack[i][0] = 'D'
    for j in range(n+1):
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

v = "HILHATSMFYRCETDIIAFVWEYWLQHFVIFILNQLFICLNFDEIPFSWDQQSCGRHAELRQYPTKQRWMMMSPICTVHCNVQGEWAGYLEKTRAYEWSWDYWWRTLSTQALDEYRFEWVKLVTHAHMIVKRMRSGQIVQVFCPDHNGICCWDTEFLYMALHNIKTHFFQRCGDLQADFMDTTMLLRDCSNMKFMGVDQEAWAARDKYPANTRSRLQPADQANAMNWRAFMLCLKSESMPKEWTVAQPKMVWDMCPELTDHPLQQIWMSGWKFNNVLEDYVQMNGFLQTLIKDPRYFHSLILSYWSQTNMHASVNHAYGRWFGKISKFIHKPPDLMVNGDDNQPAIQIFKMDPARQGGHTSGGVKQIMAMADLCGGYAEDKSLVNRHMEGTPTCTIICERKQNQSHEVVCNAMHRSPTFCSHWASNWGMVQRARLPFTVTFRTYCQYVFIKMNVGFKPYPANRIRKCWTAEYHCGQWPLFHIVKNGVKHYELHTFEYIFKAKPASAIVMKHCFNHGVLWHIYHVKQYHSDTWIRDGSPFGYDSNVLRNPFIGQCLDSEQDSTNLYFHWDYKHAFAWLKDLIWWYRQHHHVAIPQKYVIPYLKFELPAHVHNCYRAYMCDGMKRFAGNMNWIMPCDPYWKPYHKVWSFVYGDAVPPQCITDKDQEPFWTRMRMISNPRGIACRPEVTSIGLTHKVKCIEDGKHQYHMHTWEERYAWAFGERHRKIRGLHPDSTQDESTLDMIDCPQVGHFAMPVYFEEPSLTDVTSYVWKDTKIDDSMGQVDNYKHAGLSEWR"
w = "HILHATSMFYRCETDIIAFVWECNALQHFVIFILNCCFIDLDHSFAFDLIPDSWDQQVCGRHAELRQYPTSQRWMMMSPICTVHWNVQGRKTRAYEWSWDYWWRTLSTCALRTYEMYRFEWVKLRWRTTTHAEMIVKRMRRGCPDHNGICCRNNFRTWDTEFLYMDWILLHNIKTHFFQRCGDLCPLLIRQAADYMGMVQHWTTMLCRDCSNMKFWGVDQEAWAARDKYPANTSRLQPADQANPMNWRAFMLCLKSESMPKVWTVAQPKMMWDMCPELIDHPADEGVAQQIWMSGWKIHQMNGFLQTLIKDPVHKLILSYTSHASVNHAYGRWFGKISKFIHNQQSLPPDSKCSTRNQPAIQIFKMDPKIWTWRHDEGGVKQGGYAEDDSLVNVHMMAEGTPTCTGGVTTFHYGIYERKQNQAWHCNCHVHKHGEAYPYVVCNAMHRSPTFWSHTRSNWGMVPTAFTVTFRTYCQYVQIKMLVGFKPFPANRIRKCWTAFYHCGQWGDFHHVQPLFHIVKNGVKHYELHTFHHMWRAIASAEMWVMGLLLELWHIYHVKQYHSDTVITDGSPFLRNPFIGICLDSEQDSYNLYFLLGYWDYKVAFAWLKDLIWWKYQQHHHVAIPQKYVPNVDEKRHVHNCYRLYMSYWQYIDIMPCDPTKPYHKVWWACNLWFVYGDMWTHVWYAVPPQKDQEPFWTRMRMISNRVIACRPERKCIERGKHCYHMHTWEERYAWAFGSRHRKIRGLHPDSTQDESTLDMIYTPQVGHFAFPVDFEEPSLTDVTSYVWKDTKDSMMLTWIISCMGYLVMHVDNYQNKQPRSSRAIYFCKLSEWR"

l, backtrack = LCS(v,w)
print l
#OutputLCS(backtrack, v, len(v), len(w))
output_strs(v,w,backtrack)


