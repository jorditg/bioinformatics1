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
#include <map>

class DNAString {
public:
    DNAString();
    DNAString(const DNAString& orig);
    virtual ~DNAString();
    DNAString(const char * filename);
    
    void print_de_brujin_graph();    
    void calculate_de_brujin_graph();
private:
    std::list<std::string> reads;    // DNA strings
    std::map<std::string, std::list<std::string> > debrujin;
    
};

#endif	/* DNASTRING_H */

