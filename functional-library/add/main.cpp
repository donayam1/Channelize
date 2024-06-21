// #include "../src/datatypes/enc_lib.h"
#include "../../Shared/shared_se.h"
#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../src/vip-functional-library.h"
#include <stdlib.h> 

#include <cstring>
#include <unistd.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <asm/unistd.h>
using namespace std;
using namespace enc_lib;

/*
    function that adds the number x[index] to itself n-times and checks if the result is equal to  product 
    x in an integer array   
*/
enc_int *x;
int arr_size;
enc_int all;
enc_int expected;

enc_bool ecall_add(){
    
    enc_int sum = 0;
    enc_int zero=0;
    enc_int ran_enc;
    enc_bool cond = all == 0;

    for (int i=0;i<arr_size;i++){
        int random = rand()%arr_size;
            ran_enc = random;
        #ifdef VIP_DO_MODE            
            enc_int num = 0;
            
            enc_int index = CMOV(cond,zero,ran_enc);

            for(int j=0;j<arr_size;j++) {             
                num = CMOV(index == j, x[j], num);
            }
            sum = sum + num;
        #else 
            if(all==0) {
                sum += x[0]; //expect almost no cache miss 
            }else {
                sum += x[random]; //expect a lot of cache miss 
            }
        #endif
    }
    #ifdef VIP_DO_MODE            
        enc_bool cond3= sum == expected;                
        enc_bool res = CMOV(cond3,cond3,false);        
        return res;
    
    #else
        if(sum == expected){
            return returnTrue();
        }else{
            return returnFalse();
        }        
    #endif 
}

void testAdd(char **argv){
    VIPInit();
    //Create a dynamic array to hold the values
	vector<enc_int> numbers;

	// //Create an input file stream
    char* outFileName = argv[1];
    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    enc_int numx;
    while (in >> number) {
        numx = number;
		numbers.push_back(numx);
	}
    in.close();

    all = atoi(argv[3]);
    expected = atoi(argv[4])/100;
    


    arr_size = numbers.size()/100; //60,000/100
    x = &numbers[0];
    
    // printf("Measuring instruction count for this printf\n");
    enc_bool res  = profile_func(ecall_add,outFileName);       
    printf("%d\n",res.GET_DECRYPTED_VALUE());
}


int main(int argc, char *argv[])
{
    if(argc < 4){
        printf("Usage format ./app outFileName filename all max \n");
        exit(1);
    }

   testAdd(argv);           
	return 0;
}