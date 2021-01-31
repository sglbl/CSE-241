#ifndef ABSTRACTHEX_H
#define ABSTRACTHEX_H

/*
*		HEXGAME WITH OBJECT ORIENTED TECHNIQUES.
*		BY SULEYMAN GOLBOL
*		1801042656
*/
namespace hexname{

enum sides: 	// C++11 Based Scoped Enum Type. (It doesn't work in C++03)
		char 	//To make enum's memory 1 byte(like char) and not more.
		{
			x='x',
			o='o',
			dot='.',
			X='X',
			O='O'
		};

class AbstractHex{
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

		AbstractHex(const AbstractHex &HObject);					
		//Copy constructor											
		const AbstractHex& operator=(const AbstractHex &other);		
		//Assignment Operator= overloading   						
		~AbstractHex();												
		//Destructor												
		AbstractHex();
		//This constructor is for creating game for the first time.	
		AbstractHex(int is_done); //If is_done 0 -> firstTime, 1 ->open game again , if 2 -> game is over.
		//Opening game again so not to initialize boardsize etc again.
		AbstractHex(int &is_done, const std::string &loadfile);
		//Opening game from file.
		void setIsDone(const int& is_done);
		// Changing is_done values.
		int size_of_string(const std::string &str) ;
		// Returns size of string.
		int current_length() const;
		// Length of the board.
		char change_turn(char turn);
		//Changing the turn of x and o.
		Cell lastMove();
		//Returns last move, if there isn't, throws an exception.
		virtual Cell play() = 0;
		// Play of the computer.
		virtual bool play(Cell &c) = 0;
		// Play of the user.
		virtual bool playGame(int is_done) = 0; 	
		//Starting game and playing.
		virtual void createEmptyTable(int size) = 0;
		// Creating empty table for first time ord resizing cells to bigger.
		virtual void deleteTable() = 0;
		//Deletes table
		virtual void reset() = 0;
		// Resets hexcells.
		virtual int isEnd(int &flag) = 0;
		// Controlling the check_full function if game is done or not.
		virtual int getScore() = 0;		//Not const because it changes some values because of reference.
		// Returns the score for the user im 1 player game.
		virtual int commandInput(std::string &coord, std::string filename) = 0;
		// Checks if user entered LOAD, SAVE, RBACK.
		virtual int check_full(int x, int y, int visitedplaces[][26], char check, int &score) = 0;
		// Recursively checking if x or o has won the game.
		virtual void makeLettersCapital(char check, int visitedplaces[26][26]) = 0;
		// At the end of the game make letters uppercase.
		virtual bool is_valid_move(int x, int y, char letter) = 0;
		//Checking if next move is valid or not.
		virtual bool input_wrong(std::string coord) = 0;
		// Just checks if coordinate input is true or false.
		virtual int  getIsDone() const = 0;
		// Showing is_done values.
		virtual void setSize(const int& bs) = 0;
		// Sets boardsize
		virtual void setOldMove(const Cell& c) = 0;
		// Saves the last move to oldMoves.
		virtual void print() = 0;
		// Printing the board.
		virtual void readFromFile(const std::string &filename) = 0;
		// Reading the file.
		virtual void writeToFile(const std::string &filename) = 0;
		// Printing board
		virtual void getInput() = 0;
		// Getting input at the beginning.
		virtual Cell operator()(int a,int b) = 0;
		// Operator overloading for () operator for returning cell content.
		virtual int numberOfMoves() = 0;
		//Returns number of moves of the board.
		bool operator==(AbstractHex& game2);
		// Operator overloading for == operator.
		static int markedCells(AbstractHex &game1);
		// Returns how many cells are not empty.
		static int getRunningGames();
		// Returns total running games.
		static void increaseRunningGames();
		// Increases the total running games.
	protected:
		Cell oldMoves[26*26];	//In hw4, it was like that too.(Didn't change)
		//Holding old moves.
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
