/* 
 * File:   Peptide.cpp
 * Author: jdelatorre
 * 
 * Created on 11 de noviembre de 2013, 13:51
 */

#include "Peptide.h"

#include <string>
#include <cstdio>
#include <list>

const char Peptide::amino[] = "GASPVTCINDKEMHFRYW";
//const int Peptide::weight[] = {57,71,87,97,99,101,103,113,113,114,115,
//                               128,128,129,131,137,147,156,163,186};
    /////////////////////////////////////////////////////////
    ///// WARNING!! AMINO NR. CHANGED TO DO THE EXERCISE/////
    /////////////////////////////////////////////////////////
const int Peptide::weight[] = {57,71,87,97,99,101,103,113,114,115,
                               128,129,131,137,147,156,163,186};


Peptide::Peptide() {
    peptide.assign("");
}

Peptide::Peptide(const Peptide& orig) {
    peptide.assign(orig.toString());
}

Peptide::Peptide(const std::string value) {
    peptide.assign(value);
}

Peptide::~Peptide() {
}

std::string Peptide::toWeightString()
{
    std::string s("");
    
    for(int i=0;i<peptide.size();i++) {
        if(s != "") s.append("-");
        for(int j=0;j<AMINO_LEN;j++) {            
            if(peptide[i] == amino[j]) {
                char str[32];
                sprintf(str, "%d", weight[j]);
                s.append(str);
                break;
            }
        }
    }
    return s;
}

int Peptide::toWeight(const std::string p)
{
    int sum = 0;
    for(int i=0;i<p.size();i++) {
        for(int j=0;j<AMINO_LEN;j++) {
            if(p[i] == amino[j]) {
                sum += weight[j];
                break;
            }
        }
    }
    return sum;
}

std::list<int> & Peptide::cyclospectrum(std::list<int> * result, int & nr_cycles)
{
    result->push_back(0);
    
    for(int len=1;len<peptide.size();len++) {
            for(int i=0;i<peptide.size();i++) {
                    std::string val("");
                    for(int j=0;j<len;j++) {
                        const char c[2] = {peptide[(i+j)%peptide.size()], '\0'};
                        val.append(c);
                    }
                    result->push_back(toWeight(val));
            }           
    }
    result->push_back(toWeight(peptide));    
        
    result->sort();
    //result->unique();
    
    if(peptide.size() <= 2)
        nr_cycles = 0;
    else {
        int n = peptide.size() - 1;
        nr_cycles = n*(n-1)/2;
    }
    
    return *result;
}

bool Peptide::spectrumIsEqual (std::list<int> &spec1, std::list<int> &spec2)
{
    // other cyclospectrum should be already sorted
    unsigned int l1 = spec1.size();
    unsigned int l2 = spec2.size();
    if(l1 != l2)
        return false;
    else {
        std::list<int>::iterator i = spec1.begin();
        std::list<int>::iterator end = spec1.end();

        std::list<int>::iterator i2 = spec2.begin();
        while ((i  != end))
        {
            if(*i != *i2)
                return false;
            i++;
            i2++;
        }        
    }
    return true;
}

bool Peptide::spectrumIsConsistent(std::list<int> &primary, std::list<int> &secondary, int nr_cycles)
{
    int nr_errors = 0;
    // other cyclospectrum should be already sorted
    if(primary.size() >= secondary.size()) {        
        for(std::list<int>::iterator is = secondary.begin(), ends = secondary.end();
            is != ends; is++) {
            bool found = false;
            for(std::list<int>::iterator ip = primary.begin(), endp = primary.end();
            ip != endp; ip++) {
                if(*ip == *is) {
                    found = true;
                    break;
                } else if(*ip > *is) {
                    break;
                }
            }
            if(!found) nr_errors++;
            if(nr_errors > nr_cycles) return false;
        }            
        return true;
    }
    return false;
}
