
// #include "../Enclave_t.h"
#include "../../Shared/shared_se.h"
#include "../src/vip-functional-library.h"
#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
// #include "../../Shared/shared.h"
#include <stdlib.h> 

using namespace std;
using namespace enc_lib;

     
enc_int *array;
size_t arr_size;
enc_int number;
enc_int efreq;  

/**
 s: int array to check for duplicate values 
 number: the number to look for 
 efreq: the frequency to check for
 Asummption: the maximum element in s is less than or equal to SIZE  
*/
enc_bool ecall_checkFreqecny() {
    enc_int *freq = (enc_int*)malloc(sizeof(enc_int)*arr_size);
    for(int k=0;k<arr_size;k++){
        freq[k] = 0;
        // printf("freq %d= %d\n",k,freq[k].GET_DECRYPTED_VALUE());
    }
    //Calculate the frequency of every number 
    for(long i =0;i<arr_size;i++){ 

        #ifdef VIP_DO_MODE
            
            for(long j=0;j<arr_size;j++){                
                freq[j] = CMOV(array[i] == j,freq[j]+1,freq[j]);
            }
        #else 
            freq[array[i]] += 1; 
        #endif 
    }        
    #ifdef VIP_DO_MODE    
       enc_bool res = false;
        for(long j=0;j<arr_size;j++) {
            res = CMOV(number == j,freq[j] == efreq,res);
            // res = VIP_CMOV(freq[number] != efreq,returnFalse(),res);
        }
        return res;    
    #else
        if(freq[number] == efreq) {
            return returnTrue();
        } else {
            return returnFalse();  
        }        
    #endif 
}

void testCheckFreqecny(char **argv){
    //Create a dynamic array to hold the values
	vector<enc_int> numbers;

	//Create an input file stream
    char* outfilename = argv[1];    
    // printf("outputfile=%s\n",outfilename);

    char* fileName = argv[2];
    // printf("fileName = %s\n",fileName);

	ifstream in(fileName,ios::in);	
    int innumber;  //Variable to hold each number as it is read
    while (in >> innumber) {
        enc_int number_e = innumber;
		numbers.push_back(number_e);
	}
    in.close();

    number = atoi(argv[3]);
    efreq = atoi(argv[4]);
    // printf("number=%ld\n",number.GET_DECRYPTED_VALUE());
    // printf("efreq=%ld\n",efreq.GET_DECRYPTED_VALUE());

    arr_size = numbers.size();
    array = &numbers[0];
    // printf("arr_size= %d",arr_size);
    enc_bool res  = profile_func(ecall_checkFreqecny,outfilename);
    
    printf("%d\n",res.GET_DECRYPTED_VALUE());
    
}

int main(int argc, char *argv[])
{
    if(argc < 5){
        printf("Usage format ./app outfileName filename num freq\n");
        exit(1);
    }
   VIPInit();
   testCheckFreqecny(argv);
   
        
	return 0;
}
