/* 
 * File:   StringCollection.h
 * Author: jdelatorre
 *
 * Created on 19 de noviembre de 2013, 10:28
 */

#ifndef STRINGCOLLECTION_H
#define	STRINGCOLLECTION_H

#include <vector>
#include <string>
#include <list>

class StringCollection {
public:    
    StringCollection();
    StringCollection(const StringCollection& orig);
    virtual ~StringCollection();
    StringCollection(const char * filename);
    inline const std::vector<std::string> & getStrings() const { return str_col; };
    void print();
    void motif_enumeration();
    int distance(const char * a, const char * b, int len) const;
    void print_kmer(const char *kmer, int k) const;
    void find_mutation(std::string mutation) const;
    
    static std::list<std::string> & mutation_values(int len, std::list<std::string> &result);
    static std::list<std::string> & mutation_positions(int n, int k, std::list<std::string> &result);
    
    
    static void print(std::list<std::string> s);
    
private:
    static std::string other_bases(char base);
    std::string mutate(const std::string &kmer, const std::string position, const std::string value);
    
    
    std::list<std::string> mutation_possibilities;
    std::list<std::string> combinations;
    
    std::vector<std::string> str_col;
    int k;
    int d;
};

#endif	/* STRINGCOLLECTION_H */

