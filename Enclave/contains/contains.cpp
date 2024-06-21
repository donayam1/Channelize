
#include "../Enclave_t.h"
#include <stdio.h>
#include <string>
#include "../../Shared/shared_sgx.h"
#include <stdlib.h> 
using namespace std;

VIP_ENCBOOL ecall_contains(VIP_ENCINT elements[],size_t size, VIP_ENCINT dup)
{
        VIP_ENCBOOL res = false;
        for(int i=0;i<size;i++){
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
