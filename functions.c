#include "header.h"




void initializeBoard(GameBoard *board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board->board[i][j] = WATER;
        }
    }
}

void show_boards(GameBoard *playerBoard, GameBoard *computerBoard) {
    printf("~~ The Enemy's Board ~~~\n");

    printf("   ");
    for (int i = 0; i < BOARD_SIZE; ++i) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; ++i) {
        printf("%d ", i);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (computerBoard->board[i][j] == WATER_SHOT) {
                printf("%d ", WATER_SHOT);
            } else if (computerBoard->board[i][j] == WRECK) {
                printf("%d ", WRECK);
            } else {
                printf("%d ", WATER);
            }
        }
        printf("\n");
    }

    printf("~~~~~ Your Board ~~~~~\n");
    printf("   ");
    for (int i = 0; i < BOARD_SIZE; ++i) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; ++i) {
        printf("%d ", i);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (playerBoard->board[i][j] == BOAT) {
                printf("%d ", BOAT);
            } else if (playerBoard->board[i][j] == WATER_SHOT) {
                printf("%d ", WATER_SHOT);
            } else{
                printf("%d ", playerBoard->board[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n");
    printf("\n%d : Water\n%d : Boat\n%d : Boat Hit\n%d : Missed Shot\n",WATER,WATER_SHOT,WRECK,BOAT);
}

int isValidPlacement(GameBoard *board, Boat *boat) {
    int i, j;

    if (boat->start.row == boat->end.row) {
        // Horizontal placement
        for (j = boat->start.col; j <= boat->end.col; ++j) {
            if (board->board[boat->start.row][j] != WATER) {
                return 0; // Invalid placement
            }
        }
    } else if (boat->start.col == boat->end.col) {
        // Vertical placement
        for (i = boat->start.row; i <= boat->end.row; ++i) {
            if (board->board[i][boat->start.col] != WATER) {
                return 0; // Invalid placement
            }
        }
    } else {
        return 0; // Diagonal placement is not allowed
    }

    return 1; // Valid placement
}

void placeBoat(GameBoard *board, Boat *boat) {
    if (boat->start.row == boat->end.row) {
        // Horizontal placement
        for (int j = boat->start.col; j <= boat->end.col; ++j) {
            board->board[boat->start.row][j] = BOAT;
        }
    } else if (boat->start.col == boat->end.col) {
        // Vertical placement
        for (int i = boat->start.row; i <= boat->end.row; ++i) {
            board->board[i][boat->start.col] = BOAT;
        }
    }
}

void generateRandomBoatPosition(Boat *boat) {
    boat->size = rand() % 3 + 3; // Boat size is between 3 and 5
    boat->start.row = rand() % BOARD_SIZE;
    boat->start.col = rand() % BOARD_SIZE;

    // Randomly choose orientation: 0 for horizontal, 1 for vertical
    int orientation = rand() % 2;

    if (orientation == 0) {
        // Horizontal placement
        boat->end.row = boat->start.row;
        boat->end.col = boat->start.col + boat->size - 1;
    } else {
        // Vertical placement
        boat->end.row = boat->start.row + boat->size - 1;
        boat->end.col = boat->start.col;
    }
}

int isHit(GameBoard *board, Coordinates *target) {
    return board->board[target->row][target->col] == BOAT;
}

void updateBoard(GameBoard *board, Coordinates *target) {
    if (isHit(board, target)) {
        board->board[target->row][target->col] = WRECK;
    } else {
        board->board[target->row][target->col] = WATER_SHOT;
    }
}

int areAllBoatsSunk(GameBoard *board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board->board[i][j] == BOAT) {
                return 0; // At least one boat is still afloat
            }
        }
    }
    return 1; // All boats are sunk
}

void new_boat(GameBoard *board, int size) {
    Boat boat;

    generateRandomBoatPosition(&boat);

    while (!isValidPlacement(board, &boat)) {
        generateRandomBoatPosition(&boat);
    }

    placeBoat(board, &boat);
}

void filling_board(GameBoard *playerBoard, GameBoard *computerBoard) {
    int size;
    for (int i = 0; i < NUM_BOATS; i++) {
        switch (i) {
            case 0:
            case 1:
                size = 5;
                break;
            case 2:
            case 3:
                size = 4;
                break;
            default:
                size = 3;
                break;
        }
        new_boat(playerBoard, size);
        new_boat(computerBoard, size);
    }
}
