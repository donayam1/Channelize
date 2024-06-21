#include "shared_sgx.h"





bool __attribute__((__aligned__(64))) returnTrue(){
	return true;
}

bool __attribute__((__aligned__(64))) returnFalse(){
	return false;
}