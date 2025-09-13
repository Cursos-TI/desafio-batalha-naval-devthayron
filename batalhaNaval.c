#include <stdio.h>

#define BOARD_SIZE 10   // tamanho do tabuleiro (10x10)
#define SHIP_SIZE 3     // tamanho fixo de cada navio (3 casas)
#define SHIP_VAL 3      // valor para representar parte de navio na matriz

/* ---------------------------------------------------------
   Funções de validação (verificam limites e sobreposição)
   Todas retornam 1 se possível posicionar, 0 caso contrário.
   --------------------------------------------------------- */

/* Horizontal: linha fixa, coluna aumenta */
int can_place_horizontal(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size) {
    if (row < 0 || row >= BOARD_SIZE) return 0;
    if (col < 0 || col + size - 1 >= BOARD_SIZE) return 0;
    int i;
    for (i = 0; i < size; i++) {
        if (board[row][col + i] != 0) return 0; // sobreposição
    }
    return 1;
}

/* Vertical: coluna fixa, linha aumenta */
int can_place_vertical(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size) {
    if (col < 0 || col >= BOARD_SIZE) return 0;
    if (row < 0 || row + size - 1 >= BOARD_SIZE) return 0;
    int i;
    for (i = 0; i < size; i++) {
        if (board[row + i][col] != 0) return 0;
    }
    return 1;
}

/* Diagonal para baixo-direita: (row+i, col+i) */
int can_place_diag_down_right(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size) {
    if (row < 0 || col < 0) return 0;
    if (row + size - 1 >= BOARD_SIZE || col + size - 1 >= BOARD_SIZE) return 0;
    int i;
    for (i = 0; i < size; i++) {
        if (board[row + i][col + i] != 0) return 0;
    }
    return 1;
}

/* Diagonal para baixo-esquerda: (row+i, col-i) */
int can_place_diag_down_left(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size) {
    if (row < 0 || col >= BOARD_SIZE) return 0;
    if (row + size - 1 >= BOARD_SIZE || col - (size - 1) < 0) return 0;
    int i;
    for (i = 0; i < size; i++) {
        if (board[row + i][col - i] != 0) return 0;
    }
    return 1;
}

/* ---------------------------------------------------------
   Funções de posicionamento: copiam os valores do vetor
   do navio para a matriz do tabuleiro.
   --------------------------------------------------------- */

void place_horizontal(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int ship[SHIP_SIZE]) {
    int i;
    for (i = 0; i < SHIP_SIZE; i++) {
        board[row][col + i] = ship[i];
    }
}

void place_vertical(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int ship[SHIP_SIZE]) {
    int i;
    for (i = 0; i < SHIP_SIZE; i++) {
        board[row + i][col] = ship[i];
    }
}

void place_diag_down_right(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int ship[SHIP_SIZE]) {
    int i;
    for (i = 0; i < SHIP_SIZE; i++) {
        board[row + i][col + i] = ship[i];
    }
}

void place_diag_down_left(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int ship[SHIP_SIZE]) {
    int i;
    for (i = 0; i < SHIP_SIZE; i++) {
        board[row + i][col - i] = ship[i];
    }
}

/* ---------------------------------------------------------
   Exibe o tabuleiro na tela (0 = água, 3 = navio)
   Mostra índices para facilitar visualização.
   --------------------------------------------------------- */
void exibirTabuleiro(int board[BOARD_SIZE][BOARD_SIZE]) {
    int i, j;
    printf("\n   "); // cabeçalho de colunas
    for (j = 0; j < BOARD_SIZE; j++) {
        printf("%d ", j);
    }
    printf("\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%d: ", i); // índice da linha
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* ---------------------------------------------------------
   Programa principal
   - Inicializa tabuleiro
   - Declara vetores navio (cada um com 3 posições)
   - Define coordenadas FIXAS (no código) para 4 navios:
       * 1 horizontal
       * 1 vertical
       * 1 diagonal (baixo-direita)
       * 1 diagonal (baixo-esquerda)
   - Valida e posiciona cada navio (imprime mensagem de erro
     caso algo esteja inválido)
   --------------------------------------------------------- */
int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    int i, j;

    // 1) Inicializa tabuleiro com 0 (água)
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }

    // 2) Vetores que representam os navios (cada posição vale 3)
    int navioA[SHIP_SIZE] = {SHIP_VAL, SHIP_VAL, SHIP_VAL}; // horizontal/vertical
    int navioB[SHIP_SIZE] = {SHIP_VAL, SHIP_VAL, SHIP_VAL}; // horizontal/vertical
    int navioC[SHIP_SIZE] = {SHIP_VAL, SHIP_VAL, SHIP_VAL}; // diagonal
    int navioD[SHIP_SIZE] = {SHIP_VAL, SHIP_VAL, SHIP_VAL}; // diagonal

    // 3) Coordenadas definidas diretamente no código (sem input)
    // Escolhi coordenadas que cabem no tabuleiro e não se sobrepõem.
    int h_row = 2, h_col = 4;   // navio A: horizontal -> ocupa (2,4),(2,5),(2,6)
    int v_row = 6, v_col = 1;   // navio B: vertical   -> ocupa (6,1),(7,1),(8,1)
    int dr_row = 0, dr_col = 0; // navio C: diagonal baixo-direita -> (0,0),(1,1),(2,2)
    int dl_row = 1, dl_col = 9; // navio D: diagonal baixo-esquerda -> (1,9),(2,8),(3,7)

    // 4) Valida e posiciona cada navio
    if (can_place_horizontal(board, h_row, h_col, SHIP_SIZE)) {
        place_horizontal(board, h_row, h_col, navioA);
        printf("Navio horizontal posicionado em (%d,%d) -> direita.\n", h_row, h_col);
    } else {
        printf("ERRO: não foi possível posicionar navio horizontal em (%d,%d)\n", h_row, h_col);
    }

    if (can_place_vertical(board, v_row, v_col, SHIP_SIZE)) {
        place_vertical(board, v_row, v_col, navioB);
        printf("Navio vertical posicionado em (%d,%d) -> para baixo.\n", v_row, v_col);
    } else {
        printf("ERRO: não foi possível posicionar navio vertical em (%d,%d)\n", v_row, v_col);
    }

    if (can_place_diag_down_right(board, dr_row, dr_col, SHIP_SIZE)) {
        place_diag_down_right(board, dr_row, dr_col, navioC);
        printf("Navio diagonal (baixo-direita) posicionado em (%d,%d).\n", dr_row, dr_col);
    } else {
        printf("ERRO: não foi possível posicionar navio diagonal (baixo-direita) em (%d,%d)\n", dr_row, dr_col);
    }

    if (can_place_diag_down_left(board, dl_row, dl_col, SHIP_SIZE)) {
        place_diag_down_left(board, dl_row, dl_col, navioD);
        printf("Navio diagonal (baixo-esquerda) posicionado em (%d,%d).\n", dl_row, dl_col);
    } else {
        printf("ERRO: não foi possível posicionar navio diagonal (baixo-esquerda) em (%d,%d)\n", dl_row, dl_col);
    }

    // 5) Exibe tabuleiro final
    exibirTabuleiro(board);

    return 0;
}
