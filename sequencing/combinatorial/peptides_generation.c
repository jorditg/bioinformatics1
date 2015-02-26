/* 24.12.2008 last modification: 26.06.2013
Copyright (c) 2008-2013 by Siegfried Koepf

This file is distributed under the terms of the GNU General Public License
version 3 as published by the Free Software Foundation.
For information on usage and redistribution and for a disclaimer of all
warranties, see the file COPYING in this distribution.

testing
gen_comb_norep_lex_init() and gen_comb_norep_lex_next()

compile
gcc -o comb_norep_lex_example comb_norep_lex_example.c comb_norep_lex.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "_generate.h"

int generate_combinations(unsigned char k, float max_weight);

const char  amino[] = { 'G','A','S','P','V','T','C','I','L','D',
                        'N','Q','K','E','M','H','F','R','Y','W'};

const float weight[20] = { 
                           57.05,71.09,87.08,97.12,99.14,101.11,103.15,
                           113.16,113.16,114.11,115.09,128.14,128.17,
                           129.12,131.19,137.14,147.18,156.19,163.18,186.12
                         };

int main(int argc, char *argv[])
{
    int n;
    float max_weight          = atof(argv[1]);
    unsigned char k           = 1;    //length of figures

    if(argc == 3) {
        k = atoi(argv[2]);
        n = generate_combinations(k, max_weight);
    } else {
        do {
            n = generate_combinations(k, max_weight);
            k++;
        } while(n > 0);
    }
}

int generate_combinations(unsigned char k, float max_weight)
{
    unsigned char n           = 20;    //length of alphabet
    unsigned char *vector     = NULL; //where the current figure is stored
    unsigned char *actual_amino = NULL;
    int           gen_result;         //return value of generation functions
    unsigned long  set_counter;        //counting generated sequences
    int           x;                  //iterator
    float w;

    if(weight[0]*k > max_weight) return 0;
    
    //alloc memory for vector
    vector = (unsigned char *)malloc(sizeof(unsigned char) * k);
    actual_amino = (unsigned char *)malloc(sizeof(unsigned char) * (k + 1));
    actual_amino[k] = '\0';
    
    if(vector == NULL)
     {
         fprintf(stderr, "error: insufficient memory\n");
         exit(EXIT_FAILURE);
     }

    set_counter = 0;
    //printf("comb_norep_lex(%u, %u)\n", n, k);

    //initialize
    gen_result = gen_comb_rep_lex_init(vector, n, k);

    if(gen_result == GEN_ERROR)
     {
         fprintf(stderr, "error: couldn't initialize\n");
         return(EXIT_FAILURE);
     }

    if(gen_result == GEN_EMPTY)
     {
         set_counter++;
         printf("{} (%u)\n", set_counter);
     }

    //generate all successors
    while(gen_result == GEN_NEXT)
     {                 
         w = 0.0;
         for(x = 0; x < k; x++)
         {
            actual_amino[x] = amino[vector[x]];
            w += weight[vector[x]];
         }
         if(w <= max_weight) {
            printf("%s %.2f \n", actual_amino, w);
            set_counter++;
         }

         gen_result = gen_comb_rep_lex_next(vector, n, k);
     }
    
    free(vector);
    free(actual_amino);
    
    return(set_counter);
}