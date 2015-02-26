/* 
 * File:   main.cpp
 * Author: jdelatorre
 *
 * Created on 11 de noviembre de 2013, 14:10
 */

#include "Peptide.h"
#include <cstdlib>
#include <list>
#include <string>
#include <iostream>
#include <fstream>

void print(std::list<int> &l);
void print(std::list<std::string> &l);
void sequence(std::list<Peptide *> &l, std::list<int> &result_spec, std::list<std::string> &result);
void expand(std::list<Peptide *> &l);
int load_spectrum(const char * filename, std::list<int> &spectrum);

/*
 * 
 */
int main(int argc, char** argv) 
{
    std::list<int> spectrum, s2;
    std::list<Peptide *> l;
    std::list<std::string> result;
    int nr_cycles = 0;

    load_spectrum(argv[1], spectrum);
    print(spectrum);
    
//    Peptide p("LEQ");
//    p.cyclospectrum(&s2, nr_cycles);
//    std::cout << "Nr. cycles : " << nr_cycles << std::endl;
//    print(s2);
//    bool r = Peptide::spectrumIsConsistent(spectrum, s2, nr_cycles);
//    std::cout << "Consistent: " << r << std::endl;

    
    sequence(l, spectrum, result);
    print(result);
            
    return 0;
}

void print(std::list<int> &l)
{
    for (std::list<int>::const_iterator iterator = l.begin(), 
         end = l.end(); iterator != end; ++iterator) {
        std::cout << *iterator << " ";
    }
    std::cout << std::endl;
}

void print(std::list<std::string> &l)
{
    for (std::list<std::string>::const_iterator iterator = l.begin(), 
         end = l.end(); iterator != end; ++iterator) {
        std::cout << *iterator << " ";
    }
    std::cout << std::endl;
}


void sequence(std::list<Peptide *> &l, std::list<int> &result_spec, std::list<std::string> &result)
{
    std::list<int> cyclospec;
    int nr_cycles;
    
    result.clear();
    l.clear();
    l.push_back(new Peptide(""));
    while(!l.empty())
    {
        expand(l);
        std::list<Peptide *>::iterator iterator = l.begin(), end = l.end();
        while (iterator != end) {
            Peptide *p = *iterator;
            
            cyclospec.clear();
            p->cyclospectrum(&cyclospec, nr_cycles);
            
            //std::cout << p->toString() << " ";
            //print(cyclospec);
            
            if(Peptide::spectrumIsEqual (result_spec, cyclospec)) {
                result.push_back(p->toWeightString());
                iterator = l.erase(iterator);
                delete p;
            } else if(!Peptide::spectrumIsConsistent(result_spec, cyclospec, nr_cycles)) {
                iterator = l.erase(iterator);
                delete p;
            } else {
                iterator++;
            }
        }
    }
    result.sort();
    result.unique();
}

void expand(std::list<Peptide *> &l)
{
    std::list<Peptide *>::iterator iterator = l.begin(), end = l.end();
    while (iterator != end) {
        Peptide * actual = *iterator;
        for(int i=0;i<Peptide::aminoLen();i++) {
            std::string pep(actual->toString());
            pep.append(1, Peptide::aminoAt(i));
            Peptide *newpep = new Peptide(pep);
            l.insert(iterator, newpep);            
        }
        delete *iterator;
        iterator = l.erase(iterator);
    }
}

int load_spectrum(const char * filename, std::list<int> &spectrum)
{
    int i;
    std::ifstream infile(filename, std::ifstream::in);

    if (!infile) {
        std::cout << "There was a problem opening file "
             << filename
             << " for reading."
             << std::endl;
        return 0;
    }

    while (infile >> i) spectrum.push_back(i);
    
    return 0;
    
}
