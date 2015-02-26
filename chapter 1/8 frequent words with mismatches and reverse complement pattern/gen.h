#ifndef GEN_H
#define GEN_H

#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void index2kmer(size_t kmer_idx, size_t k, char * kmer);
size_t kmer2index(char *kmer, size_t k);
char * load_genome(const char * fsa_filename, size_t *size);

#endif
