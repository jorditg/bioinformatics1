/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 26 de noviembre de 2013, 9:34
 */

#include <cstdlib>

#include "DNAString.h"

/*
 * 
 */
int main(int argc, char** argv) {
    DNAString d(argv[1]);
    d.string_reconstruct();
    d.print_results();
    return 0;
}

