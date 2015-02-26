/* 
 * File:   UniversalCircularString.cpp
 * Author: jordi
 * 
 * Created on 1 de diciembre de 2013, 22:22
 */

#include "UniversalCircularString.h"
#include "EulerianGraph.h"

#include <iostream>
#include <map>
#include <list>

UniversalCircularString::UniversalCircularString(unsigned int k) {
    generate_graph(k);
    eg->find_eulerian();
    eg->print_eulerian();
    print();
}

UniversalCircularString::UniversalCircularString(const UniversalCircularString& orig) {
}

UniversalCircularString::~UniversalCircularString() {
    delete eg;
}

void UniversalCircularString::generate_graph(const unsigned int k)
{
    this->k = k;
    
    const unsigned int mask = (1 << (k-1)) - 1;
    std::map<int, std::list<int> > graph;
    
    unsigned int len = 1 << k;
    for(int i=0;i<len;i++) {
        const unsigned int from = (i >> 1);
        const unsigned int to = (i & mask);
        
        //std::cout << from << " -> " << to << std::endl;
        
        std::map<int,std::list<int> >::iterator it_g = graph.find(from);
        if(it_g != graph.end()) {
            std::list<int> &l = it_g->second;
            l.push_back(to);
        } else {
            std::list<int> l;            
            l.push_back(to);
            graph[from] = l;
        }
    }
    
    eg = new EulerianGraph(graph);
}

void UniversalCircularString::print()
{
    const std::list<int> &l = eg->get_eulerian();
    
    int v;
    std::list<int>::const_iterator iterator = l.begin(), end = l.end();
    iterator++;
    for (; iterator != end; ++iterator) {
        v =  *iterator;
        std::cout << (v >> (k-2));
    }
    std::cout << std::endl;
}
