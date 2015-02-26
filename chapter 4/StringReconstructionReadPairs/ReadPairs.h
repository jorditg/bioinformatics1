/* 
 * File:   ReadPairs.h
 * Author: jdelatorre
 *
 * Created on 2 de diciembre de 2013, 15:27
 */

#ifndef READPAIRS_H
#define	READPAIRS_H

#include <map>
#include <list>
#include <vector>
#include <string>

class ReadPairs {
public:
    ReadPairs();
    ReadPairs(const ReadPairs& orig);
    ReadPairs(char * filename);
    virtual ~ReadPairs();
private:
    void split(std::vector<std::string> &result, std::string str, char delim );
    void load(char * filename);
    std::map<int, std::list<int> > graph;
    std::vector<std::string> map_pairs;
    int d;
};

#endif	/* READPAIRS_H */

