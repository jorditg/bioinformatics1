/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 22 de noviembre de 2013, 11:18
 */

#include <cstdlib>
#include "RandomizedSearch.h"


/*
 * 
 */
int main(int argc, char** argv) {
    RandomizedSearch r("in.txt", 1000);
    r.search();
    
    return 0;
}

