


#include "../Enclave_t.h"
#include <limits>
#include <string>
#include <stdlib.h>
#include "../../Shared/shared_sgx.h"


VIP_ENCBOOL ecall_isDistinct_leaky(VIP_ENCINT* elements, size_t length)
{	
		
#ifdef VIP_DO_MODE
	VIP_ENCBOOL dup = false;
  
  for (int i=length-1; i >= 0; i--)
  {
    for (int j=0; j < length; j++){
		    VIP_ENCBOOL cond = ((elements[i] == elements[j]) && (i != j));
        dup = VIP_CMOV(cond , true, dup);
	  }
  }
  return !dup;
#else /* !VIP_DO_MODE */
 for (int i=0; i < length; i++)
  {
    for (int j=0; j < length; j++){
		VIP_ENCBOOL cond = ((elements[i] == elements[j]) && (i != j));
    if(cond){
			return false;
		}
	}
  }
	return true;
#endif /* VIP_DO_MODE */

}


