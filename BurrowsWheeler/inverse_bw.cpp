/* 
 * File:   inverse_bw.cpp
 * Author: jordi
 * 
 * Created on 19 de enero de 2014, 20:53
 */

#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <iostream>

#include "inverse_bw.h"

inverse_bw::inverse_bw(const std::string &str) : bwt(str), op(str) {
    si.reserve(str.size());
    for(int i=0;i<str.size();i++) {
        si.push_back(i);
    }
    sa = si;
    std::sort(si.begin(), si.end(), op);
    
//    for(int i=0;i<si.size();i++)
//        std::cout << si[i] << " ";
//    std::cout << std::endl;

    last2first = si;
    for(int i=0;i<si.size();i++) {
        last2first[si[i]] = i;
        std::map<char, unsigned int>::iterator it = first_occurrence.find(bwt[si[i]]);
        if(it == first_occurrence.end())
            first_occurrence.insert(std::pair<char, unsigned int>(bwt[si[i]], i));
    }    
    
//    for(int i=0;i<last2first.size();i++)
//        std::cout << last2first[i] << " ";
//    std::cout << std::endl;
}

inverse_bw::inverse_bw(const inverse_bw& orig) : bwt(orig.bwt), op(orig.bwt) {
}

inverse_bw::~inverse_bw() {
}

void inverse_bw::reverse() {        
    int i = 0;
    while(bwt[i] != '$') i++;
    int idx = si[i];
    i = 0;
    while(i<bwt.size()) {
        std::cout << bwt[idx];
        idx = si[idx];
        i++;
    }
    std::cout << std::endl;
}

int inverse_bw::matches(std::string &pattern) {    
    std::string p(pattern);    
    int top = 0;
    int bottom = bwt.size()-1;    
    while(top<=bottom) {
        if(p.size() != 0) {
            char symbol = p[p.size()-1];
            p.resize(p.size()-1);
            while(bwt[top] != symbol && top <= bottom) top++;
            while(bwt[bottom] != symbol && top <= bottom) bottom--;
            if(top>bottom) return 0;
            top = last2first[top];
            bottom = last2first[bottom];
        } else {
            return bottom - top + 1;
        }
    }    
}

int inverse_bw::better_matches(std::string &pattern) {    
    std::pair<int, int> r = better_matches_top_bottom(pattern);
    return r.second - r.first + 1;
}

std::pair<int, int> inverse_bw::better_matches_top_bottom(std::string &pattern) {    
    std::string p(pattern);    
    int top = 0;
    int bottom = bwt.size()-1;    
    while(top<=bottom) {
        if(p.size() != 0) {
            char symbol = p[p.size()-1];
            p.resize(p.size()-1);
            while(bwt[top] != symbol && top <= bottom) top++;
            while(bwt[bottom] != symbol && top <= bottom) bottom--;
            if(top>bottom) return std::pair<int, int>(0, -1);
            top = first_occurrence[symbol] + count_last_col(symbol, top);
            bottom = first_occurrence[symbol] + count_last_col(symbol, bottom+1) - 1;
        } else { 
            return std::pair<int, int>(top, bottom);
        }
    }    
}


int inverse_bw::count_last_col(char symbol, int top) {
    int c = 0;
    for(int i=0;i<top;i++)
        if(bwt[i] == symbol) c++;
    return c;
}

void inverse_bw::print_suffix_array(int k) {
    for(int i=0;i<si.size();i++) {
        int mod = si[i]%k;
        if(mod == 0)
            std::cout << i << "," << si[i] << std::endl;
    }
}
