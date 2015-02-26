/* 
 * File:   main.cpp
 * Author: jordi
 *
 * Created on 10 de diciembre de 2013, 7:04
 */

#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "sqlite3pp.h"

template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}

void load_weights(std::vector<double> & numbers) {
    std::ifstream infile("../spectrum.txt");

    std::string temp;

    while (std::getline(infile, temp)) {
        std::istringstream buffer(temp);
        std::istream_iterator<double> val(buffer);
        for (; val != std::istream_iterator<double>(); val++)
            numbers.push_back(*val);
    }  
}


/*
 * 
 */
int main(int argc, char** argv) {
    const char * DATABASE_NAME  = "../peptides.db";
    const double ALLOWED_SPAN = 0.15;

    std::map<std::pair<char, char>, int> join_prob;
    
    std::vector<double> weights;
    load_weights(weights);

    sqlite3pp::database db(DATABASE_NAME);
    

    for(int i=0;i<weights.size();i++) {
        const double act_weight = weights[i];
        const double low = act_weight - ALLOWED_SPAN;
        const double high = act_weight + ALLOWED_SPAN;
        std::string str_query = "SELECT peptide FROM peptide WHERE weight > ";
        str_query.append(to_string(low));
        str_query.append(" AND weight < ");
        str_query.append(to_string(high));        
        sqlite3pp::query qry(db, str_query.c_str());
                
        for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {            
            std::string peptide(i->get<char const*>(0));
            std::cout << peptide << "\n";
            for(int i=0;i<peptide.size();i++) {
                for(int j=i+1;j<peptide.size();j++) {
                    const std::pair<char, char> key_f = std::pair<char,char>(peptide[i], peptide[j]);
                    const std::pair<char, char> key_b = std::pair<char,char>(peptide[j], peptide[i]);
                    std::map<std::pair<char,char>, int>::iterator it = join_prob.find(key_f);
                    if(it != join_prob.end()) {
                        //element found;
                        join_prob[key_f] = it->second + 1;
                        join_prob[key_b] = it->second + 1;
                    } else {
                        join_prob.insert(std::pair<std::pair<char, char>, int>(key_f, 1));
                        join_prob.insert(std::pair<std::pair<char, char>, int>(key_b, 1));
                    }
                }
            }
        }
    }
        
    return 0;
}

