

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


enc_int *array;
size_t arr_size;

enc_bool isDistinct_leaky()
{
#ifdef VIP_DO_MODE
  enc_bool dup = false;

  for (int i=0; i < arr_size; i++)
  {	
    for (int j=0; j < arr_size; j++){		
	  enc_bool cond = ((array[i] == array[j]) && (i!=j)); 	 	
      dup = CMOV(cond, cond, dup);
	}	
  }
  return !dup;
#else /* !VIP_DO_MODE */
		for (int i=0; i < arr_size; i++)
		{	
			for (int j=0; j < arr_size; j++){		
			enc_bool cond = ((array[i] == array[j]) && (i!=j)); 	 	
				if(cond){
					return false;
				}
			}	
		}
		return true;
#endif /* VIP_DO_MODE */
}


int main(int argc, char *argv[])
{	
    if(argc < 3){
        printf("Usage format ./app outfileName filename\n");
        exit(1);
    }
    VIPInit();
	// printf("Main Called\n");
    //Create a dynamic array to hold the values
	vector<enc_int> numbers;

	//Create an input file stream
    char* outfileName = argv[1];
    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		enc_int num = number;
		numbers.push_back(num);
	}
    in.close();
	// printf("Function Called\n");
    arr_size = numbers.size();
    array = &numbers[0];    
    enc_bool res = profile_func(isDistinct_leaky,outfileName);
    printf("%d\n",res.GET_DECRYPTED_VALUE());

 
	return 0;
}

