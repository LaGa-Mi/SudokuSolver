#include <stdio.h>

#define NUM_ROWS 9
#define NUM_COLS 9
#define N 9
#define SQUARE_SIZE 3

typedef struct Board {
    int boardState[NUM_ROWS][NUM_COLS];
} Board;

int isValidSquare(int squareIndex, Board* board);
int isValidColumn(int columnIndex, Board* board);
int isValidRow(int rowIndex, Board* board);
int isValidBoard(Board* board);
int isValidMove(int rowIndex, int columnIndex, int value, Board* board);
int solveRecursively(int rowIndex, int columnIndex, Board* board);
void displayBoardState(Board* board);

int main(char* argv, int argc) {
    /*
    Board board = {{
        {0, 1, 0, 2, 0, 8, 0, 0, 0},
        {0, 0, 0, 7, 0, 0, 0, 2, 6},
        {0, 0, 2, 1, 4, 0, 0, 9, 0},
        {0, 0, 0, 0, 0, 2, 7, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 0, 4, 8, 0, 0, 0, 0, 0},
        {0, 3, 0, 0, 2, 7, 5, 0, 0},
        {4, 8, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 6, 0, 1, 0, 3, 0},
    }};
    */
    Board board = {{
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    }};

    if (!isValidBoard(&board)) {
        printf("Board is not valid!");

        return 0;
    }

    if (!solveRecursively(0, 0, &board)) printf("There are no solutions\n");
    else displayBoardState(&board);

    return 0;
}

int isValidSquare(int squareIndex, Board* board) {
    int squareRowIndex = (squareIndex / SQUARE_SIZE) * SQUARE_SIZE;
    int squareColumnIndex = (squareIndex % SQUARE_SIZE) * SQUARE_SIZE;
    int seenNumbers[N] = {0};
    int checkedSquare;

    for (int i = 0; i < SQUARE_SIZE; i++) {
        for (int j = 0; j < SQUARE_SIZE; j++) {
            checkedSquare = board->boardState[squareRowIndex + i][squareColumnIndex + j];
            if (checkedSquare == 0) continue;
            else checkedSquare -= 1; 
            if (seenNumbers[checkedSquare]) return 0;
            else seenNumbers[checkedSquare] = 1;
        }
    }

    return 1;
}

int isValidColumn(int columnIndex, Board* board) {
    int seenNumbers[N] = {0};
    int checkedSquare;

    for (int i = 0; i < N; i++) {
        checkedSquare = board->boardState[i][columnIndex];
        if (checkedSquare == 0) continue;
        else checkedSquare -= 1; 
        if (seenNumbers[checkedSquare]) return 0;
        else seenNumbers[checkedSquare] = 1;
    }

    return 1;
}

int isValidRow(int rowIndex, Board* board) {
    int seenNumbers[N] = {0};
    int checkedSquare;

    for (int i = 0; i < N; i++) {
        checkedSquare = board->boardState[rowIndex][i];
        if (checkedSquare == 0) continue;
        else checkedSquare -= 1; 
        if (seenNumbers[checkedSquare]) return 0;
        else seenNumbers[checkedSquare] = 1;
    }

    return 1;
}

int isValidBoard(Board* board) {
    int i;

    for (i = 0; i < N; i++) {
        if (!isValidSquare(i, board) || !isValidRow(i, board) || !isValidColumn(i, board)) return 0;
    }

    return 1;
}

int isValidMove(int rowIndex, int columnIndex, int value, Board* board) {
    int previousValue = board->boardState[rowIndex][columnIndex];
    int isValidMove;

    board->boardState[rowIndex][columnIndex] = value;

    if (isValidSquare((rowIndex / 3) * 3 + columnIndex / 3, board) && isValidColumn(columnIndex, board) && isValidRow(rowIndex, board)) isValidMove = 1;
    else isValidMove = 0;

    board->boardState[rowIndex][columnIndex] = previousValue;

    return isValidMove;
}

int solveRecursively(int rowIndex, int columnIndex, Board* board) {
    int nextRowIndex;
    int nextColumnIndex;

    if (rowIndex == N) return 1;

    nextRowIndex = rowIndex + (columnIndex == 8 ? 1 : 0);
    nextColumnIndex = (columnIndex + 1) % 9;

    if (board->boardState[rowIndex][columnIndex] != 0) return solveRecursively(nextRowIndex, nextColumnIndex, board);
    for (int i = 1; i < N + 1; i++) {
        if (isValidMove(rowIndex, columnIndex, i, board)) {
            board->boardState[rowIndex][columnIndex] = i;
            if (solveRecursively(nextRowIndex, nextColumnIndex, board)) {
                return 1;
            }
        }
    }

    board->boardState[rowIndex][columnIndex] = 0;
    return 0;
}

void displayBoardState(Board* board) {
    int lastColumnIndex = NUM_COLS - 1;

    printf("\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < lastColumnIndex; j++) {
            if (((j + 1) % SQUARE_SIZE) != 0) printf("%c ", (board->boardState[i][j] == 0 ? ' ' : board->boardState[i][j] + '0'));
            else printf("%c || ", (board->boardState[i][j] == 0 ? ' ' : board->boardState[i][j] + '0'));
        }
        if (((i + 1) % SQUARE_SIZE) != 0 || i == NUM_ROWS - 1) printf("%c\n", board->boardState[i][lastColumnIndex] == 0 ? ' ' : board->boardState[i][lastColumnIndex] + '0');
        else printf("%c\n=======================\n", board->boardState[i][lastColumnIndex] == 0 ? ' ' : board->boardState[i][lastColumnIndex] + '0');
    }
    printf("\n");
}