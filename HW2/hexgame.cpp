#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include "hexgame.h"
#define EXIT_SUCCESS 0
using namespace std;

bool is_valid_move(sides board[][12], int x, int y, int boardSize, char letter){
	if( x>=0 && y>=0 && x<boardSize && y<boardSize && (board[y][x]==static_cast<sides>(letter) || board[y][x]==static_cast<sides>(letter-32) ) )	
		return true;

	return false;
}

char make_uppercase(char letter){
	return letter-32;
}

int check_full_o(sides board[][12], int boardSize, int x, int y, int visitedplaces[][12]){
	/* If visitedplaces[y][x] == 2, then it means it's visited ;  
	   If visitedplaces[x][y] == 0, then it means it's not visited yet.	
	*/
	/*
		case 1:	x2=x+1;	y2=y-1;		//upright
		case 2:	x2=x+1;	y2=y;		//right
		case 3:	x2=x;	y2=y+1;		//downright
		case 4:	x2=x-1;	y2=y+1;		//downleft
		case 5:	x2=x-1;	y2=y;		//left
		case 6:	x2=x;	y2=y-1;		//upleft			
	*/

	if( y == boardSize-1 ){
		for(int m=0; m<boardSize; m++)
			if (visitedplaces[boardSize-1][m] == 0 && ( board[boardSize-1][m] == static_cast<sides>('o') || board[boardSize-1][m] == static_cast<sides>('O')) ){
				//Making the winner uppercase letters.
				for (int y = 0; y < boardSize; ++y)
					for (int x = 0; x < boardSize; ++x)
						if( visitedplaces[y][x]==2 ){
							board[y][x] =  static_cast<decltype(sides::o)>( make_uppercase('o') );
							if(y==boardSize-2 && board[boardSize-1][x] == static_cast<sides>('o'))		board[boardSize-1][x]   = static_cast<decltype(sides::o)>(make_uppercase('o'));
							if(y==boardSize-2 && board[boardSize-1][x-1] == static_cast<sides>('o'))	board[boardSize-1][x-1] = static_cast<decltype(sides::o)>(make_uppercase('o'));
						}
				return 3;
			}
	}else{
			//Recursively finding if it wins with Backtrack technique.
			if(visitedplaces[y-1][x+1]==0 && is_valid_move(board, x+1, y-1, boardSize,'o') == true){
				visitedplaces[y][x] = 2;
				if (check_full_o(board, boardSize, x+1, y-1, visitedplaces)) return 3;
			}

			if(visitedplaces[y][x+1]==0 && is_valid_move(board, x+1, y, boardSize,'o') == true){
				visitedplaces[y][x] = 2;
				if (check_full_o(board, boardSize, x+1, y, visitedplaces)) return 3;
			}

			if(visitedplaces[y+1][x]==0 && is_valid_move(board, x, y+1, boardSize,'o') == true){
				visitedplaces[y][x] = 2;
				if (check_full_o(board, boardSize, x, y+1, visitedplaces)) return 3;
			}

			if(visitedplaces[y+1][x-1]==0 && is_valid_move(board, x-1, y+1, boardSize,'o') == true){
				visitedplaces[y][x] = 2;
				if (check_full_o(board, boardSize, x-1, y+1, visitedplaces)) return 3;
			}

			if(visitedplaces[y][x-1]==0 && is_valid_move(board, x-1, y, boardSize,'o') == true){
				visitedplaces[y][x] = 2;
				if (check_full_o(board, boardSize, x-1, y, visitedplaces)) return 3;
			}

			if(visitedplaces[y-1][x]==0 && is_valid_move(board, x, y-1, boardSize,'o') == true){
				visitedplaces[y][x] = 2;
				if (check_full_o(board, boardSize, x, y-1, visitedplaces)) return 3;
			}			

			visitedplaces[y][x]=0;
		}
	
	return 0;
}

