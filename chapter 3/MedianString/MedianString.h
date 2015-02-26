/* 
 * File:   MedianString.h
 * Author: jdelatorre
 *
 * Created on 20 de noviembre de 2013, 16:49
 */

#ifndef MEDIANSTRING_H
#define	MEDIANSTRING_H

#include <vector>
#include <string>

class MedianString {
public:
    MedianString();
    MedianString(const MedianString& orig);
    MedianString(const char * filename);
    virtual ~MedianString();
    int distance(const char * a, const char * b, int len) const;
    void find_kmer();
private:
    int k;
    std::vector<std::string> str_col;
};

#endif	/* MEDIANSTRING_H */

