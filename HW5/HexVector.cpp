#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <fstream>
#include "Errors.h"
#include "HexVector.h"
#include "AbstractHex.h"
using namespace std;

namespace hexname{

HexVector::HexVector(): AbstractHex()
{/*BODY INTENTIONALLY EMPTY*/} 

HexVector::HexVector(int is_done): AbstractHex(is_done)
{  setSize(10);  }

HexVector::HexVector(int &is_done, const string &loadfile): AbstractHex(is_done,loadfile)
{/*BODY INTENTIONALLY EMPTY*/}

HexVector::~HexVector(){
	cout << "Derived object is destructed.\n";
}

void HexVector::setSize(const int& bs){
	boardSize = bs;
	reset();
}

void HexVector::createEmptyTable(int size){		//Creates an empty table.
	for(int i=0; i<26*26; i++){	//Because there are 26 lettters so max 26*26 board.
		oldMoves[i].setStatus('.');
	}

	for(int row=0; row<boardSize; row++){
		hexCells.push_back( vector<Cell>() );
		for(int column=0; column<boardSize; column++)
			hexCells[row].push_back( HexVector::Cell(column, row, '.') );
	}
}

void HexVector::reset(){	        //This function is resets size.	
	deleteTable();

	for(int row=0; row<boardSize; row++){
		hexCells.push_back( vector<Cell>() );
		for(int column=0; column<boardSize; column++)
			hexCells[row].push_back( HexVector::Cell(column, row, '.') );
	}
}

void HexVector::deleteTable(){
	for(int i=0; i< hexCells.size(); i++)
			hexCells.pop_back();	//Delete everything.
}

bool HexVector::playGame(int is_done){
	string coord, filename;
	int command,flag;  //game didn't end flag=0, x won flag=2, o won flag=2 
	int temp0, temp1;
	setIsDone(is_done);
	if(is_done==0)				//First time opening game.
		getInput();			//Using overloaded extraction operator for this object.
	
	// Starting to game.
	if(how_many_player==1)	cout << "It is One Player Game so score is counting.\n"
								 << "Scores are increasing 5 or 10 points in accordance with movement. \n"; 
	cout << turn << " starts..." << endl;	//If turn=x it is x's turn;   if turn=o it is o's turn. 
	flag=0;
	while ( isEnd(flag) == false && (getIsDone()==0 || getIsDone()==1) ){
		command=0;
		print();		//Using overloaded insertion operator for this object.
		cout << turn << "'s turn!\n";
		cout << "(For ex. F5 or LOAD or SAVE or LMOVE or NOMOVES or RBACK(to go back to menu) )\n";
		cout << "Please enter a command like above: ";
		getline(cin>>ws, coord);

		command = commandInput(coord, filename);
		if	   (command==1)	continue;		//Save file.
		else if(command==2) continue;		//Load file.
		else if(command==3)	break;			//Return back to main menu.
		else if(command==4) continue;		//Return last move.
		else if(command==5) continue;		//Return number of moves.

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
			else if(flag != 0)	//if not 0 then somebody won.
				break;
			//COMPUTER IS PLAYING
			else
				play();
			cout << "Score is " << getScore() << endl; //Score of user in 1 player game
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
			else if(flag != 0)	//if not 0 then somebody won.
				break;
			//CHANGING PLAYER
			turn = change_turn(turn);
		}
	}

	if(flag != 0){		//That means it is over.
		runningGames--;
		setIsDone(2); 				// That means game is over not opening again.
		if(flag==2) cout << "Winner is X\n"; 
		if(flag==3) cout << "Winner is O\n"; 
		print();		//Printing board.
		return false;			//So game ended, we should make pop_back() in main
	}
	return true;	//Return back to main menu becuase no one won yet.
}

void HexVector::getInput(){
	int input=6;
	cout << "What board size you want?" << endl;
	cout << "6) 6x6\n7) 7x7\n8) 8x8 \n9) 9x9 \n10) 10x10 \n11) 11x11 \n12) 12x12 and etc. (Till 26 because there are 26 letters.)\n";
	cout << "(For ex. 6): ";
	while ( !(cin >> input) || input<6 || input>26 )
		{ cerr << "Try again: "; cin.clear(); cin.ignore(10000,'\n');	}

	boardSize = input;
	this->createEmptyTable(input);
	this->setSize(input);

	cout << "Which one?\n";
	cout << "1) You VS Computer		2) Two Player Game: "; 
	while ( !(cin >> how_many_player) )
		{ cerr << "Try again: "; cin.clear(); cin.ignore(10000,'\n');	}
	
	while(how_many_player !=1 && how_many_player != 2){
		cerr << "You entered wrong input. Try again: ";	
		while ( !(cin >> how_many_player) )
			{ cerr << "Try again: "; cin.clear(); cin.ignore(10000,'\n');	}
	}

}

