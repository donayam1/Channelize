

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
#define MAX std::numeric_limits<int>::max()

VIP_ENCBOOL Contains(VIP_ENCINT elements[],size_t size, VIP_ENCINT dup)
{
	VIP_ENCBOOL res = false; 
	VIP_ENCBOOL done = false; 
	for(int i=0;i<size;i++){
		#ifdef VIP_DO_MODE
			VIP_ENCBOOL cond = elements[i] == dup;
			res = CMOV(cond && !done,true, cond);
			done = CMOV(cond, true,cond);
		#else
		if (elements[i] == dup){
			return returnTrue();
		}
		#endif 
	}
	#ifndef VIP_DO_MODE
		return returnFalse();
	#else
		return res;
	#endif 
}


int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("Usage format ./app filename index\n");
        exit(1);
    }
	
	vector<VIP_ENCINT> numbers;

	//Create an input file stream
    char* fileName = argv[1];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbers.push_back(number);
	}
    in.close();

	int index = atoi(argv[2]);
	VIP_ENCINT dup = index;
	
    size_t count = numbers.size();
    int* a = &numbers[0];

    
    VIP_ENCBOOL res = Contains(a,count, dup);
    printf("%d\n",res);

	return 0;
}

