#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lista {
    int contador;
    int arr[100000], aux[100000][10], auxLen[100000];
    int len;
};

void shift(struct Lista *lista) {
    int arr[100000];
    memset(arr, -1, sizeof(arr));
    int ind = 0;
    for(int i = 0; i < 100000; i++) {
        for(int j = (lista->auxLen)[i]; j >= 0; j--) {
            arr[ind++] = (lista->aux)[i][j];
        }
        lista->auxLen[i] = -1;
        arr[ind++] = (lista->arr)[i];
    }
    memcpy(lista->arr, arr, sizeof(lista->arr));
}


void insert(int x, int ind, struct Lista *lista) {
    if((lista->arr)[ind] == -1) {
        (lista->arr)[ind] = x;
    }
    else {
        int indAux = (lista->auxLen)[ind] + 1;
        (lista->auxLen)[ind] += 1;
        (lista->aux)[ind][indAux] = x;
    }
    if(lista->contador == 5) shift(lista);
    lista->contador += 1;
    lista->len += 1;
}


void printLista(struct Lista *lista) {
    shift(lista);
    for(int i = 0; i < lista->len; i++) {
        printf("%d ", (lista->arr)[i]);
    }
    printf("\npronto\n");
}

int main() {
    struct Lista lista;
    lista.contador = 0;
    lista.len = 0;
    memset(lista.arr, -1, sizeof(lista.arr));
    memset(lista.auxLen, -1, sizeof(lista.auxLen));
}
