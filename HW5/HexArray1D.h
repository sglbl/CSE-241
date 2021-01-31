#ifndef HEXARRAY1D_H
#define HEXARRAY1D_H

#include "AbstractHex.h"
/*
*		HEXGAME WITH OBJECT ORIENTED TECHNIQUES.
*		BY SULEYMAN GOLBOL
*		1801042656
*/
namespace hexname{

class HexArray1D: public AbstractHex{	//Derived class
		public:
		HexArray1D();
		HexArray1D(int is_done);
		HexArray1D(int &is_done, const std::string &loadfile);
		//Constructors
		~HexArray1D();		//BIG THREE
		//Destructor
		HexArray1D(const HexArray1D &HObject);
		//Copy constructor
		const HexArray1D &operator=(const HexArray1D &other);
		//Assignment operator
		void createEmptyTable(int size) override;
		// Creating empty table.
		void deleteTable();
		//Deletes table
		void reset() override;
		// Resets hexcells.
		void setSize(const int& bs) override;
		//Set size and calls reset()
		bool playGame(int is_done) override;	
		//Starting game and playing.
		Cell play() override;
		// Play of the computer.
		bool play(Cell &c) override;
		// Play of the user.
		int check_full(int x, int y, int visitedplaces[][26], char check, int &score) override;
		// Recursively checking if x or o has won the game.
		int isEnd(int &flag) override;
		// Controlling the check_full function if game is done or not.
		int size_of_string(const std::string &str);
		// Returns size of string.
		int getScore();		//Not const because it changes some values because of reference.
		// Returns the score for the user im 1 player game.
		int commandInput(std::string &coord, std::string filename);
		// Checks if user entered LOAD, SAVE, RBACK.
		void makeLettersCapital(char check, int visitedplaces[26][26]);
		// At the end of the game make letters uppercase.
		bool is_valid_move(int x, int y, char letter);
		//Checking if next move is valid or not.
		bool input_wrong(std::string coord);
		// Just checks if coordinate input is true or false.
		int  getIsDone()	const;
		// Showing is_done values.
		void setOldMove(const Cell& c);
		// Saves the last move to oldMoves.
		int numberOfMoves();
		//Returns number of moves of the board.
		void print();
		// Printing the board.
		void readFromFile(const std::string &filename);
		//For reading the file.
		void writeToFile(const std::string &filename);
		// Printing board
		void getInput();
		//Gets how many player game and board size from the user.
		Cell operator()(int a,int b);
	private:
		Cell* hexCells = nullptr;
		//Pointer for holding hex cells.
		

};




}	//End of namespace.
#endif