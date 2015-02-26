/* 24.12.2008 last modification: 26.06.2013
Copyright (c) 2008-2013 by Siegfried Koepf

This file is distributed under the terms of the GNU General Public License
version 3 as published by the Free Software Foundation.
For information on usage and redistribution and for a disclaimer of all
warranties, see the file COPYING in this distribution.

k-combinations with repetition in lexicographic order

Algorithm by Siegfried Koepf

Functions:
  int gen_comb_rep_lex_init(unsigned char *vector, const unsigned char n, const unsigned char k)
    Test for special cases
    Initialization of vector
    Possible return values are: GEN_EMPTY, GEN_NEXT

  int gen_comb_rep_lex_next(unsigned char *vector, const unsigned char n, const unsigned char k)
    Transforms current figure in vector into its successor
    Possible return values are: GEN_NEXT, GEN_TERM

Arguments:
  unsigned char *vector; //pointer to the array where the current figure is stored
  const unsigned char n; //length of alphabet
  const unsigned char k; //length of figures

Usage and restrictions:
  Arguments and elements in vector are restricted to the interval (0, 255)
  Memory allocation for vector must be provided by the calling process

Cardinality:
  (n + k - 1)! / (k! * (n - 1)!) == Binomial(n + k - 1, k)
*/

#include "_generate.h"

int gen_comb_rep_lex_init(unsigned char *vector, const unsigned char n, const unsigned char k)
{
int j; //index

//test for special cases
if(n == 0 || k == 0)
 return(GEN_EMPTY);

//initialize: vector[0, ..., k - 1] are zero
for(j = 0; j < k; j++)
 vector[j] = 0;

return(GEN_NEXT);
}

int gen_comb_rep_lex_next(unsigned char *vector, const unsigned char n, const unsigned char k)
{
int j; //index

//easy case, increase rightmost element
if(vector[k - 1] < n - 1)
 {
 vector[k - 1]++;
 return(GEN_NEXT);
 }

//find rightmost element to increase
for(j = k - 2; j >= 0; j--)
 if(vector[j] != n - 1)
  break;

//terminate if all elements are n - 1
if(j < 0)
 return(GEN_TERM);

//increase
vector[j]++;

//set right-hand elements
for(j += 1; j < k; j++)
 vector[j] = vector[j - 1];

return(GEN_NEXT);
}
