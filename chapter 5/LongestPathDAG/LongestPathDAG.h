/* 
 * File:   LongestPathDAG.h
 * Author: jordi
 *
 * Created on 12 de diciembre de 2013, 15:06
 */

#ifndef LONGESTPATHDAG_H
#define	LONGESTPATHDAG_H

#include "ngraph.hpp"

using namespace NGraph;
 
class LongestPathDAG {

    typedef std::pair<int, int> t_edge;

public:
    LongestPathDAG();
    LongestPathDAG(const LongestPathDAG& orig);
    virtual ~LongestPathDAG();
private:
    std::map<t_edge, int> weight;    
    std::vector<int> s;
    std::vector<int> backtrack;
    Graph A;
    int from;
    int to;
    
    void doit();
    void load(const char * filename);
};

#endif	/* LONGESTPATHDAG_H */

