/* 
 * File:   StringCollection.cpp
 * Author: jdelatorre
 * 
 * Created on 19 de noviembre de 2013, 10:28
 */

#include "StringCollection.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <string>
#include <regex>

#include "combinations.h"

StringCollection::StringCollection(const char * filename) {
    std::ifstream infile(filename);

    std::string line;
    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> k >> d;
    while (std::getline(infile, line))
    {
        // remove spaces 
        line.erase(std::remove_if( line.begin(), line.end(), 
                [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), line.end() );
        str_col.push_back(line);
    }
}


StringCollection::StringCollection() {
    k = d = 0;
}

StringCollection::StringCollection(const StringCollection& orig) {
    k = orig.d;
    d = orig.k;
    
    for (std::vector<std::string>::const_iterator iterator = orig.getStrings().begin(), 
         end = orig.getStrings().end(); iterator != end; ++iterator) {
        std::string s(*iterator);
        str_col.push_back(s);
    }
}

StringCollection::~StringCollection() {
}

void StringCollection::print()
{
    std::cout << "k=" << k << std::endl;
    std::cout << "d=" << d << std::endl;
    for (std::vector<std::string>::const_iterator iterator = str_col.begin(), 
         end = str_col.end(); iterator != end; ++iterator) {
        std::cout << *iterator << std::endl;
    }
}

int StringCollection::distance(const char * a, const char * b, int len) const
{
    int dist = 0;
    for(int i=0;i<len;i++) {
        if(a[i] != b[i])
            dist++;
    }
    return dist;
}

void StringCollection::print_kmer (const char *kmer, int k) const
{
    for(int i=0;i<k;i++)
        std::cout << kmer[i];
    std::cout << std::endl;
}

std::string StringCollection::other_bases(char base)
{
    switch(base) {
        case 'A': return std::string("TGC");
        case 'T': return std::string("AGC");
        case 'G': return std::string("ATC");
        case 'C': return std::string("ATG");
    }            
    return "";
}

void StringCollection::find_mutation(std::string mutation) const
{
    const char * kmer1 = mutation.c_str();
    bool present = false;
    for(std::vector<std::string>::size_type i = 0; i != str_col.size(); i++) {    
        const char * str = str_col[i].c_str();
        const int len = str_col[i].size();
        const int end = len - k + 1;
        present = false;
        for(int j = 0;j<end;j++) {
            const char * kmer2 = str_col[i].substr(j,k).c_str();
            if(distance(kmer1, kmer2, k) <= d) {
                present = true;
                break;
            }
        }
        if(!present) break;
    }
    if(present) print_kmer(kmer1, k);
}

std::string StringCollection::mutate(const std::string &kmer, const std::string position, const std::string value) 
{
    std::string ret(kmer);
    for(int i=0;i<position.size();i++) {
        int pos = position[i] - 1;      // Begins from 1 not from 0
        std::string bases = other_bases(kmer[pos]);
        int val = value[i] - '0';
        ret[pos] = bases[val];
    }
    return ret;
}

void StringCollection::motif_enumeration()
{
    for(int i=d;i>=0;i--) {
        std::list<std::string> mut_pos;
        mutation_positions(k, d, mut_pos);
        std::list<std::string> mut_val;
        mutation_values(d, mut_val);
        
        for(std::vector<std::string>::size_type i = 0; i != str_col.size(); i++) {    
            const int len = str_col[i].size();
            const int end = len - k + 1;
            
            for(int j = 0;j<end;j++) {
                std::string kmer = str_col[i].substr(j, k);

                for (std::list<std::string>::const_iterator it1 = mut_pos.begin(), 
                     end1 = mut_pos.end(); it1 != end1; ++it1) {
                    std::string position = *it1;
                    for (std::list<std::string>::const_iterator it2 = mut_val.begin(), 
                         end2 = mut_val.end(); it2 != end2; ++it2) {
                         std::string value = *it2;
                         
                         std::string mutation = mutate(kmer, position, value);
                         
                         find_mutation(mutation);
                         
                    }
                }

            }
        }
    }    
}

std::list<std::string> & StringCollection::mutation_values(int len, std::list<std::string> &result)
{
    result.clear();
    
    result.push_back("");
    int l=0;
    while(l<len) {
        std::list<std::string>::iterator iterator = result.begin(), end = result.end();
        while (iterator != end) {
            for(int i=0;i<3;i++) {
                std::string s(*iterator);
                std::ostringstream convert;   // stream used for the conversion
                convert << i;      // insert the textual representation of 'Number' in the characters in the stream                
                s.append(convert.str());
                result.insert(iterator, s);
            }
            iterator = result.erase(iterator);
        }
        l++;
    }
}

std::list<std::string> & StringCollection::mutation_positions(int n, int k, std::list<std::string> &result)
{
    result.clear();
    
    std::string s;
    for(int i=1;i<=n;i++) {       // use char as numbers not as characters
        char p[2] = {(char) i, '\0'};
        s.append(p);
    }
   
    do {
        result.push_back(std::string(s.begin(), s.begin() + k));
    } while(next_combination(s.begin(),s.begin() + k,s.end()));
    
}

void StringCollection::print(std::list<std::string> s)
{
    for (std::list<std::string>::const_iterator iterator = s.begin(), 
         end = s.end(); iterator != end; ++iterator) {
        std::cout << *iterator << std::endl;
    }    
}
