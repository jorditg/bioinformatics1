/* 
 * File:   inverse_bw.h
 * Author: jordi
 *
 * Created on 19 de enero de 2014, 20:53
 */

#ifndef INVERSE_BW_H
#define	INVERSE_BW_H

#include <string>
#include <vector>
#include <map>

class inverse_bw {
public:
    inverse_bw(const std::string &str);
    inverse_bw(const inverse_bw& orig);
    virtual ~inverse_bw();
    
    int matches(std::string &pattern);
    std::pair<int, int> better_matches_top_bottom(std::string &pattern);
    int better_matches(std::string &pattern);
    void print_suffix_array(int k);
    void reverse();
private:
    int count_last_col(char symbol, int top);
    
    struct op_comp
    {
        op_comp(const std::string & str) : bwt(str) {};
        bool operator() (const unsigned int a, const unsigned int b) {
            if(bwt[a] == bwt[b]) 
                return a<b;
            else 
                return bwt[a]<bwt[b];
//            int i = 0;
//            const int len = bwt.size();
//            while(bwt[(a+i)%len] == bwt[(b+i)%len] && i < len) i++;
//            if(i<len) return bwt[a+i] < bwt[b+i];
//            else return false;
        };
        const std::string & bwt;
    };

    op_comp op;    // functor for comparison operator
    
    const std::string &bwt;           // burrows wheeler tranform
    std::vector<unsigned int> si;        // sorted bwt indexes    
    std::vector<unsigned int> last2first;
    std::vector<unsigned int> sa;   
    std::map<char, unsigned int> first_occurrence;
};

#endif	/* INVERSE_BW_H */

