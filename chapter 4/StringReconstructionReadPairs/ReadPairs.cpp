/* 
 * File:   ReadPairs.cpp
 * Author: jdelatorre
 * 
 * Created on 2 de diciembre de 2013, 15:27
 */

#include "ReadPairs.h"
#include "EulerianGraph.h"

#include <map>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <list>
#include <iostream>
#include <string>


ReadPairs::ReadPairs() {
}

ReadPairs::ReadPairs(const ReadPairs& orig) {
}

ReadPairs::~ReadPairs() {
}

ReadPairs::ReadPairs(char *filename)
{
    load(filename);
    EulerianGraph eg(graph);
    int from, to;
    eg.rebalance_vertexs(from, to);
    eg.find_eulerian(from, to);
    eg.print_eulerian();
    const std::list<int> &l = eg.get_eulerian();
    
    int idx;
    for (std::list<int>::const_iterator iterator = l.begin(), 
         end = l.end(); iterator != end; ++iterator) {
        idx = *iterator;
        std::cout << map_pairs[idx].substr(0,1);
    }
    std::size_t found = map_pairs[idx].find("-");
    std::cout << map_pairs[idx].substr(1,found-1);
    std::list<int>::const_iterator it = l.end();
    it--; // we are now over the last element of the eulerian graph
    for(int i=d;i>=0;i--) it--;
    for(int i=d;i>=0;i--) {std::cout << map_pairs[*it].substr(found+1,1); it++;}
    
    std::cout << map_pairs[*it].substr(found+1) << std::endl;
}

void ReadPairs::load(char * filename)
{
    std::ifstream infile(filename);

    std::string line;
    std::getline(infile, line);    
    d = atoi(line.c_str());
    
    while (std::getline(infile, line))
    {
        // remove spaces 
        line.erase(std::remove_if( line.begin(), line.end(), 
                [](char c){ return (c =='\r' || c == '\n');}), line.end() );
        
        std::vector <std::string> fields;
        split( fields, line, '|' );
        
        std::string from_str = fields[0].substr(0,fields[0].size() - 1) + 
                               "-" + fields[1].substr(0,fields[1].size() - 1);
        std::string to_str =   fields[0].substr(1) + "-" + fields[1].substr(1);
                
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
            l.push_back(to);
        }
    }    
}

void ReadPairs::split(std::vector<std::string> &result, std::string str, char delim ) 
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