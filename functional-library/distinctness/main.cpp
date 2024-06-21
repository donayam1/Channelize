

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

enc_bool isDistinct()
{
#ifdef VIP_DO_MODE
  enc_bool dup = false;

  for (int i=0; i < arr_size-1; i++)
  {	
    for (int j = i+1; j < arr_size; j++){		
	  enc_bool cond = (array[i] == array[j]); 	 	
      dup = CMOV(cond, cond, dup);
	}	
  }
  return !dup;
#else /* !VIP_DO_MODE */
	for (int i=0; i < arr_size-1; i++)
	{	
		for (int j = i+1; j < arr_size; j++){		
			enc_bool cond = (array[i] == array[j]); 	 	
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
    char *outfileNmae = argv[1];
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
    enc_int dup;
    enc_bool res = profile_func(isDistinct,outfileNmae);
    printf("%d\n",res.GET_DECRYPTED_VALUE());

    // if (res1)
    //         cout<<"The elements of `elements1' are distinct"<<endl;
    //     else
    //         cout<<"The elements of `elements1' are not distinct (e.g., " << dup << " is duplicated)"<<endl;
        
	return 0;
}

// int main(int argc, char *argv[])
// {
// 	enc_int a[] = {1,2,3,4,5,6,7};
// 	enc_bool res= isDistinct(a,7);
// 	printf("res = %d",res.value);
// }