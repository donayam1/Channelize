#include <stdio.h>
#include <string.h>
#include <assert.h>
// #include <sys/time.h>

# include <unistd.h>
// # include <pwd.h>
# define MAX_PATH FILENAME_MAX

#include <sgx_urts.h>
#include <sgx_uswitchless.h>
#include "App.h"
#include "Enclave_u.h"

/////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <limits>
#include <unistd.h>
#include <omp.h>
#include <fstream>

#include <vector>
#include "profile.h"


using namespace std;


void testCheckFreqency(int argc, char **argv){
    if(argc < 4){
        printf("Usage format ./app outfileName filename num freq\n");
        exit(1);
    }
    //Create a dynamic array to hold the values
	vector<int> numbers;
    printf("Starting");
	//Create an input file stream
    char* outfileName = argv[1];
    char* fileName = argv[2];
    // printf("file input=%s\n",fileName);
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbers.push_back(number);
	}
    in.close();

    int num = atoi(argv[3]);
    int freq = atoi(argv[4]);
    // printf("%d  , %d\n",num,freq);

    size_t count = numbers.size();
    int* a = &numbers[0];    
    VIP_ENCBOOL res;
    // printf("%d,%d,%d",count,num,freq);
    res = profile_func(ecall_checkFreqecny, outfileName, global_eid, a, count,num,freq);
    // sgx_status_t status0 = ecall_checkFreqecny(global_eid, &res, a, count,num,freq);
    // if (status0 != SGX_SUCCESS) {
    //     printf("ERROR: ECall failed\n");
    //     print_error_message(status0);
    //     exit(-1);
    // }
    // sgx_destroy_enclave(global_eid);
    printf("%d\n",res);
    
}

// void testDistinctness(int argc,char **argv){
    
//     if(argc < 3){
//         printf("Usage format ./app outfileName filename\n");
//         exit(1);
//     }

//     //Create a dynamic array to hold the values
// 	vector<VIP_ENCINT> numbers;

// 	//Create an input file stream
//     char* outfileName= argv[1];
//     char* fileName = argv[2];
// 	ifstream in(fileName,ios::in);	
//     int number;  //Variable to hold each number as it is read
//     while (in >> number) {
// 		numbers.push_back(number);
// 	}
//     in.close();


//     size_t count = numbers.size();
//     int* a = &numbers[0];
    
//     VIP_ENCBOOL res;
//     res = profile_func(ecall_isDistinct, outfileName, global_eid, a, count);
   
//     printf("%d\n",res);
// }


// void testValidParenthesis(int argc, char **argv) {
//     if(argc < 3){
//         printf("Usage format ./app outfileName filename\n");
//         exit(1);
//     }

//     //Create a dynamic array to hold the values
// 	vector<char> chars;

// 	//Create an input file stream
//     char* outfileName = argv[1];
//     char* fileName = argv[2];
// 	ifstream in(fileName,ios::in);	
//     char brace;  //Variable to hold each number as it is read
//     while (in >> brace) {
// 		chars.push_back(brace);
// 	}
//     in.close();


//     size_t count = chars.size();
//     char* a = &chars[0];

//     VIP_ENCBOOL res;
//     res = profile_func(ecall_isValid, outfileName, global_eid, a, count);
   
   
//     printf("%d\n",res);
// }