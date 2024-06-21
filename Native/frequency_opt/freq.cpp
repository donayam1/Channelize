
// #include "../Enclave_t.h"
#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../../Shared/shared.h"
#include <stdlib.h> 
using namespace std;

     
/**
 s: int array to check for duplicate values 
 number: the number to look for 
 efreq: the frequency to check for
 Asummption: the maximum element in s is less than or equal to SIZE  
*/
VIP_ENCBOOL ecall_checkFreqecny(int *s,size_t length,int number,int efreq) {
    int *freq = (int*)malloc(sizeof(int)*length);
    //Calculate the frequency of every number 
    for(long i =0;i<length;i++){ 
        int index = s[i];
        // printf("%d\n",index);
        #ifdef VIP_DO_MODE
            
            for(long j=0;j<length;j++){
                freq[j] = VIP_CMOV(index==j,freq[j]+1,freq[j]);
            }
        #else 
            freq[index] += 1; 
        #endif 
    }    
    
    #ifdef VIP_DO_MODE    
        bool res = false;
        for(long j=0;j<length;j++) {
            res = VIP_CMOV(number ==j,freq[j] == efreq,res);
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
	vector<int> numbers;

	//Create an input file stream
    char* fileName = argv[1];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbers.push_back(number);
	}
    in.close();

    int num = atoi(argv[2]);
    int freq = atoi(argv[3]);


    size_t count = numbers.size();
    int* a = &numbers[0];
    VIP_ENCBOOL res  = ecall_checkFreqecny(a, count,num,freq);
    
    printf("%d\n",res);
    
}

int main(int argc, char *argv[])
{
    if(argc < 4){
        printf("Usage format ./app filename num freq\n");
        exit(1);
    }

   testCheckFreqecny(argv);
   
        
	return 0;
}
