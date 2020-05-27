// A C++ Program to play tic-tac-toe
#include<bits/stdc++.h>
using namespace std;

#define COMPUTER 1
#define HUMAN 2

#define SIDE 3 // Length of the board

#define COMPUTERMOVE 'O' // Computer will move with 'O'
#define HUMANMOVE 'X'  // and human with 'X'

struct Move {
    int row, col;
};

// A function to show the instructions 

void showInstructions() {
    printf("\t\t\t  Tic-Tac-Toe\n\n");
    printf("Choose a cell numbered from 1 to 9 as below and play\n\n");
    printf("\t\t\t  ROW=0,COL=0 | ROW=0,COL=1  | ROW=0,COL=2 \n");
    printf("\t\t\t-------------------------------------------\n");
    printf("\t\t\t  ROW=1,COL=0 | ROW=1,COL=1  | ROW=1,COL=2  \n");
    printf("\t\t\t-------------------------------------------\n");
    printf("\t\t\t  ROW=2,COL=0 | ROW=2,COL=1  | ROW=2,COL=2  \n\n");
    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
    return;
}

// A function to show the current board status

void showBoard(char board[][SIDE]) {
    printf("\n\n");
    printf("\t\t\t  %c | %c  | %c  \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t  %c | %c  | %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t  %c | %c  | %c  \n\n", board[2][0], board[2][1], board[2][2]);
    printf("\n\n");
}


// A function that returns true if any of the row 
// is crossed with the same player's move 

bool rowCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return (true);
    }
    return (false);
}


// A function that returns true if any of the diagonal is crossed with the same player's move 

bool diagonalCrossed(char board[][SIDE]) {
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return (true);

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return (true);

    return (false);
}


// A function that returns true if any of the column is crossed with the same player's move 

bool columnCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return (true);
    }
    return (false);
}


// A function to initialise the game  

void initialise(char board[][SIDE], int moves[]) {
    srand(time(NULL));
    // Fill the moves with numbers 
    for (int i = 0; i < SIDE * SIDE; i++)
        moves[i] = i;
    // randomise the moves 
    random_shuffle(moves, moves + SIDE * SIDE);

    return;
}


// A function that verify if there are no moves left to play. 

bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

// A function to declare the winner of the game for plays vs computer

void declareWinner(int whoseTurn) {
    if (whoseTurn == COMPUTER)
        printf("COMPUTER has won\n");
    else
        printf("HUMAN has won\n");
    return;
}


// A function to declare the winner of the game for two local players

void declareWinnerTwo(int whoseTurn) {
    if (whoseTurn == COMPUTER)
        printf("PLAYER 1 has won\n");
    else
        printf("PLAYER 2 has won\n");
    return;
}


// A function that returns true if the game is over else it returns a false 

bool gameOver(char board[][SIDE]) {
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

//A function that return score based on the evaluation of the board

int evaluate(char board[3][3]) {
    // Checking for Rows for X or O victory. 
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == COMPUTERMOVE)
                return +10;
            else if (board[row][0] == HUMANMOVE)
                return -10;
        }
    }

    // Checking for Columns for X or O victory. 
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == COMPUTERMOVE)
                return +10;

            else if (board[0][col] == HUMANMOVE)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory. 
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTERMOVE)
            return +10;
        else if (board[0][0] == HUMANMOVE)
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTERMOVE)
            return +10;
        else if (board[0][2] == HUMANMOVE)
            return -10;
    }

    // Else if none of them have won then return 0 
    return 0;
}

// A function that considers all the possible ways the game can go and returns the value of the board 

