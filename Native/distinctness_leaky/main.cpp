

// #include "distinctness.h"
#include <stdlib.h>
#include "../../Shared/shared.h"
#include <limits>
#include <stdio.h>
#include <vector>
#include <fstream>
// #include "../config.h"

using namespace std;

// #define MAX std::numeric_limits<int>::max()
VIP_ENCINT *array;
size_t arr_size;

VIP_ENCBOOL isDistinct()
{
#ifdef VIP_DO_MODE
  VIP_ENCBOOL dup = false;

  for (int i=arr_size-1; i >= 0; i--)
  {
    for (int j=0; j < arr_size; j++){
	  VIP_ENCBOOL cond = ((array[i] == array[j]) && (i!=j)); 	
      dup = VIP_CMOV(cond, array[j], dup);
	}
  }

  return !dup;
#else /* !VIP_DO_MODE */
	for (int i=0; i < arr_size; i++)
	{
		for (int j=0; j < arr_size; j++){
			VIP_ENCBOOL cond = ((array[i] == array[j]) && (i!=j)); 	
			if(cond){
				return false;
			}
		}
	}

	return true;
#endif /* VIP_DO_MODE */
}


int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("Usage format ./app outfileName filename\n");
        exit(1);
    }
   

    //Create a dynamic array to hold the values
	vector<VIP_ENCINT> numbers;

	//Create an input file stream
	char* outfileName = argv[1];
    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbers.push_back(number);
	}
    in.close();

    arr_size = numbers.size();
    array = &numbers[0];
    
    VIP_ENCBOOL res = profile_func(isDistinct,outfileName);
    printf("%d\n",res);

    // if (res1)
    //         cout<<"The elements of `elements1' are distinct"<<endl;
    //     else
    //         cout<<"The elements of `elements1' are not distinct (e.g., " << dup << " is duplicated)"<<endl;
        
	return 0;
}

