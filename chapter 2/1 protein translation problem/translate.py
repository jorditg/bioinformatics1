#!/usr/bin/python

import sys

def load_RNA_codon_table(file):
    d = {}
    with open(file) as f:
        for line in f:
            (key, val) = line.split()
            d[key] = val
    
    return d

def load_RNA_string(file):
    with open(file) as f:
        return f.readline().rstrip()

if __name__ == "__main__":
    rna_codon = load_RNA_codon_table("RNA_codon_table_1.txt")
    
    RNA_string = load_RNA_string("other.txt")
    
    i = 0
    while len(RNA_string) > i+2:
        v = rna_codon[RNA_string[i:i+3]]
        if v != "<END>":
            sys.stdout.write(v)
        else:
            break
        i = i+3
    print
