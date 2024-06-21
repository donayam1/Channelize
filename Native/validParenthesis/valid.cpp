

#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../../Shared/shared.h"

using namespace std;



const char *array;
size_t arr_size;

/**
 s: string to check if there are equal number of  "(" and ")"
*/
VIP_ENCBOOL ecall_isValid() {
    int oCounter = 0;
    char obrace = '(';
        
    for(int i =0;i<arr_size;i++){                 
        #ifdef VIP_DO_MODE
            int t = oCounter +1;
            int f = oCounter -1;
            oCounter = VIP_CMOV(array[i] == obrace, t , f);            
        #else
            if (array[i] == obrace) //(obraces.find(c) != obraces.end()) 
            {
                oCounter++;
            }else {          
                oCounter--;                        
            }    
        #endif    
    }    
    
    return oCounter==0;            
}

void testValidParenthesis(char **argv){
    //Create a dynamic array to hold the values
	vector<char> chars;

	//Create an input file stream
    char* outfileName = argv[1];
    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    char brace;  //Variable to hold each number as it is read
    while (in >> brace) {
		chars.push_back(brace);
	}
    in.close();

    arr_size = chars.size();
    array = &chars[0];
    
    VIP_ENCBOOL res = profile_func( ecall_isValid, outfileName);
    
    
    printf("%d\n",res);
}

int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("Usage format ./app outfilename filename\n");
        exit(1);
    }

    
   testValidParenthesis(argv);
//    string s =  string("(((((((())(()");
//     const char * sa = s.c_str();
//     ecall_isValid(sa,13);

	return 0;
}

