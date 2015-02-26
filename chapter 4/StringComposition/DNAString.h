/* 
 * File:   DNAString.h
 * Author: jordi
 *
 * Created on 25 de noviembre de 2013, 21:49
 */

#ifndef DNASTRING_H
#define	DNASTRING_H

#include <list>
#include <string>
#include <iostream>

class DNAString {
public:
    DNAString();
    DNAString(const DNAString& orig);
    virtual ~DNAString();
    DNAString(const char * filename);
    
    void calculate_composition();
    void print_composition();
private:
    std::string dna;    // DNA string
    int k; // kmer length
    std::list<std::string> l_kmers;
    bool stringCompare(const std::string & l, const std::string & r);
};

#endif	/* DNASTRING_H */

