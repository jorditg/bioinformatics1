/* 24.12.2008 last modification: 26.06.2013
Copyright (c) 2008-2013 by Siegfried Koepf

This file is distributed under the terms of the GNU General Public License
version 3 as published by the Free Software Foundation.
For information on usage and redistribution and for a disclaimer of all
warranties, see the file COPYING in this distribution.

Partitions in reverse lexicographic order

Based on Algorithm ZS1 in: Zoghbi, Antoine and Stojmenovic, Ivan: Fast Algorithms for Generating Integer Partitions. International Journal of Computer Mathematics, 70, 1998, 319-332.

Functions:
  int gen_part_revlex_init(unsigned char *vector, const unsigned char n, unsigned char *k)
    Test for special cases
    Initialization of vector
    Initialization of k
    Possible return values are: GEN_EMPTY, GEN_NEXT

  int gen_part_revlex_next(unsigned char *vector, unsigned char *k)
    Transforms current figure in vector into its successor
    Sets k to the appropriate value
    Possible return values are: GEN_NEXT, GEN_TERM

Arguments:
  unsigned char *vector; //pointer to the array where the current figure is stored
  const unsigned char n; //length of alphabet
  const unsigned char k; //length of figures

Usage and restrictions:
  Arguments and elements in vector are restricted to the interval (0, 255)
  Memory allocation for vector must be provided by the calling process

Cardinality see:
  Sloane, N.J.A. et al.: The On-Line Encyclopedia of Integer Sequences, 2008.
  http://oeis.org/A000041
  see also:
  http://mathworld.wolfram.com/Partition.html
*/

#include "_generate.h"

int gen_part_revlex_init(unsigned char *vector, const unsigned char n, unsigned char *k)
{
int j; //index

//test for special cases
if(n == 0)
 {
 (*k) = 0;
 return(GEN_EMPTY);
 }

//initialize: vector[0] = n, vector[1, ..., n - 1] are 1
vector[0] = n;

for(j = 1; j < n; j++)
 vector[j] = 1;

(*k) = 1;

return(GEN_NEXT);
}

int gen_part_revlex_next(unsigned char *vector, unsigned char *k)
{
static int j = 0; //remember index of the rightmost part which is greater than 1
int        r;     //temporary remainder
int        temp;  //auxiliary element

//easy case
if(vector[j] == 2)
 {
 vector[j] = 1;
 j--;
 (*k)++;
 return(GEN_NEXT);
 }

//terminate if all parts are 1
if(vector[0] == 1)
 {
 j = 0;
 return(GEN_TERM);
 }

//decrease
vector[j]--;
temp = vector[j];
r = *k - j;

//set right-hand elements
while(r > temp)
 {
 j++;
 vector[j] = temp;
 r -= temp;
 }

*k = j + 2;

//set rightmost element
if(r > 1)
 {
 j++;
 vector[j] = r;
 }

return(GEN_NEXT);
}
