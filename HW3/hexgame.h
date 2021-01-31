#ifndef HEXGAME_H
#define HEXGAME_H

/*
*		HEXGAME WITH OBJECT ORIENTED TECHNIQUES.
*		BY SULEYMAN GOLBOL
*		1801042656
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

class Hex{
	private:
		class Cell{									
			private:
				sides status;
				int x;
				int y;
			public:
				Cell(char status2){
					status = (sides)status2;
				}
				Cell(int x2, int y2){
					x=x2;
					y=y2;
					status = (sides)('.');
				}
				Cell(int x2, int y2, char status2){
					x = x2;
					y = y2;
					status = (sides)status2;
				}
				inline char getStatus(){		//Returns cell's status as char like x o .
					return  static_cast<char>(status);
				}
				inline void setStatus(char status2){ //Changes cell's status as char like x o .
					status = (sides)status2;
				}
		};	//End of nested class definition.
		std::vector< std::vector<Cell> > hexCells;
		//2D Vector for holding hex cells.
		int boardSize = 0;
		int is_done2  = 0;
		int how_many_player = 1;	
		char turn = 'x';
		static int runningGames;

	public:
		Hex();	
		//Creating game for the first time.	
		Hex(int is_done); //If is_done 0 -> firstTime, 1 ->open again , if 2 -> game is over.
		//Opening game again so not to initialize boardsize etc again.
		Hex(int is_done, const std::string &loadfile);
		//Opening game from file.
		void playGame(int is_done);	
		//Starting game and playing.
		void play();
		// Play of the computer.
		bool play(std::string coord);
		// Play of the user.
		void createEmptyTable(int size, char side);
		// Creating empty table for first time ord resizing cells to bigger.
		void resizeHexCells(int oldboardSize);
		// Resize hexcells to smaller.
		void printBoard();
		// Printing board to the screen.
		int current_length()  const;
		// Length of the board.
		bool CompareGames(Hex game2);
		// Comparing 2 different hex games.
		int check_if_ended();
		// Controlling the check_full function if game is done or not.
		int Ask();
		// Asks how many player game.
		int size_of_string(std::string str);
		// Returns size of string.
		int commandInput(std::string &coord, std::string filename);
		// Checks if user entered LOAD, SAVE, RBACK.
		int check_full(int x, int y, int visitedplaces[][26], char check);
		// Recursively checking if x or o has won the game.
		void makeLettersCapital(char check, int visitedplaces[26][26]);
		// At the end of the game make letters uppercase.
		bool is_valid_move(int x, int y, char letter);
		//Checking if next move is valid or not.
		void load_from_file(const std::string &filename);
		// Current infos in file transfer to the game.
		void save_to_the_file(const std::string &filename);
		// Current infos transfer to the file called filename.
		bool input_wrong(std::string coord);
		// Just checks if coordinate input is true or false.
		char change_turn(char turn);
		//Changing the turn of x and o.
		int  getIsDone()	const;
		// Showing is_done values.
		void setIsDone(int is_done);
		// Changing is_done values.
		static int markedCells(Hex game1);
		// Returns how many cells are not empty.
		static int markedCells(std::vector<Hex> hexgames, int k);
		// Returns how many cells are not empty in all. games
		static int getRunningGames();
		// Returns total running games.
};

int show_runningGames(int &i, int &j, bool flag, std::vector<Hex> hexgames);
// Helper to my main function just to prevent code repeating.

#endif