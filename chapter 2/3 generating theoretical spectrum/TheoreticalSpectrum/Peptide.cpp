#include "Peptide.h"

#include <list>
#include <string>

const char Peptide::amino[] = "GASPVTCILNDKQEMHFRYW";
const int Peptide::weight[] = {57,71,87,97,99,101,103,113,113,114,115,
                               128,128,129,131,137,147,156,163,186};

Peptide::Peptide(const char * pep)
{
    peptide.assign(pep);
}

int Peptide::toWeight(std::string subpeptide)
{
    const char * p = subpeptide.c_str();
    int sum = 0;
    for(int i=0;i<subpeptide.size();i++) {
        for(int j=0;j<AMINOACID_NUMBER;j++) {
            if(subpeptide[i] == amino[j]) {
                sum += weight[j];
                break;
            }
        }
    }
    return sum;
}

std::list<std::string *> * Peptide::subpeptides()
{  
	subpeptide_list = new std::list<std::string *>();
	
	for(int i=0;i<peptide.size();i++)
	{
		for(int size=1;size<peptide.size();size++)
		{
			std::string *result = new std::string("");
			for(int j=i;j<size+i;j++)
			{
				*result += peptide[j%peptide.size()];
			}
			subpeptide_list->push_back(result);
		}
	}
        
        return subpeptide_list;
} 

Peptide::~Peptide()
{
    if(subpeptide_list != NULL) {
        for(std::list<std::string *>::const_iterator iterator = subpeptide_list->begin(), 
         end = subpeptide_list->end(); iterator != end; ++iterator) {        
                delete *iterator;
        }
        delete subpeptide_list;
    }
}
