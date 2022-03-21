#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define ROW 6
#define COL 6


struct Grid {
    char data;
    struct Grid *up;
    struct Grid *down;
    struct Grid *left;
    struct Grid *right;
    struct Grid *upLeft;
    struct Grid *upRight;
    struct Grid *downLeft;
    struct Grid *downRight;
};

//function to initialize the board, return the pointer to the Grid (0,0)
struct Grid* newBoard();

//function to assign starting point of AI given the pointer to the board, return pointer to the Grid
struct Grid* initAI(struct Grid *board);

//function to assign starting point of Player given the pointer to the board, return pointer to the Grid
struct Grid* initPlayer(struct Grid *board);

//function to find and execute a move for the AI, finding the maximal point for that turn. 
//Param: a reference to the current position of the AI.
//Return the data of the destination point
char AIMove(struct Grid **position);

//function to execute a player move with user command 
//Param: a reference to the current position of the player
//Return the data of the destination point
char playerMove(char* command, struct Grid **position);

//function to print the board.
//params: pointer to the board
void printBoard(struct Grid* board);

//function to check for available moves
//params: pointer to a point in the board
int hasMove(struct Grid *position);

//function to compute the sum from a list given in string with '+' separate the number
int sumOf(char* list);

int main(int argc, char *argv[]) {
    struct Grid* board = newBoard();

    char *playerPoints, *comPoints;
    char chr= '1';

    playerPoints = (char*)malloc(sizeof(char) * 100);
    strncat(playerPoints, &chr, 1);
    comPoints = (char*)malloc(sizeof(char) * 100);
    strncat(comPoints, &chr, 1);

    struct Grid *P, *AI;
	P = initPlayer(board);
    AI = initAI(board);

    for (;;) {

        printBoard(board);

        int hasMoveP, hasMoveAI;
        hasMoveP = hasMove(P);
        hasMoveAI = hasMove(AI);

        if (hasMoveP < 0 && hasMoveAI < 0) {
            int pPoints = sumOf(playerPoints);
            int AIPoints = sumOf(comPoints);

            printf("Player's points: %s = %i\n", playerPoints, pPoints);
            printf("AI's points: %s = %i\n", comPoints, AIPoints);

            if (pPoints > AIPoints) {
                printf("Player wins!\n");
                break;
            } else if (pPoints == AIPoints) {
                printf("It's a draw.\n");
                break;
            } else {
                printf("AI wins!\n");
                break;
            }
        }

        if (hasMoveP > 0) {
            char *command = NULL;
            size_t sz = 0;
            int characters;

            printf("Your move: ");
            characters = getline(&command, &sz, stdin);

            char playerP = playerMove(command, &P);

            if (playerP != '0') {
                strcat(playerPoints, "+");
                strncat(playerPoints, &playerP, 1);
            } else {
                printf("Invalid Move. Please choose another!\n");
                continue;
            }
        } else {
            printf("Player has no more moves.\n");
        }

        if (hasMoveAI > 0) {
            char comp = AIMove(&AI);
            strcat(comPoints, "+");
            strncat(comPoints, &comp, 1);

        } else {
            printf("AI has no more moves.\n");
        }
    }

    free(board);
    free(playerPoints);
    free(comPoints);

    exit(0);
}

struct Grid* newBoard() {
    struct Grid* board = (struct Grid*)malloc(sizeof(struct Grid) * ROW*COL);
    struct Grid *cur;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cur = board + COL*i + j;

            if (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1) { 
                cur->data = '1';
            } else if (i == 1 || i == ROW - 2 || j == 1 || j == COL - 2) {
                cur->data = '2';
            } else {
                cur->data = '3';
            }

            int l = j - 1, r = j + 1;
            int u = i - 1, d = i + 1;

            if (l < 0) {
                cur->left = NULL;
            } else {
                cur->left = board + COL*i + l;
            }
            if (r >= COL) {
                cur->right = NULL;
            } else {
                cur->right = board + COL*i + r;
            }
            if (u < 0) {
                cur->up = NULL;
            } else {
                cur->up = board + COL*u + j;
            }
            if (d >= ROW) {
                cur->down = NULL;
            } else {
                cur->down = board + COL*d + j;
            }
            if (l < 0 || u < 0) {
                cur->upLeft = NULL;
            } else {
                cur->upLeft = board + COL*u + l;
            }
            if (r >= COL || u < 0) {
                cur->upRight = NULL;
            } else {
                cur->upRight = board + COL*u + r;
            }
            if (l < 0 || d >= ROW) {
                cur->downLeft = NULL;
            } else {
                cur->downLeft = board + COL*d + l;
            }
            if (r >= COL || d >= ROW) {
                cur->downRight = NULL;
            } else {
                cur->downRight = board + COL*d + r;
            }
        }
    }
    return board;
}

