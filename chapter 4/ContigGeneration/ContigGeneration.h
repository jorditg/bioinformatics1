/* 
 * File:   ContigGeneration.h
 * Author: jdelatorre
 *
 * Created on 3 de diciembre de 2013, 10:30
 */

#ifndef CONTIGGENERATION_H
#define	CONTIGGENERATION_H

#include <vector>
#include <map>
#include <string>
#include <list>
#include "EulerianGraph.h"

class ContigGeneration {
public:
    ContigGeneration();
    ContigGeneration(char * filename);
    ContigGeneration(const ContigGeneration& orig);
    virtual ~ContigGeneration();
    void get_contigs(EulerianGraph &eg);
private:
    void load(char * filename);
    std::map<int, std::list<int> > graph;
    std::vector<std::string> map_pairs;
    void print(const std::list<int> &l);
};

#endif	/* CONTIGGENERATION_H */

