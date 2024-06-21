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


void testAdd(int argc, char **argv){
    if(argc < 5){
        printf("Usage format ./app outFileName filename all expected \n");
        exit(1);
    }
    //Create a dynamic array to hold the values
	vector<int> numbers;

	// //Create an input file stream
    char* outfileName = argv[1];
    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbers.push_back(number);
	}
    in.close();


    int add_index_zero = atoi(argv[3]);
    // printf("add_index_0=%d",add_index_zero);
    int expected = atoi(argv[4]);
    size_t arr_size= numbers.size();
    int* array = &numbers[0];
    //VIP_ENCBOOL ecall_add(int *x,size_t length,int all,int expected)
    VIP_ENCBOOL res  = profile_func(ecall_add,outfileName,global_eid,array,arr_size,add_index_zero,expected);
      // profile_func(ecall_add, outfileName, global_eid, elements, arr_size ,dup);
    printf("%d\n",res);    
}

// int testContains(int argc, char *argv[])
// {
//     if(argc < 4){
//         printf("Usage format ./app outfileName filename index\n");
//         exit(1);
//     }
	
// 	vector<VIP_ENCINT> numbers;

// 	//Create an input file stream
// 	char* outfileName = argv[1];
//     char* fileName = argv[2];
// 	ifstream in(fileName,ios::in);	
//     int number;  //Variable to hold each number as it is read
//     while (in >> number) {
// 		numbers.push_back(number);
// 	}
//     in.close();

// 	int dup = atoi(argv[3]);
	
	
//     size_t arr_size = numbers.size();
//     int* elements = &numbers[0];

//     // ecall_contains(VIP_ENCINT *elements,size_t arr_size,VIP_ENCINT dup)    
//     VIP_ENCBOOL res = profile_func(ecall_contains, outfileName, global_eid, elements, arr_size ,dup); //profile_func(Contains,outfileName);
//     printf("%d\n",res);

// 	return 0;
// }

