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

void DNAString::calculate_de_brujin_graph()
{    
    for(int i=0;i<dna.length()-k+1;i++) {
        const std::string &from = dna.substr(i,k-1);
        const std::string &to = dna.substr(i+1,k-1);
        if ( debrujin.find(from) == debrujin.end() ) {
            // not found
            std::list<std::string> value;
            value.push_back(to);
            debrujin.insert(std::pair<std::string, std::list<std::string> >(from, value));
        } else {
            // found
            std::list<std::string> &l = debrujin.at(from);
            l.push_back(to);
            l.sort();
            l.unique();
        }        
    }
}

void DNAString::print_de_brujin_graph()
{
    std::map<std::string,std::list<std::string> >::iterator it = debrujin.begin();
    for (it=debrujin.begin(); it!=debrujin.end(); ++it) {
        std::cout << it->first << " -> ";
        std::list<std::string> &l = it->second;
        std::list<std::string>::const_iterator iterator = l.begin();
        std::cout << *iterator;
        iterator++;
        while(iterator != l.end()) {
            std::cout << "," << *iterator;
            iterator++;
        }
        std::cout << "\n";
    }
}
    