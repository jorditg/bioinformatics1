/* 
 * File:   Peptide.h
 * Author: jdelatorre
 *
 * Created on 11 de noviembre de 2013, 13:51
 */

#ifndef PEPTIDE_H
#define	PEPTIDE_H

#include <list>
#include <string>

class Peptide {
public:
    Peptide();    
    Peptide(const Peptide& orig);
    Peptide(const std::string value);
    virtual ~Peptide();
    
    std::list<int> & cyclospectrum(std::list<int> * result, int & nr_cycles);
    std::string toWeightString();
    
    static bool spectrumIsEqual (std::list<int> &spec1, std::list<int> &spec2);
    static bool spectrumIsConsistent(std::list<int> &principal, std::list<int> &secondary, int nr_cycles);
    static int toWeight(const std::string p);
    static inline const char aminoAt(int i) { return amino[i]; };
    static inline const int aminoLen() { return AMINO_LEN; };
    static inline const int weightAt(int i) { return weight[i]; }
    
    inline const std::string toString() const {return peptide;};
private:
    //static const int AMINO_LEN = 20;
    /////////////////////////////////////////////////////////
    ///// WARNING!! AMINO NR. CHANGED TO DO THE EXERCISE/////
    /////////////////////////////////////////////////////////
    static const int AMINO_LEN = 18;
    static const char amino[];
    static const int weight[];
    
    std::string peptide;
    
};

#endif	/* PEPTIDE_H */

