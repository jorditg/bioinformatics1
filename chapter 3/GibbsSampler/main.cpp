/* 
 * File:   main.cpp
 * Author: jordi
 *
 * Created on 24 de noviembre de 2013, 9:37
 */

#include <cstdlib>

#include "GibbsSampler.h"
#include <string>

/*
 * 
 */
int main(int argc, char** argv) {
    GibbsSampler s("in2.txt");
    s.search();
    return 0;
}