int check_full_x(sides board[][12], int boardSize, int x, int y, int visitedplaces[][12]){
	/* If visitedplaces[y][x] == 1, then it means it's visited ;  
	   If visitedplaces[x][y] == 0, then it means it's not visited yet.	
	*/
	/*
		case 1:	x2=x+1;	y2=y-1;		//upright
		case 2:	x2=x+1;	y2=y;		//right
		case 3:	x2=x;	y2=y+1;		//downright
		case 4:	x2=x-1;	y2=y+1;		//downleft
		case 5:	x2=x-1;	y2=y;		//left
		case 6:	x2=x;	y2=y-1;		//upleft			
	*/

	if( x == boardSize-1 ){
		for(int m=0; m<boardSize; m++)
			if (visitedplaces[m][boardSize-1] == 0 && (board[m][boardSize-1] == static_cast<sides>('x') || board[m][boardSize-1] == static_cast<sides>('X') ) ){

				//Making the winner uppercase letters.
				for (int y = 0; y < boardSize; ++y)
					for (int x = 0; x < boardSize; ++x)
						if( visitedplaces[y][x]==1 ){
							board[y][x] = static_cast<decltype(sides::x)>(make_uppercase('x'));
							if(x==boardSize-2 && board[y][boardSize-1] == static_cast<sides>('x'))		board[y][boardSize-1]   = static_cast<decltype(sides::x)>(make_uppercase('x'));
							if(x==boardSize-2 && board[y-1][boardSize-1] == static_cast<sides>('x'))	board[y-1][boardSize-1] = static_cast<decltype(sides::x)>(make_uppercase('x'));
						}

				return 2;
			}
	}else{
			//Recursively finding if it wins with Backtrack technique.
			if(visitedplaces[y-1][x+1]==0 && is_valid_move(board, x+1, y-1, boardSize,'x') == true){
				visitedplaces[y][x] = 1;
				if (check_full_x(board, boardSize, x+1, y-1, visitedplaces)) return 2;
			}

			if(visitedplaces[y][x+1]==0 && is_valid_move(board, x+1, y, boardSize,'x') == true){
				visitedplaces[y][x] = 1;
				if (check_full_x(board, boardSize, x+1, y, visitedplaces)) return 2;
			}

			if(visitedplaces[y+1][x]==0 && is_valid_move(board, x, y+1, boardSize,'x') == true){
				visitedplaces[y][x] = 1;
				if (check_full_x(board, boardSize, x, y+1, visitedplaces)) return 2;
			}

			if(visitedplaces[y+1][x-1]==0 && is_valid_move(board, x-1, y+1, boardSize,'x') == true){
				visitedplaces[y][x] = 1;
				if (check_full_x(board, boardSize, x-1, y+1, visitedplaces)) return 2;
			}

			if(visitedplaces[y][x-1]==0 && is_valid_move(board, x-1, y, boardSize,'x') == true){
				visitedplaces[y][x] = 1;
				if (check_full_x(board, boardSize, x-1, y, visitedplaces)) return 2;
			}

			if(visitedplaces[y-1][x]==0 && is_valid_move(board, x, y-1, boardSize,'x') == true){
				visitedplaces[y][x] = 1;
				if (check_full_x(board, boardSize, x, y-1, visitedplaces)) return 2;
			}			

			visitedplaces[y][x]=0;
		}
	
	return 0;
}

int check(sides board[][12], int boardSize){
	int visitedplaces[12][12];

	for(int m=0; m<boardSize; m++){
		//Checking x
		for(int i=0; i<boardSize; i++)
    		for(int j=0; j<boardSize; j++)
    			visitedplaces[i][j]=0;

		if(board[m][0] == static_cast<sides>('x') || board[m][0] == static_cast<sides>('X'))
			if( check_full_x(board, boardSize, 0, m, visitedplaces) == 2)	return 2;

		//Checking o
		for(int i=0; i<boardSize; i++)
    		for(int j=0; j<boardSize; j++)
    			visitedplaces[i][j]=0;

		if(board[0][m] == static_cast<sides>('o') || board[0][m] == static_cast<sides>('O'))
			if( check_full_o(board, boardSize, m, 0, visitedplaces) == 3)	return 3;
	}
	
	return 0;
}

