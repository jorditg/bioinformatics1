/* 
 * File:   main.cpp
 * Author: jordi
 *
 * Created on 25 de noviembre de 2013, 22:17
 */

#include <cstdlib>
#include <list>
#include <string>
#include "DNAString.h"

/*
 * 
 */
int main(int argc, char** argv) {
    DNAString d("in.txt");
    d.calculate_composition();
    d.print_composition();
    return 0;
}

