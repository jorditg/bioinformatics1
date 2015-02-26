/* 
 * File:   Profile.h
 * Author: jordi
 *
 * Created on 21 de noviembre de 2013, 6:32
 */

#ifndef KMERPROFILE_H
#define	KMERPROFILE_H

#include <vector>
#include <array>
#include <string>


class KmerProfile {
public:
    KmerProfile(const KmerProfile& orig);
    virtual ~KmerProfile();    
    KmerProfile(const char *filename);
    std::string most_probable_kmer();
    float kmer_prob(std::string kmer);
    
private:
    int k;
    std::vector<std::array<float, 4> > prob;
    std::vector<char> char_v;
    std::string dna_str;
};

#endif	/* KMERPROFILE_H */

