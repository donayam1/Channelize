#include "shared_se.h"
#include <cstring>
#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>
#include <asm/unistd.h>
#include <fstream>

using namespace enc_lib;

// enc_lib::enc_bool __attribute__((__aligned__(64))) returnTrue(){
// 	enc_lib::enc_bool true_enc = true;
// 	return true_enc;
// }

// enc_lib::enc_bool __attribute__((__aligned__(64))) returnFalse(){
// 	enc_lib::enc_bool false_enc = false;
// 	return false_enc;
// }

unsigned long long getElapsedTime(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
}

enc_bool profile_func(enc_bool (*func)(void),char* outFileName){

    std::vector<PerfEvent> eventVector;
    
    PerfEvent cache_misses{"cache-misses", PERF_TYPE_HARDWARE, PERF_CACHE_MISS_CONFIG}; 
    PerfEvent cache_references{"cache-references", PERF_TYPE_HARDWARE, PERF_CACHE_REFERENCES_CONFIG};
    PerfEvent context_switches{"context-switches", PERF_TYPE_SOFTWARE, PERF_CONTEXT_SWITCHES_CONFIG}; 
    PerfEvent cpu_migrations{"cpu-migrations", PERF_TYPE_SOFTWARE, PERF_CPU_MIGRATIONS_CONFIG};
    PerfEvent cpu_cycles{"cpu-cycles",PERF_TYPE_HARDWARE,PERF_CPU_CYCLES_CONFIG}, 
              instructions{"instructions",PERF_TYPE_HARDWARE,PERF_INSTRUCTIONS_CONFIG}, 
              branch_misses{"branch-misses",PERF_TYPE_HARDWARE,PERF_BRANCH_MISSES_CONFIG},  
              branches{"branches",PERF_TYPE_HARDWARE,PERF_BRANCH_CONFIG},  
              page_faults{"page-faults",PERF_TYPE_SOFTWARE,PERF_PAGE_FAULTS_CONFIG} ;

    PerfEvent l1_dcache_load_misses{"L1-dcache-load-misses",PERF_TYPE_HW_CACHE,PERF_L1D_READ_MISS_CONFIG}, 
              count_l1_dcache_loads{"L1-dcache-loads",PERF_TYPE_HW_CACHE,PERF_CACHE_L1D_LOAD_CONFIG}, 
              count_l1_dcache_stores{"L1-dcache-stores",PERF_TYPE_HW_CACHE,PERF_CACHE_L1D_STORE_CONFIG};

    PerfEvent count_l1_icache_load_misses{"L1-icache-load-misses",PERF_TYPE_HW_CACHE,PERF_CACHE_L1I_LOAD_MISS_CONFIG}, 
                count_llc_load_misses{"LLC-load-misses",PERF_TYPE_HW_CACHE,PERF_CACHE_LL_LOAD_MISS_CONFIG}, 
                count_llc_loads{"LLC-loads",PERF_TYPE_HW_CACHE,PERF_LLC_LOADS_CONFIG},
                count_llc_store_misses{"LLC-store-misses",PERF_TYPE_HW_CACHE,PERF_CACHE_LL_STORE_MISS}, 
                count_llc_stores{"LLC-stores",PERF_TYPE_HW_CACHE,PERF_CACHE_LL_STORE};

    eventVector.push_back(cache_misses);
    eventVector.push_back(cache_references);
    eventVector.push_back(context_switches);
    eventVector.push_back(cpu_migrations);
    eventVector.push_back(cpu_cycles);
    eventVector.push_back(instructions);
    eventVector.push_back(branch_misses);
    eventVector.push_back(branches);
    eventVector.push_back(page_faults);
    eventVector.push_back(l1_dcache_load_misses);
    eventVector.push_back(count_l1_dcache_loads);
    eventVector.push_back(count_l1_dcache_stores);

    eventVector.push_back(count_l1_icache_load_misses);
    eventVector.push_back(count_llc_load_misses);
    eventVector.push_back(count_llc_loads);
    eventVector.push_back(count_llc_store_misses);
    eventVector.push_back(count_llc_stores);
    

	float total_time;     
    enc_bool res = profile(eventVector,func,&total_time);	

	std::ofstream outputFile; // Declare an output file stream object    
    outputFile.open(outFileName);

    if (outputFile.is_open()) {
        // Write data to the file
        for(auto &event : eventVector){            
            outputFile <<event.name <<":"<<event.count<< std::endl;        
        }   
        outputFile <<"seconds:" <<total_time <<std::endl;

        outputFile.close();
        std::cout << "File write successful. The file is closed." << std::endl;
    } else {
        std::cout << "Failed to open the file." << std::endl;
    }


    return res;
}
enc_bool profile(std::vector<PerfEvent>& events,enc_bool (*func)(void),float* total_time){	
    struct perf_event_attr pe;
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;
    pe.disabled = 1;
    pe.size = sizeof(struct perf_event_attr);
    
    
    for (auto& event : events) {
        pe.type = event.type;    
        pe.config = event.config;

        event.fd = syscall(__NR_perf_event_open, &pe, 0, -1, -1, 0);
        if (event.fd == -1) {
            std::cerr << "Failed to open "<<event.name << " perf event" << std::endl;
            return 1;
        }
        
        ioctl(event.fd, PERF_EVENT_IOC_RESET, 0);      
        ioctl(event.fd, PERF_EVENT_IOC_ENABLE, 0);              
     }
    struct timespec startTime;
    clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);
	
    enc_bool res = func();
	
    struct timespec endTime;
    clock_gettime(CLOCK_MONOTONIC_RAW, &endTime);

    for(auto&event:events){
        ioctl(event.fd, PERF_EVENT_IOC_DISABLE, 0);    
        read(event.fd, &event.count, sizeof(long long));
        close(event.fd);
    }
	
    *total_time = getElapsedTime(startTime, endTime)/1e9; 


    return res;
}

