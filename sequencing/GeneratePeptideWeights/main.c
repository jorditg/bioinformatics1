/* 
 * File:   main.c
 * Author: jordi
 *
 * Created on 8 de diciembre de 2013, 19:59
 */

#include <stdio.h>
#include <stdlib.h>

const char  amino[] = { 'G','A','S','P','V','T','C','I','L','D',
                        'N','Q','K','E','M','H','F','R','Y','W'};

const float weight[20] = { 
                           57.05,71.09,87.08,97.12,99.14,101.11,103.15,
                           113.16,113.16,114.11,115.09,128.14,128.17,
                           129.12,131.19,137.14,147.18,156.19,163.18,186.12
                         };

char advance_idx(int idx[], int m, int n, float max_weight)
{
    if(n*57.05 > max_weight) return 1;
    
    char end = 0;
    int i = n-1;
    do {
        idx[i]++;
        if(idx[i] == m) {
            idx[i]=0;
            i--;
        } else {
            break;
        }
    } while(i>=0);
    
    if(i == -1) end = 1;
    return end;
}

unsigned long choose_by_weight(float max_weight, int m, int n) 
{
    unsigned long count = 0;
    int idx[n];
    for(int i=0;i<n;i++) {
        idx[i] = 0;
    }
    do {
        float w = 0;
        for(int i=0;i<n;i++)
            w += weight[idx[i]];
        if(w < max_weight) {
            for(int i=0;i<n;i++)
                printf("%c", amino[idx[i]]);
            printf(" %f\n", w);
            count++;
        } else {
            idx[n-1] = m-1;
        }
    } while(!advance_idx(&idx[0], m, n, max_weight));
 
    return count;
}



int main(int argc, char* argv[])
{
    float max_weight;
    
    if(argc == 2) { max_weight = atof(argv[1]); }

    int n = 1;
    char end = 0;
    while(1) {
        if(choose_by_weight(max_weight, 20, n) == 0) 
            break;
        n++;        
    }
    //printf("\n%ld choices\n", total);

    return 0;
}

