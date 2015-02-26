#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * load_genome(char * fsa_filename, size_t *size);
void pattern_match(char * genome, size_t genome_len, char * pattern, size_t pattern_len);
size_t next_state(char * genome, size_t genome_act_pos, char * pattern, size_t act_state, size_t pattern_len);


int main(int argc, char *argv[])
{
	size_t genome_len;
	char * genome = load_genome(argv[1], &genome_len);
	char * pattern = argv[2];
	
	size_t pattern_len = strlen(pattern);
	
	printf("genome_len=%i, pattern=%s, pattern_len=%i\n", genome_len, pattern, pattern_len);
	pattern_match(genome, genome_len, pattern, pattern_len);
}


void pattern_match(char * genome, size_t genome_len, char * pattern, size_t pattern_len)
{
	size_t state = 0;
	size_t i = 0;
	while(i<genome_len)
	{
		if(genome[i] == pattern[state])	
		{
			// if not already found the complete pattern
			// but actual character equals actual pattern character 
			state++;	// increment the state
			if(state == pattern_len) // pattern found
			{
				state = 0;
				i -= (pattern_len - 1);
				printf("%i ", i);
			}
			i++;
		} else {
			i -= (state - 1);
			state = 0;
		}
	}
}


/*
	char * load_genome(char * fsa_filename, size_t *size)
	
	Loads the genome from a file.
	The file should be a text file (UNIX or DOS type) with the genome including
	ONLY the letters A, G, T, C separated by lines.
	
	Returns a pointer to a dynamically allocated memory location
	where the genome is saved.
	
	This memory should be freed after use (free(genome))
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

	if (fp == NULL) exit(EXIT_FAILURE);

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
