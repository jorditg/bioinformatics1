/* 
 * File:   EulerianGraph.cpp
 * Author: jordi
 * 
 * Created on 25 de noviembre de 2013, 21:49
 */

#include "EulerianGraph.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <map>

EulerianGraph::EulerianGraph() {
}

EulerianGraph::EulerianGraph(const EulerianGraph& orig) {
}

EulerianGraph::~EulerianGraph() {
}

EulerianGraph::EulerianGraph(const char * filename) {
    
    srand((unsigned)time(0)); 
    
    std::ifstream infile(filename);

    std::string line;
    while (std::getline(infile, line))
    {
        // remove spaces 
        line.erase(std::remove_if( line.begin(), line.end(), 
                [](char c){ return (c =='\r' || c == '\n');}), line.end() );
        
        std::vector <std::string> fields;
        split( fields, line, ' ' );
        
        const int from = atoi(fields[0].c_str());
        
        std::list<int> value;
        std::vector <std::string> to;
        split( to, fields[1], ',' );
        for(std::vector<int>::size_type i = 0; i != to.size(); i++) {
            value.push_back(atoi(to[i].c_str()));
        }
        graph.insert(std::pair<int, std::list<int> >(from, value));
    }
    
}


void EulerianGraph::split(std::vector<std::string> &result, std::string str, char delim ) 
{
  std::string tmp;
  std::string::iterator i;
  result.clear();

  for(i = str.begin(); i <= str.end(); ++i) {
    if((const char)*i != delim  && i != str.end()) {
      tmp += *i;
    } else {
      result.push_back(tmp);
      tmp = "";
    }
  }
}

void EulerianGraph::print()
{
    std::map<int,std::list<int> >::iterator it = graph.begin();
    for (it=graph.begin(); it!=graph.end(); ++it) {
        std::cout << it->first << "->";
        std::list<int> &l = it->second;
        std::list<int>::const_iterator iterator = l.begin();
        std::cout << *iterator;
        iterator++;
        while(iterator != l.end()) {
            std::cout << "," << *iterator;
            iterator++;
        }
        std::cout << "\n";
    }
}

int EulerianGraph::get_random_number(int lowest, int highest)
{
    int range=(highest-lowest)+1;
    
    int random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0));
    
    return random_integer;        
}

void EulerianGraph::find_eulerian()
{
    std::map<int, std::list<int> > graph_copy(graph);
    
    graph_copy = graph;
    
    int nr_vertex;
    std::map<int,std::list<int> >::iterator it = graph_copy.begin();
    
    while(it != graph_copy.end()) {
        int first_element = it->first;
        std::list<int>::iterator it_eulerian = std::find(eulerian.begin(), eulerian.end(), it->first);
        int last_element = !first_element;
        //std::cout << first_element;
        if(it_eulerian != eulerian.end()) {
            it_eulerian = eulerian.erase(it_eulerian);
        }
        it_eulerian = eulerian.insert(it_eulerian,first_element);
        it_eulerian++;        
        
        while(first_element != last_element) { 
            std::list<int> &l = it->second;
            
            int nr_vertex2 = l.size();

            if(nr_vertex2 == 1) {
                last_element = *(l.begin());
                //std::cout << "->" << last_element;
                it = graph_copy.erase(it);
                it = graph_copy.find(last_element);                
            } else {
                int rnd = get_random_number(0, nr_vertex2-1);
                std::list<int>::iterator it2 = l.begin();
                int i = 0;
                while (i<rnd) { it2++; i++; }
                last_element = *it2;
                //std::cout << "->" << last_element;            
                l.erase(it2);
                it = graph_copy.find(last_element);
            }        
            it_eulerian = eulerian.insert(it_eulerian,last_element);
            it_eulerian++;
        }
        //std::cout << std::endl;
        it = graph_copy.begin();
        // prepare next iteration
        std::list<int>::const_iterator iter;
        for(iter=eulerian.begin();iter != eulerian.end();iter++) {
            it = graph_copy.find(*iter);
            if(it != graph_copy.end()) { 
                break;
            }
        }
    }
}

