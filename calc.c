#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    double value;
    char op;
    struct Node *next;
};

struct Stack {
    struct Node *head;
    int size;
};

struct Stack* criarStack() {
    struct Stack* temp = malloc(sizeof(struct Stack));
    temp->head = NULL;
    temp->size = 0;
    return temp;
};

void adicionarOp(struct Stack* stack, char op) {
    struct Node* temp = malloc(sizeof(struct Node));
    temp->op = op;
    temp->next = stack->head;
    stack->head = temp;
    stack->size += 1;
}

void adicionarVal(struct Stack* stack, double value) {
    struct Node* temp = malloc(sizeof(struct Node));
    temp->value = value;
    temp->next = stack->head;
    stack->head = temp;
    stack->size += 1;
}

void removeNode(struct Stack* stack) {
    struct Node* temp = stack->head;
    if(temp == NULL) return;
    stack->head = temp->next;
    free(temp);
    stack->size -= 1;
}

char topOp(struct Stack* stack) {
    return stack->head->op;
}

double topNum(struct Stack* stack) {
    return stack->head->value;
}

int getNextInt(char *exp, int *i) {
    int num = 0;
    while(exp[*i] != '\0') {
        if(exp[*i] >= '0' && exp[*i] <= '9') {
            num *= 10;
            num += exp[*i] - '0';
            *i += 1;
        }
        else break;
    }
    *i -= 1;
    return num;
}

void realize(struct Stack* stackOp, struct Stack* stackVal) {
    double num2 = topNum(stackVal);
    removeNode(stackVal);
    double num1 = topNum(stackVal);
    removeNode(stackVal);

    char op = topOp(stackOp);
    removeNode(stackOp);

    double res = 0;
    if(op == '*') res = num1*num2;
    else if(op == '/') res = num1/num2;
    else if(op == '+') res = num1 + num2;
    else if(op == '-') res = num1 - num2;

    adicionarVal(stackVal, res);
}

double resolverExp(char exp[], int st, int len) {
    struct Stack* pilhaValores = criarStack();
    struct Stack* pilhaOp = criarStack();
    for(int i = 0; i < len; i++) {
        char curr = exp[i];
        if(curr == ' ') continue;
        if(curr == ')') {
            while(pilhaValores->size > 1)
                realize(pilhaOp, pilhaValores);
            return pilhaValores->head->value;
        }

        if(curr >= '0' && curr <= '9') {
            int num = getNextInt(exp, &i);
            adicionarVal(pilhaValores, num);
        }
        else {
            if(curr == '+' || curr == '-') {
                while(pilhaOp->head != NULL &&  (pilhaOp->head->op == '*' || pilhaOp->head->op == '/')) {
                    realize(pilhaOp, pilhaValores);
                    printf("a\n");
                }
            }
            adicionarOp(pilhaOp, curr);
        }
    }
}

int main() {
    char exp[100000];
    scanf("%[^\n]", exp);
    struct Stack* pilhaValores = criarStack();
    struct Stack* pilhaOp = criarStack();
    int len = strlen(exp);
    for(int i = 0; i < len; i++) {
        //printf("%d", i);
        char curr = exp[i];
        if(curr == ' ') continue;

        if(curr >= '0' && curr <= '9') {
            int num = getNextInt(exp, &i);
            adicionarVal(pilhaValores, num);
        }
        else {
            if(curr == '+' || curr == '-') {
                while(pilhaOp->head != NULL &&  (pilhaOp->head->op == '*' || pilhaOp->head->op == '/')) {
                    realize(pilhaOp, pilhaValores);
                    printf("a\n");
                }
            }
            adicionarOp(pilhaOp, curr);
        }
    }
    while(pilhaValores->size > 1)
        realize(pilhaOp, pilhaValores);
    printf("%lf\n", pilhaValores->head->value);
}