#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        // skip first line
        read = getline(&line, &len, fp);
		
		size_t pos = 0;
        while ((read = getline(&line, &len, fp)) != -1) {
                //printf("Retrieved line of length %zu :\n", read);
                line[read-1] = '\0';  // remove newline
                strcpy(&genome[pos], line);
                pos += read-1;
                //printf("%s", line);
        }

        *size = pos;
        if (line)
                free(line);

        return genome;
}

int look_for_asc(char * genome, size_t size)
{
    size_t i;
    char state = 12;

    for(i=0;i<size;i++)
    {
       switch(state)
       {
            case 1:
                state=(genome[i] == 'T')?2:1;
            break;
            case 2:
                state=(genome[i] == 'T')?3:1;
            break;
            case 3:
                state=(genome[i] == 'T')?4:1;
            break;
            case 4:
                state=(genome[i] == 'A')?5:1;
            break;
            case 5:
                state=(genome[i] == 'T')?6:1;
            break;
            case 6:
                state=(genome[i] == 'G' || genome[i] == 'A')?7:1;
            break;
            case 7:
                state=(genome[i] == 'T')?8:1;
            break;
            case 8:
                state=(genome[i] == 'T')?9:1;
            break;
            case 9:
                state=(genome[i] == 'T')?10:1;
            break;
            case 10:
                state=(genome[i] == 'T' || genome[i] == 'A')?11:1;
            break;
            case 11:
                state=(genome[i] == 'G' || genome[i] == 'T')?12:1;
            break;
            case 12:
                printf("Found in position: %d\n", i-13);
                state=(genome[i] == 'T')?2:1;
            break;
            default:
                state = 1;
            break;
       }
    }
}

int main(int argc, char * argv[])
{
	char * filename = "S288C_reference_sequence_R64-1-1_20110203.fsa";
	size_t size;

	char * genome = load_genome(filename, &size);

	look_for_asc(genome, size);

	return 1;
}
