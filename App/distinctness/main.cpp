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


void testDistinctness(int argc,char **argv){
    
    if(argc < 3){
        printf("Usage format ./app outfileName filename\n");
        exit(1);
    }

    //Create a dynamic array to hold the values
	vector<VIP_ENCINT> numbers;

	//Create an input file stream
    char* outfileName= argv[1];
    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbers.push_back(number);
	}
    in.close();


    size_t count = numbers.size();
    int* a = &numbers[0];
    
    VIP_ENCBOOL res;
    res = profile_func(ecall_isDistinct, outfileName, global_eid, a, count);
   
    printf("%d\n",res);
}


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