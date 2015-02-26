/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 21 de noviembre de 2013, 10:22
 */

#include <cstdlib>
#include <iostream>
#include "KmerProfile.h"


/*
 * 
 */
int main(int argc, char** argv) {

    const char * filename = "in.txt";
    KmerProfile p(filename);
    
    std::cout << p.most_probable_kmer();
    
    return 0;
}

