/* 
 * File:   DNAStringGenerator.h
 * Author: jdelatorre
 *
 * Created on 20 de noviembre de 2013, 14:38
 */

#ifndef DNASTRINGGENERATOR_H
#define	DNASTRINGGENERATOR_H

#include <string>

class DNAStringGenerator {
public:
    inline DNAStringGenerator() {actual.assign(""); last.assign("");};
    inline DNAStringGenerator(const DNAStringGenerator& orig) {actual.assign(orig.actual); last.assign(orig.last);};
    inline DNAStringGenerator(int len) {actual.append(len, 'A'); last.append(len, 'T');};
    virtual ~DNAStringGenerator();
    
    inline const std::string & get_value() {return actual;};
    inline bool end() { return (actual == end_value)?true:false;};
    void next();
    inline void reset() {int len = actual.length(); actual.assign(""); actual.append(len, 'A');};
private:
    inline char next_char(char c) {switch(c) {case 'A':return 'C'; case 'C': return 'G';
                                              case 'G': return 'T'; case 'T': return 'A';} 
                                   return '0';};
    std::string actual;
    std::string last;
    static const std::string end_value;    
};

#endif	/* DNASTRINGGENERATOR_H */

