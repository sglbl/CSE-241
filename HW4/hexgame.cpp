#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <fstream>
#include "hexgame.h"

using namespace std;
using namespace hexname;

namespace hexname{
Hex::Hex(){
	turn = 'x';
	int is_done=0;		
	setIsDone(is_done);
	runningGames++;
}

Hex::Hex(int is_done){	
	turn = 'x';
	setIsDone(is_done);
	runningGames++;
}

Hex::Hex(int &is_done, const string &loadfile){	
	turn = 'x'; 	//Temporary values before reading file.
	ifstream file(loadfile);
	if(file.is_open() == false){
		cerr << "Couldn't find or open file.\n\n";
		is_done = -1;
		return;
	}
	cout << "This game object has been created with " << loadfile << " file.\n";
	setIsDone(1);			// Means game is ready, no need for asking boardsize etc.
	runningGames++;
	file >> (*this);		//Loading game from file.
}
/***********	BIG THREE 	************/
Hex::Hex(const Hex &HObject): 		//Copy Constructor
	oldMoves(HObject.oldMoves), boardSize(HObject.boardSize), 
	is_done2(HObject.is_done2), how_many_player(HObject.how_many_player), turn(HObject.turn)  
{
	createEmptyTable(boardSize);	
	for(int i=0; i<26*26; i++)	//Because there are 26 lettters so max 26*26 board.
		oldMoves[i]= HObject.oldMoves[i];
}

const Hex &Hex::operator=(const Hex &other){	//Assignment Operator
	if(this == &other)	return *this;
	else{
		deleteTable(boardSize);
		createEmptyTable(boardSize);
		for(int i=0; i<boardSize; i++)
			hexCells[i] = other.hexCells[i];
		boardSize = other.boardSize;
		is_done2 = other.is_done2;
		how_many_player = other.how_many_player;	
		turn = other.turn;	
		return *this;
	}
}

Hex::~Hex(){
	//Object is destructed.
	deleteTable(boardSize);	//Deleting **hexCells with delete[].
}

void Hex::increaseRunningGames(){
	runningGames++;
}

void Hex::resizeHexCells(int oldboardSize){	//This function is changing size.
	deleteTable(oldboardSize);
		createEmptyTable(boardSize);
}

void Hex::createEmptyTable(int size){		//Creates an empty table.
	for(int i=0; i<26*26; i++){	//Because there are 26 lettters so max 26*26 board.
		oldMoves[i].setStatus('.');
	}

	hexCells = new Cell*[size];
	for(int row=0; row<size; row++)
		hexCells[row] = new Cell[size];
}

void Hex::deleteTable(int size){
	for(int row=0; row<size; row++)
		delete[] hexCells[row];
	delete[] hexCells;

	hexCells=nullptr;
}

bool Hex::playGame(int is_done){
	string coord, filename;
	int command;
	int temp0, temp1;
	setIsDone(is_done);
	if(is_done==0){				//First time opening game.
		cin >> (*this);			//Using overloaded extraction operator for this object.
	}

	// Starting to game.
	if(how_many_player==1)	cout << "It is One Player Game so score is counting.\n"
								 << "Scores are increasing 5 or 10 points in accordance with movement. \n"; 
	cout << turn << " starts..." << endl;	//If turn=x it is x's turn;   if turn=o it is o's turn. 

	while ( check_if_ended(false) == 0 && (getIsDone()==0 || getIsDone()==1) ){
		command=0;
		cout << (*this);		//Using overloaded insertion operator for this object.
		cout << turn << "'s turn!\n";
		cout << "(For ex. F5 or LOAD or SAVE or UNDO or RBACK(to go back to menu) )\n";
		cout << "Please enter a command like above: ";
		getline(cin>>ws, coord);

		command = commandInput(coord, filename);
		if	   (command==1)	continue;		//Save file.
		else if(command==2) continue;		//Load file.
		else if(command==3)	break;			//Return back to main menu.
		else if(command==4) continue;		//Undo the game.

		if(how_many_player==1){				// 1 player game. 
			//USER IS PLAYING			
			temp0 = int (coord[0]) - 65;		//functional type-casting to integer.
			if(current_length() >= 10 && (int)coord[2] != 0)				// For 2 digit numbers.
				temp1 = ((int)coord[1] - 48)*10 + (int)coord[2]-49;
			else														// For 1 digit numbers.
				temp1 = coord[1] - 49;				//char to int.
			hexCells[temp1][temp0].setY(temp1);		//y value of cell.
			hexCells[temp1][temp0].setX(temp0);		//x value of cell.

			if(play(hexCells[temp1][temp0])==false)
				continue;
			//CHEKING IF USER WON
			else if(check_if_ended(true) != 0)	//if true
				break;
			//COMPUTER IS PLAYING
			else
				play();
		}

		else if(how_many_player==2){		// 2 player game.
			//USER IS PLAYING			
			temp0 = int (coord[0]) - 65;		//functional type-casting to integer.
			if(current_length() >= 10 && (int)coord[2] != 0)				// For 2 digit numbers.
				temp1 = ((int)coord[1] - 48)*10 + (int)coord[2]-49;
			else														// For 1 digit numbers.
				temp1 = coord[1] - 49;				//char to int.
			hexCells[temp1][temp0].setY(temp1);		//y value of cell.
			hexCells[temp1][temp0].setX(temp0);		//x value of cell.

			if(play(hexCells[temp1][temp0])==false)	//Playing user.
				continue;
			//CHEKING IF USER WON
			else if(check_if_ended(false) != 0)	//if true
				break;
			//CHANGING PLAYER
			turn = change_turn(turn);
		}
	}

	if(check_if_ended(false) != 0){		//That means it is over.
		runningGames--;
		setIsDone(2); 				// That means game is over not opening again.
		if(check_if_ended(false)==2) cout << "Winner is X\n"; 
		if(check_if_ended(false)==3) cout << "Winner is O\n"; 
		cout << (*this);		//Printing board.
		return false;			//So game ended, we should make pop_back() in main
	}
	return true;	//Return back to main menu becuase no one won yet.
}

Hex::Cell Hex::play(){
	Cell temp;
	random_device myrand;
	int randnum, randnum2;
	boardSize = current_length();
	do{
		mt19937 rand(myrand());
	    uniform_int_distribution<mt19937::result_type> myrandforBoard(1,boardSize);

	    randnum = myrandforBoard(myrand);			// Random number for cell column number. 
	    randnum2 = myrandforBoard(myrand);			// Random number for cell row letter.
	}while(hexCells[randnum-1][randnum2-1].getStatus() != '.' || hexCells[randnum-1][randnum2-1].getStatus() == 'x' );

	cout << "Choice of AI is " << char (randnum2-1 + 'A') << randnum << endl;
	
	hexCells[randnum-1][randnum2-1].setStatus('o');			//Set status to 'o'.
	hexCells[randnum-1][randnum2-1].setY(randnum -1);		//y value of cell.
	hexCells[randnum-1][randnum2-1].setX(randnum2-1);		//x value of cell.
	setOldMove( hexCells[randnum-1][randnum2-1] );			//Put this value for Undo.
	return hexCells[randnum-1][randnum2-1];
}

bool Hex::play(Cell &c){
	if(c.getStatus() == '.')		//If cell is empty.
		c.setStatus(turn);
	else{							//If cell is not empty.
		cerr << "THIS IS NOT AN EMPTY CELL. TRY AGAIN !!!\n";
		return false;
	}

	setOldMove(c);
	cout << "Your choice is " << c << endl; 
	return true;
}

int Hex::commandInput(string &coord, string filename){
	ofstream file;
	ifstream file2;
	bool askflag=false;
	do{
		if(askflag==true){			//If second time wrong ask this.
			cerr << "You entered wrong input. Try again: ";
			getline(cin>>ws, coord);
		}

		if(coord.compare(0,5, "SAVE ",0, 5) == 0){	    //It compares "SAVE " with coord from 0th index to the 5 characters.
			filename = coord.substr(5);   				// The word after "SAVE " is file's name. 
			file.open(filename);
			if(file.is_open() == false)
				{ cerr << "Couldn't open file.\n"; }
			else
				file << (*this) << endl;	 				//Operator overloading for file. (ofstream)
			return 1;
		}
		else if(coord.compare(0,5, "LOAD ",0, 5) == 0){
			filename = coord.substr(5);    				// The word after "FILE " is file's name. 
			file2.open(filename);
			if(file2.is_open() == false)
				{ cerr << "Couldn't open file.\n"; }
			else
				file2 >> (*this);	 				//Operator overloading for file. (ifstream)
			return 2;
		}
		else if(coord.compare(0,5, "RBACK ",0, 5) == 0){	//Returns back to the main function.
			setIsDone(1);
			return 3;
		}
		else if(coord.compare(0,4, "UNDO ",0, 4) == 0){		//Returns back to the main function.
			if(how_many_player==1) {--(*this); --(*this); }	//Operator-- preDecrement //Two times because of user and bot will be undo.
			if(how_many_player==2) (*this)--;				//Operator-- postDecrement
			return 4;
		}
		askflag=true;
	}while( input_wrong(coord) == false );	//Wrong inputs

	return 0;
}

char Hex::change_turn(char turn){
	char flag = 'x';
	if(turn=='x')	flag = 'o';
	return flag;
}

int Hex::check_if_ended(bool showScore){
	int visitedplaces[26][26];
	int score=0;

	if(showScore==true)	cout << "Score is " << getScore() << endl; //Score of user in 1 player game
	for(int m=0; m<boardSize; m++){
		//Checking x if wom
		for(int i=0; i<boardSize; i++)
    		for(int j=0; j<boardSize; j++)
    			visitedplaces[i][j]=0;
		if(hexCells[m][0].getStatus() == 'x' || hexCells[m][0].getStatus() == 'X')
			if( check_full(0, m, visitedplaces, 'x', score) == 2)	return 2;

		//Checking o if won
		for(int i=0; i<boardSize; i++)
    		for(int j=0; j<boardSize; j++)
    			visitedplaces[i][j]=0;

		if(hexCells[0][m].getStatus() == 'o' || hexCells[0][m].getStatus() == 'O')
			if( check_full(m, 0, visitedplaces, 'o', score) == 2)	return 3;
	}

	return 0;
}

int Hex::getScore(){
	//If wins 100
	//Every connected one 5 points
	//In beginning with 0 point.
	//If x doesn't have connection to a cell in first column point is also zero because conting starts with first column. 
	int visitedplaces[26][26];
	int score=0;

	for(int m=0; m<boardSize; m++){
		for(int i=0; i<boardSize; i++)
    		for(int j=0; j<boardSize; j++)
    			visitedplaces[i][j]=0;
		if(hexCells[m][0].getStatus() == 'x' || hexCells[m][0].getStatus() == 'X'){
			if (check_full(0, m, visitedplaces, 'x', score)==2)
				return 100;			
		}
			
	}
	return score;
}

int Hex::check_full(int x, int y, int visitedplaces[][26], char check, int &score){
	/* If visitedplaces[y][x] == 1, then it means it's visited ;  
	   If visitedplaces[x][y] == 0, then it means it's not visited yet.	
	---
		case 1:	x2=x+1;	y2=y-1;		//upright
		case 2:	x2=x+1;	y2=y;		//right
		case 3:	x2=x;	y2=y+1;		//downright
		case 4:	x2=x-1;	y2=y+1;		//downleft
		case 5:	x2=x-1;	y2=y;		//left
		case 6:	x2=x;	y2=y-1;		//upleft			
	*/
	if(check=='x' && x == boardSize-1 ){
		for(int m=0; m<boardSize; m++)
			if (visitedplaces[m][boardSize-1] == 0 && (hexCells[m][boardSize-1].getStatus() == 'x' || hexCells[m][boardSize-1].getStatus() == 'X') )
				{ makeLettersCapital('x', visitedplaces); score=100; return 2; }
	}
	
	if(check=='o' && y == boardSize-1 ){
		for(int m=0; m<boardSize; m++)
			if (visitedplaces[boardSize-1][m] == 0 && (hexCells[boardSize-1][m].getStatus() == 'o' || hexCells[boardSize-1][m].getStatus() == 'O') )
				{ makeLettersCapital('o', visitedplaces); 	return 2; }
	}
			
	else{
			//Recursively finding if it wins with Backtrack technique.
			if( y>=1 && x>=0 )
			if(visitedplaces[y-1][x+1]==0 && is_valid_move(x+1, y-1, check) == true){
				visitedplaces[y][x] = 1;
				score+=5;
				if (check_full(x+1, y-1, visitedplaces, check, score)) return 2;
			}
			if( y>=0 && x>=0 )
			if(visitedplaces[y][x+1]==0 && is_valid_move(x+1, y, check) == true){
				visitedplaces[y][x] = 1;
				score+=5;
				if (check_full(x+1, y, visitedplaces, check, score)) return 2;
			}
			if( y>=0 && x>=0 )
			if(visitedplaces[y+1][x]==0 && is_valid_move(x, y+1, check) == true){
				visitedplaces[y][x] = 1;
				score+=5;
				if (check_full(x, y+1, visitedplaces, check, score)) return 2;
			}
			if( y>=0 && x>=1 )
			if(visitedplaces[y+1][x-1]==0 && is_valid_move(x-1, y+1, check) == true){
				score+=5;
				visitedplaces[y][x] = 1;
				if (check_full(x-1, y+1, visitedplaces, check, score)) return 2;
			}
			if( y>=0 && x>=1 )
			if(visitedplaces[y][x-1]==0 && is_valid_move(x-1, y, check) == true){
				visitedplaces[y][x] = 1;
				score+=5;
				if (check_full(x-1, y, visitedplaces, check, score)) return 2;
			}
			if( y>=1 && x>=0 )
			if(visitedplaces[y-1][x]==0 && is_valid_move(x, y-1, check) == true){
				visitedplaces[y][x] = 1;
				score+=5;
				if (check_full(x, y-1, visitedplaces, check, score)) return 2;
			}			

			visitedplaces[y][x]=0;
		}
	
	return 0;
}

void Hex::makeLettersCapital(char check, int visitedplaces[26][26]){
	if(check=='x')
		for(int y = 0; y < boardSize; ++y)
			for(int x = 0; x < boardSize; ++x)
				if( visitedplaces[y][x]==1 ){
					hexCells[y][x].setStatus('X');
					if(x==boardSize-2 && hexCells[y][boardSize-1].getStatus() == 'x')		
						hexCells[y][boardSize-1].setStatus('X');
					if(y>=1)
						if(x==boardSize-2 && hexCells[y-1][boardSize-1].getStatus() == 'x')
							hexCells[y-1][boardSize-1].setStatus('X');
				}
	if(check=='o')
		for(int y = 0; y < boardSize; ++y)
			for(int x = 0; x < boardSize; ++x)
				if( visitedplaces[y][x]==1 ){
					hexCells[y][x].setStatus('O');
					if(y==boardSize-2 && hexCells[boardSize-1][x].getStatus() == 'o')		
						hexCells[boardSize-1][x].setStatus('O'); 
					if(x>=1)
						if(y==boardSize-2 && hexCells[boardSize-1][x-1].getStatus() =='o')
								hexCells[boardSize-1][x-1].setStatus('O');
				}
}

bool Hex::is_valid_move(int x, int y, char letter) const{
	if( x>=0 && y>=0 && x<boardSize && y<boardSize && (hexCells[y][x].getStatus()== letter
		 || hexCells[y][x].getStatus()== letter-32 ) )	
		return true;

	return false;
}

bool Hex::input_wrong(string coord){
	auto i = size_of_string(coord);	
	if      //Checks the size of entered string to prevent false inputs.
	(
		(int)coord[0]<65 || (int)coord[0]>=(65+boardSize) || (int)coord[1]<49 || (int)coord[1]>(48+boardSize)
		|| i>4 || i<=1 || ( i==3 && (((int)coord[1] - 48)*10 + (int)coord[2]-49) >= boardSize )
	)
		return false;
	return true;
}

int Hex::size_of_string(const string &str){
	auto i=0;
	for(i=0; str[i]; i++); // Body intentionally empty!
	//Size of string is i's new value.
	return i;
}

int Hex::markedCells(Hex &game1){		                 //Static function (static declaration in header)
	int sum=0;
	decltype(sum) bSize = game1.current_length();
	for(int row=0; row<bSize; row++)
		for(int column=0; column<bSize; column++)
			if(game1.hexCells[row][column].getStatus() !='.')  sum++;
	return sum;
}

int Hex::getRunningGames(){
	return runningGames;
}

int Hex::current_length() const{
	return boardSize;
}

int Hex::getIsDone() const{
	return is_done2;
}

void Hex::setIsDone(const int& is_done){
	is_done2 = is_done;
}

void Hex::setBoardSize(const int& bs){
	boardSize = bs;
}

void Hex::setOldMove(const Hex::Cell &c){			//Entering oldMove for undo operation.
	for(int i=0; i<boardSize*boardSize; i++)
		if(oldMoves[i].getStatus() == '.'){
			oldMoves[i] = c;
			break;
		}
}

bool operator==(Hex& game1, Hex& game2){
	if( Hex::markedCells(game1) <  Hex::markedCells(game2) )	return false;
	if( Hex::markedCells(game1) >= Hex::markedCells(game2) )	return true;
	return false;
}

ostream& operator<<(ostream &os, const Hex &game){
	os << "  ";
	for(int i=0; i<game.boardSize; i++)
		os << (char)(i+97) << " ";
	os << endl;

	for(int row=0; row<game.boardSize; row++){
		os << row+1;
		for(int space=0; space<row+1; space++)	os << " ";	//Spaces
		for(int column=0; column<game.boardSize; column++)			
			os << game.hexCells[row][column].getStatus() <<" ";	//Cell status'
		os << endl;
	}
	return os;	//Because of this, we can make for ex. cout<<os<<endl together.
}

istream& operator>>(istream &is, Hex &game){
	int input=6;
	cout << "What board size you want?" << endl;
	cout << "6) 6x6\n7) 7x7\n8) 8x8 \n9) 9x9 \n10) 10x10 \n11) 11x11 \n12) 12x12 and etc. (Till 26 because there are 26 letters.)\n";
	cout << "(For ex. 6): ";
	while ( !(is >> input) || input<6 || input>26 )
		{ cerr << "Try again: "; is.clear(); is.ignore(10000,'\n');	}

	game.setBoardSize(input);
	game.createEmptyTable(game.boardSize);

	cout << "Which one?\n";
	cout << "1) You VS Computer		2) Two Player Game: "; 
	while ( !(is >> game.how_many_player) )
		{ cerr << "Try again: "; is.clear(); is.ignore(10000,'\n');	}
	
	while(game.how_many_player !=1 && game.how_many_player != 2){
		cerr << "You entered wrong input. Try again: ";	
		while ( !(is >> game.how_many_player) )
			{ cerr << "Try again: "; is.clear(); is.ignore(10000,'\n');	}
	}

	return is;
}

ostream& operator<<(ostream& os, const Hex::Cell& c){
	os << static_cast<char> (c.x +65) << c.y+1;
	return os;
}

bool operator==(const Hex::Cell& c1, const Hex::Cell& c2){
	if(c1.x == c2.x && c1.y == c2.y && c1.status == c2.status)
		return true;
	return false;
}

ifstream& operator>>(ifstream& file, Hex &game){	//For reading the file.
	int i,j, oldboardSize;
	string inside;

	oldboardSize = game.boardSize;

	file >> inside;
	if(game.size_of_string(inside) == 1)  		game.boardSize = static_cast<int>(inside[0]) - 48;
	else if(game.size_of_string(inside) ==2)	game.boardSize = (static_cast<int>(inside[0]) - 48)*10 + static_cast<int>(inside[1])-48;

	file >> inside;
	game.how_many_player = static_cast<int>(inside[0]) - 48;

	file >> inside;
	int temp = static_cast<int>(inside[0]);
	game.turn = static_cast<char>(temp);

	game.resizeHexCells(oldboardSize);		//Delete old one.

	for(i=0; i<game.boardSize; i++){
		file >> inside;
		for(j=0; j<game.boardSize; j++){
			game.hexCells[i][j].setStatus(inside[j]);
		}
	}

	for(int i=0; i<game.boardSize*game.boardSize; i++){	//Getting oldMoves from the file.
		file >> inside;
		game.oldMoves[i].setX( (int)inside[0]-65 );
		game.oldMoves[i].setY( (int)(inside[1]-49) );
		game.oldMoves[i].setStatus(inside[2]);
	}
	return file;
}

ofstream& operator<<(ofstream& file, Hex &game){		//Wrtiting to file.
	/*
	*	If one player game, player=1;  if two players game, player=2;
	*	turn could be x or o.
	*	boardSize is size of board columns/rows.
	*/

	file << game.boardSize  << endl;
	file << game.how_many_player<< endl;
	file << (char)game.turn << endl;

	for(int i=0; i< game.boardSize; i++){
		for(int j=0; j< game.boardSize; j++)
			file << game.hexCells[i][j].getStatus();
		file << endl;
	}

	for(int i=0; i<game.boardSize*game.boardSize; i++)	//Writing oldMoves to the file.
		file << game.oldMoves[i] << game.oldMoves[i].getStatus() << endl;
	
	cout << "File is saved to the device.\nSTILL "<< game.turn << "'S TURN\n";
	file.close();

	return file;
}

Hex Hex::operator--( ){		// Predecrement (1player)	 
	for(int i=0; i<boardSize*boardSize; i++)
		if(i != 0 && oldMoves[i].getStatus() == '.'){
			oldMoves[i-1].setStatus('.');
			hexCells[ oldMoves[i-1].getY() ][ oldMoves[i-1].getX() ] = '.';
			break;
		}

	return *this;
}

Hex Hex::operator--(int){	// Postdecrement (2player)			UNDO THE LAST MOVE
	Hex temp(*this);		// Using Copy constructor
	--*this;
	this->turn = change_turn(turn);	//Becuase we undo the game just one time.
	return temp;
}

//Cell Implemantations
Hex::Cell::Cell(){
	status = (sides)('.');
	x=0, y=0;
}

Hex::Cell::Cell(char status2){
	status = (sides)status2;
}

Hex::Cell::Cell(int x2, int y2){
	x=x2;
	y=y2;
	status = (sides)('.');
}

Hex::Cell::Cell(int x2, int y2, char status2){
	x = x2;
	y = y2;
	status = (sides)status2;
}

Hex::Cell::Cell(const Hex::Cell &c):
	status( c.status ), x(c.x), y(c.y)
	{ /*Intentionally empty */}

const Hex::Cell &Hex::Cell::operator=(const Hex::Cell &other){	//Copy constructor of Cell.
	if(this == &other)	return *this;
	else{
		status= other.status;
		x= other.x;
		y= other.y;
		return *this;
	}
}

}//End of namespace