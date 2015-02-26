#!/usr/bin/python

import sys

def load_inverse_RNA_codon_table(file):
    d = {}
    with open(file) as f:
        for line in f:
            (key, val) = line.split()
            if d.has_key(key):
                d[key].append(val)
            else:
                d[key] = [val,]
    return d

def load_data(file):
    with open(file) as f:
        DNA = f.readline().rstrip()
        peptide = f.readline().rstrip()
    return DNA, peptide
    
def RNA2DNA_char(RNA_char):
    if RNA_char == 'A':
        return 'T'
    elif RNA_char == 'U':
        return 'A'
    elif RNA_char == 'G':
        return 'C'
    elif RNA_char == 'C':
        return 'G'

def RNA2DNA(RNA):
    DNA = ""
    for c in RNA:
        DNA = DNA + RNA2DNA_char(c)
    return DNA

def rc(DNA):
    out = ""
    for c in DNA:
        if c == 'A':
            out = out + 'T'
        elif c == 'T':
            out = out + 'A'
        elif c == 'G':
            out = out + 'C'
        elif c == 'C':
            out = out + 'G'                     
    return out[::-1]

def find_DNA_substrings(DNA, out, l):
    for i in range(0,len(DNA)-l+1):
        for o in out:
            if DNA[i:i+l] == o:
                print DNA[i:i+l],
            elif rc(DNA[i:i+l]) == o:
                print DNA[i:i+l],

def peptide2DNA(peptide):
    out = []
    for amino in peptide:
        temp = out
        out = []
        for enc in inv_codon_tbl[amino]:
            if len(temp) == 0:
                if len(out) == 0:
                    out = [enc.replace('U', 'T')]
                else:
                    out.append(enc.replace('U', 'T'))
            else:
                for t in temp:
                    out.append(t+enc.replace('U', 'T'))
    return out

if __name__ == "__main__":
    inv_codon_tbl = load_inverse_RNA_codon_table("reverse_codon_table.txt")
    DNA, peptide = load_data("B_brevis.txt")
    
    peptide_DNA = peptide2DNA(peptide)
    

#    print "Candidates"
#    for o in out:
#        print o  
    
#    print ""
#    print "Found"    

    l = len(peptide*3)   
    find_DNA_substrings(DNA, peptide_DNA, l)               

