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
    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> k;
    while (std::getline(infile, line))
    {
        // remove spaces 
        line.erase(std::remove_if( line.begin(), line.end(), 
                [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), line.end() );
                dna = line; // SOLO COJE UNA LÍNEA!!!!!!!!!!!!!!!!!!
    }
    
}

void DNAString::calculate_composition()
{    
    for(int i=0;i<dna.length()-k+1;i++)
        l_kmers.push_back(dna.substr(i,k));
    
    l_kmers.sort();
    l_kmers.unique();
}

bool DNAString::stringCompare(const std::string & l, const std::string & r)
{
   return (l==r);
}

void DNAString::print_composition()
{
    std::list<std::string>::iterator it; 
    for(it = l_kmers.begin(); it != l_kmers.end(); ++it)                                                                               
    {                                                                                                                                      
        std::cout << *it << std::endl;                                                                                                                 
    }      
}