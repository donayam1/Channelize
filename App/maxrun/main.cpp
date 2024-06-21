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

void testmaxrun(int argc, char *argv[])
{
    if(argc < 4){
        printf("Usage format ./app outfile infile maxrun\n");
        exit(1);
    }
	
	vector<VIP_ENCINT> numbers;

	//Create an input file stream
    char* outfileName = argv[1];

    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbers.push_back(number);
	}
    in.close();


    int expected = atoi(argv[3]);	
    int arr_size = numbers.size();
    int* array = &numbers[0];
    
    // ecall_maxrun(VIP_ENCINT *array, size_t size,VIP_ENCINT expected) 
    bool res = profile_func(ecall_maxrun, outfileName, global_eid, array, arr_size,expected);
    // bool res = profile_func(maxrun2,outfileName);
    // bool res = maxrun2();
    printf("%d\n",res);

	// return 0;
}
