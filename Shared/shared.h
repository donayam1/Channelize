#ifndef __SHARED_H__
#define __SHARED_H__

#include <stdbool.h>
#include <linux/perf_event.h>
#include <string>
#include <vector> 
#include <time.h>

#define VIP_DO_MODE




typedef int VIP_ENCINT;
typedef bool VIP_ENCBOOL;

// int __attribute__((always_inline))  CMOV(bool cond, int v_true, int v_false);
inline int __attribute__((always_inline))  CMOV(bool cond, int v_true, int v_false) {
                int result;
                __asm__ __volatile__ (
                    "test   %1, %1;"
                    "cmovz  %3, %0;"  //zero flag cleared?
                    "cmovnz %2, %0;" //zero flag not cleared?
                    : "=r" (result)
                    : "r" (cond), "r" (v_true), "r" (v_false)
                    : "cc"
                );
                return result;
}

#define VIP_CMOV(P,A,B)    CMOV((P), (A), (B))
#define MAX std::numeric_limits<int>::max() 





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
bool profile(std::vector<PerfEvent>& events,bool (*func)(void),float* total_time);
bool profile_func(bool (*func)(void),char* outFileName);
unsigned long long getElapsedTime(struct timespec start, struct timespec end);

/**
	to get cache line size 
	getconf -a | grep CACHE
*/
bool returnTrue(void);

bool returnFalse(void);

// VIP_ENCBOOL isDistinct(VIP_ENCINT elements[], size_t size);

#endif
