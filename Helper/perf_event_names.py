
CONTEXT_SWITCHES        ="context-switches"
CPU_MIGRATIONS          ="cpu-migrations"

CACHE_MISSES            ="cache-misses"
CACHE_REFERENCES        ="cache-references"
CPU_CYCLES              ="cpu-cycles"
INSTRUCTIONS            ="instructions"
BRANCH_MISSES           ="branch-misses"
BRANCHES                ="branches"
PAGE_FAULTS             ="page-faults"
L1_DCACHE_LOAD_MISSES   ="L1-dcache-load-misses"
L1_DCACHE_LOADS         ="L1-dcache-loads"
L1_DCACHE_STORES        ="L1-dcache-stores"
L1_ICACHE_LOAD_MISSES   ="L1-icache-load-misses"


LLC_LOAD_MISSES         ="LLC-load-misses"
LLC_LOADS               ="LLC-loads"
LLC_STORE_MISSES        ="LLC-store-misses"
LLC_STORES              ="LLC-stores"
SECONDS                 ="seconds" #"execution-time"
EXECUTION_TIME          = "execution-time"
LABEL                   = 'label'

__all__ = ['CONTEXT_SWITCHES', 'CPU_MIGRATIONS', 'CACHE_MISSES','CACHE_REFERENCES',
           'CPU_CYCLES','INSTRUCTIONS','BRANCH_MISSES','BRANCHES','PAGE_FAULTS',
           'L1_DCACHE_LOAD_MISSES','L1_DCACHE_LOADS','L1_DCACHE_STORES','L1_ICACHE_LOAD_MISSES',
           'LLC_LOAD_MISSES','LLC_LOADS','LLC_STORE_MISSES','LLC_STORES','SECONDS']

NamesToIndexMap={ 
        CONTEXT_SWITCHES:0,
        CPU_MIGRATIONS:1,
        CACHE_MISSES:2,
        CACHE_REFERENCES:3,
        CPU_CYCLES:4,
        INSTRUCTIONS:5,
        BRANCH_MISSES:6,
        BRANCHES:7,
        PAGE_FAULTS:8,
       
        L1_DCACHE_LOAD_MISSES:9,
        L1_DCACHE_LOADS:10,   
        L1_DCACHE_STORES:11,     
        L1_ICACHE_LOAD_MISSES:12,          
        LLC_LOAD_MISSES:13,
        LLC_LOADS:14,
        LLC_STORE_MISSES:15,
        LLC_STORES:16,
        EXECUTION_TIME:17,
        
        SECONDS:17,        
        LABEL:18,
       }

namesList=[k for k,_ in NamesToIndexMap.items()  ]
namesList=namesList[:-2]

namesInverse = {v:k for k,v in NamesToIndexMap.items()}

if __name__ == "__main__":
    print(namesList)
    