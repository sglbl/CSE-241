#include <iostream>
#include <string>
#include <random>
#include "hexgame.h"

using namespace std;

int main(){
	int boardSize;
	int input;
	char board[12][12];

	boardSize = initial();			//Initialize the game and determine the size of board.
	input = Ask(boardSize);		//Determining Computer vs Player  or  2 Player Game.


	for(int i=0; i<boardSize; i++)
		for(int j=0; j<boardSize; j++)
			board[i][j] = '.'; 			//Initialization of board with '.' character.

	if     (input==1)	startGame_computer(board, boardSize);
	else if(input==2)	startGame_2player (board, boardSize);

	return 0;
}