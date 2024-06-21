
// #include "../Enclave_t.h"
#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../../Shared/shared.h"
#include <stdlib.h> 
using namespace std;

     
/**
 s: int array to check for duplicate values 
 number: the number to look for 
 efreq: the frequency to check for
 Asummption: the maximum element in s is less than or equal to SIZE  
*/
void
ecall_bubblesort(VIP_ENCINT *data, size_t size)
{
  for (unsigned i=size; i > 1; i--)
  {
    #ifndef VIP_DO_MODE
        // bool swapped = false;
    #endif /* !VIP_DO_MODE */
        for (unsigned j=0; j < i-1; j++)
        {
            #ifndef VIP_DO_MODE
                if (data[j] > data[j+1])
                {
                    VIP_ENCINT tmp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = tmp;
                    // swapped = true;
                    // swaps++;
                }
            #else /* VIP_DO_MODE */
                VIP_ENCBOOL do_swap = data[j] > data[j+1];
                VIP_ENCINT tmp = data[j];
                data[j] = VIP_CMOV(do_swap, data[j+1], data[j]);
                data[j+1] = VIP_CMOV(do_swap, tmp, data[j+1]);
                // swaps++;
            #endif /* VIP_DO_MODE */
        }
    #ifndef VIP_DO_MODE
        // done?
        // if (!swapped)
        // break;
    #endif /* !VIP_DO_MODE */
  }
}

void testBubbleSort(char **argv) {
    //Create a dynamic array to hold the values
	vector<int> numbers;

	//Create an input file stream
    char* fileName = argv[1];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbers.push_back(number);
	}
    in.close();




    size_t count = numbers.size();
    int* a = &numbers[0];
    ecall_bubblesort(a, count);
    
    printf("done\n");
    
}

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Usage format ./app filename num freq\n");
        exit(1);
    }

   testBubbleSort(argv);
   
        
	return 0;
}
