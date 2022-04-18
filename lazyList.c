#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 1000
const int VAZIO = INT_MIN;
int TAM_MAX;

int conversor(int i) {
    if(i % 2 == 0) return i/2;
    else return TAM_MAX - ((i + 1) / 2);
}

//definindo a estrutura da lista:
typedef struct lazyList {
    int vetor[MAX_SIZE], expoente[MAX_SIZE], tam, indice_min;
    /*
    Desc. das variáveis:
    vetor: espaço na memória responsável por guardar os elementos.
    expoente: espaço na memória responsável por guardar o que fica acima dos elementos.
    tam: tamanho da lista.
    indice_min: indice minimo até então alterado.
    */
} lazyList;

lazyList *criar_lazyList() {
    lazyList *ptr = malloc(sizeof(lazyList));
    //enchendo as memórias de vazio:
    for(int i = 0; i < MAX_SIZE; i++)
        (ptr->vetor)[i] = (ptr->expoente)[i] = VAZIO;
    
    ptr->tam = 0;
    ptr->indice_min = INT_MAX;

    return ptr;
}

void ajeitar_lazyList(lazyList *lazy_list) {
    //array temporária:
    int temp[TAM_MAX];
    for(int i = 0; i < TAM_MAX; i++)
        temp[i] = VAZIO;
    //indice auxiliar que vai incrementando:
    int indTemp = 0;
    for(int i = 0; i < TAM_MAX; i++) {
        //atribuindo VAZIO caso os elementos já tenham acabado:
        //pegando tanto o possível elemento inserido acima
        //quanto o elemento do vetor em si
        int indReal = conversor(i);
        int elementoAcima = (lazy_list->expoente)[indReal],
            elementoIndice = (lazy_list->vetor)[indReal];
        
        //se algum for diferente de vazio, ponha na temporaria:
        if(elementoAcima != VAZIO) {
            int indTempReal = conversor(indTemp);
            temp[indTempReal] = elementoAcima;
            indTemp += 1;
        }
        if(elementoIndice != VAZIO) {
            int indTempReal = conversor(indTemp);
            temp[indTempReal] = elementoIndice;
            indTemp += 1;
        }
        //atribua vazio ao expoente:
        (lazy_list->expoente)[indReal] = VAZIO;
    }

    //copiando para a struct:
    for(int i = 0; i < TAM_MAX; i++)
        (lazy_list->vetor)[i] = temp[i];
    
    //ao ajeitar, o minimo indice volta para o maior possível:
    lazy_list->indice_min = INT_MAX;
}

void inserir_lazyList(lazyList *lazy_list, int valor, int indice) {
    //se o indice já estiver depois de um que já foi alterado:
    if(indice >= lazy_list->indice_min) {
        ajeitar_lazyList(lazy_list);
    }
    //prossiga:
    lazy_list->indice_min = indice;
    //já que estou adicionando, insiro no expoente;
    indice = conversor(indice);
    (lazy_list->expoente)[indice] = valor;
    lazy_list->tam += 1;
}

void remover_lazyList(lazyList *lazy_list, int indice) {
    if(lazy_list->tam == 0) return;
    //se o indice já estiver depois de um que já foi alterado:
    if(indice >= lazy_list->indice_min) {
        ajeitar_lazyList(lazy_list);
    }
    //prossiga:
    if(lazy_list->indice_min > indice)
        lazy_list->indice_min = indice;
    //já que estou removendo, insira um valor vazio no vetor:
    indice = conversor(indice);
    (lazy_list->vetor)[indice] = VAZIO;
    lazy_list->tam -= 1;
}

void trocar_lazyList(lazyList *lazy_list, int valor, int indice) {
    //se o indice já estiver depois de um que já foi alterado:
    if(indice >= lazy_list->indice_min) {
        ajeitar_lazyList(lazy_list);
    }
    //prossiga:
    if(lazy_list->indice_min > indice)
        lazy_list->indice_min = indice;
    //já que estou adicionando, insiro no expoente;
    int indiceReal = conversor(indice);
    (lazy_list->vetor)[indiceReal] = valor;
}

void print_lazyList(lazyList *lazy_list) {
    printf("Representação da lista:\n");
    ajeitar_lazyList(lazy_list);
    for(int i = 0; i < lazy_list->tam; i++) {
        int indiceReal = conversor(i);
        printf("%d -> ", (lazy_list->vetor)[indiceReal]);
    }
    printf("@\n");
}

void print_memoria(lazyList *lazy_list) {
    printf("Representacao da memoria:\n");
    for(int i = 0; i < TAM_MAX; i++) {
        int value = (lazy_list->vetor)[i];
        if(value != VAZIO) printf("%d ", value);
        else printf("@ ");
    }
    printf("\n");
}

void requisitar_inserts(lazyList *lazy_list) {
    int indice;
    long long valor;
    printf("Requisitando inserções, aperte enter sem enviar nada para sair:\n");
    while(1) {
        scanf("%d%lld", &indice, &valor);
        if(indice < 0 || indice > TAM_MAX) {
            printf("Indice fora o range, tente novamente:\n");
            continue;
        }
        if(valor > INT_MAX || valor <= INT_MIN) {
            printf("Valor fora do range, tente novamente:\n");
            continue;
        }
        printf("Realizado:\n");
        inserir_lazyList(lazy_list, valor, indice);
        print_lazyList(lazy_list);
        print_memoria(lazy_list);
        break;
    }
}

void requistar_remocao(lazyList *lazy_list) {
    int indice;
    printf("Requisitando remoções, aperte enter sem enviar nada para sair:\n");
    while(1) {
        scanf("%d", &indice);
        if(indice < 0 || indice >= lazy_list->tam) {
            printf("Indice fora o range, tente novamente:\n");
            continue;
        }
        printf("Realizado:\n");
        remover_lazyList(lazy_list, indice);
        print_lazyList(lazy_list);
        print_memoria(lazy_list);
        break;
    }
}

void requisitar_trocas(lazyList *lazy_list) {
    int indice;
    long long valor;
    printf("Requisitando trocas, aperte enter sem enviar nada para sair:\n");
    
    while(1) {
        scanf("%d%lld", &indice, &valor);
        if(indice < 0 || indice >= lazy_list->tam) {
            printf("Indice fora o range, tente novamente:\n");
            continue;
        }
        if(valor > INT_MAX || valor <= INT_MIN) {
            printf("Valor fora do range, tente novamente:\n");
            continue;
        }
        printf("Realizado:\n");
        trocar_lazyList(lazy_list, valor, indice);
        print_lazyList(lazy_list);
        print_memoria(lazy_list);
        break;
    }
    
}

int main() {
    lazyList *lazy_list = criar_lazyList();
    printf("Insira o tamanho máximo para sua lista:\n");
    scanf("%d", &TAM_MAX);
    while(TAM_MAX > MAX_SIZE) {
        printf("Este tamanho ultrapassou o limite, tente outro:\n");
        scanf("%d", &TAM_MAX);
    }
    
    printf("Escolha sua opção:\n1)Inserir.\n2)Remover.\n3)Trocar.\n4)Sair\n");
    while(1) {
        int escolha;
        scanf("%d", &escolha);
        if(escolha == 1) requisitar_inserts(lazy_list);
        else if(escolha == 2) requistar_remocao(lazy_list);
        else if(escolha == 3) requisitar_trocas(lazy_list);
        else if(escolha == 4) break;
        else {
            printf("Escolha inválida, tente novamente:\n");
            continue;
        }
        printf("\nEscolha outra vez:\n");
    }
}
