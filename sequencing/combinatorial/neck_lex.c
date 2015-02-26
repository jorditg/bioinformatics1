/* 24.12.2008 last modification: 26.06.2013
Copyright (c) 2008-2013 by Siegfried Koepf

This file is distributed under the terms of the GNU General Public License
version 3 as published by the Free Software Foundation.
For information on usage and redistribution and for a disclaimer of all
warranties, see the file COPYING in this distribution.

Necklaces in lexicographic order

Based on FKM-algorithm by Fredricksen, Kessler, Maiorana as discussed by Donald Knuth as Algorithm F (Prime and preprime string generation) in: Knuth, Donald E.: The Art of Computer Programming, Vol. 4: Fascicle 2. Generating All Tuples and Permutations. Upper Saddle River, NJ 2005.

Functions:
  int gen_neck_lex_init(unsigned char *vector, const unsigned char m, const unsigned char n)
    Test for special cases
    Initialization of vector
    Possible return values are: GEN_EMPTY, GEN_NEXT

  int gen_neck_lex_next(unsigned char *vector, const unsigned char m, const unsigned char n)
    Transforms current figure in vector into its successor
    Possible return values are: GEN_NEXT, GEN_TERM

Arguments:
  unsigned char *vector; //pointer to the array where the current figure is stored
  const unsigned char m; //length of alphabet
  const unsigned char n; //length of figures

Usage and restrictions:
  Arguments and elements in vector are restricted to the interval (0, 255)
  Memory allocation for vector must be provided by the calling process

Cardinality see:
  http://mathworld.wolfram.com/Necklace.html
*/

#include "_generate.h"

int gen_neck_lex_init(unsigned char *vector, const unsigned char m, const unsigned char n)
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

int gen_neck_lex_next(unsigned char *vector, const unsigned char m, const unsigned char n)
{
int j; //index
int i; //help index
int r; //temporary remainder, for hand made modulo computation only

SKIP: //previous prenecklace skipped

//find rightmost element to increase
for(j = n - 1; j >= 0; j--)
 if(vector[j] < m - 1)
  break;

//terminate if all elements are m - 1
if(j < 0)
 return(GEN_TERM);

//increase
vector[j]++;

//set right-hand elements
for(i = j + 1; i < n; i++)
 vector[i] = vector[i - j - 1];

//necklaces only
r = n;
j++;

while(r >= j)
 r -= j;

if(r > 0)
 goto SKIP; //skip this prenecklace

return(GEN_NEXT);
}
