#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 20

const int VAZIO = INT_MIN;
const int NUM_TO_SHIFT = 5;

int conversor(int i) {
    if(i % 2 == 0) return i/2;
    else return MAX_SIZE - ((i + 1) / 2);
}

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
        int elemento_atual = (lista->vetor)[conversor(i)];
        if(elemento_atual == VAZIO) {
            contador_vazio++;
            continue;
        }
        contador_elemento++;
        (lista->vetor)[conversor(i)] = VAZIO;
        (lista->vetor)[conversor(i - contador_vazio)] = elemento_atual;
    }
    printf("A lista foi shiftada!\n");
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
    lista->tam += 1;
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
    lista->tam -= 1;
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
        if((lista->vetor)[i] != VAZIO)
            printf("%d ", (lista->vetor)[i]);
    }
    printf("\n");
}

void printar_memoria(Lista *lista) {
    shiftar_lista(lista);
    for(int i = 0; i < MAX_SIZE; i++) {
        int val = (lista->vetor)[i];
        if(val != VAZIO) printf("%d ", val);
        else printf("@ ");
    }
    printf("\n");
}

void requisitar_insercao(Lista *lista) {
    printf("Digite o elemento a ser inserido:\n");
    long long val;
    scanf("%lld", &val);
    while(val <= INT_MIN || val > INT_MAX) {
        printf("Valor inválido, tente novamente:\n");
        scanf("%lld", &val);
    }
    inserir_lista(val, lista);
}

void requisitar_remocao(Lista *lista) {
    printf("Digite um elemento a ser removido:\n");
    long long val;
    scanf("%lld", &val);
    while(val <= INT_MIN || val > INT_MAX) {
        printf("Valor inválido, tente novamente:\n");
        scanf("%lld", &val);
    }
    remover_lista(val, lista);
}

void requisitar_trocas(Lista *lista) {
    printf("Insira o valor do elemento, e em seguida o novo valor que desejar:\n");
    long long new_value, value;
    scanf("%lld%lld", &value, &new_value);
    while(value <= INT_MIN || value > INT_MAX || new_value <= INT_MIN || new_value > INT_MAX) {
        printf("Valores inválidos, tente novamente:\n");
        scanf("%lld%lld", &value, &new_value);
    }
    trocar_lista(new_value, value, lista);
}

int main() {
    Lista *lista = criar_lista();
    printf("Escolha sua opção:\n1)Inserir.\n2)Remover.\n3)Trocar.\n4)Sair\n");
    while(1) {
        int escolha;
        scanf("%d", &escolha);
        if(escolha == 1) requisitar_insercao(lista);
        else if(escolha == 2) requisitar_remocao(lista);
        else if(escolha == 3) requisitar_trocas(lista);
        else if(escolha == 4) break;
        else {
            printf("Escolha inválida, tente novamente:\n");
            continue;
        }
        printar_memoria(lista);
        printf("\nEscolha outra vez:\n");
    }
}
