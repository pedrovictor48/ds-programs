#include <stdio.h>

int usuario = 1, computador = 2;

int check(int tab[3][3], int jogador) {
    for(int i = 0; i < 3; i++) {
        if(tab[i][0] == tab[i][1] && tab[i][1] == tab[i][2]) return tab[i][0] == jogador;
        if(tab[0][i] == tab[1][i] && tab[1][i] == tab[2][i]) return tab[0][i] == jogador;
    }
    if(tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2]) return tab[0][0] == jogador;
    if(tab[2][0] == tab[1][1] && tab[0][2] == tab[1][1]) return tab[0][0] == jogador;
    return 0;
}

int brute(int i, int j, int tab[3][3], int vez) {
    int ret = 0;
    if(i == 3) {
        return check(tab, usuario);
    }
    int old = tab[i][j];
    if(old == 0) tab[i][j] = vez;
    int nI = i, nJ = j;
    if(nJ == 2) nI++, nJ = 0;
    else nJ++;
    ret += brute(nI, nJ, tab, vez == 1 ? 2 : 1);
    tab[i][j] = old;
    return ret;
}

void printTable(int tab[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int simbolo = tab[i][j];
            if(simbolo == 1) printf("x ");
            else if(simbolo == 2) printf("o ");
            else printf("- ");
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tab[3][3];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            tab[i][j] = 0;
    int vez = 1;
    while(check(tab, computador) == 0 && check(tab, usuario) == 0) {
        //iterando jogadas
        if(vez == computador) {
            int pI[9], pJ[9], qtdP = 0;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(tab[i][j] == 0) {
                        pI[qtdP] = i;
                        pJ[qtdP] = j;
                        qtdP++;
                    }
                }
            }

            //e agora testando qual escolha o usuario ganha 0

            for(int i = 0; i < qtdP; i++) {
                int indI = pI[i], indJ = pJ[i];
                tab[indI][indJ] = vez;
                int qtdVitorias = brute(0, 0, tab, vez);

                //se o usuario ganha 0 vezes escolha essa
                if(qtdVitorias == 0) {
                    break;
                }
                //do contrario tente a proxima
                else tab[indI][indJ] = 0;
            }
        }
        else {
            int indI, indJ;
            scanf("%d %d", &indI, &indJ);
            tab[indI][indJ] = vez;
        }
        printTable(tab);
        vez = (vez == 1) ? 2 : 1;
    }

    if(check(tab, computador)) printf("pc ganhou\n");
    else printf("usuario ganhou\n");
    printTable(tab);
}