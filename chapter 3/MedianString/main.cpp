/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 20 de noviembre de 2013, 14:37
 */

#include <cstdlib>
#include <iostream>
#include "DNAStringGenerator.h"
#include "MedianString.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    MedianString m("in.txt");
    m.find_kmer();
    
    return 0;
}

