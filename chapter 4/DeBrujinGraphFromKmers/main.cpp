/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 26 de noviembre de 2013, 14:36
 */

#include <cstdlib>

#include "DNAString.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    DNAString d("in.txt");
    d.calculate_de_brujin_graph();
    d.print_de_brujin_graph();
    
    return 0;
}

