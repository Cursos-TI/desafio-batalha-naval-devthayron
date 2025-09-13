#include <stdio.h>

#define BOARD_SIZE 10   // Tamanho do tabuleiro
#define SHIP_SIZE 3     // Tamanho dos navios
#define SHIP_VAL 3      // Valor para navios
#define SKILL_VAL 5     // Valor para área de habilidade
#define SKILL_SIZE 5    // Matrizes de habilidade 5x5

/* -------------------------------------------------------
   Função utilitária: inicializa tabuleiro com 0 (água)
   ------------------------------------------------------- */
void inicializarTabuleiro(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

/* -------------------------------------------------------
   Funções para criar as matrizes de habilidades (5x5)
   Cada uma usa condicionais para marcar 1 onde a área
   da habilidade afeta e 0 onde não afeta.
   ------------------------------------------------------- */

// Cone apontando para baixo (topo = 1, base expandida)
void criarCone(int cone[SKILL_SIZE][SKILL_SIZE]) {
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            if (j >= (SKILL_SIZE/2 - i) && j <= (SKILL_SIZE/2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Cruz (centro + linhas horizontal e vertical)
void criarCruz(int cruz[SKILL_SIZE][SKILL_SIZE]) {
    int centro = SKILL_SIZE / 2;
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            if (i == centro || j == centro)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Octaedro (losango)
void criarOctaedro(int oct[SKILL_SIZE][SKILL_SIZE]) {
    int centro = SKILL_SIZE / 2;
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                oct[i][j] = 1;
            else
                oct[i][j] = 0;
        }
    }
}

/* -------------------------------------------------------
   Sobrepõe habilidade no tabuleiro
   - skill: matriz 5x5 com 0 e 1
   - origem: linha e coluna no tabuleiro (centro da skill)
   ------------------------------------------------------- */
void aplicarHabilidade(int board[BOARD_SIZE][BOARD_SIZE],
                       int skill[SKILL_SIZE][SKILL_SIZE],
                       int origemRow, int origemCol) {
    int centro = SKILL_SIZE / 2;
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            if (skill[i][j] == 1) {
                int row = origemRow + (i - centro);
                int col = origemCol + (j - centro);
                // valida limites
                if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
                    if (board[row][col] == 0) { 
                        // não sobrescreve navio
                        board[row][col] = SKILL_VAL;
                    }
                }
            }
        }
    }
}

/* -------------------------------------------------------
   Exibe tabuleiro com:
   0 = água, 3 = navio, 5 = habilidade
   ------------------------------------------------------- */
void exibirTabuleiro(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("\n   ");
    for (int j = 0; j < BOARD_SIZE; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d: ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) printf("~ "); // água
            else if (board[i][j] == SHIP_VAL) printf("# "); // navio
            else if (board[i][j] == SKILL_VAL) printf("* "); // habilidade
        }
        printf("\n");
    }
}

/* -------------------------------------------------------
   Programa principal
   ------------------------------------------------------- */
int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    inicializarTabuleiro(board);

    // Exemplos de navios fixos (mesmos do nível anterior)
    board[2][4] = board[2][5] = board[2][6] = SHIP_VAL; // horizontal
    board[6][1] = board[7][1] = board[8][1] = SHIP_VAL; // vertical
    board[0][0] = board[1][1] = board[2][2] = SHIP_VAL; // diagonal
    board[1][9] = board[2][8] = board[3][7] = SHIP_VAL; // diagonal

    // Matrizes de habilidades
    int cone[SKILL_SIZE][SKILL_SIZE];
    int cruz[SKILL_SIZE][SKILL_SIZE];
    int oct[SKILL_SIZE][SKILL_SIZE];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(oct);

    // Aplicar habilidades em pontos de origem fixos
    aplicarHabilidade(board, cone, 5, 5);  // cone no centro
    aplicarHabilidade(board, cruz, 7, 7);  // cruz na parte inferior
    aplicarHabilidade(board, oct, 3, 3);   // octaedro na parte superior

    // Exibir resultado
    exibirTabuleiro(board);

    return 0;
}
