
#include <stdio.h>
#include <string>
// #include <stack>
#include <fstream>
#include <vector>
#include "../../Shared/shared.h"
#include <stdlib.h> 

#include <cstring>
#include <unistd.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <asm/unistd.h>
using namespace std;



int *array;
int arr_size;
int add_index_zero;
int expected;
/*
    function that adds the number x[index] to itself n-times and checks if the result is equal to  product 
    x in an integer array   
*/
VIP_ENCBOOL ecall_add(){
    // printf("array[0]=%d\n",array[0]);
    int sum = 0;
    for (int i=0;i<arr_size;i++){
        int random = rand()%arr_size;

        #ifdef VIP_DO_MODE            
            int num=0;
            int index = VIP_CMOV(add_index_zero==0,0,random);
           
            for(int j=0;j<arr_size;j++) {
                num = VIP_CMOV(j==index, array[j], num);
            }
            
            sum += num;
        #else 
            if(add_index_zero==0) {
                sum += array[0]; //expect almost no cache miss 
            }else {
                // int random = rand()%SIZE;
                // printf("%7d\n",random);
                sum += array[random]; //expect a lot of cache miss 
            }
        #endif
    }
    #ifdef VIP_DO_MODE
    
        // printf("sum=%d,expected=%d\n",sum,expected);
        bool res = VIP_CMOV(sum == expected,true,false);
        
        return res;
    
    #else

        if(sum == expected){
            return true;
        }else{
            return false;
        }
        
    #endif 

    
    
}
void testAdd(char **argv){
    //Create a dynamic array to hold the values
	vector<int> numbers;

	// //Create an input file stream
    char* outfileName = argv[1];
    char* fileName = argv[2];
	ifstream in(fileName,ios::in);	
    int number;  //Variable to hold each number as it is read
    while (in >> number) {
		numbers.push_back(number);
	}
    in.close();


    add_index_zero = atoi(argv[3]);
    // printf("add_index_0=%d",add_index_zero);
    expected = atoi(argv[4]);
    arr_size= numbers.size();
    array = &numbers[0];
    
    // printf("Measuring instruction count for this printf\n");
    VIP_ENCBOOL res  = profile_func(ecall_add,outfileName);
       
    printf("%d\n",res);
    
}
// void testAdd(char **argv){
//     //Create a dynamic array to hold the values
// 	vector<int> numbers;

// 	// //Create an input file stream
//     char* fileName = argv[1];
// 	ifstream in(fileName,ios::in);	
//     int number;  //Variable to hold each number as it is read
//     while (in >> number) {
// 		numbers.push_back(number);
// 	}
//     in.close();
//     int all = atoi(argv[2]);
//     int max = atoi(argv[3]);
//     // int freq = atoi(argv[3]);


//     size_t count = numbers.size();
//     int* x = &numbers[0];
//     // int x[]= {1,2,3,4};
//     struct perf_event_attr pe;
//     long long event_count;
//     int fd;

//     memset(&pe, 0, sizeof(struct perf_event_attr));
//     pe.type = PERF_TYPE_HARDWARE;
//     pe.size = sizeof(struct perf_event_attr);
//     pe.config = PERF_COUNT_HW_INSTRUCTIONS;
//     pe.disabled = 1;
//     pe.exclude_kernel = 1;
//     pe.exclude_hv = 1;

//     fd = perf_event_open(&pe, 0, -1, -1, 0);
//     if (fd == -1) {
//        fprintf(stderr, "Error opening leader %llx\n", pe.config);
//        exit(EXIT_FAILURE);
//     }

//     ioctl(fd, PERF_EVENT_IOC_RESET, 0);
//     ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);

//     // printf("Measuring instruction count for this printf\n");
//     VIP_ENCBOOL res  = ecall_add(x,count, all,max);

//     ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
//     read(fd, &event_count, sizeof(long long));

//     printf("Used %lld instructions\n", event_count);

//     close(fd);


   
    
//     printf("%d\n",res);
    
// }

int main(int argc, char *argv[])
{
    

    if(argc < 5){
        printf("Usage format ./app outFileName filename all expected \n");
        exit(1);
    }


   testAdd(argv);
   
        
	return 0;
}