/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 27 de noviembre de 2013, 10:14
 */

#include <cstdlib>

#include "EulerianGraph.h"


/*
 * 
 */
int main(int argc, char** argv) {
    EulerianGraph e("in.txt");
    e.find_eulerian();
    e.print_eulerian();
    
    return 0;
}

