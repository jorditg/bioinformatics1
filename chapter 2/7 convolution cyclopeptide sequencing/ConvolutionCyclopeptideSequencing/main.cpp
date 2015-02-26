/* 
 * File:   main.cpp
 * Author: jordi
 *
 * Created on 17 de noviembre de 2013, 19:18
 */

#include <cstdlib>
#include <iostream>

#include "Peptide.h"

struct amino_freq {
    int amino;
    int freq;
    
    inline amino_freq() {};
    inline amino_freq(int amino, int freq) {this->amino = amino; this->freq=freq;};
    inline amino_freq(const amino_freq& a) {this->amino = a.amino; this->freq = a.freq;};
    
    inline bool operator<(const amino_freq & b) {return this->freq > b.freq;};
};    

void get_most_frequent_amino(std::list<int> &convolution, int M, std::list<int> &result);

void print(std::list<std::string> &l);
void sequence(std::list<Peptide *> &leaderboard, std::list<int> *result_spec, std::list<std::string> &result, int N);
void expand(std::list<Peptide *> &l, std::list<int> *result_spec);
bool petide_score_compare(const Peptide * const & a, const Peptide * const & b);
void cut_leaderboard(std::list<Peptide *> &leaderboard, int N);
void printLeaderboard(std::list<Peptide *> &leaderboard);



/*
 * 
 */
int main(int argc, char** argv) {
    std::list<int> spectrum, convolution, result;
    Peptide::loadSpectrum("in.txt", spectrum);
    spectrum.sort();
    Peptide::spectralConvolution(spectrum, convolution);
    
    std::cout << "Spectrum:" << std::endl;
    Peptide::printSpectrum(spectrum);
    
    //std::cout << "Convolution:" << std::endl;
    //Peptide::printSpectrum(convolution);
    
    int M = 20;
    int N = 1000;
    
    get_most_frequent_amino(convolution, M, result);

    int L = result.size();
    int * we = new int[L];
    char * am = new char[L];
        
    int j = 0;
    for (std::list<int>::const_iterator iterator = result.begin(), end = result.end(); iterator != end; ++iterator) {
        we[j] = *iterator;
        am[j] = (char) *iterator;
        j++;
    } 
    L = result.size();
   
    Peptide::setNewAminoArray(am, we, L);
    
//    for(int i=0;i<L;i++)
//        std::cout << (int) am[i] << " " << we[i] << "|";
//    std::cout << std::endl;
    
    std::list<Peptide *> l;
    std::list<std::string> res;
    
    sequence(l, &spectrum, res, N);    
    print(res);
    
    delete[] we;
    delete[] am;
    
    return 0;
}

void get_most_frequent_amino(std::list<int> &convolution, int M, std::list<int> &result)
{
    
    if(M == 0) return;
    
    std::list<amino_freq> element;
    // we sort the convolution and count the M most frequent elements
    convolution.sort();
    //Peptide::printSpectrum(convolution);
    
    std::list<int>::const_iterator iterator = convolution.begin(), end = convolution.end();
    while(iterator != end) {
        int actual = *iterator;
        int count = 0;
        while(actual == *iterator) { count++; iterator++; } 
        if(actual >=57 && actual < 200) element.push_back(amino_freq(actual, count));
    }
    
    element.sort();
    
    int i = 0;
    int freq_M_element = 0;
    
    for (std::list<amino_freq>::const_iterator iterator = element.begin(), end = element.end(); iterator != end; ++iterator) {
        const amino_freq &v = *iterator;
        i++;
        if(i <= M || v.freq == freq_M_element) result.push_back(v.amino); else break;
        if(i == M) freq_M_element = v.freq;
    }
    result.sort();
}

void print(std::list<std::string> &l)
{
    for (std::list<std::string>::const_iterator iterator = l.begin(), 
         end = l.end(); iterator != end; ++iterator) {
        std::cout << *iterator << " ";
    }
    std::cout << std::endl;
}


void sequence(std::list<Peptide *> &leaderboard, std::list<int> *result_spec, std::list<std::string> &result, int N)
{
    const int parent_mass = Peptide::peptideMass(*result_spec);    
    
    //std::cout << "Spectrum: (inside sequence)" << std::endl;
    result_spec->sort();
    //Peptide::printSpectrum(*result_spec);
    
    leaderboard.clear();
    leaderboard.push_back(new Peptide(""));
    
    Peptide * leader = *(leaderboard.begin());
    int leader_score = leader->getScore();
    std::string leader_str;
    
    while(!leaderboard.empty())
    {
        expand(leaderboard, result_spec);
        std::list<Peptide *>::iterator iterator = leaderboard.begin(), end = leaderboard.end();
        while (iterator != end) {
            Peptide *p = *iterator;
            
            //std::cout << p->toString() << " ";
            //print(cyclospec);
            const std::string &p_str = p->toString();
            int p_weight = p->getWeight();
            if(p_weight == parent_mass) {
                int p_score = p->getScore();
                if(p_score > leader_score) {
                    leader_str = p->toWeightString();
                    leader_score = p_score;   
                    result.clear();
                    result.push_back(p->toWeightString());
                } else if(p_score == leader_score) {
                    result.push_back(p->toWeightString());
                }
                iterator++;
            } else if(p_weight > parent_mass) {
                iterator = leaderboard.erase(iterator);                
                delete p;
            } else {
                iterator++;
            }
        }
        //printLeaderboard(leaderboard);
        cut_leaderboard(leaderboard, N);
        //printLeaderboard(leaderboard);
    }
    std::cout << "Result score: " << leader_score << std::endl;
    std::cout << "Nr. results: " << result.size() << std::endl;
}

void expand(std::list<Peptide *> &l, std::list<int> *result_spec)
{
    std::list<Peptide *>::iterator iterator = l.begin(), end = l.end();
    while (iterator != end) {
        Peptide * actual = *iterator;
        for(int i=0;i<Peptide::aminoLen();i++) {
            std::string pep(actual->toString());
            pep.append(1, Peptide::aminoAt(i));
            Peptide *newpep = new Peptide(pep);
            newpep->setScore(result_spec);
            l.insert(iterator, newpep);            
        }
        delete *iterator;
        iterator = l.erase(iterator);
    }
}

void cut_leaderboard(std::list<Peptide *> &leaderboard, int N)
{
    leaderboard.sort(petide_score_compare);
    
    int i = 0;
    int cut = 0;
    std::list<Peptide *>::iterator iterator = leaderboard.begin(), end = leaderboard.end();
    while(iterator != end) {
        i++;
        const Peptide * p = *iterator;
        if(i == N) {
            cut = p->getScore();
            iterator++;
        } else if(i > N && p->getScore() != cut) {
            delete *iterator;
            iterator = leaderboard.erase(iterator);
        } else {
            iterator++;
        } 
    }
}

bool petide_score_compare(const Peptide * const & a, const Peptide * const & b)
{
   return a->getScore() > b->getScore();
}

void printLeaderboard(std::list<Peptide *> &leaderboard)
{
    std::cout << "BEGIN" << std::endl;
    for (std::list<Peptide *>::const_iterator iterator = leaderboard.begin(), 
         end = leaderboard.end(); iterator != end; ++iterator) {
        Peptide *p = *iterator;
        std::cout << p->toString() << " " << p->getScore() << " " << p->toWeightString() << std::endl;        
    }
    std::cout << "END" << std::endl;
}
