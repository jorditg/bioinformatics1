#include "stdio.h"

int main(void)
{
  char c;
  unsigned char flag = 0;

  char act = '+';
  int count = 0;
  unsigned long reads = 0;
  while (flag == 0)
  {
    scanf("%c",&c);
    reads++;
    if (c == '$')
      flag = 1;
    else { 
        if(c != act) {
            act = c;
            count = 1;
        } else {
            count++;
        }
        
        if(count == 10) {
            printf("%lu\n", reads-10);
        }
    }    
  }

  return (0);
}
