/* 
 * File:   GreedySearch.h
 * Author: jdelatorre
 *
 * Created on 21 de noviembre de 2013, 12:03
 */

#ifndef GREEDYSEARCH_H
#define	GREEDYSEARCH_H

#include <string>
#include <vector>
#include <array>
#include "Motif.h"

class GreedySearch {
public:
    GreedySearch();
    GreedySearch(const GreedySearch& orig);
    virtual ~GreedySearch();
    
    GreedySearch(const char * filename);
    
    int distance(const char * a, const char * b, int len) const;
    void search();
private:
    int k;
    int t;
    std::vector<std::string> dna_str;
    
    void init_motif(Motif &m);
};

#endif	/* GREEDYSEARCH_H */

