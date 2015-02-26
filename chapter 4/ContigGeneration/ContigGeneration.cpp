/* 
 * File:   ContigGeneration.cpp
 * Author: jdelatorre
 * 
 * Created on 3 de diciembre de 2013, 10:30
 */

#include "ContigGeneration.h"
#include "EulerianGraph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

ContigGeneration::ContigGeneration() {
}

ContigGeneration::ContigGeneration(const ContigGeneration& orig) {
}

ContigGeneration::~ContigGeneration() {
}

ContigGeneration::ContigGeneration(char *filename)
{
    load(filename);
    for(int i=0;i<map_pairs.size();i++)
        std::cout << map_pairs[i] << " ";
    std::cout << std::endl;
    
    EulerianGraph eg(graph);
    get_contigs(eg);

}

void ContigGeneration::load(char * filename)
{
    std::ifstream infile(filename);

    std::string line;
    
    while (std::getline(infile, line))
    {
        // remove spaces 
        line.erase(std::remove_if( line.begin(), line.end(), 
                [](char c){ return (c =='\r' || c == '\n');}), line.end() );
        
        
        std::string from_str = line.substr(0,line.size() - 1);
        std::string to_str =   line.substr(1);
                
        std::vector<std::string>::iterator it_from = std::find(map_pairs.begin(), map_pairs.end(), from_str);        
        int from;
        if(it_from != map_pairs.end()){
            from = (int)std::distance(map_pairs.begin(), it_from);
        } else {
            from = map_pairs.size();
            map_pairs.push_back(from_str);
        }
        
        std::vector<std::string>::iterator it_to = std::find(map_pairs.begin(), map_pairs.end(), to_str);
        int to;
        if(it_to != map_pairs.end()){
            to = (int)std::distance(map_pairs.begin(), it_to);
        } else {
            to = map_pairs.size();
            map_pairs.push_back(to_str);
        }
                
        std::map<int, std::list<int> >::iterator it_m = graph.find(from);
        if(it_m == graph.end()) {
            std::list<int> value;
            value.push_back(to);
            graph.insert(std::pair<int, std::list<int> >(from, value));
        } else {
            std::list<int> & l = it_m->second;
            std::list<int>::iterator it = std::find(l.begin(), l.end(), to);
            if(it == l.end()) l.push_back(to);
        }
    }    
}

void ContigGeneration::get_contigs(EulerianGraph &eg)
{
    for(int i=0;i<map_pairs.size();i++) {
        std::cout << map_pairs[i] << std::endl;
        const int pred = eg.nr_predecessors(i);
        std::cout << "predecessors: " << pred << std::endl;
        if(pred != 1) {
            std::string result = map_pairs[i].substr(0,1);
            int j = i;
            std::cout << "next nodes: ";
            print(graph[j]);
            const int pred_j = eg.nr_predecessors(j);
            while(graph[j].size() == 1 && pred_j <= 1) {
                j = *(graph[j].begin());
                result.append(map_pairs[j].substr(0,1));
            }
            result.append(map_pairs[j].substr(1));
            std::cout << result << std::endl;
        }
    }   
}

void ContigGeneration::print(const std::list<int> &l)
{
    for (std::list<int>::const_iterator iterator = l.begin(), 
         end = l.end(); iterator != end; ++iterator) {
        std::cout << map_pairs[*iterator] << " ";
    }
    std::cout << std::endl;
}