void printBoard(sides board[][12], int boardSize){
	cout<<"  ";
	for(int i=0; i<boardSize; i++)
		cout << (char)(i+97) << " ";
	cout<<endl;

	for(int i=0; i<boardSize; i++){
		cout << i+1;
		for(int k=0; k<i+1; k++)
			cout << " ";
		for(int j=0; j<boardSize; j++)
			cout << (char)board[i][j] << " "; 
		cout << endl;
	}
}

char change_turn(char turn){
	char flag = 'x';
	if(turn=='x')	flag = 'o';
	return flag;
}

int absval(int a){
	if (a<0)
		return -a;
	return a;
}

void AI_choice(sides board[][12], int boardSize){
	random_device myrand;
	int randnum, randnum2;

	do{
		mt19937 rand(myrand());
	    uniform_int_distribution<mt19937::result_type> myrandforBoard(1,boardSize);

	    randnum = myrandforBoard(myrand);			// Random number for cell column number. 
	    randnum2 = myrandforBoard(myrand);			// Random number for cell row letter.
	}while(board[randnum-1][randnum2-1] != static_cast<sides>('.') || board[randnum-1][randnum2-1] == static_cast<sides>('x') );

	cout << "Choice of AI is " << char (randnum2-1 + 'A') << randnum << endl;
	board[randnum-1][randnum2-1] = sides::o;

}

void save_to_the_file(sides board[][12], int boardSize, int player, const string &filename, char whose_turn /*='x' */){ //Default argument used in header file
	/*																													//So no need to write again in definition.
	*	If one player game, player=1;  if two players game, player=2;
	*	whose_turn could be x or o.
	*	boardSize is size of board columns/rows.
	*/
	ofstream file(filename);
	if(file.is_open() == false){
		cerr << "Couldn't open file.\n";
		return;
	}

	file << boardSize  << endl;
	file << player     << endl;
	file << (char)whose_turn << endl;

	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++)
			file << static_cast<char>(board[i][j]);
		file << endl;
	}

	cout << "File is saved to the device.\nSTILL "<< whose_turn << "'S TURN\n";
	file.close();
}

void load_from_file(sides board[][12], int &boardSize, int &player, const string &filename, char &whose_turn){
	/*
	*	First line in file shows board size.
	*	Second line shows if game is 1 player or 2 players.
	*	Third line  shows whose turn it is (x or o).
	*/
	int i,j;

	string inside;
	ifstream file(filename);
	if(file.is_open() == false){
		cerr << "Couldn't open file.\n";
		return;
	}

	file >> inside;
	if(size_of_string(inside) == 1)  		boardSize = static_cast<int>(inside[0]) - 48;
	else if(size_of_string(inside) ==2)		boardSize = (static_cast<int>(inside[0]) - 48)*10 + static_cast<int>(inside[1])-48;
	//cout << boardSize << endl;

	file >> inside;
	player = static_cast<int>(inside[0]) - 48;

	file >> inside;
	decltype(i) temp = static_cast<int>(inside[0]);   // declrtype of item is integer.
	whose_turn = static_cast<char>(temp);

	for(i=0; i<boardSize; i++){
		file >> inside;
		//cout << inside << endl;
		for(j=0; j<boardSize; j++){
			board[i][j] = static_cast<sides>(inside[j]);
		}
	}
	file.close();
}

int size_of_string(string str){
	auto i=0;
	for(i=0; str[i]; i++); // Body intentionally empty!
	//Size of string is i's new value.
	return i;
}

bool input_wrong(string coord, int boardSize){
	auto i = size_of_string(coord);		
	//Checks the size of entered string to prevent false inputs.
	if
	(
		(int)coord[0]<65 || (int)coord[0]>=(65+boardSize) || (int)coord[1]<49 || (int)coord[1]>(48+boardSize)
		|| i>4 || ( i==3 && (((int)coord[1] - 48)*10 + (int)coord[2]-49) >= boardSize )
	)
		return false;
	return true;
}

