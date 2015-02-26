/* 
 * File:   Motif.cpp
 * Author: jdelatorre
 * 
 * Created on 21 de noviembre de 2013, 14:37
 */

#include "Motif.h"
#include <iostream>

Motif::Motif() {
}

Motif::Motif(const Motif& orig) {
    this->prob = orig.prob;
    this->m = orig.m;
}

Motif::~Motif() {
}

void Motif::insert(std::string &val)
{
    m.push_back(std::string(val));
}

void Motif::clear()
{
    m.clear();
}


void Motif::calculate_probabilities_with_pseudocounts()
{
    prob.clear();
    int k = m[0].size();
    //               A   C   G   T
    std::array<float, 4> a = {1.0,1.0,1.0,1.0};
    prob.resize(k, a);
    for(int j = 0;j<k;j++) {
        for(std::vector<int>::size_type i = 0; i != m.size(); i++) {
            switch(m[i][j]) {
                case 'A': prob[j][0]++;
                          break;
                case 'C': prob[j][1]++;
                          break;
                case 'G': prob[j][2]++;
                          break;
                case 'T': prob[j][3]++;
                          break;
            }
        }
    }
    float c = (1./(float) (m.size()+4));
    for(int j = 0;j<k;j++) {
        for(int i=0;i<4;i++)
            prob[j][i] *= c;
    }
        
}

int Motif::score()
{
    int scr = 0;
    
    //std::string consensus;
    for(int i = 0; i<prob.size();i++) {
        int idx = 0;
        float g = prob[i][0];
        for(int j=1;j<4;j++) {
            if(prob[i][j] > g) {
                g = prob[i][j];
                idx = j;
            }
        }
        char c = idx2char(idx);
        //consensus.append(1,c);
        int part_scr = 0;
        for(std::vector<int>::size_type l = 0; l != m.size(); l++) {
            if(m[l][i] != c)
                part_scr++;
        }
        scr += part_scr;
    }
    return scr;
}

void Motif::print()
{
   for(std::vector<int>::size_type l = 0; l != m.size(); l++) {
       std::cout << m[l] << std::endl;
   } 
}

void Motif::print_probabilities()
{
    int k = m[0].length();
    for(int j = 0;j<k;j++) {
        std::cout << prob[j][0] << " " << prob[j][1] << " " << prob[j][2] << " " << prob[j][3] << std::endl;
    }
}