/* 
 * File:   cyclic_string.h
 * Author: jdelatorre
 *
 * Created on 16 de enero de 2014, 14:41
 */

#ifndef CYCLIC_STRING_H
#define	CYCLIC_STRING_H

#include <string>
#include <vector>
#include <algorithm>

class cyclic_string {
public:
    class element {
    public:   
        int first;
        cyclic_string &cstr;
        
        inline element(const element& orig) : first(orig.first), cstr(orig.cstr) {};
        inline element(int first, cyclic_string &cstr) : first(first), cstr(cstr) {};        
        inline element& operator=(const element& a) {first = a.first; cstr = a.cstr;};
        
        const char& operator[](int idx) const;
        const std::string to_string() const;
        
        static bool lower(const element &a, const element &b);
    };
    const cyclic_string::element& operator[](int idx) const;
    const std::string to_string() const;
    
    std::string burrows_wheeler_transform();
    
    inline void sort() {std::sort(el.begin(), el.end(), element::lower);};
    
    cyclic_string(const std::string &s);
    cyclic_string(const cyclic_string& orig);
    virtual ~cyclic_string();
    
    const char * str;
    int len;
private:
    std::vector<element> el;
};

#endif	/* CYCLIC_STRING_H */

