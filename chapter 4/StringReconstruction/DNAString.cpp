/* 
 * File:   DNAString.cpp
 * Author: jordi
 * 
 * Created on 25 de noviembre de 2013, 21:49
 */

#include "DNAString.h"

#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>


DNAString::DNAString() {
}

DNAString::DNAString(const DNAString& orig) {
}

DNAString::~DNAString() {
}

DNAString::DNAString(const char * filename) {
    
    std::ifstream infile(filename);

    std::string line;
    while (std::getline(infile, line))
    {
        // remove spaces 
        line.erase(std::remove_if( line.begin(), line.end(), 
                [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), line.end() );
                reads.push_back(line);
    }
    
}

void DNAString::string_reconstruct()
{
    for (std::list<std::string>::const_iterator it1 = reads.begin(), 
         end = reads.end(); it1 != end; ++it1) {
        const std::string &p1 = *it1;
        int l = p1.length()-1;
        std::list<std::string>::const_iterator from = it1;
        from++;
        for (std::list<std::string>::const_iterator it2 = from, 
             end = reads.end(); it2 != end; ++it2) {
            const std::string &p2 = *it2;
            const std::string &tail1 = p1.substr(1,l);
            const std::string &head1 = p2.substr(0,l);
            if(tail1 == head1) {
                std::string s(p1 + " -> " + p2);
                result.push_back(s);
            } 
            const std::string &tail2 = p2.substr(1,l);
            const std::string &head2 = p1.substr(0,l);
            if(tail2 == head2) {
                std::string s(p2 + " -> " + p1);
                result.push_back(s);
            }
        }
     }
    result.sort();
    result.unique();
}

void DNAString::print_results()
{
    std::list<std::string>::iterator it; 
    for(it = result.begin(); it != result.end(); ++it)                                                                               
    {                                                                                                                                      
        std::cout << *it << std::endl;                                                                                                                 
    }      
}
