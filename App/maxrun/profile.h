#ifndef _PROFILE_H_
#define _PROFILE_H_ 
#include "sgx_edger8r.h" /* for sgx_status_t etc. */
#include <string>
#include <vector>
#include <linux/perf_event.h>
#include "../../Shared/shared_sgx.h"

// sgx_status_t ecall_isValid(sgx_enclave_id_t eid, VIP_ENCBOOL* retval, char* elements, size_t size);

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


VIP_ENCBOOL profile_func(sgx_status_t (*func)(sgx_enclave_id_t,VIP_ENCBOOL*,  int*, size_t,int),
                    char* outFileName,
                    sgx_enclave_id_t eid,                    
                    int* number, 
                    size_t size,
                    int dup);
VIP_ENCBOOL profile(std::vector<PerfEvent>& events, sgx_status_t (*func)(sgx_enclave_id_t,VIP_ENCBOOL*,  int*,size_t,int), 
            float* total_time,            
            sgx_enclave_id_t eid,            
            int* number, 
            size_t size,
            int dup);

// VIP_ENCBOOL profile_func(sgx_status_t (*func)(sgx_enclave_id_t, VIP_ENCBOOL*, char*, size_t),
//                     char* outFileName,
//                     sgx_enclave_id_t eid,                    
//                     char * number, 
//                     size_t size);

unsigned long long getElapsedTime(struct timespec start, struct timespec end);
#endif 
