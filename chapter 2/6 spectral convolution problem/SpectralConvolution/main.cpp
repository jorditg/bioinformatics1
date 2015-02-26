/* 
 * File:   main.cpp
 * Author: jordi
 *
 * Created on 16 de noviembre de 2013, 23:20
 */

#include <cstdlib>
#include "Peptide.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    std::list<int> spectrum, convolution;
    
    Peptide::loadSpectrum("in.txt", spectrum);
    Peptide::spectralConvolution(spectrum, convolution);
    
    Peptide::printSpectrum(convolution);
    
    return 0;
}

