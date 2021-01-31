#ifndef HEXGAME_H
#define HEXGAME_H

int initial();
//Makes initial board info and returns boardsize
int boardsize(int input);
//Define the board size.
int Ask(int boardSize);
//Asks 2 Player Game or 1 Player Game versus Computer.
void startGame_2player(char board[][12], int boardSize);
//2 Player Game Process
void startGame_computer(char board[][12], int boardSize);
//Player vs Computer Game Process
void AI_choice(char board[][12], int boardSize);
//Random or smart choices of Computer
char change_turn(char turn);
//Changing the turn of x and o
void printBoard(char board[][12], int boardSize);
//Printing Board
int check(char board[][12], int boardSize);
//Controlling the check_full_x and check_full_o function if it's done or not.
int check_full_x(char board[][12], int boardSize, int x, int y, int visitedplaces[][12]);
//Recursively checking if x has won the game.
int check_full_o(char board[][12], int boardSize, int x, int y, int visitedplaces[][12]);
//Recursively checking if o has won the game.
bool is_valid_move(char board[][12], int x, int y, int boardSize, char letter);
//Checking if next move is valid or not.
char make_uppercase(char letter);
//At the end of the game make letters uppercase.
#endif