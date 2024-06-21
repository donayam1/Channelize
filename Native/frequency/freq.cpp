
// #include "../Enclave_t.h"
#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../../Shared/shared.h"
#include <stdlib.h> 
using namespace std;

     

int *array;
size_t arr_size;
int number;
int efreq;     
/**
 s: int array to check for duplicate values 
 number: the number to look for 
 efreq: the frequency to check for
 Asummption: the maximum element in s is less than or equal to SIZE  
*/
VIP_ENCBOOL ecall_checkFreqecny() {
    int* freq = (int*)calloc(arr_size, sizeof(int));
    //Calculate the frequency of every number 
    for(int i =0;i<arr_size;i++){ 
        // int index = s[i];
        // printf("%d\n",index);
        #ifdef VIP_DO_MODE            
            for(int j=0;j<arr_size;j++){
                freq[j] = VIP_CMOV(array[i]==j,freq[j]+1,freq[j]);
            }
        #else 
            freq[array[i]] += 1; 
        #endif 
    }    
    
    #ifdef VIP_DO_MODE    
        bool res = false;
        for(int j=0;j<arr_size;j++) {
            res = VIP_CMOV(number ==j,freq[j] == efreq,res);
        }
        return res;    
    #else
        // printf("%d,%d,%d",number,freq[number],efreq);
        return freq[number] == efreq;   

    #endif 
}

void testCheckFreqecny(char **argv){
    //Create a dynamic array to hold the values
	vector<int> numbers;

	//Create an input file stream
    char* outfileName = argv[1];
    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    int int_number;  //Variable to hold each number as it is read
    while (in >> int_number) {
		numbers.push_back(int_number);
	}
    in.close();

    number = numbers[0]; // atoi(argv[3]);
    efreq = atoi(argv[3]);


    arr_size = numbers.size();
    array = &numbers[0];
    VIP_ENCBOOL res  = profile_func(ecall_checkFreqecny,outfileName);
    
    printf("%d\n",res);
    
}
// void testCheckFreqecny_maxrunin(char **argv){
//     //Create a dynamic array to hold the values
// 	vector<int> numbers;

// 	//Create an input file stream
//     char* fileName = argv[1];
// 	ifstream in(fileName,ios::in);	
//     int number;  //Variable to hold each number as it is read
//     while (in >> number) {
// 		numbers.push_back(number);
// 	}
//     in.close();

//     int freq = atoi(argv[2])+1;
//     int num  = numbers[0];
     


//     size_t count = numbers.size();
//     int* a = &numbers[0];
//     VIP_ENCBOOL res  = ecall_checkFreqecny(a, count,num,freq);
    
//     printf("\n%d\n",res);    
// }

int main(int argc, char *argv[])
{
    if(argc < 4){
        printf("Usage format ./app outfileName filename num freq\n");
        exit(1);
    }

   testCheckFreqecny(argv);
//    testCheckFreqecny_maxrunin(argv);
        
	return 0;
}
