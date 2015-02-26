/* 
 * File:   RandomizedSearch.h
 * Author: jdelatorre
 *
 * Created on 22 de noviembre de 2013, 11:21
 */

#ifndef RANDOMIZEDSEARCH_H
#define	RANDOMIZEDSEARCH_H

#include "Motif.h"

#include <vector>
#include <string>
#include <random>

class RandomizedSearch {
public:
    RandomizedSearch();
    RandomizedSearch(const RandomizedSearch& orig);
    virtual ~RandomizedSearch();
    RandomizedSearch(const char * filename, int iterations);
    void search();
    
private:
    int iterations;
    int k;
    int t;
    std::vector<std::string> dna_str;
    std::mt19937 rng;
    std::uniform_int_distribution<int> *dist;
    
    std::mt19937 create_seeded_rng();
    inline int get_random_number() {  (*dist)(rng); }
    Motif & generate_motif(Motif &m);
};

#endif	/* RANDOMIZEDSEARCH_H */

