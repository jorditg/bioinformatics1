/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 21 de noviembre de 2013, 11:19
 */

#include <cstdlib>
#include <iostream>

#include "GreedySearch.h"
#include "KmerProfile.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
   GreedySearch s("in.txt");
   s.search();
//    Motif m;
//    std::string s("ACCT");
//    m.insert(s);
//    std::string t("ATGT");
//    m.insert(t);
//    std::string u("GCGT");
//    m.insert(u);
//    std::string v("ACGA");
//    m.insert(v);
//    std::string w("AGGT");
//    m.insert(w);
//
//    m.calculate_probabilities_with_pseudocounts();
//    m.print_probabilities();
//    std::cout << m.score() << std::endl;


//    std::vector<std::array<float, 4> > prob;
//    
//    std::array<float, 4> a = {0.2,0.4,0.3,0.1};
//    prob.push_back(a);
//    std::array<float, 4> b = {0.2,0.3,0.3,0.2};
//        prob.push_back(b);
//    std::array<float, 4> c =   {0.3,0.1,0.5,0.1};
//        prob.push_back(c);
//    std::array<float, 4> d= {0.2,0.5,0.2,0.1};
//       prob.push_back(d);
//    std::array<float, 4> e= {0.3,0.1,0.4,0.2};
//       prob.push_back(e);
//       
//    std::string dna_str("ACCTGTTTATTGCCTAAGTTCCGAACAAACCCAATATAGCCCGAGGGCCT");
//    KmerProfile p(dna_str, prob);
//    std::cout << p.most_probable_kmer();
    return 0;
}









