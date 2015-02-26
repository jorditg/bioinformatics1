#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * reverse_complement(char * from, size_t len);
char reverse(char c);
char * load_genome(char * fsa_filename, size_t *size);

int main(char *argc, char *argv[])
{
	size_t size;
	char *from;
	char * to;
	
	from = load_genome(argv[1], &size);

	to = reverse_complement(from, size);
	
	for(size_t i = 0; i<size;i++)
		printf("%c", to[i]);
	printf("\n");
	
	return 1;
}

char * reverse_complement(char * from, size_t len)
{
	char * to = malloc(len);
	
	for(size_t i = 0; i<len; i++)
		to[len-i-1] = reverse(from[i]);
		
	return to;
}

char reverse(char c) 
{
	switch(c)
	{
		case 'A': return 'T';
		case 'G': return 'C';
		case 'T': return 'A';
		case 'C': return 'G';
	}
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

