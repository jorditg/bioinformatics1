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
    KmerProfile(const std::string dna_str, 
                const std::vector<std::array<float, 4> > prob);
    std::string most_probable_kmer();
    float kmer_prob(std::string kmer); 
    void print_probabilities();
    std::string random_with_probabilities(float random);
    
    
private:
    std::vector<std::array<float, 4> > prob;
    std::string dna_str;
};

#endif	/* KMERPROFILE_H */

