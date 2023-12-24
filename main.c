
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>   
#define nbofboats 5
#define board_size 10

enum {
    WATER,
    WATER_SHOT,
    BOAT,
    WRECK,
}Cell_type;
/*ypedef struct{
    int bow[2]; //the front of the boat
    int stern[2];// the back of the boat
}Boat_coordinates;*/

typedef struct {
    int size;
    char orientation; // 'H' for horizontal, 'V' for vertical
    int row;
    int column;
}Boat;

typedef struct {
    int **cell;

}Board;

typedef struct{
	Board *player_board;
	Board *computer_board;
	Boat *player_boats;
	Boat *computer_boats;
}Game;

void initializeBoard(Board *board) {
    board->cell = (int **)malloc( board_size * sizeof(int *));
    if(board->cell == NULL){
        printf("Problem creating board!!!!\n");
        exit(2);
    }
    for (int i = 0; i < board_size; i++) {
        board->cell[i] = (int *)malloc(board_size  * sizeof(int));
        if(board->cell[i] == NULL){
            printf("Problem creating board!!!!\n");
            exit(2);
            for (int j = 0; j < board_size; j++) {
                board->cell[i][j] = WATER;
            }
        }
    }
}

void show_board(Board *board){
	printf("   0 1 2 3 4 5 6 7 8 9  \n\n");
	for(int i=0; i < board_size; i++){
		printf("%d  ",i);
		for(int j=0; j < board_size; j++){
			printf("%d ",board->cell[i][j]);
		}
		printf("\n");
	}

	printf("\n%d : Water\n%d : Missed shot\n%d : Boat Down\n%d : Boat Hit\n",WATER,WATER_SHOT,WRECK,BOAT);


}
Boat new_boat(int row, int column, int size){ // this function creates a new boat using ...
     Boat boat;
	 printf("hello world!!!");
	 return boat;
}



int main(){
	
	Game *game= malloc(sizeof(Game)); // Allocate memory for the Game structure
	game->player_board=malloc(sizeof(Board));
	game->computer_board=malloc(sizeof(Board));
    if (game == NULL || game->player_board == NULL || game->computer_board == NULL) {
        printf("Problem creating board!\n");
        exit(2);
    }
	initializeBoard(game->player_board);
	initializeBoard(game->computer_board);
	show_board(game->player_board);
	show_board(game->computer_board);
	// Free memory for each row and the array of pointers
	for (int i = 0; i < board_size; i++) {
		free(game->player_board->cell[i]);
	}
	// Free the array of pointers
	free(game->player_board->cell);
	// Free the Board structure
	free(game->player_board);
	return 0;
}
