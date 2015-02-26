#ifndef KMERLIST_HPP
#define KMERLIST_HPP

#include "Genome.hpp"

#include <cstring>
#include <map>
#include <list>

class KmerList
{
private:
	size_t * list;
	size_t k;
	size_t size;
	void find_max_on_list(size_t t, std::map<size_t,size_t> &where, std::list<int> &result);
	bool is_next(size_t &i, std::map<size_t,size_t> &window_list, size_t L);
	void print_max(std::map<size_t,size_t> &window_list, size_t t);

public:
	KmerList(Genome &g, size_t k);
	~KmerList();
	inline size_t * get() { return list; };
	inline size_t len() { return size; };
	void find_max_kmers(size_t L, size_t t, std::list<int> &result);
};

#endif