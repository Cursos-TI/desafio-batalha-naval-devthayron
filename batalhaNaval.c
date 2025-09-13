#include <stdio.h>

#define TAM 10   // tamanho fixo do tabuleiro
#define NAVIO 3  // valor que representa as partes do navio
#define TAM_NAVIO 3 // tamanho fixo dos navios (3 casas)

// Função para exibir o tabuleiro completo
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]); // imprime o valor da posição
        }
        printf("\n");
    }
}

int main() {
    // -------------------------------
    // 1. Inicializar tabuleiro 10x10
    // -------------------------------
    int tabuleiro[TAM][TAM];
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0; // todas as posições começam com água
        }
    }

    // -------------------------------
    // 2. Declarar navios (vetores)
    // Cada navio ocupa 3 casas
    // -------------------------------
    int navioHorizontal[TAM_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAM_NAVIO]   = {NAVIO, NAVIO, NAVIO};

    // -------------------------------
    // 3. Definir coordenadas iniciais
    // Exemplo fixo: horizontal na linha 2, col 4
    //              vertical   na linha 5, col 7
    // -------------------------------
    int linhaH = 2, colH = 4; // navio horizontal
    int linhaV = 5, colV = 7; // navio vertical

    // -------------------------------
    // 4. Posicionar navio horizontal
    // -------------------------------
    for (int i = 0; i < TAM_NAVIO; i++) {
        // validação: não pode sair do limite
        if (colH + i < TAM && tabuleiro[linhaH][colH + i] == 0) {
            tabuleiro[linhaH][colH + i] = navioHorizontal[i];
        }
    }

    // -------------------------------
    // 5. Posicionar navio vertical
    // -------------------------------
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (linhaV + i < TAM && tabuleiro[linhaV + i][colV] == 0) {
            tabuleiro[linhaV + i][colV] = navioVertical[i];
        }
    }

    // -------------------------------
    // 6. Exibir tabuleiro
    // -------------------------------
    exibirTabuleiro(tabuleiro);

    return 0;
}
