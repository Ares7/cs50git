//
//  os
//
//  Created by Sergey Nasonov on 05/09/16.
//  Copyright © 2016 Sergey Nasonov. All rights reserved.
//

#include <stdio.h>//printf
#include <string.h>

#include <iostream>//C++ cout/cin
using namespace std;

int main()
{
	int m[] = {8,7,9,3,4,1,2,0,5,6};
	
	string trType;
	int trNum;
	string trMtd;
	
	int k = 1;
	
	while (cin.eof())
		{
		cin>>trType>>trNum>>trMtd;
		cout<<"OUT: "<<k<<" " <<trType<<trNum<<trMtd;
		k++;
		}
	
	
	
	for (int i=0; i<sizeof(m)/sizeof(int); i++) {
		//cout<<"he";
	}
	
	return 0;
}