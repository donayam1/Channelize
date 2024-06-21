
// #include "../Enclave_t.h"
#include "../Enclave_t.h"
#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../../Shared/shared_sgx.h"
#include <stdlib.h> 
using namespace std;

     
/**
 s: int array to check for duplicate values 
 number: the number to look for 
 efreq: the frequency to check for
 Asummption: the maximum element in s is less than or equal to SIZE  
*/
VIP_ENCBOOL 
ecall_set_intersect(int* setA, int* setB, size_t sizeA, size_t sizeB)
{
VIP_ENCBOOL res = false;
  for (unsigned i=0; i < sizeA; i++)
  {
    VIP_ENCBOOL match = false;
    for (unsigned j=0; j < sizeB; j++)
    {
        #ifdef VIP_DO_MODE
            match = VIP_CMOV(setA[i] == setB[j], (VIP_ENCBOOL)true, match);
        #else /* !VIP_DO_MODE */
            if (setA[i] == setB[j]){
                match = true;
    //            res = true;
            }
        #endif /* VIP_DO_MODE */
    }
	#ifdef VIP_DO_MODE
        	res = CMOV(match,match,res);
	#else 
	    if(match)
		res = match;
	#endif

   // res = VIP_CMOV(match,match,res);
    // setA_match[i] = match;
  }
  return res;
}



// int main(int argc, char *argv[])
// {
//     if(argc < 3){
//         printf("Usage format ./app filename num freq\n");
//         exit(1);
//     }

//    testSetIntersection(argv);
          
//     return 0;
// }
