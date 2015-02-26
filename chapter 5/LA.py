# -*- coding: utf-8 -*-
"""
Created on Wed Dec 11 11:39:47 2013

@author: jordi
"""
#import sys 

def get_score(amino_from, amino_to):
    aminoacid = "ACDEFGHIKLMNPQRSTVWY"
    score=  [
            [2,-2,0,0,-3,1,-1,-1,-1,-2,-1,0,1,0,-2,1,1,0,-6,-3],
            [-2,12,-5,-5,-4,-3,-3,-2,-5,-6,-5,-4,-3,-5,-4,0,-2,-2,-8,0],
            [0,-5,4,3,-6,1,1,-2,0,-4,-3,2,-1,2,-1,0,0,-2,-7,-4],
            [0,-5,3,4,-5,0,1,-2,0,-3,-2,1,-1,2,-1,0,0,-2,-7,-4],
            [-3,-4,-6,-5,9,-5,-2,1,-5,2,0,-3,-5,-5,-4,-3,-3,-1,0,7],
            [1,-3,1,0,-5,5,-2,-3,-2,-4,-3,0,0,-1,-3,1,0,-1,-7,-5],
            [-1,-3,1,1,-2,-2,6,-2,0,-2,-2,2,0,3,2,-1,-1,-2,-3,0],
            [-1,-2,-2,-2,1,-3,-2,5,-2,2,2,-2,-2,-2,-2,-1,0,4,-5,-1],
            [-1,-5,0,0,-5,-2,0,-2,5,-3,0,1,-1,1,3,0,0,-2,-3,-4],
            [-2,-6,-4,-3,2,-4,-2,2,-3,6,4,-3,-3,-2,-3,-3,-2,2,-2,-1],
            [-1,-5,-3,-2,0,-3,-2,2,0,4,6,-2,-2,-1,0,-2,-1,2,-4,-2],
            [0,-4,2,1,-3,0,2,-2,1,-3,-2,2,0,1,0,1,0,-2,-4,-2],
            [1,-3,-1,-1,-5,0,0,-2,-1,-3,-2,0,6,0,0,1,0,-1,-6,-5],
            [0,-5,2,2,-5,-1,3,-2,1,-2,-1,1,0,4,1,-1,-1,-2,-5,-4],
            [-2,-4,-1,-1,-4,-3,2,-2,3,-3,0,0,0,1,6,0,-1,-2,2,-4],
            [1,0,0,0,-3,1,-1,-1,0,-3,-2,1,1,-1,0,2,1,-1,-2,-3],
            [1,-2,0,0,-3,0,-1,0,0,-2,-1,0,0,-1,-1,1,3,0,-5,-3],
            [0,-2,-2,-2,-1,-1,-2,4,-2,2,2,-2,-1,-2,-2,-1,0,4,-6,-2],
            [-6,-8,-7,-7,0,-7,-3,-5,-3,-2,-4,-4,-6,-5,2,-2,-5,-6,17,0],
            [-3,0,-4,-4,7,-5,0,-1,-4,-1,-2,-2,-5,-4,-4,-3,-3,-2,0,10],
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

            maximum = max(0,right,down,diagonal)
                
            if maximum == 0:
                backtrack[i][j] = 'I'
            elif maximum == down:
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
    maximum = 0
    imax = 0
    jmax = 0
    for i in range(1,m+1):
        for j in range(1,n+1):
            if s[i][j] > maximum:
                maximum = s[i][j]
                imax = i
                jmax = j
    
    return s[imax][jmax], backtrack, imax, jmax


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
        elif backtrack[i][j] == 'I':
            i = 0
            j = 0
            
    str1 = str1[::-1]
    str2 = str2[::-1]
    
    print str1
    print str2


v="RRVSNVSYNHRNSWQWMMSIVEDITIFKASKNVYHFYWEKKYQLLHCRHHNPRTTSVRFHWTVKRNGSDPNDCSITVWYNCYNPLCQVFTALPWCWCIKRYITSKGYHFSITGLGTHEGFTWLYLGGQNVEQKNTIAISVHFIMFLERVMHYHKGSWMDRWMKRRMNVCQQKVKRITSAPFSWGWWKQLLFSFVTTINFLPQTLRTMTKYPNATQNATQWQNKRICESNPWCMLWKTMMNRSCADFHGYMGPGRILYTGIPTSMIHKQSELRPLWYCAWATWNMTNYHHTATLGAGHGEETQIDFDFWRAGQFFIPDKHSCFEPIKNCIANYEFNEYQQVTLQTFIKHLYLISQWMTHTDALSHEQYMECRFMPRQILASEVRPNKSPVGITLAFKTYAFPETDCGLQYQTLYMRQKKNTCKTGVQTWWYHWGFQPQVWHFTWHMMANRIISMSLLKRQQAQQIEYRIATENFKAWGQPKGWHQDIVSHCKMPCGMVRPVSHSLKTSFSKFIVSMILLMSWWEIFAMTLAIPWAQGAPTEKYPYCSSDMQGFYHAFNGTNIGSCQWQEYDDLAPPSHGGDFTPSFEWCQYYRESNMQIVHPVFQKKTWTQGGSTYCIVVDINGDGLAGFWPFYLKETDKCEWTPVCGCKIQCHFRREDWADCGLFLYWQLIIVWSSIHDCVHPVDRLGGQNVPVDTLHTHNLCPETVRNCDDHATPRKGNWMHLLSLMHSTECFYNWFVAPFPFMYAQHGERDDDEPASMQSDENQPRSMMAPRMFKHWCLWRQQSCKLNTVVQMTMMPLVTHKGWLMGLVMLCRTLMYDPHMADGSMSMSRMGYQKDCGSHVCTNGNICLDVQSFFTFLRGPRCIFFKAMEQTIVIICTIKTVCFTFIPKSWKLPCQHF"
w="HVTLCDPITNVFNDHTGNRIQVRMQNAIRGSHCGPYIWCCHPKFPQMHWPCQLKPIDDRWRSLDEMKFFRMMAAFCFWHRLVICYFNPYLEFSMYTYGFLKQVLRNMGGYTPELTDHTKWKQLSFDGASAHPAYVANNPAKQHRSVDYWFARQEYNTRGAKNCKLECKSHDCYRRRSDKPPWQPQFYNCNMYNTAIKTKSRTLDMNFAGPWIAHDDFCPERRSEHRRTSNDMKSQKGMNWGDVMGIPTSHNIHKHSELRPLWYCAWATMSVITGGFYCCRVRGHGSEWPLPYQPDGYQCIFVMFYPFWNAGQFFRKDKHSCFIWDFGNPIKELQTFIKHLYKISQWMTRKPFDDALSHEQYMECRFMPRQAEVRPRCQQQSPVRITLAFATTDCGLQYQTLYMRQQWKQILSSYNTIKTGVQTWWYHWGFQFQTVAMVWTWHMWGANRIISMSLLKRQMPFALMVQQIEYRIATENFKAWGFPLVSHCDMQCGMVRSAKTSFSKFIVSMILLMSWWWIFAMTLAIPWAQGAPTDGSRTFNFGKGRLDNIGQEYDDLAPPSHGGDFTPSFEWPCEKAAGACFYYRESNMQIGHRNFQGHSAPICKMFMCQMECAWTEKPMPDKKCCLWEFFIENGKLCIVGNVFIVDSPYSEHCGGDQSKDLGPPWQFFFPKEYRHEDPSMILQYELVVGGLSMTKAVMLCMYDCICRNKLCLFCAWHIAWGRDYRWMSGHCNASNRYAFMFNAMKDLHHAKIETCAVYEQCARFEHMTNTAFFPILLYKCACERSRVTQSNSRVWAPIMHLCASATEGKPRFRHTGKTNECVMVQFFVPRSLFNHLYYVECCAYHQFLAWKKADNNFVVTW"

l, backtrack, imax, jmax = LCS(v,w)
print l
output_strs(v[0:imax],w[0:jmax],backtrack[0:imax+1][0:jmax+1])


