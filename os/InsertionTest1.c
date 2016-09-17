//
//  InsertionTest1.c
//  os
//
//  Created by Sergey Nasonov on 04/09/16.
//  Copyright © 2016 Sergey Nasonov. All rights reserved.
//

#include <stdio.h>


int InsertionTest1(void)
{
	int m[] = {8,7,9,3,4,1,2,0,5,6};

	for (int i = 1; i<sizeof(m)/sizeof(int) ; i++)
	{
		int k=i-1;
		int min=m[i];
	
		while (k>=0 && min < m[k])
		{
			m[k+1]=m[k];
			k--;
		}
		m[k+1] = min;

	}
	
	for (int i=0; i<sizeof(m)/sizeof(int); i++) {
		printf("%d, ", m[i]);
	}
	
	return 0;
}
