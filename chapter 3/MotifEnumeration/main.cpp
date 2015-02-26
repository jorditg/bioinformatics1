/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 19 de noviembre de 2013, 10:27
 */

#include <cstdlib>
#include <iostream>

#include "StringCollection.h"
#include "combinations.h"

/*
 * 
 */
int main(int argc, char** argv) {
    std::string file("in.txt");
    StringCollection sc(file.c_str());
    //sc.find_mutation("GCA");
    
    sc.motif_enumeration();
    //sc.print();
    //sc.motif_enumeration();
    
//    std::string s = "123456789ABCDEFG";
//    std::size_t comb_size = 3;
//    do {
//        std::cout << std::string(s.begin(), s.begin() + comb_size) << std::endl;
//    } while(next_combination(s.begin(),s.begin() + comb_size,s.end()));

//    std::list<std::string> s;
//    StringCollection::mutation_list(1, s);
//    StringCollection::print(s);
    
    return 0;
}

