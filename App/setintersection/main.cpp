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


void testSetIntersection(int argc, char **argv){
	if(argc < 4){
        	 printf("Usage format ./app outfileName filenameA filenameB\n");
         	exit(1);
         }

    //Create a dynamic array to hold the values
	vector<int> numbersA;
    vector<int> numbersB;
    

	//Create an input file stream
    char* outfileName= argv[1];
    char* fileNameA = argv[2];
	ifstream in(fileNameA,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbersA.push_back(number);
	}
    in.close();
    size_t count1 = numbersA.size();

    //Create an input file stream
    char* fileNameB = argv[3];
	ifstream in2(fileNameB,ios::in);	
    int number2;  //Variable to hold each number as it is read
    while (in2 >> number2) {
		numbersB.push_back(number2);
	}
    in2.close();
   
    size_t count2 = numbersB.size();
    
    int*a  = &numbersA[0];
    int*b = &numbersB[0];

    VIP_ENCBOOL res;
    res = profile_func(ecall_set_intersect, outfileName, global_eid, a,b,count1, count2);
   
    printf("%d\n",res);

   // sgx_status_t status0 = ecall_set_intersect(global_eid, &res, a,b, count1,count2);

   
}

