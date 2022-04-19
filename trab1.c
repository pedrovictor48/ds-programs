#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 20

const int VAZIO = INT_MIN;
const int NUM_TO_SHIFT = 5;

typedef struct Lista {
    int vetor[MAX_SIZE], tam, contador_shift;
} Lista;

Lista *criar_lista() {
    Lista *ptr = malloc(sizeof(Lista));
    ptr->tam = ptr->contador_shift = 0;
    for(int i = 0; i < MAX_SIZE; i++) {
        (ptr->vetor)[i] = VAZIO;
    }
    return ptr;
}

void shiftar_lista(Lista *lista) {
    int contador_vazio = 0, contador_elemento = 0;
    for(int i = 0; contador_elemento < lista->tam && i < MAX_SIZE; i++) {
        int elemento_atual = (lista->vetor)[i];
        if(elemento_atual == VAZIO) {
            contador_vazio++;
            continue;
        }
        contador_elemento++;
        (lista->vetor)[i] = VAZIO;
        (lista->vetor)[i - contador_vazio] = elemento_atual;
    }
    
}

void inserir_lista(int elemento, Lista* lista) {
    if(lista->contador_shift == NUM_TO_SHIFT)
        shiftar_lista(lista);
    //achar primeiro indice vazio:
    int indice_vazio = 0;
    while(indice_vazio < MAX_SIZE && (lista->vetor)[indice_vazio] != VAZIO)
        indice_vazio++;
    if(indice_vazio >= MAX_SIZE) {
        //nao existem mais espaços vazios
        return;
    }
    //atribua
    (lista->vetor)[indice_vazio] = elemento;
    lista->contador_shift += 1;
}

void remover_lista(int elemento, Lista *lista) {
    if(lista->contador_shift == NUM_TO_SHIFT)
        shiftar_lista(lista);
    int ind_elemento = 0;
    while(ind_elemento < MAX_SIZE && (lista->vetor)[ind_elemento] != elemento)
        ind_elemento++;
    if(ind_elemento >= MAX_SIZE) {
        //nao existe esse elemento:
        return;
    }
    (lista->vetor)[ind_elemento] = VAZIO;
    lista->contador_shift += 1;
}


void trocar_lista(int novo_elemento, int elemento, Lista *lista) {
    int ind_elemento = 0;
    while(ind_elemento < MAX_SIZE && (lista->vetor)[ind_elemento] != elemento)
        ind_elemento++;
    if(ind_elemento >= MAX_SIZE) {
        //nao existe esse elemento:
        return;
    }
    (lista->vetor)[ind_elemento] = novo_elemento;
}

void printar_lista(Lista *lista) {
    shiftar_lista(lista);
    for(int i = 0; i < lista->tam; i++) {
        printf("%d ", (lista->vetor)[i]);
    }
    printf("\n");
}
