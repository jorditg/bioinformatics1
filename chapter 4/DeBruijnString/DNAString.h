/* 
 * File:   DNAString.h
 * Author: jordi
 *
 * Created on 25 de noviembre de 2013, 21:49
 */

#ifndef DNASTRING_H
#define	DNASTRING_H

#include <map>
#include <list>
#include <string>
#include <iostream>

class DNAString {
public:
    DNAString();
    DNAString(const DNAString& orig);
    virtual ~DNAString();
    DNAString(const char * filename);
    
    void calculate_de_brujin_graph();
    void print_de_brujin_graph();
private:
    std::string dna;    // DNA string
    int k; // kmer length
    std::map<std::string, std::list<std::string> > debrujin;
};

#endif	/* DNASTRING_H */

