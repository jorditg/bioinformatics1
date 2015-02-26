/* 
 * File:   GibbsSampler.cpp
 * Author: jdelatorre
 * 
 * Created on 22 de noviembre de 2013, 11:21
 */

#include "GibbsSampler.h"
#include "KmerProfile.h"
#include "Motif.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h> // So we can use time() function


GibbsSampler::GibbsSampler() {
}

GibbsSampler::GibbsSampler(const GibbsSampler& orig) {
}

GibbsSampler::~GibbsSampler() {
    delete dist;
}

GibbsSampler::GibbsSampler(const char * filename) {
    srand( time(NULL) );
    
    std::ifstream infile(filename);

    std::string line;
    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> k >> t >> iterations;
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
    this->dist_t = new std::uniform_int_distribution<int>(0,t-1);
        
}

std::mt19937 GibbsSampler::create_seeded_rng() 
{ 
    std::random_device rd; 
    std::array<std::mt19937::result_type, std::mt19937::state_size> seed_data; 
    std::generate(seed_data.begin(), seed_data.end(), std::ref(rd)); 
    std::seed_seq seq(seed_data.begin(), seed_data.end()); 
    return std::mt19937(seq); 
}

Motif & GibbsSampler::generate_motif(Motif &m)
{
    m.clear();
    for(int i=0;i<t;i++) {
        int v = get_random_number();
        std::string kmer = dna_str[i].substr(v,k);        
        m.insert(kmer);
    }
    
}

void GibbsSampler::search()
{

    Motif actual;
    generate_motif(actual);
    actual.calculate_probabilities_with_pseudocounts();
    actual.print_probabilities();
    Motif best_motifs = actual;
    int best_score = best_motifs.score();
    std::cout << "best motifs" << std::endl;
    best_motifs.print();

    int it = 0;    
    while(it < iterations) {
      
//        std::cout << "probabilities (previous)\n";
//        previous.print_probabilities();
        int s = get_random_motif_index();
        actual.print();
        std::cout << "index removed: " << s << std::endl;
        actual.calculate_probabilities_with_pseudocounts_without(s);
        actual.print_probabilities();
        KmerProfile p(dna_str[s], actual.get_prob());
        float randNum = (float) rand()/ (float) RAND_MAX ;
        std::cout << "random: " << randNum << std::endl;
        std::string kmer = p.random_with_probabilities(randNum);
        
        actual.substitute(s, kmer);
        actual.print();
        
        actual.print_probabilities();

//        std::cout << "previous\n";
//        previous.print_probabilities();
//        std::cout << "actual\n";
//        actual.print_probabilities();
//        actual.print();
        int actual_score = actual.score();
        if(actual_score < best_score) {
            best_score = actual_score;
            best_motifs = actual;       
        }
        
        it++;
    } 
    
    best_motifs.print();
    std::cout << "Score: " << best_motifs.score() << std::endl;
    
}