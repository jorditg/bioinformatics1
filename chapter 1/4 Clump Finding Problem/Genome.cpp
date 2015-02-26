#include "Genome.hpp"
#include <fstream>
#include <sstream>

//extern "C" {
//	#include "gen.h"
//}

Genome::Genome(string file)
{
	//genome = load_genome(file.c_str(), &size);
	std::ifstream ifs(file.c_str());
	contents = static_cast<stringstream const&>(stringstream() << ifs.rdbuf()).str();
}

Genome::~Genome()
{
	// free(genome);
}

