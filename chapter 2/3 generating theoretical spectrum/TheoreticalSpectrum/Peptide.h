/* 
 * File:   Peptide.h
 * Author: jdelatorre
 *
 * Created on 6 de noviembre de 2013, 12:19
 */

#ifndef PEPTIDE_H
#define	PEPTIDE_H

#include <string>
#include <list>

class Peptide
{
private:
        static const int AMINOACID_NUMBER = 20;
	static const char amino[];
	static const int weight[];

	std::string peptide;
        std::list<std::string *> *subpeptide_list;
	
public:
        Peptide(const char * p);   
        ~Peptide();
        static int toWeight(std::string subpeptide);
	std::list<std::string *> * subpeptides();
        
};

#endif	/* PEPTIDE_H */

