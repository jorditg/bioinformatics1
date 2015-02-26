/* 
 * File:   GibbsSampler.h
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

class GibbsSampler {
public:
    GibbsSampler();
    GibbsSampler(const GibbsSampler& orig);
    virtual ~GibbsSampler();
    GibbsSampler(const char * filename);
    void search();
    
private:
    int iterations;
    int k;    int t;
    std::vector<std::string> dna_str;
    std::mt19937 rng;
    std::uniform_int_distribution<int> *dist;
    std::uniform_int_distribution<int> *dist_t;
    
    std::mt19937 create_seeded_rng();
    inline int get_random_number() {  (*dist)(rng); };
    inline int get_random_motif_index() {  (*dist_t)(rng); };
    Motif & generate_motif(Motif &m);
};

#endif	/* RANDOMIZEDSEARCH_H */