int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);

    // If Maximizer has won the game return his score 
    if (score == 10)
        return score;

    // If Minimizer has won the game return his score 
    if (score == -10)
        return score;

    // If there are no more moves and no winner then it is a tie 
    if (isMovesLeft(board) == false)
        return 0;

    // If this maximizer's move 
    if (isMax) {
        int best = -1000;

        // Traverse all cells 
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty 
                if (board[i][j] == ' ') {
                    // Make the move 
                    board[i][j] = COMPUTERMOVE;

                    // Call minimax recursively and choose the maximum value 
                    best = max(best, minimax(board, depth + 1, !isMax));

                    // Undo the move 
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }        // If this minimizer's move 
    else {
        int best = 1000;

        // Traverse all cells 
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty 
                if (board[i][j] == ' ') {
                    // Make the move 
                    board[i][j] = HUMANMOVE;

                    // Call minimax recursively and choose the minimum value 
                    best = min(best, minimax(board, depth + 1, !isMax));
                    // Undo the move 
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}


// A function to  return the best possible move for the player 

Move findBestMove(char board[3][3]) {
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    //evaluate minimax function for all empty cells and return the cell with optimal value. 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if cell is empty 
            if (board[i][j] == ' ') {
                // Make the move 
                board[i][j] = COMPUTERMOVE;

                // compute evaluation function for this move. 
                int moveVal = minimax(board, 0, false);

                // Reset the move 
                board[i][j] = ' ';

                // If the value of the move is more than the best value, then return best 
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    printf("The value of the best Move is : %d\n\n",
            bestVal);

    return bestMove;
}

// A function to play Tic-Tac-Toe easy

void playTicTacToe_easy(int whoseTurn, char board[SIDE][SIDE]) {
    int moves[SIDE * SIDE];
    // Initialise the game 
    initialise(board, moves);
    int moveIndex = 0, x, y;
    // Keep playing till the game is over or it is a draw 
    while (gameOver(board) == false && moveIndex != SIDE * SIDE) {
        if (whoseTurn == COMPUTER) {
            x = moves[moveIndex] / SIDE;
            y = moves[moveIndex] % SIDE;
            while (board[x][y] != ' ') {
                moveIndex++;
                x = moves[moveIndex] / SIDE;
                y = moves[moveIndex] % SIDE;
            }
            board[x][y] = COMPUTERMOVE;
            printf("COMPUTER has put a %c in ROW %d COL %d\n", COMPUTERMOVE, x, y);
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        } else if (whoseTurn == HUMAN) {
            do {
                printf("ROW=");
                scanf("%d", &x);
                printf("COLUMN=");
                scanf("%d", &y);
            } while (board[x][y] != ' ');
            board[x][y] = HUMANMOVE;
            printf("HUMAN has put a %c in ROW %d COL %d\n", HUMANMOVE, x, y);
            showBoard(board);
            whoseTurn = COMPUTER;
        }
    }
    // If the game has drawn 
    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
        printf("It's a draw\n");
    else {
        // Toggling the user to declare the actual winner 
        if (whoseTurn == COMPUTER)
            whoseTurn = HUMAN;
        else if (whoseTurn == HUMAN)
            whoseTurn = COMPUTER;
        // Declare the winner 
        declareWinner(whoseTurn);
    }
    return;
}

// A function to play Tic-Tac-Toe with two players

void playTicTacToe_Two(int whoseTurn, char board[SIDE][SIDE]) {
    int x, y;
    // Keep playing till the game is over or it is a draw 
    while (gameOver(board) == false && isMovesLeft(board) == true) {
        if (whoseTurn == COMPUTER) {
            do {
                printf("ROW=");
                scanf("%d", &x);
                printf("COLUMN=");
                scanf("%d", &y);
            } while (board[x][y] != ' ');
            board[x][y] = COMPUTERMOVE;
            printf("PLAYER 1 has put a %c in ROW %d COL %d\n", COMPUTERMOVE, x, y);
            showBoard(board);
            whoseTurn = HUMAN;
        } else if (whoseTurn == HUMAN) {
            do {
                printf("ROW=");
                scanf("%d", &x);
                printf("COLUMN=");
                scanf("%d", &y);
            } while (board[x][y] != ' ');
            board[x][y] = HUMANMOVE;
            printf("PLAYER 2 has put a %c in ROW %d COL %d\n", HUMANMOVE, x, y);
            showBoard(board);
            whoseTurn = COMPUTER;
        }
    }

    // If the game has drawn 
    if (gameOver(board) == false)
        printf("It's a draw\n");
    else {
        // Toggling the user to declare the actual 
        // winner 
        if (whoseTurn == COMPUTER)
            whoseTurn = HUMAN;
        else if (whoseTurn == HUMAN)
            whoseTurn = COMPUTER;
        // Declare the winner 
        declareWinnerTwo(whoseTurn);
    }
    return;
}

// A function to play Tic-Tac-Toe hard

void playTicTacToeminmax(int whoseTurn, char board[SIDE][SIDE]) {
    int x, y;
    // Keep playing till the game is over or it is a draw 
    while (gameOver(board) == false && isMovesLeft(board) == true) {
        if (whoseTurn == COMPUTER) {
            Move bestMove = findBestMove(board);
            x = bestMove.row;
            y = bestMove.col;
            board[x][y] = COMPUTERMOVE;
            printf("COMPUTER has put a %c in ROW %d COL %d\n", COMPUTERMOVE, x, y);
            showBoard(board);
            whoseTurn = HUMAN;
        } else if (whoseTurn == HUMAN) {
            do {
                printf("ROW=");
                scanf("%d", &x);
                printf("COLUMN=");
                scanf("%d", &y);
            } while (board[x][y] != ' ');
            board[x][y] = HUMANMOVE;
            printf("HUMAN  has put a %c in ROW %d COL %d\n", HUMANMOVE, x, y);
            showBoard(board);
            whoseTurn = COMPUTER;
        }
    }

    // If the game has drawn 
    if (gameOver(board) == false)
        printf("It's a draw\n");
    else {
        // Toggling the user to declare the actual 
        // winner 
        if (whoseTurn == COMPUTER)
            whoseTurn = HUMAN;
        else if (whoseTurn == HUMAN)
            whoseTurn = COMPUTER;

        // Declare the winner 
        declareWinner(whoseTurn);
    }
    return;
}

int main() {
    // A 3*3 Tic-Tac-Toe board for playing  
    char board[SIDE][SIDE];
    int choice, choice_computer, n;

    // Initially the board is empty 
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++)
            board[i][j] = ' ';
    }
    printf("WELCOME TO THE TIC-TAC-TOE GAME\n ARE YOU READY !\n SO LET'S START\n");
    printf("if you want to play with a local player press 1 \nif you want to play with the computer press 2\n");
    scanf("%d", &choice);
    if (choice == 2) {
        printf("EASY_MODE :press 1 \t\t HARD_MODE:press 2\n");
        scanf("%d", &choice_computer);
        if (choice_computer == 1) {
            // Show the instructions before playing 
            showInstructions();
            printf("press 2 to play first else press 1 ");
            scanf("%d", &n);
            playTicTacToe_easy(n, board);
        } else {
            // Show the instructions before playing 
            showInstructions();
            printf("press 2 to play first else press 1 ");
            scanf("%d", &n);
            playTicTacToeminmax(n, board);

        }

    } else {
        // Show the instructions before playing 
        showInstructions();
        playTicTacToe_Two(1, board);

    }
    return 0;
}