struct Grid* initAI(struct Grid *board) {
    int i, j;
    struct Grid* cur;
    srand(time(0));
    for (;;) {
        i = rand() % 6;
        j = rand() % 6;
        cur = board + i * COL + j;
        if (cur->data == '1') {
            cur->data = 'A';
            break;
        }
    }
    return cur;
}

struct Grid* initPlayer(struct Grid *board) {
    int i, j;
    struct Grid* cur;
    srand(time(0));
    for (;;) {
        i = rand() % 6;
        j = rand() % 6;
        cur = board + i * COL + j;
        if (cur->data == '1') {
            cur->data = 'P';
            break;
        }
    }
    return cur;
}

char AIMove(struct Grid **position) {
    char max = '0';
    struct Grid* des = *position;
    struct Grid* cur;
    for (int i = 0; i < 8; i++) {
        cur = *position;

        for (;;) {
            switch(i) {
                case 0:
                    cur = cur->up;
                    break;
                case 1:
                    cur = cur->upRight;
                    break;
                case 2:
                    cur = cur->right;
                    break;
                case 3:
                    cur = cur->downRight;
                    break;
                case 4:
                    cur = cur->down;
                    break;
                case 5:
                    cur = cur->downLeft;
                    break;
                case 6:
                    cur = cur->left;
                    break;
                case 7:
                    cur = cur->upLeft;
                    break;
                default:
                    break;
            }

            if (cur == NULL || cur->data == '.' || cur->data == 'P') {
                break;
            } else if (cur->data > max) {
                max = cur->data;
                des = cur;
            }
        }
    }

    char point = des->data;
    des->data = 'A';
    (*position)->data = '.';
    *position = des;
    return point;
}

char playerMove(char* command, struct Grid **position) {
    char* dir = strtok(command, " ");
    int step = atoi(strtok(NULL, " "));
    struct Grid* cur = *position;

    for (int k = 0; k < step; k++) {
        if (strcasecmp(dir, "LEFT") == 0) {
            cur = cur->left;
        }
        else if (strcasecmp(dir, "RIGHT") == 0) {
            cur = cur->right;
        }
        else if (strcasecmp(dir, "UP") == 0) {
            cur = cur->up;
        }
        else if (strcasecmp(dir, "DOWN") == 0) {
            cur = cur->down;
        }
        else if (strcasecmp(dir, "UPLEFT") == 0) {
            cur = cur->upLeft;
        }
        else if (strcasecmp(dir, "UPRIGHT") == 0) {
            cur = cur->upRight;
        }
        else if (strcasecmp(dir, "DOWNLEFT") == 0) {
            cur = cur->downLeft;
        }
        else if (strcasecmp(dir,"DOWNRIGHT") == 0) {
            cur = cur->downRight;
        } else {
            return '0';
        }
        
        if (cur == NULL || cur->data == '.' || cur->data == 'A') {
            return '0';
        }
    }

    char result = cur->data;
    cur->data = 'P';
    (*position)->data = '.';
    *position = cur;
    return result;
}

void printBoard(struct Grid* board) {
    printf("\n\n");
    printf("  %i %i %i %i %i %i \n", 1, 2, 3, 4, 5, 6);
    for (int i = 0; i < ROW; i++) {
        printf("%i ", i + 1);
        for (int j = 0; j < COL; j++) {
           struct Grid* cur = board + COL*i + j;
            printf("%c ", cur->data);
        }
        printf("\n");
    }
    return;
}

int hasMove(struct Grid *position) {
    struct Grid* cur;
    for (int i = 0; i < 8; i++) {
        cur = position;
        switch(i) {
            case 0:
                cur = cur->up;
                break;
            case 1:
                cur = cur->upRight;
                break;
            case 2:
                cur = cur->right;
                break;
            case 3:
                cur = cur->downRight;
                break;
            case 4:
                cur = cur->down;
                break;
            case 5:
                cur = cur->downLeft;
                break;
            case 6:
                cur = cur->left;
                break;
            case 7:
                cur = cur->upLeft;
                break;
            default:
                break;
        }

        if (cur != NULL && cur->data != '.' && cur->data != 'P' && cur->data != 'A') {
            return 1;
        }
    } 

    return -1;
}

int sumOf(char* list) {
    int sum = 0;
    for (int i = 0; i < strlen(list); i++) {
        char num = list[i];
        if (num != '+') {
            sum += atoi(&num);
        }
    }
    return sum;
}