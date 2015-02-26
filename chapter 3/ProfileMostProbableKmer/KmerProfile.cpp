/* 
 * File:   Profile.cpp
 * Author: jordi
 * 
 * Created on 21 de noviembre de 2013, 6:32
 */

#include "KmerProfile.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

KmerProfile::KmerProfile(const KmerProfile& orig) {
    k = orig.k;
    dna_str = orig.dna_str;
}

KmerProfile::~KmerProfile() {
}

KmerProfile::KmerProfile(const char *filename) {
    std::ifstream infile(filename);

    std::string line;
    std::getline(infile, dna_str);
    std::getline(infile, line);

    std::istringstream iss(line);
    iss >> k;
    std::getline(infile, line);
    std::istringstream char_set(line);

    char c;
    char_set >> c;
    char_v.push_back(c);
    char_set >> c;
    char_v.push_back(c);
    char_set >> c;
    char_v.push_back(c);
    char_set >> c;
    char_v.push_back(c);

    int i = 0;    
    while (std::getline(infile, line))
    {        
        std::istringstream iss(line);
        std::array<float, 4> readv;
        iss >> readv[0] >> readv[1] >> readv[2] >> readv[3];
        prob.push_back(readv);
        i++;
    }
}

float KmerProfile::kmer_prob(std::string kmer) 
{
    float pr = 1;
    for(int i=0;i<k;i++) {
        for(int j=0;j<4;j++) {
            if(char_v[j] == kmer[i]) {
                pr *= prob[i][j];
            }
        }
    }
    return pr;
}

std::string KmerProfile::most_probable_kmer()
{
    int k_idx = 0;
    float k_pr = 0.0;
    for(int i=0;i<dna_str.length()-k+1;i++) {
        std::string kmer = dna_str.substr(i,k);
        float act_prob = kmer_prob(kmer);
        if(act_prob > k_pr) {
            k_pr = act_prob;
            k_idx = i;
        }
    }
    return dna_str.substr(k_idx,k);
}
