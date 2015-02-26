/* 
 * File:   Motif.h
 * Author: jdelatorre
 *
 * Created on 21 de noviembre de 2013, 14:36
 */

#ifndef MOTIF_H
#define	MOTIF_H

#include <string>
#include <vector>
#include <array>

class Motif {
public:
    Motif();
    Motif(const Motif& orig);
    virtual ~Motif();
    
    void calculate_probabilities();
    void calculate_probabilities_with_pseudocounts();
    void calculate_probabilities_with_pseudocounts_without(int j);
    void insert(std::string &val);
    void clear();
    int score();
    void print();
    inline const std::vector<std::array<float, 4> > & get_prob() const { return prob; };
    void print_probabilities();
    inline std::string substitute(int j, std::string value) {std::string old= m[j]; m[j] = value; return m[j];};
private:
    inline char idx2char(int idx) {switch(idx) {case 0: return 'A'; break; case 1: return 'C'; break; 
                              case 2: return 'G'; break; case 3: return 'T'; break; }};
    std::vector<std::string> m;
    std::vector<std::array<float, 4> > prob;
};

#endif	/* MOTIF_H */

