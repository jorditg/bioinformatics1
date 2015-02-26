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
    
    void print_results();    
    void string_reconstruct();
private:
    std::list<std::string> reads;    // DNA strings
    std::list<std::string> result;
    
};

#endif	/* DNASTRING_H */

