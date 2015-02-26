/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 16 de enero de 2014, 14:39
 */
#include "inverse_bw.h"

#include <cstdlib>
#include <iostream>
#include "cyclic_string.h"
#include <fstream>
#include <string>
#include <cerrno>
#include <vector>

std::string get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

struct op_comp_suffix_array
{
    op_comp_suffix_array(const std::string & str) : s(str) {};
    bool operator() (const unsigned int a, const unsigned int b) {
            int i = 0;
            const int len = s.size();
            while(s[(a+i)%len] == s[(b+i)%len] && i < len) i++;
            if(i<len) return s[a+i] < s[b+i];
            else return false;
    };
    const std::string & s;
};

/*
 * 
 */
int main(int argc, char** argv) {

    std::string str = get_file_contents("in.txt");
    std::cout << str << std::endl;
    str.erase(str.find_last_not_of(" \n\r\t")+1);
    cyclic_string cs(str);
    std::string bwt = cs.burrows_wheeler_transform();
    std::cout << bwt << std::endl;

//    std::string bwt = "GGCGCCGC$TAGTCACACACGCCGTA";
    inverse_bw ibwt(bwt);    
//    ibwt.reverse();

    
    std::vector<int> suffix_array;
    for(int i=0;i<str.size();i++) {
        suffix_array.push_back(i);
    }
    op_comp_suffix_array op(str);
    std::sort(suffix_array.begin(), suffix_array.end(), op);
//    for(int i=0;i<suffix_array.size();i++)
//        std::cout << suffix_array[i] << " ";
    std::string s = "ATCG GGGT ";
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        //std::cout << ibwt.better_matches(token) << " ";
        std::pair<int, int> top_bottom = ibwt.better_matches_top_bottom(token);
        for(int i=top_bottom.first;i<=top_bottom.second;i++)
            std::cout << suffix_array[i] << " ";
        s.erase(0, pos + delimiter.length());
    }
    //std::cout << std::endl;
    
    return 0;
}

