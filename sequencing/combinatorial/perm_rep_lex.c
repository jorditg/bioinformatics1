/* 24.12.2008 last modification: 26.06.2013
Copyright (c) 2008-2013 by Siegfried Koepf

This file is distributed under the terms of the GNU General Public License
version 3 as published by the Free Software Foundation.
For information on usage and redistribution and for a disclaimer of all
warranties, see the file COPYING in this distribution.

Permutations with repetition in lexicographic order

Based on Algorithm L (Lexicographic permutation generation) in: Knuth, Donald E.: The Art of Computer Programming, Vol. 4: Fascicle 2. Generating All Tuples and Permutations. Upper Saddle River, NJ 2005.

Functions:
  int gen_perm_rep_lex_init(const unsigned char n)
    Test for special cases
    Possible return values are: GEN_EMPTY, GEN_NEXT

  int gen_perm_rep_lex_next(unsigned char *vector, const unsigned char n)
    Transforms current figure in vector into its successor
    Possible return values are: GEN_NEXT, GEN_TERM

Arguments:
  unsigned char *vector; //pointer to the array where the current figure is stored
  const unsigned char n; //length of alphabet
  const unsigned char k; //length of figures

Usage and restrictions:
  Arguments and elements in vector are restricted to the interval (0, 255)
  Memory allocation for vector must be provided by the calling process
  vector must be initialized by the calling process. At that point elements in vector must be arranged in increasing order to obtain all possible permutations

Cardinality:
  n! / ((s(1)! * ... * s(x)!)) with s(1) + ... + s(x) == n where s(x) is the number of occurrences of the xth disitinct element
*/

#include "_generate.h"

int gen_perm_rep_lex_init(const unsigned char n)
{
//test for special cases
if(n == 0)
 return(GEN_EMPTY);

//initialize: vector must be initialized by the calling process

return(GEN_NEXT);
}

int gen_perm_rep_lex_next(unsigned char *vector, const unsigned char n)
{
int j = n - 2; //index
int i = n - 1; //help index
int temp;      //auxiliary element

//find rightmost element to increase
while(j >= 0)
 {
 if(vector[j] < vector[j + 1])
  break;

 j--;
 }

//terminate if all elements are in decreasing order
if(j < 0)
 return(GEN_TERM);

//find i
while(vector[i] <= vector[j])
 i--;

//increase (swap)
temp = vector[j];
vector[j] = vector[i];
vector[i] = temp;

//reverse right-hand elements
for(j += 1, i = n - 1; j < i;  j++, i--)
 {
 temp = vector[j];
 vector[j] = vector[i];
 vector[i] = temp;
 }

return(GEN_NEXT);
}
