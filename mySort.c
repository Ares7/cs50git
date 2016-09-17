#include "cs50.c"
#include <stdio.h>

int mySort(void)
{

    int m[] = {8,7,9,3,4,1,2,0,5,6};

    for (int i = 0; i < sizeof(m)/sizeof(int) -1 ; i++)
    {
      int min = i;
      for (int j = i; j < sizeof(m)/sizeof(int); j++)
      {
        if (m[j] < m[min])
          min = j;
      }

      int tmp = m[i];
      m[i]=m[min];
      m[min] = tmp;
      
  }
  for (int j = 0; j < sizeof(m)/sizeof(int); j++)
      {
        printf("%i\n", m[j]);
      }
    return 0;
}