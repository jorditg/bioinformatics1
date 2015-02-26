/* 
 * File:   DNAStringGenerator.cpp
 * Author: jdelatorre
 * 
 * Created on 20 de noviembre de 2013, 14:38
 */

#include "DNAStringGenerator.h"

const std::string DNAStringGenerator::end_value = "END";


DNAStringGenerator::~DNAStringGenerator()
{

}

void DNAStringGenerator::next()
{
    if (actual == last || actual == end_value) { 
        actual = end_value; 
    } else {  
        for(int i=actual.length()-1;i>=0;i--) {
            char c = next_char(actual[i]);
            actual.replace(i,1,1,c);
            if(c != 'A') break;
        }   
    }
}

