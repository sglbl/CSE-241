#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <fstream>
#include "Errors.h"
#include "AbstractHex.h"

using namespace std;

namespace hexname{

//CONSTRUCTORS
AbstractHex::AbstractHex(){
	turn = 'x';
	int is_done=0;		
	setIsDone(is_done);
	runningGames++;
}

AbstractHex::AbstractHex(int is_done){	
	turn = 'x';
	setIsDone(is_done);
	//runningGames++;
}

AbstractHex::AbstractHex(int &is_done, const string &loadfile){	
	turn = 'x'; 	//Temporary values before reading file.
	ifstream file(loadfile);
	if(file.is_open() == false){
		cerr << "Couldn't find or open "<< loadfile << " file.\n\n";
		is_done = -1;
		return;
	}
	if(is_done != 3 && is_done != -1){
		cout << "This game object has been created with " << loadfile << " file.\n";
		setIsDone(1);			// Means game is ready, no need for asking boardsize etc.
		runningGames++;
	}
}

AbstractHex::~AbstractHex(){
}

bool AbstractHex::operator==(AbstractHex& game2){
	int size = this->current_length();
	if(size != game2.current_length())	return false;

	for(int row=0; row<size; row++)
		for(int column=0; column<size; column++){
			if( (*this)(column,row).getStatus() != game2(column,row).getStatus() ) //I used operator() overload.
				try{
					return false;
				}
				catch(const Errors& myerror){
					cerr << myerror.what() << endl;
				}
		}
	return true;
}

void AbstractHex::setIsDone(const int& is_done){
	is_done2 = is_done;
}

char AbstractHex::change_turn(char turn){
	char flag = 'x';
	if(turn=='x')	flag = 'o';
	return flag;
}

int AbstractHex::current_length() const{
	return boardSize;
}

//STATIC FUNCTIONS
int AbstractHex::getRunningGames(){
	return runningGames;
}

void AbstractHex::increaseRunningGames(){
	runningGames++;
}

//CELL IMPLEMENTATIONS
AbstractHex::Cell::Cell(){
	status = (sides)('.');
	x=0, y=0;
}

AbstractHex::Cell::Cell(char status2){
	status = (sides)status2;
}

AbstractHex::Cell::Cell(int x2, int y2){
	x=x2;
	y=y2;
	status = (sides)('.');
}

AbstractHex::Cell::Cell(int x2, int y2, char status2){
	x = x2;
	y = y2;
	status = (sides)status2;
}

AbstractHex::Cell::Cell(const AbstractHex::Cell &c):
	status( c.status ), x(c.x), y(c.y)
	{ /*Intentionally empty */}

ostream& operator<<(ostream& os, const AbstractHex::Cell& c){
	os << static_cast<char> (c.x +65) << c.y+1;
	return os;
}

bool operator==(const AbstractHex::Cell& c1, const AbstractHex::Cell& c2){
	if(c1.x == c2.x && c1.y == c2.y && c1.status == c2.status)
		return true;
	return false;
}

AbstractHex::Cell AbstractHex::lastMove(){
	if(oldMoves[0].getStatus() == '.') 
		throw( Errors("There is no last move. Thrown an exception.\n") );

	for(int i=0; i<boardSize*boardSize; i++)
		if(i != 0 && oldMoves[i].getStatus() == '.')
			return oldMoves[i-1];

	return oldMoves[0];
}

const AbstractHex::Cell &AbstractHex::Cell::operator=(const AbstractHex::Cell &other){	//Copy constructor of Cell.
	if(this == &other)	return *this;
	else{
		status= other.status;
		x= other.x;
		y= other.y;
		return *this;
	}
}

}//End of namespace