HexVector::Cell HexVector::play(){	//Play of computer
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

bool HexVector::play(Cell &c){		//Play of user
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

int HexVector::commandInput(string &coord, string filename){
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
				writeToFile(filename);	 				//Operator overloading for file. (ofstream)
			return 1;
		}
		else if(coord.compare(0,5, "LOAD ",0, 5) == 0){
			filename = coord.substr(5);    				// The word after "FILE " is file's name. 
			file2.open(filename);
			if(file2.is_open() == false)
				{ throw( Errors("Couldn't open file error caught.\n") ); }
			else
				readFromFile(filename);	 				//Operator overloading for file. (ifstream)
			return 2;
		}
		else if(coord.compare(0,5, "RBACK ",0, 5) == 0){	//Returns back to the main function.
			setIsDone(1);
			return 3;
		}
		else if(coord.compare(0,5, "LMOVE ",0, 5) == 0){	//Returns last move.
			try{
				cout << "Last move is " << lastMove() << endl;
			}
			catch(const Errors& myerror){ 
				cerr << "not found. (Exception caught)\n" << 
				myerror.what();
			}
			return 4;
		}
		else if(coord.compare(0,6, "NOMOVES ",0, 6) == 0){	//Returns last move.
			cout << "Number of steps this board made is " << numberOfMoves() << endl;
			return 5;
		}
		askflag=true;
	}while( input_wrong(coord) == false );	//Wrong inputs

	return 0;
}

int HexVector::isEnd(int &flag){
	int visitedplaces[26][26];
	int score=0;

	for(int m=0; m<boardSize; m++){
		//Checking x if wom
		for(int i=0; i<boardSize; i++)
    		for(int j=0; j<boardSize; j++)
    			visitedplaces[i][j]=0;
		if(hexCells[m][0].getStatus() == 'x' || hexCells[m][0].getStatus() == 'X')
			if( check_full(0, m, visitedplaces, 'x', score) == 2){
				flag=2;	// x won.
				return true;
			}	

		//Checking o if won
		for(int i=0; i<boardSize; i++)
    		for(int j=0; j<boardSize; j++)
    			visitedplaces[i][j]=0;

		if(hexCells[0][m].getStatus() == 'o' || hexCells[0][m].getStatus() == 'O')
			if( check_full(m, 0, visitedplaces, 'o', score) == 2){
				flag=3;	//o won.
				return true;
			}	
	}

	return false;
}

