
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
// #include "../src/interface/interface.h"
#include <stdint.h>

using namespace std;
using namespace enc_lib;

     
/**
 s: int array to check for duplicate values 
 number: the number to look for 
 efreq: the frequency to check for
 Asummption: the maximum element in s is less than or equal to SIZE  
*/
enc_bool ecall_checkFreqecny(enc_int *s,size_t length,enc_int number,enc_int efreq) {
    enc_int *freq = (enc_int*)malloc(sizeof(enc_int)*length);
    
    for(int k=0;k<length;k++){
        freq[k] = 0;
        // printf("freq %d= %d\n",k,freq[k].GET_DECRYPTED_VALUE());
    }
    //Calculate the frequency of every number 
    for(long i =0;i<length;i++){         
        #ifdef VIP_DO_MODE
            
            for(int j=0;j<length;j++){                
                // enc_int new_f = freq[j]+1;
                // printf("new_f %d, freqj=%d\n",j,new_f,freq[j].GET_DECRYPTED_VALUE());
                freq[j] = CMOV(s[i] == j,freq[j]+1,freq[j]);
                // printf("freq %d= %d\n",j,freq[j].GET_DECRYPTED_VALUE());
            }
        #else 
            freq[index] += 1; 
        #endif 
    }    
    
    #ifdef VIP_DO_MODE    
       enc_bool res = false;
        for(int j=0;j<length;j++) {
            // printf("%d = %d\n",j, freq[j].GET_DECRYPTED_VALUE() );
            res = CMOV(number==j,freq[j] == efreq,res);
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
    char* fileName = argv[1];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
        enc_int number_e = number;
		numbers.push_back(number_e);
	}
    in.close();

    enc_int num = atoi(argv[2]);
    enc_int freq = atoi(argv[3]);


    size_t count = numbers.size();
    enc_int* a = &numbers[0];
    enc_bool res  = ecall_checkFreqecny(a, count,num,freq);
    
    printf("%d\n",res.GET_DECRYPTED_VALUE());
    
}

int main(int argc, char *argv[])
{
    
    if(argc < 4){
        printf("Usage format ./app filename num freq\n");
        exit(1);
    }
   VIPInit();
   testCheckFreqecny(argv);
   
        
	return 0;
}
// int main0(int argc, char *argv[])
// {
//     VIPInit();
//     enc_int a[]= {1,2,3,4,5,6};
//     int count = 6;
//     enc_int num = 4;
//     enc_int freq = 2;
//     enc_bool res  = ecall_checkFreqecny(a, count,num,freq);
//     printf("res=%d\n",res.GET_DECRYPTED_VALUE());
        
// 	return 0;
// }