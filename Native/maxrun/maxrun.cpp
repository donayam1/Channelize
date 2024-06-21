#include <stdlib.h>
#include "../../Shared/shared.h"
#include <limits>
#include <stdio.h>
#include <vector>
#include <fstream>
// #include "../config.h"

#ifdef VIP_DO_MODE
   #pragma message("DO mode compilation")
#else
    #pragma message("Non DO mode compilation")
#endif 

using namespace std;

VIP_ENCINT *array;
int arr_size;
VIP_ENCINT expected;


VIP_ENCBOOL maxrun2() {
   VIP_ENCINT max = 1;
   VIP_ENCINT current = 1;
   

   for (int i = 1; i < arr_size; i++) {
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
//    printf("max=%d, expected=%d",max,expected);
   return max == expected;
}

int main(int argc, char *argv[])
{
    if(argc < 4){
        printf("Usage format ./app outfile infile maxrun\n");
        exit(1);
    }
	
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


    expected = atoi(argv[3]);	
    arr_size = numbers.size();
    array = &numbers[0];

    bool res = profile_func(maxrun2,outfileName);
    // bool res = maxrun2();
    printf("%d\n",res);

	return 0;
}

// VIP_ENCBOOL maxrun(VIP_ENCINT *array, int size,VIP_ENCINT expected) {
//    VIP_ENCINT max = 1;
//    VIP_ENCINT current = 1;
   

//    for (int i = 1; i < size; i++) {
//       #ifdef VIP_DO_MODE
//           VIP_ENCBOOL cond = array[i - 1] == array[i];
//           current = VIP_CMOV(cond,current+1,1);
//         //   current = VIP_CMOV(!cond,1,current);
//           VIP_ENCBOOL cond2 = current > max;
//           max = VIP_CMOV(cond2,current,max);
//       #else   
//         if (array[i - 1] == array[i]) {    /* the run continues */
//             current++;
//             max = current > max ? current : max;
//         } else {    /* the run was broken */
//             current = 1;
//         }
//       #endif 
//    }
//    return max == expected;
// }

// int main0(int argc, char *argv[])
// {
//     if(argc < 3){
//         printf("Usage format ./app filename\n");
//         exit(1);
//     }
	
// 	vector<VIP_ENCINT> numbers;

// 	//Create an input file stream
//     char* fileName = argv[1];
// 	ifstream in(fileName,ios::in);	
//     int number;  //Variable to hold each number as it is read
//     while (in >> number) {
// 		numbers.push_back(number);
// 	}
//     in.close();

//     VIP_ENCINT expected = atoi(argv[2]);
	
//     size_t count = numbers.size();
//     int* a = &numbers[0];

    
//     int res = maxrun(a,count,expected);
//     printf("%d\n",res);

// 	return 0;
// }