
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <time.h>   
#define nbofboats 5
#define board_size 10
#define total_boats 24 

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

void show_boards(Game *game){
	printf("~~ The Enemy's Board ~~~\n");

	printf("   0 1 2 3 4 5 6 7 8 9  \n\n");
	for(int i=0; i < board_size; i++){
		printf("%d  ",i);
		for(int j=0; j < board_size; j++){
			printf("%d ",game->computer_board->cell[i][j]);
		}
		
		printf("\n");
	}
	printf("\n~~~~~ Your Board ~~~~~\n");
	printf("   0 1 2 3 4 5 6 7 8 9  \n\n");
	for(int i=0; i < board_size; i++){
		printf("%d  ",i);
		for(int j=0; j < board_size; j++){
			printf("%d ",game->player_board->cell[i][j]);
		}
		
		printf("\n");
	}

	printf("\n%d : Water\n%d : Missed shot\n%d : Boat Down\n%d : Boat Hit\n",WATER,WATER_SHOT,WRECK,BOAT);


}
Boat* new_boat(int size){ // this function creates a new boat using ...
     Boat *boat=malloc(sizeof(Boat));
	 if( boat == NULL){
		printf("Captain we dont have a ship!\n");
		exit(2);
	 }
	 return boat;
}

Board* filling_board(Board *board){
	   srand( time( NULL ) );
	   int maxboats = total_boats;
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
	show_boards(game);
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
