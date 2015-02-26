/* 
 * File:   cyclic_string.cpp
 * Author: jdelatorre
 * 
 * Created on 16 de enero de 2014, 14:41
 */

#include <vector>
#include <string>

#include "cyclic_string.h"

const char& cyclic_string::element::operator[](int idx) const {
    return cstr.str[(idx + first)%cstr.len];
}

const cyclic_string::element& cyclic_string::operator[](int idx) const {
    return el[idx];
}

bool cyclic_string::element::lower(const cyclic_string::element &a, const cyclic_string::element &b) {
    for(int i=0;i<a.cstr.len;i++) {
        if(a[i] != b[i])
            return a[i]<b[i];
    }
    return false;
}

const std::string cyclic_string::to_string() const {
    std::string res;
    for(int i=0; i<el.size();i++) {
        res.append(el[i].to_string());
        res.append("\n");
    }
    return res;
}

const std::string cyclic_string::element::to_string() const {
    std::string res;
    const element &e = *this;
    
    for(int i=0;i<cstr.len;i++) {
        res.append(1,e[i]);
    }
    return res;
}

cyclic_string::cyclic_string(const std::string &s) : str(s.c_str()), len(s.size()) {
    for(int i=0;i<len;i++) {
        element e(i, *this);
        el.push_back(e);
    }
}

cyclic_string::cyclic_string(const cyclic_string& orig) : str(orig.str), len(orig.len) {
}

cyclic_string::~cyclic_string() {
}

std::string cyclic_string::burrows_wheeler_transform() {
    sort();
    
    std::string res;
    for(int i=0; i<el.size();i++) {
        res.append(1,el[i][len-1]);
    }
    return res;    
}