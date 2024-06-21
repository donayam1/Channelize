#include <stdlib.h>
#include "../../Shared/shared_se.h"
#include "../src/vip-functional-library.h"
#include <limits>
#include <stdio.h>
#include <vector>
#include <fstream>

using namespace std;
using namespace enc_lib;

enc_int *array;
int arr_size;
enc_int expected;

//Trains Branch predictor 
enc_bool maxrun() {
   enc_int max = -1;
   enc_int current = 1;   
   enc_int one =1;
   
   for (int i = 1; i < arr_size; i++) {
      #ifdef VIP_DO_MODE
          enc_bool cond = array[i - 1] == array[i];
          current = CMOV(cond,current+1,one);

          enc_bool cond2 = current > max;
          max = CMOV(cond2,current,max);
      #else   
        if (array[i - 1] == array[i]) {    /* the run continues */
            current++;
            max = current > max ? current : max;
        } else {    /* the run was broken */
            current = 1;
        }
      #endif 
   }    
   return max == expected;
}

int main(int argc, char *argv[])
{
    VIPInit();
    if(argc < 3){
        printf("Usage format ./app filename expected\n");
        exit(1);
    }	
	vector<enc_int> numbers;

    char *outfilename = argv[1];
	//Create an input file stream
    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
        enc_int numx = number;
		numbers.push_back(numx);
	}
    in.close();
    enc_int ex = atoi(argv[3]);	 
    expected = ex;	
    arr_size = numbers.size();
    array = &numbers[0];

    
    enc_bool res = profile_func(maxrun,outfilename);
    printf("expected=%d, res= %d\n",expected.GET_DECRYPTED_VALUE(), res.GET_DECRYPTED_VALUE());

	return 0;
}

// int main(int argc, char *argv[])
// {
   

//     enc_int expected = 2;
	
//     size_t count = 6;
//     enc_int a[] = {1,2,2,3,4,5};

    
//     enc_bool res = maxrun(a,count,expected);
//     printf("expected=%d, res= %d\n",expected.GET_DECRYPTED_VALUE(), res.GET_DECRYPTED_VALUE());

// 	return 0;
// }