int HexVector::getScore(){
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

void HexVector::makeLettersCapital(char check, int visitedplaces[26][26]){
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

bool HexVector::is_valid_move(int x, int y, char letter){
	if( x>=0 && y>=0 && x<boardSize && y<boardSize && (hexCells[y][x].getStatus()== letter
		 || hexCells[y][x].getStatus()== letter-32 ) )	
		return true;

	return false;
}

bool HexVector::input_wrong(string coord){
	auto i = size_of_string(coord);	
	if      //Checks the size of entered string to prevent false inputs.
	(
		(int)coord[0]<65 || (int)coord[0]>=(65+boardSize) || (int)coord[1]<49 || (int)coord[1]>(48+boardSize)
		|| i>4 || i<=1 || ( i==3 && (((int)coord[1] - 48)*10 + (int)coord[2]-49) >= boardSize )
	)
		return false;
	return true;
}

int HexVector::size_of_string(const string &str){
	auto i=0;
	for(i=0; str[i]; i++); // Body intentionally empty!
	//Size of string is i's new value.
	return i;
}

void HexVector::setOldMove(const HexVector::Cell &c){			//Entering oldMove for undo operation.
	for(int i=0; i<boardSize*boardSize; i++)
		if(oldMoves[i].getStatus() == '.'){
			oldMoves[i] = c;
			break;
		}
}

void HexVector::print(){
	cout<<"  ";
	for(int i=0; i<boardSize; i++)
		cout << (char)(i+97) << " ";
	cout<<endl;

	for(int row=0; row<boardSize; row++){
		cout << row+1;
		for(int space=0; space<row+1; space++)	cout << " ";
		for(int column=0; column<boardSize; column++){
			cout << hexCells[row][column].getStatus() <<" ";
		}
		cout << endl;
	}
}

int HexVector::check_full(int x, int y, int visitedplaces[][26], char check, int &score){
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
			if(visitedplaces[y-1][x+1]==0 && is_valid_move(x+1, y-1, check) == true){
				visitedplaces[y][x] = 1;
				score+=5;
				if (check_full(x+1, y-1, visitedplaces, check, score)) return 2;
			}

			if(visitedplaces[y][x+1]==0 && is_valid_move(x+1, y, check) == true){
				visitedplaces[y][x] = 1;
				score+=5;
				if (check_full(x+1, y, visitedplaces, check, score)) return 2;
			}

			if(visitedplaces[y+1][x]==0 && is_valid_move(x, y+1, check) == true){
				visitedplaces[y][x] = 1;
				score+=5;
				if (check_full(x, y+1, visitedplaces, check, score)) return 2;
			}

			if(visitedplaces[y+1][x-1]==0 && is_valid_move(x-1, y+1, check) == true){
				score+=5;
				visitedplaces[y][x] = 1;
				if (check_full(x-1, y+1, visitedplaces, check, score)) return 2;
			}

			if(visitedplaces[y][x-1]==0 && is_valid_move(x-1, y, check) == true){
				visitedplaces[y][x] = 1;
				score+=5;
				if (check_full(x-1, y, visitedplaces, check, score)) return 2;
			}

			if(visitedplaces[y-1][x]==0 && is_valid_move(x, y-1, check) == true){
				visitedplaces[y][x] = 1;
				score+=5;
				if (check_full(x, y-1, visitedplaces, check, score)) return 2;
			}			

			visitedplaces[y][x]=0;
		}
	
	return 0;
}

void HexVector::readFromFile(const string &filename){	//For reading the file.
	int i,j, oldboardSize;
	string inside;

	ifstream file(filename);
	if(file.is_open() == false){
		throw( Errors("File didn't found or open error caught\n") );
	}
	oldboardSize = boardSize;

	file >> inside;
	if     (size_of_string(inside) == 1)  	boardSize = static_cast<int>(inside[0]) - 48;
	else if(size_of_string(inside) ==2)	    boardSize = (static_cast<int>(inside[0]) - 48)*10 + static_cast<int>(inside[1])-48;

	file >> inside;
	how_many_player = static_cast<int>(inside[0]) - 48;

	file >> inside;
	int temp = static_cast<int>(inside[0]);
	turn = static_cast<char>(temp);

	reset();		//Resets everything in board to '.'	//ÇÇ

	for(i=0; i<boardSize; i++){
		file >> inside;
		for(j=0; j<boardSize; j++){
			hexCells[i][j].setStatus(inside[j]);
		}
	}

	for(int i=0; i<boardSize*boardSize; i++){	//Getting oldMoves from the file.
		file >> inside;
		oldMoves[i].setX( (int)inside[0]-65 );
		oldMoves[i].setY( (int)(inside[1]-49) );
		oldMoves[i].setStatus(inside[2]);
	}
	file.close();
}

void HexVector::writeToFile(const string &filename){		//Wrtiting to file.
	/*
	*	If one player game, player=1;  if two players game, player=2;
	*	turn could be x or o.
	*	boardSize is size of board columns/rows.
	*/
	ofstream file(filename);
	file << boardSize  << endl;
	file << how_many_player<< endl;
	file << (char)turn << endl;

	for(int i=0; i< boardSize; i++){
		for(int j=0; j< boardSize; j++)
			file << hexCells[i][j].getStatus();
		file << endl;
	}

	for(int i=0; i<boardSize*boardSize; i++)	//Writing oldMoves to the file.
		file << oldMoves[i] << oldMoves[i].getStatus() << endl;
	
	cout << "File is saved to the device.\nSTILL "<< turn << "'S TURN\n";
	file.close();
}

int HexVector::numberOfMoves(){
	for(int i=0; i<boardSize*boardSize; i++)
		if(oldMoves[i].getStatus() == '.')
			return i;
	return 0;
}

int HexVector::getIsDone() const{
	return is_done2;
}

HexVector::Cell HexVector::operator()(int x,int y){	//I used this operator() in operator== to compare.
	bool flag=true;
	if(x<0 || y<0 || y>= boardSize || x>=boardSize) 
		flag = false;
	if(flag == false)	throw Errors("Error occured about the border.\n");
	return hexCells[y][x];
}


}   //End of namespace