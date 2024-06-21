
// #include "../Enclave_t.h"
#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../../Shared/shared_se.h"
#include "../src/vip-functional-library.h"
#include <stdlib.h> 
using namespace std;
using namespace enc_lib;
     
/**
 s: int array to check for duplicate values 
 number: the number to look for 
 efreq: the frequency to check for
 Asummption: the maximum element in s is less than or equal to SIZE  
*/

enc_int* setA;
enc_int* setB;
int arr_size;
enc_bool *setA_match;

enc_bool set_intersect()
{
  enc_bool res = false;
  for (int i=0; i < arr_size; i++)
  {
    enc_bool match = false;
    for (int j=0; j < arr_size; j++)
    {
        #ifdef VIP_DO_MODE
            match = CMOV(setA[i] == setB[j], true, match);
          
        #else /* !VIP_DO_MODE */
            if (setA[i] == setB[j]){
                match = true;
                res = true;
            }
        #endif /* VIP_DO_MODE */
    }
    res = CMOV(match,match,res);
    setA_match[i] = match;
  }
  return res;
}

void testSetIntersection(char **argv){
    //Create a dynamic array to hold the values
	vector<enc_int> numbersA;
    vector<enc_int> numbersB;
    

	//Create an input file stream
    char* outFileNameA = argv[1];
    char* fileNameA = argv[2];
	ifstream in(fileNameA,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
        enc_int numx = number;
		numbersA.push_back(numx);
	}
    in.close();
    size_t count1 = numbersA.size();

    //Create an input file stream
    char* fileNameB = argv[3];
	ifstream in2(fileNameB,ios::in);	
    int number2;  //Variable to hold each number as it is read
    while (in2 >> number2) {
         enc_int numx = number2;
		numbersB.push_back(numx);
	}
    in2.close();
   
    // size_t count2 = numbersB.size();
    vector<enc_bool> matchs(count1);

    setA  = &numbersA[0];
    setB = &numbersB[0];
    arr_size = count1;
    setA_match= &matchs[0];
    enc_bool res = profile_func(set_intersect,outFileNameA);    
    printf("%d\n",res.GET_DECRYPTED_VALUE());    
}

int main(int argc, char *argv[])
{
    if(argc < 4){
        printf("Usage format ./app outFileName filename num freq\n");
        exit(1);
    }
    VIPInit();
   testSetIntersection(argv);
          
    return 0;
}
