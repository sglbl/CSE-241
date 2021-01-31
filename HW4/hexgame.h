#ifndef HEXGAME_H
#define HEXGAME_H

/*
*		HEXGAME WITH OBJECT ORIENTED TECHNIQUES.
*		BY SULEYMAN GOLBOL
*		1801042656
*/
namespace hexname{
	
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
	public:
		class Cell{									
			private:
				sides status;
				int x;
				int y;
			public:
				Cell();
				Cell(char status2);
				Cell(int x2, int y2);
				Cell(int x2, int y2, char status2);
				Cell(const Cell &c);
				//Cell constructors
				const Cell &operator=(const Cell &other);
				//Assignment operator overload.
				friend std::ostream& operator<<(std::ostream& os, const Cell& c);
				// Operator overloading for >> operator.
				friend bool operator==(const Cell& c1, const Cell& c2);
				// Operator overloading for == operator.
				inline char getStatus(){ return  static_cast<char>(status); }
				//Returns cell's status as char like x o .
				inline void setStatus(char status2){ status = static_cast<sides>(status2); }
				//Changes cell's status as char like x o .
				inline void setX(int x2){ x = x2; }
				//Changes cell's x value.
				inline void setY(int y2){ y = y2; }
				//Changes cell's y value.
				inline int getX(){ return x; }
				//Gets cell's x value.
				inline int getY(){ return y; }
				//Gets cell's y value.
		};	//End of nested class definition.

		/**************		 BIG THREE	  ***************/
			Hex(const Hex &HObject);					//
			//Copy constructor							//
			const Hex& operator=(const Hex &other);		//
			//Assignment Operator= overloading   		//
			~Hex();										//
			//Destructor								//
		/************************************************/
		explicit Hex();	
		//Creating game for the first time.	
		Hex(int is_done); //If is_done 0 -> firstTime, 1 ->open again , if 2 -> game is over.
		//Opening game again so not to initialize boardsize etc again.
		Hex(int &is_done, const std::string &loadfile);
		//Opening game from file.
		bool playGame(int is_done);	
		//Starting game and playing.
		Cell play();
		// Play of the computer.
		bool play(Cell &c);
		// Play of the user.
		void createEmptyTable(int size);
		// Creating empty table for first time ord resizing cells to bigger.
		void deleteTable(int size);
		//Deletes table
		void resizeHexCells(int oldboardSize);
		// Resize hexcells to smaller.
		int current_length()  const;
		// Length of the board.
		int check_if_ended(bool showScore);
		// Controlling the check_full function if game is done or not.
		int size_of_string(const std::string &str);
		// Returns size of string.
		int getScore();		//Not const because it changes some values because of reference.
		// Returns the score for the user im 1 player game.
		int commandInput(std::string &coord, std::string filename);
		// Checks if user entered LOAD, SAVE, RBACK.
		int check_full(int x, int y, int visitedplaces[][26], char check, int &score);
		// Recursively checking if x or o has won the game.
		void makeLettersCapital(char check, int visitedplaces[26][26]);
		// At the end of the game make letters uppercase.
		bool is_valid_move(int x, int y, char letter) const;
		//Checking if next move is valid or not.
		bool input_wrong(std::string coord);
		// Just checks if coordinate input is true or false.
		char change_turn(char turn);
		//Changing the turn of x and o.
		int  getIsDone()	const;
		// Showing is_done values.
		void setIsDone(const int& is_done);
		// Changing is_done values.
		void setBoardSize(const int& bs);
		// Sets boardsize
		void setOldMove(const Cell& c);
		// Saves the last move to oldMoves.
		Hex operator--( );
		// Prefix version of decrement  ( for undo last move in 1 player game )
		Hex operator--(int);
		// Postfix version of decrement ( for undo last move in 2 player game )
		friend bool operator==(Hex& game1, Hex& game2);
		// Operator overloading for == operator.
		friend std::ofstream& operator<<(std::ofstream& file, Hex &game);
		// Operator overloading for << operator when writing to the file.
		friend std::ifstream& operator>>(std::ifstream& file, Hex &game);
		// Operator overloading for >> operator when reading the file.
		friend std::ostream& operator<<(std::ostream& os, const Hex& game);
		// Operator overloading for >> operator. (Printing board)
		friend std::istream& operator>>(std::istream& is, Hex& game);
		// Operator overloading for >> operator.  (Getting input at the beginning)
		static int markedCells(Hex &game1);
		// Returns how many cells are not empty.
		static int getRunningGames();
		// Returns total running games.
		static void increaseRunningGames();
		// Increases the total running games.
	private:
		Cell **hexCells = nullptr;
		//Pointer for holding hex cells.
		Cell oldMoves[26*26];
		//Holding old moves for undo.
		int boardSize = 0;
		//Size of board
		int is_done2  = 0;	
		//In beginning 0 for normal games, 1 for games loaded from file.
		int how_many_player = 1;	
		//1 player or 2 player game.
		char turn = 'x';
		//Whose turn.
		static int runningGames;
};

}	//End of namespace.
#endif
