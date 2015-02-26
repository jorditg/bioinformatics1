/* 24.12.2008 last modification: 26.06.2013
Copyright (c) 2008-2013 by Siegfried Koepf

This file is distributed under the terms of the GNU General Public License
version 3 as published by the Free Software Foundation.
For information on usage and redistribution and for a disclaimer of all
warranties, see the file COPYING in this distribution.

Variations with repetition in lexicographic order

Algorithm by Siegfried Koepf, inspired by Algorithm M (Mixed-radix generation) in: Knuth, Donald E.: The Art of Computer Programming, Vol. 4: Fascicle 2. Generating All Tuples and Permutations. Upper Saddle River, NJ 2005.

Functions:
  int gen_vari_rep_lex_init(unsigned char *vector, const unsigned char m, const unsigned char n)
    Test for special cases
    Initialization of vector
    Possible return values are: GEN_EMPTY, GEN_NEXT

  int gen_vari_rep_lex_next(unsigned char *vector, const unsigned char m, const unsigned char n)
    Transforms current figure in vector into its successor
    Possible return values are: GEN_NEXT, GEN_TERM

Arguments:
  unsigned char *vector; //pointer to the array where the current figure is stored
  const unsigned char m; //length of alphabet
  const unsigned char n; //length of figures

Usage and restrictions:
  Arguments and elements in vector are restricted to the interval (0, 255)
  Memory allocation for vector must be provided by the calling process

Cardinality:
  m^n
*/

#include "_generate.h"

int gen_vari_rep_lex_init(unsigned char *vector, const unsigned char m, const unsigned char n)
{
int j; //index

//test for special cases
if(m == 0 || n == 0)
 return(GEN_EMPTY);

//initialize: vector[0, ..., n - 1] are zero
for(j = 0; j < n; j++)
 vector[j] = 0;

return(GEN_NEXT);
}

int gen_vari_rep_lex_next(unsigned char *vector, const unsigned char m, const unsigned char n)
{
int j; //index

//easy case, increase rightmost element
if(vector[n - 1] < m - 1)
 {
 vector[n - 1]++;
 return(GEN_NEXT);
 }

//find rightmost element to increase and reset right-hand elements
for(j = n - 2; j >= 0; j--)
 {
 vector[j + 1] = 0;

 if(vector[j] < m - 1)
  break;
 }

//terminate if all elements are m - 1
if(j < 0)
 return(GEN_TERM);

//increase
vector[j]++;

return(GEN_NEXT);
}
