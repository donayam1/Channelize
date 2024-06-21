#ifndef __SHARED_SGX_H__
#define __SHARED_SGX_H__

#include <stdbool.h>


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







/**
	to get cache line size 
	getconf -a | grep CACHE
*/
bool returnTrue(void);

bool returnFalse(void);

// VIP_ENCBOOL isDistinct(VIP_ENCINT elements[], size_t size);

#endif