void changing_player_from_file(sides board[][12], int boardSize, int how_many_player, char turn){
	if	   (how_many_player==1)	startGame_computer(board, boardSize, 2);
	else if(how_many_player==2)	startGame_2player(board,  boardSize, 2, turn);
	exit(EXIT_SUCCESS);
}

void startGame_computer(sides board[][12], int boardSize, int time){
	//If time==2 that means this function called because of new loaded file.
	string coord, filename;
	auto file_job=0, file_job2=0;
	int temp0, temp1, player;
	char turn='x';	//If turn=x it is x's turn;   if turn=o it is o's turn.

	cout << "You(x) starts..." << endl;

	if(time==1)	cin.ignore(100, '\n');					// I added it because getline is leaving a newline in this buffer.
	if(time==2)	cout << "Game style changed." << endl;

    while(check(board, boardSize) == 0 ){
    	file_job=0, file_job2=0, player=1;
    	printBoard(board, boardSize);
    	cout << turn << "'s turn.\n";
    	if(turn=='x'){
	    	cout << "Please enter the cell (For ex. F5):  ";
			getline(cin, coord);

			if(coord.compare(0,5, "SAVE ",0, 5) == 0){
				//It compares "SAVE " with coord from 0th index to the 5 characters.
				filename = coord.substr(5);    // The word after "FILE " is file's name.
				save_to_the_file(board, boardSize, player, filename, turn); //Third argument is 1 becuase of 1 player game.
				continue;
			}
			else if(coord.compare(0,5, "LOAD ",0, 5) == 0){
				filename = coord.substr(5);    // The word after "FILE " is file's name. 
				load_from_file(board, boardSize, player, filename, turn);  //Player is 1 becuase person vs computer.
				if(player==2)	changing_player_from_file(board, boardSize, player, turn);
				continue;
			}

			while( input_wrong(coord, boardSize) == false ){		//Wrong inputs.
				if(file_job==0)	cerr << "You entered wrong input. Try again: ";
				getline(cin, coord);

				if(coord.compare(0,5, "SAVE ",0, 5) == 0){		// There is a chance if user enters FILE after he/she types wrong.
					//It compares "SAVE " with coord from 0th index to the 5 characters.
					filename = coord.substr(5);    // The word after "FILE " is file's name. 
					save_to_the_file(board, boardSize, player, filename); //Third argument is 1 becuase of 1 player game.
					//Used default argument.
					file_job=1;
				}
				else if(coord.compare(0,5, "LOAD ",0, 5) == 0){
					filename = coord.substr(5);    // The word after "FILE " is file's name. 
					load_from_file(board, boardSize, player, filename, turn);
					if(player==2)	changing_player_from_file(board, boardSize, player, turn);
					file_job2=1;
				}
				if(file_job2==1)	break;
			}

			if(file_job2==1)	continue;

			temp0 = int (coord[0]) - 65;		//functional type-casting to integer.
			if(boardSize >= 10 && (int)coord[2] != 0)				// For 2 digit numbers.
				temp1 = ((int)coord[1] - 48)*10 + (int)coord[2]-49;
			else														// For 1 digit numbers.
				temp1 = coord[1] - 49;				//char to int.

			if(board[temp1][temp0] == static_cast<sides>('.') )		//If cell is empty.
				board[temp1][temp0] = static_cast<sides>(turn);
			else{								//If cell is not empty.
				cerr << "THIS IS NOT AN EMPTY CELL. TRY AGAIN !!!\n";
				continue;
			}
		}
		else			// if it's o's turn it means AI will play.
			AI_choice(board, boardSize);
		turn = change_turn(turn);	// Change turn in every single game.
    }			//End of the game.

    if     (check(board, boardSize) == 2)	cout << "Winner is X\n"; 
	else if(check(board, boardSize) == 3)	cout << "Winner is O\n"; 
	printBoard(board, boardSize);
}

