
#include "../Enclave_t.h"
#include <stdlib.h>
#include "../../Shared/shared_sgx.h"
#include <limits>
#include <stdio.h>
#include <vector>
#include <fstream>
// #include "../config.h"

using namespace std;


bool ecall_maxrun(VIP_ENCINT *array, size_t size,VIP_ENCINT expected) {
   VIP_ENCINT max = 1;
   VIP_ENCINT current = 1;
   

   for (int i = 1; i < size; i++) {
      #ifdef VIP_DO_MODE
          VIP_ENCBOOL cond = array[i - 1] == array[i];
          current = VIP_CMOV(cond,current+1,1);
        //   current = VIP_CMOV(!cond,1,current);
          VIP_ENCBOOL cond2 = current > max;
          max = VIP_CMOV(cond2,current,max);
      #else   
        if (array[i - 1] == array[i]) {    /* the run continues */
            current++;
            max = current > max ? current : max;
        } else {    /* the run was broken */
            current = 1;
        }
      #endif 
   }
   return  max == expected;
}

