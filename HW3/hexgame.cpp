#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <fstream>
#include "hexgame.h"

using namespace std;

Hex::Hex(){
	int is_done=0;		
	runningGames++;
	setIsDone(is_done);
	playGame(is_done);
}

Hex::Hex(int is_done){	
	runningGames++;
	setIsDone(is_done);
	playGame(is_done);
}

Hex::Hex(int is_done, const string &loadfile){	
	turn = 'x'; 	//Temporary values before reading file.
	ifstream file(loadfile);
	if(file.is_open() == false){
		cerr << "Couldn't find or open file.\n\n";
		return;
	}
	cout << "This game object has been created with " << loadfile << " file.\n";
	setIsDone(1);			// Means game is ready, no need for asking boardsize etc.
	runningGames++;
	load_from_file(loadfile);		//Loading game from file.
	if(is_done != 3) playGame(is_done);
}

void Hex::createEmptyTable(int size, char side){		//Creates an empty table.
	for(int row=0; row<size; row++){
		hexCells.push_back( vector<Cell>() );
		for(int column=0; column<size; column++){
			hexCells[row].push_back( Hex::Cell(column, row, side) );
		}
	}
}

void Hex::printBoard(){
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

int Hex::Ask(){
	int input;

	cout << "Which one?\n";
	cout << "1) You VS Computer		2) Two Player Game: "; 
	while ( !(cin >> input) ){
		cerr << "Try again: " ;
		cin.clear(),	cin.ignore(10000, '\n');		// To prevent infinite loop in reading.
	}

	while(input !=1 && input != 2){
		cerr << "You entered wrong input. Try again: ";	
		while ( !(cin >> input) ){
			cerr << "Try again: " ;
			cin.clear(),	cin.ignore(10000, '\n');		// To prevent infinite loop in reading.
		}
	}

	return input;
}

void Hex::playGame(int is_done){
	string coord, filename;
	int command;
	int input=6, rvalue;
	
	setIsDone(is_done);
	if(is_done==0){				//First time opening game.
		cout << "What board size you want?" << endl;
		cout << "6) 6x6\n7) 7x7\n8) 8x8 \n9) 9x9 \n10) 10x10 \n11) 11x11 \n12) 12x12 and etc. (Till 26 because there are 26 letters.)\n(For ex. 6): ";
		while ( !(cin >> input) || input<6 || input>26 ){
			cerr << "Try again: " ;
			cin.clear(),	cin.ignore(10000, '\n');		// To prevent infinite loop in reading.
		}

		boardSize = input;
		createEmptyTable(boardSize, '.');
		how_many_player = Ask();
	}

	// Starting to game.
	cout << turn << " starts..." << endl;	//If turn=x it is x's turn;   if turn=o it is o's turn. 

	while ( check_if_ended() == 0 && (getIsDone()==0 || getIsDone()==1) ){
		command=0;
		printBoard();
		cout << turn << "'s turn!\n";
		cout << "(For ex. F5 or LOAD or SAVE or RBACK(to go back to menu) )\n";
		cout << "Please enter a command like above: ";
		getline(cin>>ws, coord);

		command = commandInput(coord, filename);
		if	   (command==1)	continue;		//Save file.
		else if(command==2) continue;		//Load file.
		else if(command==3)	break;			//Return back to main menu.

		if(how_many_player==1){				// 1 player game. 
			if(play(coord)==false)
				continue;
			else if(check_if_ended() != 0)	//if true
				break;
			else
				play();
		}

		else if(how_many_player==2){		// 2 player game.
			if(play(coord)==false)
				continue;
			else if(check_if_ended() != 0)	//if true
				break;
			turn = change_turn(turn);
		}
	}

	if(check_if_ended() != 0){		//That means it is over.
		runningGames--;
		setIsDone(2); 				// That means game is over not opening again.
		if(check_if_ended()==2) cout << "Winner is X\n"; 
		if(check_if_ended()==3) cout << "Winner is O\n"; 
		printBoard();
	}
	return;	//Return back to main menu becuase no one won yet.
}

void Hex::play(){
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
	hexCells[randnum-1][randnum2-1].setStatus('o');
}

bool Hex::play(string coord){
	int temp0, temp1;

	temp0 = int (coord[0]) - 65;		//functional type-casting to integer.
	if(current_length() >= 10 && (int)coord[2] != 0)				// For 2 digit numbers.
		temp1 = ((int)coord[1] - 48)*10 + (int)coord[2]-49;
	else														// For 1 digit numbers.
		temp1 = coord[1] - 49;				//char to int.

	if(hexCells[temp1][temp0].getStatus() == '.' )		//If cell is empty.
		hexCells[temp1][temp0].setStatus(turn);
	else{								//If cell is not empty.
		cerr << "THIS IS NOT AN EMPTY CELL. TRY AGAIN !!!\n";
		return false;
	}
	cout << "\nYour choice is " << coord << endl; 
	return true;
}

int Hex::commandInput(string &coord, string filename){
	bool askflag=false;
	do{
		if(askflag==true){			//If second time wrong ask this.
			cerr << "You entered wrong input. Try again: ";
			getline(cin>>ws, coord);
		}

		if(coord.compare(0,5, "SAVE ",0, 5) == 0){	    //It compares "SAVE " with coord from 0th index to the 5 characters.
			filename = coord.substr(5);   				// The word after "SAVE " is file's name. 
			save_to_the_file(filename); 				//Third argument is 2 becuase of 2 players game.
			return 1;
		}
		else if(coord.compare(0,5, "LOAD ",0, 5) == 0){
			filename = coord.substr(5);    				// The word after "FILE " is file's name. 
			load_from_file(filename);  					//Player is 1 becuase person vs computer.
			return 2;
		}
		else if(coord.compare(0,5, "RBACK ",0, 5) == 0){	//Returns back to the main function.
			setIsDone(1);
			return 3;
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

int Hex::check_if_ended(){
	int visitedplaces[26][26];

	for(int m=0; m<boardSize; m++){
		//Checking x
		for(int i=0; i<boardSize; i++)
    		for(int j=0; j<boardSize; j++)
    			visitedplaces[i][j]=0;
		if(hexCells[m][0].getStatus() == 'x' || hexCells[m][0].getStatus() == 'X')
			if( check_full(0, m, visitedplaces, 'x') == 2)	return 2;

		//Checking o
		for(int i=0; i<boardSize; i++)
    		for(int j=0; j<boardSize; j++)
    			visitedplaces[i][j]=0;

		if(hexCells[0][m].getStatus() == 'o' || hexCells[0][m].getStatus() == 'O')
			if( check_full(m, 0, visitedplaces, 'o') == 2)	return 3;
	}
	
	return 0;
}

void Hex::makeLettersCapital(char check, int visitedplaces[26][26]){
	if(check=='x')
		for(int y = 0; y < boardSize; ++y)
			for(int x = 0; x < boardSize; ++x)
				if( visitedplaces[y][x]==1 ){
					hexCells[y][x].setStatus('X');
					if(x==boardSize-2 && hexCells[y][boardSize-1].getStatus() == 'x')		hexCells[y][boardSize-1].setStatus('X');
					if(y>=1)	if(x==boardSize-2 && hexCells[y-1][boardSize-1].getStatus() == 'x')	hexCells[y-1][boardSize-1].setStatus('X');;
				}
	if(check=='o')
		for(int y = 0; y < boardSize; ++y)
			for(int x = 0; x < boardSize; ++x)
				if( visitedplaces[y][x]==1 ){
					hexCells[y][x].setStatus('O');
					if(y==boardSize-2 && hexCells[boardSize-1][x].getStatus() == 'o')		hexCells[boardSize-1][x].setStatus('O'); 
					if(x>=1)	if(y==boardSize-2 && hexCells[boardSize-1][x-1].getStatus() =='o')		hexCells[boardSize-1][x-1].setStatus('O');
				}
}


int Hex::check_full(int x, int y, int visitedplaces[][26], char check){
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
				{ makeLettersCapital('x', visitedplaces);	return 2; }
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
				if (check_full(x+1, y-1, visitedplaces, check)) return 2;
			}

			if(visitedplaces[y][x+1]==0 && is_valid_move(x+1, y, check) == true){
				visitedplaces[y][x] = 1;
				if (check_full(x+1, y, visitedplaces, check)) return 2;
			}

			if(visitedplaces[y+1][x]==0 && is_valid_move(x, y+1, check) == true){
				visitedplaces[y][x] = 1;
				if (check_full(x, y+1, visitedplaces, check)) return 2;
			}

			if(visitedplaces[y+1][x-1]==0 && is_valid_move(x-1, y+1, check) == true){
				visitedplaces[y][x] = 1;
				if (check_full(x-1, y+1, visitedplaces, check)) return 2;
			}

			if(visitedplaces[y][x-1]==0 && is_valid_move(x-1, y, check) == true){
				visitedplaces[y][x] = 1;
				if (check_full(x-1, y, visitedplaces, check)) return 2;
			}

			if(visitedplaces[y-1][x]==0 && is_valid_move(x, y-1, check) == true){
				visitedplaces[y][x] = 1;
				if (check_full(x, y-1, visitedplaces, check)) return 2;
			}			

			visitedplaces[y][x]=0;
		}
	
	return 0;
}

bool Hex::is_valid_move(int x, int y, char letter){
	if( x>=0 && y>=0 && x<boardSize && y<boardSize && (hexCells[y][x].getStatus()== letter
		 || hexCells[y][x].getStatus()== letter-32 ) )	
		return true;

	return false;
}

bool Hex::input_wrong(string coord){
	auto i = size_of_string(coord);	
	//Checks the size of entered string to prevent false inputs.
	if
	(
		(int)coord[0]<65 || (int)coord[0]>=(65+boardSize) || (int)coord[1]<49 || (int)coord[1]>(48+boardSize)
		|| i>4 || i<=1 || ( i==3 && (((int)coord[1] - 48)*10 + (int)coord[2]-49) >= boardSize )
	)
		return false;
	return true;
}

int Hex::size_of_string(string str){
	auto i=0;
	for(i=0; str[i]; i++); // Body intentionally empty!
	//Size of string is i's new value.
	return i;
}

int Hex::markedCells(Hex game1){		                 //Static function (static declaration in header)
	int sum=0;
	int bSize = game1.current_length();
	for(int row=0; row<bSize; row++)
		for(int column=0; column<bSize; column++)
			if(game1.hexCells[row][column].getStatus() !='.')  sum++;
	//cout << sum << "Sum\n";
	return sum;
}

int Hex::markedCells(vector<Hex> hexgames, int k){		//Static function (static declaration in header)
	int bSize;				// int k is for (*this) doesn't work in static function.
	int i=0, j=0, sum=0;
	if(show_runningGames(i, j, true, hexgames) == 0)	return 0;
	for(int m=0; m<=i; m++)
		if( hexgames[m].getIsDone() == 0 || hexgames[m].getIsDone() == 1 )
			if(m != k)	sum += Hex::markedCells( hexgames[m] );
			else	    sum += Hex::markedCells( hexgames[k]);
	return sum;
}

bool Hex::CompareGames(Hex game2){
	if( Hex::markedCells(*this) <  markedCells(game2) )	return false;
	if( Hex::markedCells(*this) >= markedCells(game2) )	return true;
	return false;
}

void Hex::save_to_the_file(const string &filename){ 
	/*
	*	If one player game, player=1;  if two players game, player=2;
	*	turn could be x or o.
	*	boardSize is size of board columns/rows.
	*/
	ofstream file(filename);
	if(file.is_open() == false){
		cerr << "Couldn't open file.\n";
		return;
	}

	file << boardSize  << endl;
	file << how_many_player<< endl;
	file << (char)turn << endl;

	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++)
			file << hexCells[i][j].getStatus();
		file << endl;
	}

	cout << "File is saved to the device.\nSTILL "<< turn << "'S TURN\n";
	file.close();
}

