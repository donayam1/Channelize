

#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../../Shared/shared_se.h"
#include "../src/vip-functional-library.h"

using namespace std;
using namespace enc_lib;
     
enc_char *s;
size_t arr_size;

/**
 s: string to check if there are equal number of  "(" and ")"
*/
enc_bool ecall_isValid() {
    enc_int oCounter = 0;
    enc_char obrace = '(';
    // const enc_char *sa = s;//.c_str();
    enc_int t;
    enc_int f;  
    for(int i =0;i<arr_size;i++){ 
        
        // enc_char c = s[i];
        #ifdef VIP_DO_MODE
            t = oCounter +1;
            f = oCounter -1;
            oCounter = CMOV(s[i] == obrace,  t , f);            
        #else
            if (c == obrace) //(obraces.find(c) != obraces.end()) 
            {
                oCounter++;
            }else {          
                oCounter--;                        
            }    
        #endif    
    }    
    if(oCounter.GET_DECRYPTED_VALUE() == 0){
        return true;
    }
    return false;     
}

void testValidParenthesis(char **argv){
    //Create a dynamic array to hold the values
	vector<enc_char> chars;

	//Create an input file stream
    char* outfileName = argv[1];
    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    char brace;  //Variable to hold each number as it is read
    while (in >> brace) {
        enc_char brace_e = brace;
		chars.push_back(brace_e);
	}
    in.close();


    arr_size = chars.size();
    s = &chars[0];
    
    enc_bool res  = profile_func( ecall_isValid,outfileName);
    
    
    printf("%d\n",res.GET_DECRYPTED_VALUE());
}

int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("Usage format ./app outfileName filename\n");
        exit(1);
    }

    VIPInit(); 
    testValidParenthesis(argv);
//    string s =  string("(((((((())(()");
//     const char * sa = s.c_str();
//     ecall_isValid(sa,13);

	return 0;
}

