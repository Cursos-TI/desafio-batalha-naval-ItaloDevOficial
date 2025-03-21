#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
//#define TAMANHO_NAVIO 3
#define AGUA 0
//#define NAVIO 3
#define HABILIDADE 5

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

int validarPosicao(int linha, int coluna, int tamanho, int horizontal) {
    if (horizontal) {
        return (coluna + tamanho <= TAMANHO_TABULEIRO);
    } else {
        return (linha + tamanho <= TAMANHO_TABULEIRO);
    }
}

/* int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int horizontal) {
    if (!validarPosicao(linha, coluna, TAMANHO_NAVIO, horizontal)) return 0;
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + (horizontal ? 0 : i)][coluna + (horizontal ? i : 0)] != AGUA) return 0;
    }
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + (horizontal ? 0 : i)][coluna + (horizontal ? i : 0)] = NAVIO;
    }
    return 1;
}*/

/* int posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao) {
    if ((direcao == 1 && (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO)) ||
        (direcao == 0 && (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna - (TAMANHO_NAVIO - 1) < 0))) {
        return 0;
    }
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + (direcao ? i : -i)] != AGUA) return 0;
    }
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna + (direcao ? i : -i)] = NAVIO;
    }
    return 1;
} */

void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tipo) {
    if (tipo == 1) { // Cone
        for (int i = 0; i < 3; i++) {
            for (int j = -i; j <= i; j++) {
                if (linha + i < TAMANHO_TABULEIRO && coluna + j >= 0 && coluna + j < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linha + i][coluna + j] == AGUA) {
                        tabuleiro[linha + i][coluna + j] = HABILIDADE;
                    }
                }
            }
        }
    } else if (tipo == 2) { // Cruz
        for (int i = -2; i <= 2; i++) {
            if (linha + i >= 0 && linha + i < TAMANHO_TABULEIRO) {
                if (tabuleiro[linha + i][coluna] == AGUA) {
                    tabuleiro[linha + i][coluna] = HABILIDADE;
                }
            }
            if (coluna + i >= 0 && coluna + i < TAMANHO_TABULEIRO) {
                if (tabuleiro[linha][coluna + i] == AGUA) {
                    tabuleiro[linha][coluna + i] = HABILIDADE;
                }
            }
        }
    } else if (tipo == 3) { // Octaedro
        for (int i = -2; i <= 2; i++) {
            for (int j = -2 + abs(i); j <= 2 - abs(i); j++) {
                if (linha + i >= 0 && linha + i < TAMANHO_TABULEIRO && coluna + j >= 0 && coluna + j < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linha + i][coluna + j] == AGUA) {
                        tabuleiro[linha + i][coluna + j] = HABILIDADE;
                    }
                }
            }
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("     a  b  c  d  e  f  g  h  i  j\n");
    printf("   ---------------------------------");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("\n%2d |", i + 1);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            char simbolo = tabuleiro[i][j] == AGUA ? '~' : (tabuleiro[i][j] == HABILIDADE ? '#' : '*');
            printf(" %c ", simbolo);
        }
        printf("|");
    }
    printf("\n   ---------------------------------");
    printf("\n");
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);
    
    aplicarHabilidade(tabuleiro, 6, 2, 1); // Cone
    aplicarHabilidade(tabuleiro, 6, 7, 2); // Cruz
    aplicarHabilidade(tabuleiro, 2, 2, 3); // Octaedro
    
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
