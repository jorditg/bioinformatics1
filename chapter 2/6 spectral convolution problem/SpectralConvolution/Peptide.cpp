/* 
 * File:   Peptide.cpp
 * Author: jdelatorre
 * 
 * Created on 11 de noviembre de 2013, 13:51
 */

#include "Peptide.h"

#include <string>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <iostream>

#include <fstream>
#include <sstream>

const char Peptide::amino[] = "GASPVTCILNDKQEMHFRYW";
const int Peptide::weight[] = {57,71,87,97,99,101,103,113,113,114,115,
                               128,128,129,131,137,147,156,163,186};

Peptide::Peptide() {
    peptide.assign("");
    w = 0;
    score = 0;
}

Peptide::Peptide(const Peptide& orig) {
    peptide.assign(orig.toString());
    w = orig.getWeight();
    score = orig.getScore();
}

Peptide::Peptide(const std::string &value) {
    peptide.assign(value);
    w = Peptide::toWeight(peptide);
    score = 0;
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

int Peptide::setScore(const std::list<int> *primary)
{   
    if(peptide == "") { score = 0; return 0; }
    
    std::list<int> secondary;
    int nr_cycles;
    
    cyclospectrum(&secondary, nr_cycles);
    //Peptide::printSpectrum(secondary);
    std::list<int>::const_iterator ip = primary->begin();
    std::list<int>::const_iterator endp = primary->end();
    std::list<int>::const_iterator is = secondary.begin();
    std::list<int>::const_iterator ends = secondary.end();
    while(ip != endp && is != ends) {
        if(*ip == *is) {
            score++;
            ip++;
            is++;
        } else if(*ip > *is) {
            is++;
        } else {
            ip++;
        }
    }
    return score;
//    
//    //printSpectrum(secondary);
//    std::list<int>::const_iterator from = primary->begin();
//    // other cyclospectrum should be already sorted
//    for(std::list<int>::const_iterator is = secondary.begin(), ends = secondary.end();
//        is != ends; is++) {
//        bool found = false;
//        for(std::list<int>::const_iterator ip = from, endp = primary->end();
//        ip != endp; ip++) {
//            if(*ip == *is) {
//                found = true;
//                from = ip;
//                from++;
//                score++;
//                break;
//            } else if(*ip > *is) {
//                break;
//            }
//        }     
//    }    
//    return score;
}

void Peptide::printSpectrum(std::list<int> &spectrum)
{
    for (std::list<int>::const_iterator iterator = spectrum.begin(), 
         end = spectrum.end(); iterator != end; ++iterator) {
        std::cout << *iterator << " ";
    }
    std::cout << std::endl;
}

int Peptide::peptideMass(const std::list<int> &spectrum)
{
    std::list<int>::const_iterator iterator = spectrum.end();
    iterator--;
    
    return *iterator;
}

int Peptide::loadSpectrum(const char * filename, std::list<int> &spectrum)
{
    spectrum.clear();

    int i;

    std::ifstream infile(filename, std::ifstream::in);

    if (!infile) {
        std::cout << "There was a problem opening file "
             << filename
             << " for reading."
             << std::endl;
        return 0;
    }

    while (infile >> i) spectrum.push_back(i);
   
    return 0;    
}

void Peptide::spectralConvolution(const std::list<int> &spectrum, std::list<int> &convolution) {
    convolution.clear();
    std::list<int>::const_iterator it1, it2;
    for (it1 = spectrum.begin(); it1 != spectrum.end(); ++it1) {
        for (it2 = spectrum.begin(); it2 != it1; ++it2) {
            int val = abs(*it2-*it1);
            if(val != 0) convolution.push_back(val);
        }
    }
}