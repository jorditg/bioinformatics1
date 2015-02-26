/* 
 * File:   MedianString.cpp
 * Author: jdelatorre
 * 
 * Created on 20 de noviembre de 2013, 16:49
 */

#include "MedianString.h"
#include "DNAStringGenerator.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <string>

MedianString::MedianString() {
}

MedianString::MedianString(const MedianString& orig) {
}

MedianString::~MedianString() {
}

MedianString::MedianString(const char * filename) {
    std::ifstream infile(filename);

    std::string line;
    std::getline(infile, line);
    std::istringstream iss(line);
    iss >> k;
    while (std::getline(infile, line))
    {
        // remove spaces 
        line.erase(std::remove_if( line.begin(), line.end(), 
                [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), line.end() );
        str_col.push_back(line);
    }
}


int MedianString::distance(const char * a, const char * b, int len) const
{
    int dist = 0;
    for(int i=0;i<len;i++) {
        if(a[i] != b[i])
            dist++;
    }
    return dist;
}

void MedianString::find_kmer()
{
    DNAStringGenerator sg(k);
    
    std::string best_pattern;
    best_pattern.assign(k,'A');
    
    int min_dist = 99999;
    while(!sg.end())
    {
        std::string actual_kmer = sg.get_value();
        //std::cout << actual_kmer << std::endl;
        int actual_min_dist = 0;
        for(std::vector<std::string>::size_type i = 0; i != str_col.size(); i++) {    
            const int len = str_col[i].size();
            const int end = len - k + 1;
            int partial_min_dist = 99999;
            for(int j = 0;j<end;j++) {
                std::string kmer = str_col[i].substr(j, k);
                int d = distance(actual_kmer.c_str(), kmer.c_str(), k);
                if(d < partial_min_dist) partial_min_dist = d;
                if(d==0) break; // for faster loop
            }
            actual_min_dist += partial_min_dist;
            //std::cout << partial_min_dist << " ";
        }
        //std::cout << std::endl;
        
        if(actual_min_dist < min_dist) {
            min_dist = actual_min_dist;
            best_pattern = actual_kmer;
        }
        sg.next();
    }
    std::cout << best_pattern << std::endl;
}
