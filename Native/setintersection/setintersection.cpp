
// #include "../Enclave_t.h"
#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../../Shared/shared.h"
#include <stdlib.h> 
using namespace std;

int* setA;
int* setB;
int arr_size;
// VIP_ENCBOOL* setA_match;


VIP_ENCBOOL 
set_intersect()
{
  VIP_ENCBOOL res = false;
  for (unsigned i=0; i < arr_size; i++)
  {
    VIP_ENCBOOL match = false;
    for (unsigned j=0; j < arr_size; j++)
    {
        #ifdef VIP_DO_MODE
            match = VIP_CMOV(setA[i] == setB[j], true, match);
        #else /* !VIP_DO_MODE */
            if (setA[i] == setB[j]){
                match = true;
                // res = true;
            }
        #endif /* VIP_DO_MODE */
    }
    #ifdef VIP_DO_MODE
    res = CMOV(match,match,res);
    #else 
    if(match)
        res = match;
    #endif
    // setA_match[i] = match;
  }
  return res;
}

void testSetIntersection(char **argv){
    //Create a dynamic array to hold the values
	vector<int> numbersA;
    vector<int> numbersB;
    

	//Create an input file stream
    char* outFileNameA = argv[1];
    char* fileNameA = argv[2];
	ifstream in(fileNameA,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbersA.push_back(number);
	}
    in.close();
    size_t count1 = numbersA.size();

    //Create an input file stream
    char* fileNameB = argv[3];
	ifstream in2(fileNameB,ios::in);	
    int number2;  //Variable to hold each number as it is read
    while (in2 >> number2) {
		numbersB.push_back(number2);
	}
    in2.close();
   
    // size_t count2 = numbersB.size();
    vector<VIP_ENCBOOL> matchs(count1);

    setA = &numbersA[0];
    setB = &numbersB[0];
    // setA_match = &(matchs[0]);

    arr_size = count1;
    VIP_ENCBOOL res = profile_func(set_intersect , outFileNameA);  
    printf("%d\n",res);    
}

int main(int argc, char *argv[])
{
    if(argc < 4){
        printf("Usage format ./app outfilename filename num freq\n");
        exit(1);
    }

   testSetIntersection(argv);
          
    return 0;
}
