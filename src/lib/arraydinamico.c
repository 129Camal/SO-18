#include "arraydinamico.h"


struct array_dinamico{
    COMMAND* array;
    int pos;
    int capacidade;
};


ARRAY_DINAMICO init_array(int size) {
    ARRAY_DINAMICO conjunto = (ARRAY_DINAMICO) malloc(sizeof(struct array_dinamico));
    conjunto->array = (COMMAND) malloc(sizeof struct 
    conjunto->pos = 0;
    conjunto->capacidade = size;
    return conjunto;
}


ARRAY_DINAMICO array_insert(ARRAY_DINAMICO conjunto, char* valor) {
    
    int posicao = conjunto->pos;
    
    if(conjunto->pos == (conjunto->capacidade - 2)) {
        conjunto->capacidade *= 2;
        conjunto->array = realloc(conjunto->array,conjunto->capacidade *sizeof(long));
    }

    conjunto->array[posicao] = valor;
    conjunto->pos++;

    return conjunto;
}


void free_array(ARRAY_DINAMICO l) {
    
    free(l->array);
    free(l);
}

int getPos(ARRAY_DINAMICO l){
    return l->pos;
}

long* getArray(ARRAY_DINAMICO l){
    return l->array;
}

LONG_list converteArray(ARRAY_DINAMICO arr){
    long i;

    LONG_list l = create_list(arr->pos);
    for(i=0; i < arr->pos; i++){
        set_list(l, i, arr->array[i]);
        printf("%ld\n", arr->array[i]);
    }
    return l;
}


