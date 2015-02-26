#include "gen.h"

/*
	void index2kmer(size_t kmer_idx, size_t k, char * kmer)
	Decodes the k-mer encoded in an size_t integer and returns the
	associated kmer string.
*/

void index2kmer(size_t kmer_idx, size_t k, char * kmer)
{
	size_t mask = 0x03;		// Binary 11
	size_t idx = kmer_idx;
	
	for(int i=k-1;i>=0;i--) 
	{
		switch(idx & mask)
		{
			case 0x00:
				kmer[i] = 'A'; 		// Binary: 00
			break;
			case 0x01:
				kmer[i] = 'G';		// Binary: 01
			break;
			case 0x02:
				kmer[i] = 'T';		// Binary: 10
			break;
			case 0x03:
				kmer[i] = 'C';		// Binary: 11
			break;
		}
		idx >>= 2;
	}
	kmer[k] = '\0';
}

/*
	size_t kmer2index(char *kmer, size_t k)
	
	Encodes the k-mer translating each letter to their binary form.
	Each letter is translated into 2 bits.
	Returns a size_t integer that can be used as a index to an array where
	the counting is made.
*/
size_t kmer2index(char *kmer, size_t k)
{
	size_t index = 0;
	
	for(size_t i=0;i<k;i++)
	{
		index <<= 2;
		switch(kmer[i])
		{
			case 'A':
				index |= 0x00; 		// Binary: 00
			break;
			case 'G':
				index |= 0x01;		// Binary: 01
			break;
			case 'T':
				index |= 0x02;		// Binary: 10
			break;
			case 'C':
				index |= 0x03;		// Binary: 11
			break;
		}
	}
	return index;
}

/*
	char * load_genome(char * fsa_filename, size_t *size)
	
	Loads the genome from a file.
	The file should be a text file (UNIX or DOS type) with the genome including
	ONLY the letters A, G, T, C separated by lines.
	
	Returns a pointer to a dynamically allocated memory location
	where the genome is saved.
	
	This memory should be freed after use.
*/

char * load_genome(const char * fsa_filename, size_t *size)
{
	FILE * fp;
	char * line = NULL;
	size_t len = 255;
	ssize_t read;

	// open filename
	fp = fopen(fsa_filename, "r");

	// seek to the end in order to know the size
	fseek(fp, 0L, SEEK_END);
	*size = ftell(fp);

	// allocate maximum size needed
	char * genome = (char *) malloc (*size);
	if (genome==NULL) exit (1);

	// seek back to the begining
	fseek(fp, 0L, SEEK_SET);

	if (fp == NULL)
			exit(EXIT_FAILURE);

	size_t pos = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
#ifdef DEBUG	
			printf("Retrieved line of length %zu :\n", read);
#endif
			if(line[read-1] == '\n')	// remove newline (UNIX or DOS newlines)
				if(line[read-2] == '\r') {
					line[read-2] = '\0';
					read -= 2;
				} else {
					line[read-1] = '\0';
					read--;
				}
			strcpy(&genome[pos], line);
			//printf("%s\nSaved in position %i\n", line, pos);
			pos += read;
	}

	*size = pos;
	if (line) free(line);

	return genome;
}

