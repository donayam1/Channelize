

// #include "distinctness.h"
#include <stdlib.h>
#include "../../Shared/shared_se.h"
#include "../src/vip-functional-library.h"
#include <limits>
#include <stdio.h>
#include <vector>
#include <fstream>
// #include "../config.h"

using namespace std;
using namespace enc_lib;

enc_int *elements;
int arr_size;
enc_int dup;
/*Early exit timing */
enc_bool Contains()
{	
	enc_bool res = false; 	
	for(int i=0;i<arr_size;i++){		
		enc_bool cond = (elements[i] == dup);// && !done;			
		res = CMOV(cond,cond,res);
	}
	return res;	
}


int main(int argc, char *argv[])
{
	VIPInit();
    if(argc < 4){
        printf("Usage format ./app outFilename filename index\n");
        exit(1);
    }
	VIPInit();
	vector<enc_int> numbers;

	//Create an input file stream
	char* outfileName = argv[1];
    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		enc_int numx = number;
		numbers.push_back(numx);
	}
    in.close();

	dup  = atoi(argv[3]);	
    arr_size = numbers.size();
    elements = &numbers[0];

    // printf("a=%d\n",a[1].GET_DECRYPTED_VALUE());
	// printf("dup = %d\n",dup.GET_DECRYPTED_VALUE());
    enc_bool res = profile_func(Contains,outfileName);
    printf("%d\n",res.GET_DECRYPTED_VALUE());

	return 0;
}


// int main(int argc, char *argv[])
// {
  
	

// 	enc_int dup = 7;
	
//     int count = 6;
//     enc_int a[] = {1,2,3,4,5,6};

    
//     enc_bool res = Contains(a,count, dup);
//     printf("%d\n",res.GET_DECRYPTED_VALUE());

// 	return 0;
// }