void Hex::load_from_file(const string &filename){
	/*
	*	First line in file shows board size.
	*	Second line shows if game is 1 player or 2 players.
	*	Third line  shows whose turn it is (x or o).
	*/
	int i,j, oldboardSize;

	string inside;
	ifstream file(filename);
	if(file.is_open() == false){
		cerr << "Couldn't open file.\n";
		return;
	}

	oldboardSize = boardSize;

	file >> inside;
	if(size_of_string(inside) == 1)  		boardSize = static_cast<int>(inside[0]) - 48;
	else if(size_of_string(inside) ==2)		boardSize = (static_cast<int>(inside[0]) - 48)*10 + static_cast<int>(inside[1])-48;
	//cout << boardSize << endl;

	file >> inside;
	how_many_player = static_cast<int>(inside[0]) - 48;

	file >> inside;
	int temp = static_cast<int>(inside[0]);
	turn = static_cast<char>(temp);

	createEmptyTable(boardSize, '.');			// Resizing

	for(i=0; i<boardSize; i++){
		file >> inside;
		for(j=0; j<boardSize; j++){
			hexCells[i][j].setStatus(inside[j]);
		}
	}
	file.close();
	resizeHexCells(oldboardSize);		//Delete old one.
}

void Hex::resizeHexCells(int oldboardSize){	//This function is for decreasing size. For increasing ı am using createEmptyTable() function.
		for(int i=0; i< oldboardSize; i++)
			hexCells.pop_back();		 	//If oldboardSize=7 and a=1, it makes boardSize 6.
}

int Hex::getRunningGames(){
	return runningGames;
}

int Hex::current_length() const{
	return hexCells.size();
}

int Hex::getIsDone() const{
	return is_done2;
}

void Hex::setIsDone(int is_done){
	is_done2 = is_done;
}

int show_runningGames(int &i, int &j, bool flag, vector<Hex> hexgames){ 	//Helper to main function.
	if(flag==true) cout << "Running games are: " << Hex::getRunningGames()<< endl;
	do{
		if(Hex::getRunningGames() == 0)	return 0;
		if(hexgames[i].getIsDone() == 0 || hexgames[i].getIsDone() == 1){
			if(flag==true) cout << "game"<< i <<" is running.\n";
			j++;
			if(j==Hex::getRunningGames())	break;
		} ++i;
	}while(1);
	if(Hex::getRunningGames() == 0)	return 0;
	return 1;
}