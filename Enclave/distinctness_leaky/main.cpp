#include <iostream>
#include <limits>
#include "shared.h"

using namespace std;
int main(void)
{

    VIP_ENCINT elements1[SIZE] = {25,97,1,0,36,22,74,3,9,12,30,81,63,148,99,13,64,49,80,15};
    VIP_ENCINT elements2[SIZE] = {25,97,1,0,36,22,74,3,99,12,30,81,63,148,99,13,64,49,99,15};

    VIP_ENCINT dup;

    bool res1, res2;

   
    for( int k=0;k<SIZE;k++){
        elements1[k] = k;
    }

    res1 = isDistinct(elements1, dup);

    if (res1)
            cout<<"The elements of `elements1' are distinct"<<endl;
        else
            cout<<"The elements of `elements1' are not distinct (e.g., " << dup << " is duplicated)"<<endl;
        
	return 0;
}

