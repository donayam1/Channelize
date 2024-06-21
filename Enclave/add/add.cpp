#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../../Shared/shared_sgx.h"
#include <stdlib.h> 
#include <sgx_trts.h>
#include "../Enclave_t.h"

using namespace std;

/*
    function that adds the number x[index] to itself n-times and checks if the result is equal to  product 
    x in an integer array   
*/
VIP_ENCBOOL ecall_add(int *x,size_t length,int all,int expected){
    
    int sum = 0;
    uint32_t random; 
    for (int i=0; i<length; i++){        
        sgx_read_rand((unsigned char *) &random, 4);
        random %= length;

        #ifdef VIP_DO_MODE            
            int num=0;
            int index = VIP_CMOV(all==0,0,random);

            for(int j=0;j<length;j++) {
                num = VIP_CMOV(j==index, x[j], num);
            }
            sum += num;
        #else 
            if(all==0) {
                sum += x[0]; //expect almost no cache miss 
            }else {
                // int random =  rand()%SIZE;
                // printf("%7d\n",random);
                sum += x[random]; //expect a lot of cache miss 
            }
        #endif
    }
    #ifdef VIP_DO_MODE
    
        bool res = false;
        res = VIP_CMOV(sum == expected,true,false);
        // res = VIP_CMOV(sum != expected,returnFalse(),res);
        return res;
    
    #else

        if(sum == expected){
            return returnTrue();
        }else{
            return returnFalse();
        }
        
    #endif 

    
    
}

// void testAdd(char **argv){
//     //Create a dynamic array to hold the values
// 	vector<int> numbers;

// 	// //Create an input file stream
//     char* fileName = argv[1];
// 	ifstream in(fileName,ios::in);	
//     int number;  //Variable to hold each number as it is read
//     while (in >> number) {
// 		numbers.push_back(number);
// 	}
//     in.close();
//     int all = atoi(argv[2]);
//     int max = atoi(argv[3]);
//     // int freq = atoi(argv[3]);


//     size_t count = numbers.size();
//     int* x = &numbers[0];
//     // int x[]= {1,2,3,4};

//     VIP_ENCBOOL res  = ecall_add(x,count, all,max);
    
//     printf("%d\n",res);
    
// }

// int main(int argc, char *argv[])
// {
    

//     if(argc < 3){
//         printf("Usage format ./app filename all max \n");
//         exit(1);
//     }


//    testAdd(argv);
   
        
// 	return 0;
// }