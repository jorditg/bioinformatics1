/* 
 * File:   LongestPathDAG.cpp
 * Author: jordi
 * 
 * Created on 12 de diciembre de 2013, 15:06
 */

#include "LongestPathDAG.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>
#include <cstdlib>

LongestPathDAG::LongestPathDAG() {
    load("in4.txt");
    doit();
}

LongestPathDAG::LongestPathDAG(const LongestPathDAG& orig) {
}

LongestPathDAG::~LongestPathDAG() {
}

void LongestPathDAG::load(const char * filename) {
    std::ifstream infile(filename);

    std::string line;
    
    std::getline(infile, line);
    from = atoi(line.c_str());
    
    std::getline(infile, line);
    to = atoi(line.c_str());
    
    while (std::getline(infile, line))
    {
        // remove spaces 
        line.erase(std::remove_if( line.begin(), line.end(), 
                [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), line.end() );
        
        std::string::size_type pos = line.find_first_of('-');
        std::string token = line.substr(0, pos);
        int f = atoi(token.c_str());
        std::string::size_type pos1 = line.find_first_of('>');
        std::string::size_type pos2 = line.find_first_of(':');
        token = line.substr(pos1+1, pos2);
        int t = atoi(token.c_str());
        token = line.substr(pos2+1, line.size());
        int w = atoi(token.c_str());
        
        A.insert_edge(f,t);

        std::pair <t_edge,int> in;  
        t_edge te = {f,t};
        in = std::make_pair (te,w);
        weight.insert(in);        
    }
}

void LongestPathDAG::doit() {
   s.resize(A.num_nodes());
   backtrack.resize(A.num_nodes());
   for(int i=0;i<A.num_nodes();i++) { 
        s[i] = -1; // -1 => not initialized
        backtrack[i] = -1;
   }
   
   // initialize root nodes with s = 0
   for ( Graph::const_iterator p = A.begin(); p != A.end(); p++) {
          int d_i = A.in_degree(p);
          if(d_i == 0) {
              // initialize s to zero
              s[p->first] = 0;
          }
   }

   while(true) {
       bool s_completed = true;
       for ( Graph::const_iterator p = A.begin(); p != A.end(); p++) {            
            int d_i = A.in_degree(p);            
            if(d_i > 0 && s[p->first] == -1) {
                Graph::vertex_set S_i = A.in_neighbors(p);
                int max = -1;
                int idx = -1;
                bool update_allowed = true;
                for (Graph::vertex_set::const_iterator t = S_i.begin(); t !=S_i.end(); t++) {
                    int val = s[*t];
                    if(val == -1) { // not already initialized
                        update_allowed = false;
                        break;
                    }
                    t_edge e = {*t,p->first};
                    int act_val = val + weight[e];
                    if(act_val > max) {
                        max = act_val;
                        idx = *t;
                    }    
                }
                if(update_allowed) {
                        s[p->first] = max;
                        backtrack[p->first] = idx;
                }
            }
            if(s_completed && s[p->first] == -1) s_completed = false;
       }
       if(s_completed)
           break;
   }
   
   
   for ( Graph::const_iterator p = A.begin(); p != A.end(); p++) {
       std::cout << p->first << " " << backtrack[p->first] << " " << s[p->first] << "\n";
   }
   
   std::cout << s[to] - s[from] << "\n";
   
   std::list<int> path;
   int i = to;
   path.push_back(to);
   while(backtrack[i] != from) {
       path.push_back(backtrack[i]);
       i = backtrack[i];
   }
   path.push_back(from);
   
   std::list<int>::const_iterator iterator = path.end(), end = path.begin();
   iterator--;
   for (; iterator != end; --iterator) {
    std::cout << *iterator << "->";
   }
   std::cout << *(path.begin()) << std::endl;
}
