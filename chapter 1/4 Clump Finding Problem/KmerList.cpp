#include "KmerList.hpp"
#include <cstdlib>
#include <algorithm>

extern "C" {
	#include "gen.h"
}

KmerList::KmerList(Genome &g, size_t k)
{
	this->k = k;
	this->size = g.len()-k+1;
	
	char * gen = (char *) g.get().c_str();	
	list = new size_t[size];
		
	for(size_t i=0;i<size;i++) {
		list[i] = kmer2index(&gen[i], k);
	}
}

KmerList::~KmerList()
{
	delete[] list;
}

void KmerList::find_max_on_list(size_t t, std::map<size_t,size_t> &where, std::list<int> &result)
{
		std::map<size_t,size_t>::iterator it;
		for (it=where.begin(); it!=where.end(); ++it)
		{
			if(it->second >= t) {	// if the kmer is present more than t times
				std::list<int>::iterator findIter = std::find(result.begin(), result.end(), it->first);
				if(findIter == result.end())	// and not in list --> insert it
					result.push_back(it->first);
			}
		}	
}

bool KmerList::is_next(size_t &i, std::map<size_t,size_t> &window_list, size_t L)
{
	bool cont = (i<size)?true:false;
	
	if(cont) {
		if(window_list[list[i-L+k-1]] <= 1) 
			window_list.erase(list[i-L+k-1]);
		else
			window_list[list[i-L+k-1]]--;
		
		map<size_t, size_t>::const_iterator it = window_list.find(list[i]);
		if(it == window_list.end())
			window_list.insert ( std::pair<size_t,size_t>(list[i],1) );
		else
			window_list[list[i]]++;
		i++;
	}
	
	return cont;
}


void KmerList::find_max_kmers(size_t L, size_t t, std::list<int> &result)
{
	map<size_t,size_t> window_list;
	
	// initialize list with the elements present on the first window 
	for(size_t i=0;i<L-k+1;i++) {
		map<size_t, size_t>::iterator it = window_list.find(list[i]);
		if(it == window_list.end())	// not found
			window_list.insert ( std::pair<size_t,size_t>(list[i],1) );	// insert element, initialized to 1
		else	// found on list => increment
			window_list[list[i]]++;
	}
	
	size_t i = L-k+1;
	do {	
		find_max_on_list(t, window_list, result);
	} while(is_next(i, window_list, L));
	
} 

