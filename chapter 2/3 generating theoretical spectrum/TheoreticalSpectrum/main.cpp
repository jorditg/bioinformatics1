/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 6 de noviembre de 2013, 11:51
 */

#include <iostream>
#include <cstdlib>

#include "Peptide.h"


/*
 * 
 */
int main(int argc, char** argv) {

    const char * peptide = argv[1];
    
    Peptide p(peptide);    
    std::list<std::string *> * list = p.subpeptides();
    std::list<int> weights;
    for (std::list<std::string *>::const_iterator iterator = list->begin(), end = list->end(); iterator != end; ++iterator) {        
        //std::cout << **iterator << std::endl;
        weights.push_back(Peptide::toWeight(**iterator));
    }
    weights.sort();
    std::cout << '0' << ' ';
    for (std::list<int>::iterator it=weights.begin(); it!=weights.end(); ++it)
        std::cout << *it << ' ';
    std::cout << Peptide::toWeight(peptide) << std::endl;
  
    return 0;
}

