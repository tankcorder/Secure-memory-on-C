#define SECURE_MODE_OFF
#include <stdlib.h>
#include <stdio.h>
#include "automem.h"

void **memory_store;
unsigned int address_max = 0;

void add_memstore(void){
    void *tmp;
    unsigned int max_buf = address_max;
    address_max += 16;
    tmp = realloc(memory_store, sizeof(void *) * address_max);
    if(tmp == NULL){
        free(memory_store);
        exit(EXIT_FAILURE);
    }
    memory_store = (void **)tmp;
    for(int j = max_buf;j < address_max;j++)
        memory_store[j] = NULL;
}

void *malloc_secure(size_t byte){
    int i = 0;
    void *p = malloc(byte);
    if(p == NULL)
        exit(EXIT_FAILURE);
    //count memstore index
    for(;;i++){
        if(i == address_max){
            add_memstore();
        }
        if(memory_store[i] == NULL)
            break;
    }
    memory_store[i] = p;
    return p;
}

void *calloc_secure(size_t n, size_t size){
    int i = 0;
    void *p = calloc(n, size);
    if(p == NULL)
        exit(EXIT_FAILURE);
    //count memstore index
    for(;;i++){
        if(i == address_max)
            add_memstore();
        if(memory_store[i] == NULL)
            break;
    }
    memory_store[i] = p;
    return p;
}

void *realloc_secure(void *p, size_t byte){
    int i = 0;
    void *tmp;
    //count original address index
    for(;i != address_max && memory_store[i] != p;i++);
    if(i == address_max){
        tmp = malloc_secure(byte);
        return tmp;
    }
    tmp = realloc(p, byte);
    if(tmp == NULL){
        free(p);
        exit(EXIT_FAILURE);
    }
    memory_store[i] = tmp;
    return tmp;
}

void free_secure(void *p){
    int i = 0;
    if(p == NULL)
        return;
    for(;i != address_max && memory_store[i] != p;i++);
    if(i == address_max)
        return;
    free(p);
    memory_store[i] = NULL;
    return;
}

void memclear(){
    for(int i = 0;i < address_max;i++){
        if(memory_store[i] != NULL){
            free(memory_store[i]);
            memory_store[i] = NULL;
        }
    }
    free(memory_store);
    return;
}

