//#define SECURE_MODE_OFF
//#include <stdlib.h>
#include "automem.h"
int main(){
    void *p, *q;
    for(int i = 0;i < 10000;i++){
        p = malloc(100);
        q = malloc(1);
    }
    memclear();
}

