#include "header.h"


int main(){
    srand(time(NULL));

    GameBoard playerBoard, computerBoard;
    initializeBoard(&playerBoard);
    initializeBoard(&computerBoard);

    // Generate boats for player and computer
    for (int i = 0; i < NUM_BOATS; ++i) {
        new_boat(&playerBoard, 0);
        new_boat(&computerBoard, 0);
    }

    int playerTurn = 1;

    while (1) {
        show_boards(&playerBoard, &computerBoard);

        Coordinates target;
        if (playerTurn) {
            printf("Enter target coordinates (row col): ");
            scanf("%d %d", &target.row, &target.col);
        } else {
            // Computer's turn: choose random target
            target.row = rand() % BOARD_SIZE;
            target.col = rand() % BOARD_SIZE;
            printf("Computer chose: %d %d\n", target.row, target.col);
        }

        // Check if target is valid
        if (target.row < 0 || target.row >= BOARD_SIZE || target.col < 0 || target.col >= BOARD_SIZE) {
            printf("Invalid target coordinates. Try again.\n");
            continue;
        }

        if (playerTurn) {
            // Player's turn
            if (isHit(&computerBoard, &target)) {
                printf("You hit a boat!\n");
            } else {
                printf("You missed!\n");
            }
            updateBoard(&computerBoard, &target);

            if (areAllBoatsSunk(&computerBoard)) {
                printf("Congratulations! You sunk all the computer's boats.\n");
                break;
            }
        } else {
            // Computer's turn
            if (isHit(&playerBoard, &target)) {
                printf("Computer hit your boat!\n");
            } else {
                printf("Computer missed!\n");
            }
            updateBoard(&playerBoard, &target);

            if (areAllBoatsSunk(&playerBoard)) {
                printf("Oh no! All your boats are sunk.\n");
                break;
            }
        }

        playerTurn = !playerTurn; // Switch turns
    }
     // No explicit freeing needed for static arrays

    return 0;
}
