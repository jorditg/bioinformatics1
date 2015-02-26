/* 
 * File:   UniversalCircularString.h
 * Author: jordi
 *
 * Created on 1 de diciembre de 2013, 22:22
 */

#ifndef UNIVERSALCIRCULARSTRING_H
#define	UNIVERSALCIRCULARSTRING_H

#include "EulerianGraph.h"

class UniversalCircularString {
public:
    UniversalCircularString(unsigned int k);
    UniversalCircularString(const UniversalCircularString& orig);
    virtual ~UniversalCircularString();
    
    
private:
    unsigned int k;
    EulerianGraph *eg;
    void generate_graph(const unsigned int k);
    void print();
};

#endif	/* UNIVERSALCIRCULARSTRING_H */

