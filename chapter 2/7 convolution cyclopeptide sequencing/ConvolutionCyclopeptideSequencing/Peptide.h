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
    Peptide(const std::string &value);
    virtual ~Peptide();
    
    std::list<int> & cyclospectrum(std::list<int> * result, int & nr_cycles);
    std::string toWeightString();    
    inline const std::string toString() const {return peptide;};
    inline int getWeight() const {return w;};
    inline int getScore() const { return score;};
    int setScore(const std::list<int> *spectrum);
    
    static bool spectrumIsEqual (std::list<int> &spec1, std::list<int> &spec2);
    static bool spectrumIsConsistent(std::list<int> &principal, std::list<int> &secondary, int nr_cycles);
    int toWeight(const std::string p);
    static inline const char aminoAt(int i) { return amino[i]; };
    static inline const int aminoLen() { return AMINO_LEN; };
    static inline const int weightAt(int i) { return weight[i]; }
    static void printSpectrum(std::list<int> &spectrum);
    static int loadSpectrum(const char * filename, std::list<int> &spectrum);
    static int peptideMass(const std::list<int> &spectrum);
    static void spectralConvolution(const std::list<int> &spectrum, std::list<int> &convolution);
    static inline void setNewAminoArray(char am[], int we[], int len) {AMINO_LEN = len; amino = am; weight = we;};
    
private:
    //static const int AMINO_LEN = 20;
    static const int AMINO_LEN_default = 144;
    static const char amino_default[];
    static const int weight_default[];

    static int AMINO_LEN;
    static char *amino;
    static int *weight;
    
    std::string peptide;
    int w;
    int score;
    
};

#endif	/* PEPTIDE_H */

