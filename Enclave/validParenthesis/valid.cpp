
#include "../Enclave_t.h"
#include <stdio.h>
#include <string>
// #include <stack>
#include <sgx_trts.h>
// #include "../../Shared/shared_sgx.h"


using namespace std;




/**
 s: string to check if there are equal number of  "(" and ")"
*/
VIP_ENCBOOL ecall_isValid(char *s,size_t length) {
    VIP_ENCINT oCounter = 0;
    char obrace = '(';

    // const char *sa = s;

    for(int i =0;i<length;i++){                 
        #ifdef VIP_DO_MODE
            oCounter = VIP_CMOV(s[i] == obrace, oCounter + 1 , oCounter - 1);                
        #else
            if (s[i] == obrace) //(obraces.find(c) != obraces.end()) 
            {
                oCounter++;
            }else {          
                oCounter--;                        
            }    
        #endif    
    }    
    // ocall_print_int(oCounter);
    #ifdef VIP_DO_MODE
        VIP_ENCBOOL res = false;
        res = VIP_CMOV(oCounter == 0,true,false);
        // if(oCounter == 0){
        //     return true;
        // }
        // else 
        //     return false;
    #else 
        if(oCounter == 0){
            return true;
        }
        return false;
    #endif
}

