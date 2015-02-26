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
#include <vector>
#include <array>

KmerProfile::KmerProfile(const std::string dna_str, 
                const std::vector<std::array<float, 4> > prob)
{
    this->dna_str.assign(dna_str);
    this->prob = prob;
}

KmerProfile::KmerProfile(const KmerProfile& orig) {
    this->dna_str = orig.dna_str;
    this->prob = orig.prob;
}

KmerProfile::~KmerProfile() {
}

float KmerProfile::kmer_prob(std::string kmer) 
{
    float pr = 1;
    for(int i=0;i<kmer.length();i++) {
        switch(kmer[i]) {
            case 'A': pr *= prob[i][0]; break;
            case 'C': pr *= prob[i][1]; break;
            case 'G': pr *= prob[i][2]; break;
            case 'T': pr *= prob[i][3]; break;
        }
    }
    return pr;
}

std::string KmerProfile::most_probable_kmer()
{
    int k = prob.size();
    //print_probabilities();
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

void KmerProfile::print_probabilities()
{
    int k = prob.size();
    std::cout << "in kmerprofile" << std::endl;
    for(int j = 0;j<k;j++) {
        std::cout << prob[j][0] << " " << prob[j][1] << " " << prob[j][2] << " " << prob[j][3] << std::endl;
    }
}

std::string KmerProfile::random_with_probabilities(float random)
{
    const int k = prob.size();
    const int M = dna_str.length()-k+1;
    
    std::vector<float> p(M);
    float total_prob = 0.0;
    
    for(int i=0;i<M;i++) {
        std::string kmer = dna_str.substr(i,k);
        float act_prob = kmer_prob(kmer);
        
        p[i] = act_prob;
        total_prob += act_prob;
    }
    
    float v = 0.0;
    int i=0;
    while(v < random && i<M) {
        v += p[i]/total_prob;
        i++;
    }        
    
    return dna_str.substr(i-1,k);    
}
