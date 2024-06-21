#ifndef SHARED_SE_H
#define SHARED_SE_H
#include <stdbool.h>
#include "../functional-library/src/datatypes/enc_lib.h"
#include <linux/perf_event.h>
#include <string>
#include <vector> 
#include <time.h>

#define VIP_DO_MODE



#define MAX std::numeric_limits<int>::max() 

/**
	to get cache line size 
	getconf -a | grep CACHE
*/
// enc_lib::enc_bool returnTrue(void);

// enc_lib::enc_bool returnFalse(void);

// enc_lib::enc_bool __attribute__((__aligned__(64))) returnTrue(){
// 	enc_lib::enc_bool true_enc = true;
// 	return true_enc;
// }

// enc_lib::enc_bool __attribute__((__aligned__(64))) returnFalse(){
// 	enc_lib::enc_bool false_enc = false;
// 	return false_enc;
// }



#define PERF_LLC_LOADS_CONFIG (PERF_COUNT_HW_CACHE_LL | (PERF_COUNT_HW_CACHE_OP_READ << 8) | \
                (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16))

#define PERF_L1D_READ_MISS_CONFIG	((PERF_COUNT_HW_CACHE_L1D) | 		\
					                (PERF_COUNT_HW_CACHE_OP_READ << 8) |	\
					                (PERF_COUNT_HW_CACHE_RESULT_MISS << 16))

#define PERF_CACHE_MISS_CONFIG PERF_COUNT_HW_CACHE_MISSES 
#define PERF_CACHE_REFERENCES_CONFIG PERF_COUNT_HW_CACHE_REFERENCES
#define PERF_CONTEXT_SWITCHES_CONFIG PERF_COUNT_SW_CONTEXT_SWITCHES
#define PERF_CPU_MIGRATIONS_CONFIG PERF_COUNT_SW_CPU_MIGRATIONS
#define PERF_CPU_CYCLES_CONFIG PERF_COUNT_HW_CPU_CYCLES
#define PERF_INSTRUCTIONS_CONFIG PERF_COUNT_HW_INSTRUCTIONS
#define PERF_BRANCH_MISSES_CONFIG PERF_COUNT_HW_BRANCH_MISSES
#define PERF_BRANCH_CONFIG PERF_COUNT_HW_BRANCH_INSTRUCTIONS
#define PERF_PAGE_FAULTS_CONFIG PERF_COUNT_SW_PAGE_FAULTS

#define PERF_CACHE_L1D_LOAD_CONFIG (PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) | \
                (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16)) 
#define  PERF_CACHE_L1D_STORE_CONFIG (PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_WRITE << 8) | \
                (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16))

#define PERF_CACHE_L1I_LOAD_MISS_CONFIG (PERF_COUNT_HW_CACHE_L1I | (PERF_COUNT_HW_CACHE_OP_READ << 8) | \
                (PERF_COUNT_HW_CACHE_RESULT_MISS << 16))
    
#define PERF_CACHE_LL_LOAD_MISS_CONFIG (PERF_COUNT_HW_CACHE_LL | (PERF_COUNT_HW_CACHE_OP_READ << 8) | \
                (PERF_COUNT_HW_CACHE_RESULT_MISS << 16)) 

#define PERF_CACHE_LL_STORE (PERF_COUNT_HW_CACHE_LL | (PERF_COUNT_HW_CACHE_OP_WRITE << 8) | \
                (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16))
#define PERF_CACHE_LL_STORE_MISS (PERF_COUNT_HW_CACHE_LL | (PERF_COUNT_HW_CACHE_OP_WRITE << 8) | \
                (PERF_COUNT_HW_CACHE_RESULT_MISS << 16))
    



struct PerfEvent {    
    //input
    std::string name;
    int type;
    int config;
    
    //output
    int fd;
    long long count;

    // Constructor
    PerfEvent(const std::string& n, int t, int c)
        : name(n), type(t), config(c), fd(-1), count(0) {}
}; 
enc_lib::enc_bool profile(std::vector<PerfEvent>& events, enc_lib::enc_bool (*func)(void),float* total_time);
enc_lib::enc_bool profile_func(enc_lib::enc_bool (*func)(void),char* outFileName);
unsigned long long getElapsedTime(struct timespec start, struct timespec end);


// VIP_ENCBOOL isDistinct(VIP_ENCINT elements[], size_t size);

#endif
