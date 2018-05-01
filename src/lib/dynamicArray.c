#include "dynamicArray.h"

#include <stdlib.h>

struct d_array{
    COMMAND* array;
    int pos;
    int capacidade;
};

D_ARRAY init_array(int size) {
    D_ARRAY conjunto = (D_ARRAY) malloc(sizeof(struct d_array));
    conjunto->array = (COMMAND *) malloc(sizeof(COMMAND*)*size);
    conjunto->pos = 0;
    conjunto->capacidade = size;
    return conjunto;
}


D_ARRAY array_insert(D_ARRAY conjunto, COMMAND c){
    
    int posicao = conjunto->pos;
    
    if(conjunto->pos == (conjunto->capacidade - 2)) {
        conjunto->capacidade *= 2;
        conjunto->array = realloc(conjunto->array,conjunto->capacidade*sizeof(COMMAND*));
    }

    conjunto->array[posicao] = c;
    conjunto->pos++;

    return conjunto;
}


void free_array(D_ARRAY l) {
    int i;

    for(i = 0; i < l->pos; i++){
        COMMAND c = l->array[i];
        freeCommand(c);
    }

    free(l->array);
    free(l);
}

int getPos(D_ARRAY l){
    return l->pos;
}

COMMAND* getArray(D_ARRAY l){
    return l->array;
}

