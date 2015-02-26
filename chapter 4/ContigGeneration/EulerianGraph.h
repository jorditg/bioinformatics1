/* 
 * File:   EulerianGraph.h
 * Author: jordi
 *
 * Created on 25 de noviembre de 2013, 21:49
 */

#ifndef DNASTRING_H
#define	DNASTRING_H

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <map>

class EulerianGraph {
public:
    EulerianGraph();
    EulerianGraph(const EulerianGraph& orig);
    virtual ~EulerianGraph();
    EulerianGraph(const char * filename);
    inline EulerianGraph(const std::map<int, std::list<int> > & graph) {this->graph = graph;};
    
    void find_eulerian();
    void find_eulerian(int from, int to);
    void print_eulerian();
    void print();    
    void rebalance_vertexs(int &from, int &to);
    inline const std::list<int> & get_eulerian() const {return eulerian;};
    int nr_predecessors(int node);
private:
    void split(std::vector<std::string> &result, std::string str, char delim );
    int get_random_number(int lowest, int highest);
    void print(const std::list<int> &l);

    std::map<int, std::list<int> > graph;
    std::list<int> eulerian;
    
};

#endif	/* DNASTRING_H */