void EulerianGraph::find_eulerian(int from, int to)
{
    std::map<int, std::list<int> > graph_copy(graph);
    
    graph_copy = graph;
    
    int nr_vertex;
    std::map<int,std::list<int> >::iterator it = graph_copy.find(from);
    bool begin = true;
    
    while(it != graph_copy.end()) {
        int first_element = it->first;
        std::list<int>::iterator it_eulerian = std::find(eulerian.begin(), eulerian.end(), it->first);
        int last_element = !first_element;
        //std::cout << first_element;
        if(it_eulerian != eulerian.end()) {
            it_eulerian = eulerian.erase(it_eulerian);
        }
        if(!begin) {
            it_eulerian = eulerian.insert(it_eulerian,first_element);
            it_eulerian++;
        }
        
        while(first_element != last_element) { 
            std::list<int> &l = it->second;
            
            int nr_vertex2 = l.size();

            if(nr_vertex2 == 1) {
                last_element = *(l.begin());
                //std::cout << "->" << last_element;
                it = graph_copy.erase(it);
                it = graph_copy.find(last_element);                
            } else {
                std::list<int>::iterator it2;
                if(begin) {
                    it2 = std::find(l.begin(), l.end(), to);
                    begin = false;
                    last_element = to;
                } else {
                    int rnd = get_random_number(0, nr_vertex2-1);
                    it2 = l.begin();
                    int i = 0;
                    while (i<rnd) { it2++; i++; }
                    last_element = *it2;
                }
                //std::cout << "->" << last_element;            
                l.erase(it2);
                it = graph_copy.find(last_element);
            }    

            it_eulerian = eulerian.insert(it_eulerian,last_element);
            it_eulerian++;
        }
        //std::cout << std::endl;
        it = graph_copy.begin();
        // prepare next iteration
        std::list<int>::const_iterator iter;
        for(iter=eulerian.begin();iter != eulerian.end();iter++) {
            it = graph_copy.find(*iter);
            if(it != graph_copy.end()) { 
                break;
            }
        }
    }
}

void EulerianGraph::print_eulerian()
{
    std::list<int>::const_iterator iterator = eulerian.begin(), end = eulerian.end();
    std::cout << *iterator;
    iterator++;
    for (;iterator != end; ++iterator) {
        std::cout << "->" << *iterator;
    }    
    std::cout << std::endl;
}

void EulerianGraph::rebalance_vertexs(int &from, int &to)
{
    std::map<int, int> d;
    
    std::map<int,std::list<int> >::iterator it = graph.begin();
    std::map<int,int>::iterator d_it;
    for (it=graph.begin(); it!=graph.end(); ++it) {
        int from = it->first;
        const std::list<int> &to = it->second;
        d_it = d.find(from);        
        if(d_it != d.end()) {
                d[from] = d[from] + to.size();
        } else {
            d[from] = to.size();
        }
        
                
        for(std::list<int>::const_iterator it = to.begin();it != to.end();it++) {
            int to_v = *it;
            d_it = d.find(to_v);        
            if(d_it != d.end()) {
                d[to_v] = d[to_v] - 1;
            } else {
                d[to_v] = -1;
            }
        }
    }
    
    int vertex_from, vertex_to;
    int count_from=0, count_to=0;
    for (std::map<int, int>::const_iterator it=d.begin(); it!=d.end(); ++it) {
        if(it->second > 0) {
            std::cout << "disbalanced (more from): " << it->first << std::endl;
            vertex_to = it->first;
            count_to++;
            to = vertex_to;
            
        } else if(it->second < 0) {
            std::cout << "disbalanced (more to): " << it->first << std::endl;
            vertex_from = it->first;
            count_from++;
            from = vertex_from;
        }
    }
    // If only one imbalance we convert the path to cycle adding a new edge
    if(count_from == count_to && count_from == 1) {

        std::map<int,std::list<int> >::iterator it_g = graph.find(vertex_from);
        if(it_g != graph.end()) {
            std::list<int> &l = it_g->second;
            l.push_back(vertex_to);
        } else {
            std::list<int> l;            
            l.push_back(vertex_to);
            graph[vertex_from] = l;
        }
    }    
}
