#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * load_genome(char * fsa_filename, size_t *size);
void count_kmers(char * genome, size_t len, int k, size_t * counter);
void max_counter(size_t *counter, size_t len, size_t *max_values, size_t *values_length, size_t *value);
void index2kmer(size_t kmer_idx, int k, char * kmer);
size_t kmer2index(char *kmer, int k);
char * load_genome(char * fsa_filename, size_t *size);

int main(int argc, char *argv[])
{
	size_t genome_size;

	char * filename = argv[1];
	int k = atoi(argv[2]);	
	
	
	char * genome = load_genome(filename, &genome_size);

#ifdef DEBUG
	printf("k=%i\n", k);
	for(size_t i=0;i<genome_size;i++)
		printf("%c", genome[i]);
	printf("\n");
#endif

	size_t n_elements = 1<<(2*k); // counter has 4^k diferent values <=> 1<<(2*k) values
	size_t * counter = (size_t *) malloc(n_elements*sizeof(size_t));		
	count_kmers(genome, genome_size, k, counter);

#ifdef DEBUG
	printf("k-mers counted.\n");
#endif
	
	size_t values_length;
	size_t value;
	size_t *max_values = (size_t *) malloc(255*sizeof(size_t));	
	
	max_counter(counter, n_elements, max_values, &values_length, &value);
	
	char kmer[k];
	for(size_t i = 0; i<values_length; i++) 
	{
		index2kmer(max_values[i], k, kmer);
		printf("%s ", kmer);
	}
	printf("\n");
	printf("Value = %i", value);
	
	free(counter);
	free(max_values);
	free(genome);
	
	return 1;
}


/*
	void count_kmers(char * genome, size_t len, int k, size_t * counter)
	Counts the number of k-mers of size k that we have in the genome of length len.
	Returns the result in the dynamic allocated vector counter.
	This allocation should be freed after use.
*/
void count_kmers(char * genome, size_t len, int k, size_t * counter)
{	
	size_t n_elements = 1<<(2*k); // counter has 4^k diferent values <=> 1<<(2*k) values
	
	// initialize counter
	memset(counter, 0, n_elements);
		
	// count
	for(size_t i = 0;i<len-k+1;i++) 
		counter[kmer2index(&genome[i], k)]++;
	
#ifdef DEBUG
	for(size_t i = 0;i<n_elements;i++)
		printf("count_kmers: counter[i] = %i\n", counter[i]);
#endif

}

/*
	void max_counter(size_t *counter, size_t len, size_t *max_values, size_t *values_length, size_t *value)
	Returns a vector of index values that have the maximum counts in the vector counter.
	Each index value returned corresponds to a enconded value of a k-mer that can be recovered with a
	posterior call to index2kmer.
*/
void max_counter(size_t *counter, size_t len, size_t *max_values, size_t *values_length, size_t *value)
{
	int maxvalue = 0;
	*values_length = 0;
	for(size_t i = 0; i < len; i++)
	{
#ifdef DEBUG
		printf("i=%i, counter[i]=%i, maxvalue=%i\n", i, counter[i], maxvalue);
#endif
		if(counter[i] > maxvalue)
		{
			maxvalue = counter[i];
			max_values[0] = i;
			*values_length = 1;
		} else if(counter[i] == maxvalue) {
			max_values[(*values_length)++] = i;
			
		}
	}
	*value = maxvalue;
#ifdef DEBUG
	printf("value=%i",*value);
#endif
}


/*
	void index2kmer(size_t kmer_idx, int k, char * kmer)
	Decodes the k-mer encoded in an size_t integer and returns the
	associated kmer string.
*/

void index2kmer(size_t kmer_idx, int k, char * kmer)
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
	size_t kmer2index(char *kmer, int k)
	
	Encodes the k-mer translating each letter to their binary form.
	Each letter is translated into 2 bits.
	Returns a size_t integer that can be used as a index to an array where
	the counting is made.
*/
size_t kmer2index(char *kmer, int k)
{
	int i;
	
	size_t index = 0;
	
#ifdef DEBUG
	printf("kmer2index: ");
#endif	
	
	for(i=0;i<k;i++)
	{
#ifdef DEBUG
	printf("%c", kmer[i]);
#endif	
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
#ifdef DEBUG
	printf(" -> %i\n", index);
#endif	
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

char * load_genome(char * fsa_filename, size_t *size)
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

