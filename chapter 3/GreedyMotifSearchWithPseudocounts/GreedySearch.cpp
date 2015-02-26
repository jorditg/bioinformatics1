/* 
 * File:   GreedySearch.cpp
 * Author: jdelatorre
 * 
 * Created on 21 de noviembre de 2013, 12:03
 */

#include "GreedySearch.h"
#include "Motif.h"
#include "KmerProfile.h"

#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>


GreedySearch::GreedySearch() {
}

GreedySearch::GreedySearch(const GreedySearch& orig) {
}

GreedySearch::~GreedySearch() {
}

GreedySearch::GreedySearch(const char * filename) {
    std::ifstream infile(filename);

    std::string line;
    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> k >> t;
    while (std::getline(infile, line))
    {
        // remove spaces 
        line.erase(std::remove_if( line.begin(), line.end(), 
                [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), line.end() );
        dna_str.push_back(line);
    }
}

int GreedySearch::distance(const char * a, const char * b, int len) const
{
    int dist = 0;
    for(int i=0;i<len;i++) {
        if(a[i] != b[i])
            dist++;
    }
    return dist;
}

void GreedySearch::init_motif(Motif &m)
{
    m.clear();
    for(std::vector<int>::size_type i = 0; i != dna_str.size(); i++) {
        std::string kmer = dna_str[i].substr(0,k);
        m.insert(kmer);
    }
    m.calculate_probabilities_with_pseudocounts();
}

void GreedySearch::search()
{
    Motif m;
    Motif & best_motifs = m;
    init_motif(best_motifs);
    best_motifs.calculate_probabilities_with_pseudocounts();
    int best_score = best_motifs.score();
    Motif actual;
    for(int i=0;i<dna_str[0].length()-k+1;i++) {
        std::string kmer = dna_str[0].substr(i,k);
        actual.clear();
        actual.insert(kmer);
        for(int j=1;j<t;j++) {
            actual.calculate_probabilities_with_pseudocounts();
            //actual.print_probabilities();
            KmerProfile p(dna_str[j], actual.get_prob());
            std::string kmer = p.most_probable_kmer();
            //std::cout << kmer << std::endl;
            actual.insert(kmer);            
        }
        int actual_score = actual.score();
        if(actual_score < best_score) {
            best_score = actual_score;
            best_motifs = actual;
        }
    }
    best_motifs.print();    
}