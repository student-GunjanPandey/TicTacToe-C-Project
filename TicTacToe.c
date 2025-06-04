#include <stdio.h>

// Global declarations
char game[3][3];
int turnCount = 0;
int scoreX = 0, scoreO = 0;

// Function prototypes
void initializeBoard();
void showBoard();
void makeMove(char symbol);
int checkWinner();
void updateScore(char winner);

int main() {
    char current = 'X';
    char again;

    do {
        initializeBoard();
        turnCount = 0;
        int won = 0;
        current = 'X';

        while (1) {
            showBoard();
            makeMove(current);
            turnCount++;

            if (checkWinner()) {
                showBoard();
                printf("==> Player %c wins this round!\n", current);
                updateScore(current);
                won = 1;
                break;
            } else if (turnCount == 9) {
                showBoard();
                printf("==> Match Draw!\n");
                break;
            }

            // switch players
            current = (current == 'X') ? 'O' : 'X';
        }

        printf("Score => X: %d, O: %d\n", scoreX, scoreO);
        printf("Play again? (y/n): ");
        while (getchar() != '\n'); // clear input buffer
        scanf("%c", &again);

    } while (again == 'y' || again == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}

void initializeBoard() {
    char num = '1';
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            game[r][c] = num++;
        }
    }
}

void showBoard() {
    printf("\n");
    for (int r = 0; r < 3; r++) {
        printf(" %c | %c | %c \n", game[r][0], game[r][1], game[r][2]);
        if (r != 2)
            printf("---|---|---\n");
    }
    printf("\n");
}

void makeMove(char symbol) {
    int pos;
    int row, col;

    while (1) {
        printf("Player %c, enter a position (1-9): ", symbol);
        if (scanf("%d", &pos) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Try a number.\n");
            continue;
        }

        if (pos < 1 || pos > 9) {
            printf("Position out of range. Choose between 1-9.\n");
            continue;
        }

        row = (pos - 1) / 3;
        col = (pos - 1) % 3;

        if (game[row][col] != 'X' && game[row][col] != 'O') {
            game[row][col] = symbol;
            break;
        } else {
            printf("Cell already taken! Try again.\n");
        }
    }
    
}

int checkWinner() {
    // rows and columns
    for (int i = 0; i < 3; i++) {
        if (game[i][0] == game[i][1] && game[i][1] == game[i][2] &&
            (game[i][0] == 'X' || game[i][0] == 'O')) return 1;
        if (game[0][i] == game[1][i] && game[1][i] == game[2][i] &&
            (game[0][i] == 'X' || game[0][i] == 'O')) return 1;
    }

    // diagonals
    if (game[0][0] == game[1][1] && game[1][1] == game[2][2] &&
        (game[0][0] == 'X' || game[0][0] == 'O')) return 1;
    if (game[0][2] == game[1][1] && game[1][1] == game[2][0] &&
        (game[0][2] == 'X' || game[0][2] == 'O')) return 1;

    return 0;
}

void updateScore(char winner) {
    if (winner == 'X')
        scoreX++;
    else if (winner == 'O')
        scoreO++;
}
