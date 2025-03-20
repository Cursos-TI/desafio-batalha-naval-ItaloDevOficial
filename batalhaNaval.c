#include <stdio.h>

void inicializarTabuleiro(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

int posicionarNavio(int tabuleiro[10][10], int linha, int coluna, int horizontal) {
    if (horizontal) {
        if (coluna + 3 > 10) return 0;
        for (int i = 0; i < 3; i++) {
            if (tabuleiro[linha][coluna + i] != 0) return 0;
        }
        for (int i = 0; i < 3; i++) {
            tabuleiro[linha][coluna + i] = 3;
        }
    } else {
        if (linha + 3 > 10) return 0;
        for (int i = 0; i < 3; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0;
        }
        for (int i = 0; i < 3; i++) {
            tabuleiro[linha + i][coluna] = 3;
        }
    }
    return 1;
}

void exibirTabuleiro(int tabuleiro[10][10]) {
    printf("     a  b  c  d  e  f  g  h  i  j\n");
    printf("   ---------------------------------");
    for (int i = 0; i < 10; i++) {
        printf("\n%2d |", i + 1);
        for (int j = 0; j < 10; j++) {
            if (tabuleiro[i][j] == 0) {
                printf(" ~ "); // Água representada por '~'
            } else {
                printf(" # "); // Navio representado por '#'
            }
        }
        printf("|");
    }
    printf("\n   ---------------------------------");
    printf("\n");
}

int main() {
    int tabuleiro[10][10];
    inicializarTabuleiro(tabuleiro);
    
    posicionarNavio(tabuleiro, 2, 3, 1);
    posicionarNavio(tabuleiro, 5, 6, 0);
    
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
