#ifndef HEXGAME_H
#define HEXGAME_H

/*
*		HEXGAME WITH FILE OPERATIONS.
*		BY SULEYMAN GOLBOL
*		1801042656
*		
*/
enum sides: 	// C++11 Based Scoped Enum Type. (It doesn't work in older versions like C++03)
		char 	//To make enum's memory 1 byte(like char) and not more.
		{
			x='x',
			o='o',
			dot='.',
			X='X',
			O='O'
		};

int initial();
//Makes initial board info and returns boardsize
int boardsize(int input);
//Define the board size.
int Ask();
//Asks 2 Player Game or 1 Player Game versus Computer.
void startGame_2player(sides board[][12], int boardSize, int time=1, char turn='x');	//Default argument
//2 Player Game Process
void startGame_computer(sides board[][12], int boardSize, int time=1);
//Player vs Computer Game Process
void AI_choice(sides board[][12], int boardSize);
//Random or smart choices of Computer
char change_turn(char turn);
//Changing the turn of x and o
int absval(int a);
//Returns the absolute value of number a.
void printBoard(sides board[][12], int boardSize);
//Printing Board
int check(sides board[][12], int boardSize);
//Controlling the check_full_x and check_full_o function if it's done or not.
int check_full_x(sides board[][12], int boardSize, int x, int y, int visitedplaces[][12]);
//Recursively checking if x has won the game.
int check_full_o(sides board[][12], int boardSize, int x, int y, int visitedplaces[][12]);
//Recursively checking if o has won the game.
bool is_valid_move(sides board[][12], int x, int y, int boardSize, char letter);
//Checking if next move is valid or not.
char make_uppercase(char letter);
//At the end of the game make letters uppercase.
void changing_player_from_file(sides board[][12], int boardSize, int how_many_player, char turn='x');	//Default argument
// If in file, how_many_player is different than the game's, it changes the game style.
void save_to_the_file(sides board[][12], int boardSize, int player, const std::string &filename, char whose_turn='x');	//Default argument
// Current infos transfer to the file called filename.
void load_from_file(sides board[][12], int &boardSize, int &player, const std::string &filename, char &whose_turn);
// Current infos in file transfer to the game.
int size_of_string(std::string str);
// Returns the size of string.
bool input_wrong(std::string coord, int boardSize);
// Just checks if coordinate input is true or false.
#endif