#ifndef GENOME_HPP
#define GENOME_HPP

#include <string>

using namespace std;

class Genome
{
private:
	//char * genome;
	//size_t size;
	string contents;
	
public:
	Genome(string file);
	~Genome();
	inline string get() { return contents; }
	inline size_t len() { return contents.size(); }
};

#endif