/* 26.06.2013 last modification: 26.06.2013
Copyright (c) 2013 by Siegfried Koepf

This file is distributed under the terms of the GNU General Public License
version 3 as published by the Free Software Foundation.
For information on usage and redistribution and for a disclaimer of all
warranties, see the file COPYING in this distribution.

Variations with repetition in colexicographic order

Algorithm by Siegfried Koepf

Functions:
  int gen_vari_rep_colex_init(unsigned char *vector, const unsigned char m, const unsigned char n)
    Test for special cases
    Initialization of vector
    Possible return values are: GEN_EMPTY, GEN_NEXT

  int gen_vari_rep_colex_next(unsigned char *vector, const unsigned char m, const unsigned char n)
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

int gen_vari_rep_colex_init(unsigned char *vector, const unsigned char m, const unsigned char n)
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

int gen_vari_rep_colex_next(unsigned char *vector, const unsigned char m, const unsigned char n)
{
int j; //index

//easy case, increase leftmost element
if(vector[0] < m - 1)
 {
 vector[0]++;
 return(GEN_NEXT);
 }

//find leftmost element to increase and reset left-hand elements
for(j = 1; j < n; j++)
 {
 vector[j - 1] = 0;

 if(vector[j] < m - 1)
  break;
 }

//terminate if all elements are m - 1
if(j == n)
 return(GEN_TERM);

//increase
vector[j]++;

return(GEN_NEXT);
}
