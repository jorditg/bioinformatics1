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

void print(std::list<std::string> &l);
void sequence(std::list<Peptide *> &leaderboard, std::list<int> *result_spec, std::list<std::string> &result, int N);
void expand(std::list<Peptide *> &l, std::list<int> *result_spec);
bool petide_score_compare(const Peptide * const & a, const Peptide * const & b);
void cut_leaderboard(std::list<Peptide *> &leaderboard, int N);
void printLeaderboard(std::list<Peptide *> &leaderboard);


/*
 * 
 */
int main(int argc, char** argv) 
{
    std::list<int> spectrum;
    std::list<Peptide *> l;
    std::list<std::string> result;

    Peptide::loadSpectrum("in.txt", spectrum);
    Peptide::printSpectrum(spectrum);
    
    std::cout << std::endl;
    
    int N = 1000;
    
//    Peptide p("IKVYKNFWPF");
//    p.setScore(&spectrum);
//    std::list<int> re;
//    int nr;
//    p.cyclospectrum(&re, nr);
//    Peptide::printSpectrum(re);
//    std::cout << "Score: " << p.getScore() << std::endl;
   
    sequence(l, &spectrum, result, N);    
    print(result);
    
    return 0;
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