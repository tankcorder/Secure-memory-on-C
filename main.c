#include "automem.h"
int main(){
    void *p;
    minit();
    for(int i = 0;i < 100;i++){
        p = malloc(10);
    }
    free(p);
    memclear();
}

