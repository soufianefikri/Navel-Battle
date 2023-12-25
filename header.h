#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 10
#define NUM_BOATS 3

typedef enum {
    WATER,
    BOAT,
    WRECK,
    WATER_SHOT
} CellType;

typedef struct {
    int row;
    int col;
} Coordinates;

typedef struct {
    Coordinates start;
    Coordinates end;
    int size;
    char orientation;
} Boat;

typedef struct {
    CellType board[BOARD_SIZE][BOARD_SIZE];
} GameBoard;



void initializeBoard(GameBoard *board);
void show_boards(GameBoard *playerBoard, GameBoard *computerBoard);
int isValidPlacement(GameBoard *board, Boat *boat);
void placeBoat(GameBoard *board, Boat *boat);
void generateRandomBoatPosition(Boat *boat);
int isHit(GameBoard *board, Coordinates *target);
void updateBoard(GameBoard *board, Coordinates *target);
int areAllBoatsSunk(GameBoard *board);
void new_boat(GameBoard *board, int size);
void filling_board(GameBoard *playerBoard, GameBoard *computerBoard);
