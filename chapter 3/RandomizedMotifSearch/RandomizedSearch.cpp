/* 
 * File:   RandomizedSearch.cpp
 * Author: jdelatorre
 * 
 * Created on 22 de noviembre de 2013, 11:21
 */

#include "RandomizedSearch.h"
#include "KmerProfile.h"
#include "Motif.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>


RandomizedSearch::RandomizedSearch() {
}

RandomizedSearch::RandomizedSearch(const RandomizedSearch& orig) {
}

RandomizedSearch::~RandomizedSearch() {
    delete dist;
}

RandomizedSearch::RandomizedSearch(const char * filename, int iterations) {
    this->iterations = iterations;
    
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
    
    // initialize random generator
    rng = create_seeded_rng();
    this->dist = new std::uniform_int_distribution<int>(0,dna_str[0].length()-k);
        
}

std::mt19937 RandomizedSearch::create_seeded_rng() 
{ 
    std::random_device rd; 
    std::array<std::mt19937::result_type, std::mt19937::state_size> seed_data; 
    std::generate(seed_data.begin(), seed_data.end(), std::ref(rd)); 
    std::seed_seq seq(seed_data.begin(), seed_data.end()); 
    return std::mt19937(seq); 
}

Motif & RandomizedSearch::generate_motif(Motif &m)
{
    m.clear();
    for(int i=0;i<t;i++) {
        int v = get_random_number();
        std::string kmer = dna_str[i].substr(v,k);        
        m.insert(kmer);
    }
    
}

void RandomizedSearch::search()
{
    int it = 0;
    int best_best_score = 99999;
    Motif best_best;
    
    while(it < 1000) {
        Motif actual;
        generate_motif(actual);
        actual.calculate_probabilities_with_pseudocounts();
        //actual.print_probabilities();
        Motif best_motifs = actual;
        int best_score = best_motifs.score();
        //std::cout << "best motifs" << std::endl;
        //best_motifs.print();

        while(1) {        
    //        std::cout << "probabilities (previous)\n";
    //        previous.print_probabilities();
            actual.clear();
            for(int j=0;j<t;j++) {             
                KmerProfile p(dna_str[j], actual.get_prob()); // kmer profile with previous probabilities
                std::string kmer = p.most_probable_kmer();
                //std::cout << kmer << std::endl;
                //std::cout << "kemer choosed: " << kmer << std::endl;
                actual.insert(kmer);            
            }
            //actual.print();
            actual.calculate_probabilities_with_pseudocounts();
            //actual.print_probabilities();

    //        std::cout << "previous\n";
    //        previous.print_probabilities();
    //        std::cout << "actual\n";
    //        actual.print_probabilities();
    //        actual.print();
            int actual_score = actual.score();
            if(actual_score < best_score) {
                best_score = actual_score;
                best_motifs = actual;       
            } else {
                break;
            }
            it++;
        }
        //best_motifs.print(); 
        best_score = best_motifs.score();
        if(best_score < best_best_score) {
            best_best_score = best_score;
            best_best = best_motifs;
        }
        
        it++;
    } 
    
    best_best.print();
    std::cout << "Score: " << best_best.score() << std::endl;
    
}