void startGame_2player(sides board[][12], int boardSize, int time, char turn){
	//If time==2 that means this function called because of new loaded file.
	//If turn=x it is x's turn;   if turn=o it is o's turn.   //Defaultly turn is x.
	string coord,filename;
	auto file_job=0, file_job2=0;
	int temp0, temp1, player;

	cout << turn << " starts..." << endl;

	if(time==1)	cin.ignore(100, '\n');			// I added it because getline is leaving a newline in buffer.
	if(time==2)	cout << "Game style changed." << endl;

	while ( check(board, boardSize) == 0 ){
		file_job=0, file_job2=0, player=2;
		printBoard(board, boardSize);
		cout << turn << "'s turn!\n";
		cout << "Please enter the cell (For ex. F5):  ";
		getline(cin, coord);

		if(coord.compare(0,5, "SAVE ",0, 5) == 0){
			//It compares "FILE " with coord from 0th index to the 5 characters.
			filename = coord.substr(5);    // The word after "FILE " is file's name.
			save_to_the_file(board, boardSize, 2, filename, turn); //Third argument is 2 becuase of 2 players game.
			continue;
		}
		else if(coord.compare(0,5, "LOAD ",0, 5) == 0){
			filename = coord.substr(5);    // The word after "FILE " is file's name. 
			load_from_file(board, boardSize, player, filename, turn);  //Player is 1 becuase person vs computer.
			if(player==1)	changing_player_from_file(board, boardSize, player);
			continue;
		}

		while( input_wrong(coord, boardSize) == false ){		//Wrong inputs.
			if(file_job==0)	cerr << "You entered wrong input. Try again: ";
			getline(cin, coord);

			if(coord.compare(0,5, "SAVE ",0, 5) == 0){		// There is a chance if user enters SAVE after he/she types wrong.
				//It compares "SAVE " with coord from 0th index to the 5 characters.
				filename = coord.substr(5);    // The word after "SAVE " is file's name. 
				save_to_the_file(board, boardSize, 2, filename, turn); //Third argument is 2 becuase of 2 players game.
				file_job=1;
			}
			else if(coord.compare(0,5, "LOAD ",0, 5) == 0){
				filename = coord.substr(5);    // The word after "FILE " is file's name. 
				load_from_file(board, boardSize, player, filename, turn);  //Player is 1 becuase person vs computer.
				if(player==1)	changing_player_from_file(board, boardSize, player);
				file_job2=1;
			}

			if(file_job2==1)	break;
		}
		if(file_job2==1)	continue;

		temp0 = int (coord[0]) - 65;		//functional type-casting to integer.
		if(boardSize >= 10 && (int)coord[2] != 0)				// For 2 digit numbers.
			temp1 = ((int)coord[1] - 48)*10 + (int)coord[2]-49;
		else														// For 1 digit numbers.
			temp1 = coord[1] - 49;				//char to int.
 
		if(board[temp1][temp0] == static_cast<sides>('.') )		//If cell is not empty.
			board[temp1][temp0] =  static_cast<sides>(turn);
		else{
			cerr << "THIS IS NOT AN EMPTY CELL. TRY AGAIN !!!\n";
			continue;
		}
		turn = change_turn(turn);			//Changing turn like x to o || o to x.
	}
	if     (check(board, boardSize) == 2)	cout << "Winner is X\n"; 
	else if(check(board, boardSize) == 3)	cout << "Winner is O\n"; 
	printBoard(board, boardSize);
}

int Ask(){
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

int boardsize(int input){
	return input+5;
}

int initial(){
	int input, boardSize;
	//int flag=1; //If flag=1 right input, if flag=0 wrong input.
	cout << "What board size you want?" << endl;
	cout << "1) 6x6\n2) 7x7\n3) 8x8 \n4) 9x9 \n5) 10x10 \n6) 11x11 \n7) 12x12 \n(For ex. 6): ";
	while ( !(cin >> input) ){
		cerr << "Try again: " ;
		cin.clear(),	cin.ignore(10000, '\n');		// To prevent infinite loop in reading.
	}
	while(input<1 || input>7){
		cerr << "Try again: ";	
		while ( !(cin >> input) ){
			cerr << "Try again: " ;
			cin.clear(),	cin.ignore(10000, '\n');		// To prevent infinite loop in reading.
		}
	}

	boardSize = boardsize(input);
	return boardSize;
}