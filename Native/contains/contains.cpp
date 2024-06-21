

// #include "distinctness.h"
#include <stdlib.h>
#include "../../Shared/shared.h"
#include <limits>
#include <stdio.h>
#include <vector>
#include <fstream>
// #include "../config.h"

using namespace std;

// #define VIP_DO_MODE

// #define SIZE  100
// #define MAX numeric_limits<int>::max()

// typedef int VIP_ENCINT  ;
// typedef bool VIP_ENCBOOL ;


// inline int __attribute__((always_inline))  CMOV(bool cond, int v_true, int v_false) {
//                 int result;
//                 __asm__ __volatile__ (
//                     "test   %1, %1;"
//                     "cmovz  %3, %0;"  //zero flag cleared?
//                     "cmovnz %2, %0;" //zero flag not cleared?
//                     : "=r" (result)
//                     : "r" (cond), "r" (v_true), "r" (v_false)
//                     : "cc"
//                 );
//                 return result;
// }
VIP_ENCINT *elements;
size_t arr_size; 
VIP_ENCINT dup;

VIP_ENCBOOL Contains()
{
	VIP_ENCBOOL res = false; 
	for(int i=0;i<arr_size;i++){
		#ifdef VIP_DO_MODE
			VIP_ENCBOOL cond = elements[i] == dup;
			res = CMOV(cond ,true, res);
		#else
		if (elements[i] == dup){
			return true;
		}
		#endif  
	}
	#ifdef VIP_DO_MODE
		return res;
	#else
		return false;
	#endif 
}


int main(int argc, char *argv[])
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

	dup = atoi(argv[3]);
	
	
    arr_size = numbers.size();
    elements = &numbers[0];

    
    VIP_ENCBOOL res = profile_func(Contains,outfileName);
    printf("%d\n",res);

	return 0;
}

