/* 23.11.2011 last modification: 26.06.2013
Copyright (c) 2011-2013 by Siegfried Koepf

This file is distributed under the terms of the GNU General Public License
version 3 as published by the Free Software Foundation.
For information on usage and redistribution and for a disclaimer of all
warranties, see the file COPYING in this distribution.

k-compositions in colexicographic order

Algorithm by Siegfried Koepf

Functions:
  int gen_k_comp_colex_init(unsigned char *vector, const unsigned char n, const unsigned char k)
    Test for special cases
    Initialization of vector
    Possible return values are: GEN_ERROR, GEN_EMPTY, GEN_NEXT

  int gen_k_comp_colex_next(unsigned char *vector, const unsigned char k)
    Transforms current figure in vector into its successor
    Possible return values are: GEN_NEXT, GEN_TERM

Arguments:
  unsigned char *vector; //pointer to the array where the current figure is stored
  const unsigned char n; //length of alphabet
  const unsigned char k; //length of figures

Usage and restrictions:
  Arguments and elements in vector are restricted to the interval (0, 255)
  Memory allocation for vector must be provided by the calling process
  k must be <= n

Cardinality:
  Binomial(n - 1, k - 1)
*/

#include "_generate.h"

int gen_k_comp_colex_init(unsigned char *vector, const unsigned char n, const unsigned char k)
{
int j; //index

//test for special cases
if(k > n)
 return(GEN_ERROR);

if(n == 0)
 return(GEN_EMPTY);

if(k == 0)
 return(GEN_ERROR);

//initialize: vector[0] = n - k + 1, vector[1, ..., k - 1] are 1
vector[0] = n - k + 1;

for(j = 1; j < k; j++)
 vector[j] = 1;

return(GEN_NEXT);
}

int gen_k_comp_colex_next(unsigned char *vector, const unsigned char k)
{
int j; //index

//terminate, this is only needed to allow k == 1
if(k <= 1)
 return(GEN_TERM);

//easy case
if(vector[0] > 1)
 {
 vector[0]--;
 vector[1]++;
 return(GEN_NEXT);
 }

//find leftmost element to increase
for(j = 1; j < k; j++)
 if(vector[j] > 1)
  break;

//terminate if the first k - 1 parts are 1
if(j >= k - 1)
 return(GEN_TERM);

//increase
vector[j + 1]++;

//set left-hand elements
vector[0] = vector[j] - 1;
vector[j] = 1;

return(GEN_NEXT);
}
