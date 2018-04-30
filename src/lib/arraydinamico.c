#include "dinamicArray.h"


struct array_dinamico{
    COMMAND* array;
    int pos;
    int capacidade;
};


ARRAY_DINAMICO init_array(int size) {
    ARRAY_DINAMICO conjunto = (ARRAY_DINAMICO) malloc(sizeof(struct array_dinamico));
    conjunto->array = (COMMAND *) malloc(sizeof(COMMAND*)*size);
    conjunto->pos = 0;
    conjunto->capacidade = size;
    return conjunto;
}


ARRAY_DINAMICO array_insert(ARRAY_DINAMICO conjunto, COMMAND c){
    
    int posicao = conjunto->pos;
    
    if(conjunto->pos == (conjunto->capacidade - 2)) {
        conjunto->capacidade *= 2;
        conjunto->array = realloc(conjunto->array,conjunto->capacidade*sizeof(COMMAND*));
    }

    conjunto->array[posicao] = c;
    conjunto->pos++;

    return conjunto;
}


void free_array(ARRAY_DINAMICO l) {
    int i;

    for(i = 0; i < l->pos; i++){
        COMMAND c = l->array[i];
        freeCommand(c);
    }

    free(l->array);
    free(l);
}

int getPos(ARRAY_DINAMICO l){
    return l->pos;
}

COMMAND* getArray(ARRAY_DINAMICO l){
    return l->array;
}

