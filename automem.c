#define SECURE_MODE_OFF
#include <stdlib.h>
#include <stdio.h>
#include "automem.h"

void *memory_store[500];

void minit(){
    for(int i = 0;i < 500;i++)
        memory_store[i] = NULL;
}

void *malloc_secure(size_t byte){
    int i = 0;
    void *p = malloc(byte);
    if(p == NULL)
        exit(EXIT_FAILURE);
    for(;i != 500 && memory_store[i] != NULL;i++);
    if(i == 500)
        exit(EXIT_FAILURE);
    memory_store[i] = p;
    return p;
}

void free_secure(void *p){
    int i = 0;
    if(p == NULL)
        return;
    for(;i != 500 && memory_store[i] != p;i++);
    if(i == 500)
        return;
    free(p);
    memory_store[i] = NULL;
    return;
}

void memclear(){
    for(int i = 0;i < 500;i++){
        if(memory_store[i] != NULL){
            free(memory_store[i]);
            memory_store[i] = NULL;
        }
    }
    return;
}

