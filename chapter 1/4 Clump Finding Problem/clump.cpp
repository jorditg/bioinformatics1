#include "Genome.hpp"
#include "KmerList.hpp"
#include <iostream>
#include <cstdlib>
#include <list>

extern "C" {
	#include "gen.h"
}

using namespace std;

int main(int argc, char* argv[]) {
	Genome genome(argv[4]);
	
	//cout << genome.get().c_str() << endl;
	
	size_t k = atoi(argv[1]);
	size_t L = atoi(argv[2]);
	size_t t = atoi(argv[3]);

	KmerList kmer(genome, k);
	
	//for(size_t i=0;i<kmer.len();i++) {
	//	cout << kmer.get()[i] << " ";
	//}
	//cout << endl;
	
	std::list<int> l;
	kmer.find_max_kmers(L, t, l);
	
	char * kmer_str = new char[k+1];
	
	std::list<int>::const_iterator iterator;
	for (iterator = l.begin(); iterator != l.end(); ++iterator) {	
		index2kmer(*iterator, k, kmer_str);
		std::cout << kmer_str << " ";
	}
	std::cout << std::endl;

	delete[] kmer_str;
	
   return 0;
} 

