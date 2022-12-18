//#define SECURE_MODE_OFF
//#include <stdlib.h>
#include "automem.h"
int main(){
    void *p, *q;
    for(int i = 0;i < 16;i++){
        p = malloc(10);
        realloc(p, 2);
        q = calloc(2, sizeof(int));
        free(q);
    }
    memclear();
}

