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

int testContains(int argc, char *argv[])
{
    if(argc < 4){
        printf("Usage format ./app outfileName filename index\n");
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

	int dup = atoi(argv[3]);
	
	
    size_t arr_size = numbers.size();
    int* elements = &numbers[0];

    // ecall_contains(VIP_ENCINT *elements,size_t arr_size,VIP_ENCINT dup)    
    VIP_ENCBOOL res = profile_func(ecall_contains, outfileName, global_eid, elements, arr_size ,dup); //profile_func(Contains,outfileName);
    printf("%d\n",res);

	return 0;
}

