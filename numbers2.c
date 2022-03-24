#include <stdio.h>
#include <string.h>

char UDC[3][10][100] = {
    {
        "",
        "um",
        "dois",
        "tres",
        "quatro",
        "cinco",
        "seis",
        "sete",
        "oito",
        "nove"
    },
    {
        "",
        "", //trato os 'dezes' depois
        "vinte",
        "trinta",
        "quarenta",
        "cinquenta",
        "sessenta",
        "setenta",
        "oitenta",
        "noventa"
    },
    {
        "",
        "cento",
        "duzentos",
        "trezentos",
        "quatrocentos",
        "quinhentos",
        "seiscentos",
        "setecentos",
        "oitocentos",
        "novecentos"
    }
};

char especial[10][100] = {
    "dez",
    "onze",
    "doze",
    "treze",
    "quatorze",
    "quinze",
    "dezesseis",
    "dezessete",
    "dezoito",
    "dezenove"
};

//milhar[i][j] retorna uma string onde i diz se é singular
//ou plurar, e j diz o nível: mil, milhao, bilhao etc

char milhar[2][5][100] = {
    {
        "",
        "mil",
        "milhoes",
        "bilhoes",
        "trilhoes",
    },
    {
        "",
        "mil",
        "milhao",
        "bilhao",
        "trilhao",
    },
};

void tratarMilhar2(int arr[3], int nivel) {
    int soma = 0;
    for(int i = 0; i < 3; i++) soma += arr[i];

    if(soma == 0) return; //caso pra nao printar a unidade de milhar
    if(soma == 1 && arr[2] == 1 && nivel == 1) {
        printf(" mil");
        return;
    }


    for(int i = 0; i < 3; i++) {
        int numeroAtual = arr[i];
        
        //booleano pra checar se existe um número maior que 0 antes desse iésimo
        //pra ver se é pra printar o 'e' ou não
        int existe = 0;
        for(int j = i - 1; j >= 0; j--) {
            if(arr[j] > 0) existe = 1;
        }

        if(existe && numeroAtual > 0) printf(" e ");

        //caso dos 10s
        if(i == 1 && numeroAtual == 1) {
            printf("%s", especial[arr[2]]);
            break;
        }
        printf("%s", UDC[2 - i][numeroAtual]);
    }
    int ehSingular = soma == 1 && arr[2] == 1;
    printf(" %s", milhar[ehSingular][nivel]);

}

void iterarNumero2(char n[], int i, int nivel) {
    int soma = 0, arr[3] = {0};
    for(int j = 0; j < 3; j++, i--) {
        if(i >= 0) {
            arr[2 - j] = n[i] - '0';
            soma += arr[2 - j];
        }
    }
    if(i >= 0) {
        iterarNumero2(n, i, nivel + 1);
        if(soma > 0) printf(nivel == 0 ? " e " : ", ");
    }
    tratarMilhar2(arr, nivel);
}

int main() {
    char n[20];
    scanf("%s", n);
    iterarNumero2(n, strlen(n) - 1, 0);
    printf("\n");
}