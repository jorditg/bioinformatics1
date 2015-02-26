/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 8 de noviembre de 2013, 10:01
 */

#include <cstdlib>
#include <list>
#include <iostream>
#include "Peptide.h"

void expand(std::list<int> &l, std::list<unsigned long> &c);
void treat_next_list(std::list<int> & searchv, int N, std::list<unsigned long> &c, unsigned long &total_count);

/*
 * 
 */
int main(int argc, char** argv) {
    unsigned long total_count = 0;
        
    const int N = atoi(argv[1]);
    
    //std::list<Peptide *> searchv;
    std::list<int> searchv;
    std::list<unsigned long> c;
    // init search
    //searchv.push_back(new Peptide(""));
    searchv.push_back(0);
    c.push_back(1);
    while(!searchv.empty()) {
        expand(searchv, c);
        // treat next list
        treat_next_list(searchv, N, c, total_count);
    }
    
    std::cout << total_count << std::endl;
   
    return 0;
}

void treat_next_list(std::list<int> & searchv, int N, std::list<unsigned long> &c, unsigned long &total_count)
{
    std::list<int>::iterator it = searchv.begin();
    std::list<unsigned long>::iterator itc = c.begin();
    while(it != searchv.end()) {
        int weight = *it;
        if( weight > N) {    // this peptide should be removed from candidates to solution
            it = searchv.erase(it);
            itc = c.erase(itc);
        } else if (weight == N) {   // FOUND a solution
            //std::cout << actual->toString() << std::endl;
            total_count += *itc;
            it = searchv.erase(it);
            itc = c.erase(itc);
        } else {
            it++;
            itc++;
        } 
    }
}

void expand(std::list<int> &l, std::list<unsigned long> &c)
{
    std::list<int>::iterator itl = l.begin(), end = l.end();
    std::list<unsigned long>::iterator itc = c.begin();
    while (itl != end) {
        int actual = *itl;
        unsigned long count = *itc;
        for(int i=0;i<Peptide::aminoLen();i++) {
            int weight = actual + Peptide::weightAt(i);
            l.insert(itl, weight);            
            c.insert(itc, count);
        }
        itl = l.erase(itl);
        itc = c.erase(itc);
    }
    
    itl = l.begin();
    itc = c.begin();
    
    while (itl != l.end()) {
        std::list<int>::iterator itl2 = itl;
        std::list<unsigned long>::iterator itc2 = itc;
        itl2++;
        itc2++;
        while(itl2 != l.end()) {
            if(*itl2 == *itl) {
                *itc += *itc2;
                itl2 = l.erase(itl2);
                itc2 = c.erase(itc2);
            } else {
                itl2++;
                itc2++;
            }
        }
        itl++;
        itc++;
    }
}
