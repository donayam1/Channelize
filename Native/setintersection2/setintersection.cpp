
// #include "../Enclave_t.h"
#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../../Shared/shared.h"
#include <stdlib.h> 
using namespace std;

volatile int x = 0;    
/**
 s: int array to check for duplicate values 
 number: the number to look for 
 efreq: the frequency to check for
 Asummption: the maximum element in s is less than or equal to SIZE  
*/
VIP_ENCBOOL 
set_intersect(int* setA, int* setB, int sizeA, int sizeB, int* setA_match)
{
    VIP_ENCBOOL res = false;
  for (unsigned i=0; i < sizeA; i++)
  {
    int match = 0;
    for (unsigned j=0; j < sizeB; j++)
    {
        #ifdef VIP_DO_MODE
            match = VIP_CMOV(setA[i] == setB[j], (VIP_ENCBOOL)true, match);
            // for(int m=0;m<5;m++){
            //     x++;
            // }
        #else /* !VIP_DO_MODE */
            if (setA[i] == setB[j]){
                match = 1;
                res = true;        
                //  for(int m=0;m<5;m++){
                //     x++;
                //  }        
            } 
        #endif /* VIP_DO_MODE */
    }
    setA_match[i] = match;
  }
  return res;
}

void testSetIntersection(char **argv){
    //Create a dynamic array to hold the values
	vector<int> numbersA;
    vector<int> numbersB;
    

	//Create an input file stream
    char* fileNameA = argv[1];
	ifstream in(fileNameA,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbersA.push_back(number);
	}
    in.close();
    size_t count1 = numbersA.size();

    //Create an input file stream
    char* fileNameB = argv[2];
	ifstream in2(fileNameB,ios::in);	
    int number2;  //Variable to hold each number as it is read
    while (in2 >> number2) {
		numbersB.push_back(number2);
	}
    in2.close();
   
    size_t count2 = numbersB.size();
    vector<int> matchs(count2);

    

    int *a = &numbersA[0];
    int *b = &numbersB[0];
    int *m = &matchs[0];


    VIP_ENCBOOL res = set_intersect(a,b, count1,count2, m);   

    printf("%d\n",res);    
}

int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("Usage format ./app filename num freq\n");
        exit(1);
    }

   testSetIntersection(argv);
          
    return 0;
}
