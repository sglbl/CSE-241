#include <iostream>
#include <string>
#include <random>
using namespace std;

bool is_valid_move(char board[][12], int x, int y, int boardSize, char letter){
	if( x>=0 && y>=0 && x<boardSize && y<boardSize && (board[y][x]==letter || board[y][x]==letter-32) )	
		return true;

	return false;
}

char make_uppercase(char letter){
	return letter-32;
}

int check_full_o(char board[][12], int boardSize, int x, int y, int visitedplaces[][12]){
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
			if (visitedplaces[boardSize-1][m] == 0 && ( board[boardSize-1][m] == 'o' || board[boardSize-1][m] == 'O') ){
				//Making the winner uppercase letters.
				for (int y = 0; y < boardSize; ++y)
					for (int x = 0; x < boardSize; ++x)
						if( visitedplaces[y][x]==2 ){
							board[y][x] = make_uppercase('o');
							if(y==boardSize-2 && board[boardSize-1][x] == 'o')		board[boardSize-1][x]   = make_uppercase('o');
							if(y==boardSize-2 && board[boardSize-1][x-1] == 'o')	board[boardSize-1][x-1] = make_uppercase('o');
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

int check_full_x(char board[][12], int boardSize, int x, int y, int visitedplaces[][12]){
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
			if (visitedplaces[m][boardSize-1] == 0 && (board[m][boardSize-1] == 'x' || board[m][boardSize-1] == 'X' ) ){

				//Making the winner uppercase letters.
				for (int y = 0; y < boardSize; ++y)
					for (int x = 0; x < boardSize; ++x)
						if( visitedplaces[y][x]==1 ){
							board[y][x] = make_uppercase('x');
							if(x==boardSize-2 && board[y][boardSize-1] == 'x')		board[y][boardSize-1]   = make_uppercase('x');
							if(x==boardSize-2 && board[y-1][boardSize-1] == 'x')	board[y-1][boardSize-1] = make_uppercase('x');
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

int check(char board[][12], int boardSize){
	int visitedplaces[12][12];

	for(int m=0; m<boardSize; m++){
		//Checking x
		for(int i=0; i<boardSize; i++)
    		for(int j=0; j<boardSize; j++)
    			visitedplaces[i][j]=0;

		if(board[m][0] == 'x' || board[m][0] == 'X')
			if( check_full_x(board, boardSize, 0, m, visitedplaces) == 2)	return 2;

		//Checking o
		for(int i=0; i<boardSize; i++)
    		for(int j=0; j<boardSize; j++)
    			visitedplaces[i][j]=0;

		if(board[0][m] == 'o' || board[0][m] == 'O')
			if( check_full_o(board, boardSize, m, 0, visitedplaces) == 3)	return 3;
	}
	
	return 0;
}

void printBoard(char board[][12], int boardSize){
	cout<<"  ";
	for(int i=0; i<boardSize; i++)
		cout << (char)(i+97) << " ";
	cout<<endl;

	for(int i=0; i<boardSize; i++){
		cout << i+1;
		for(int k=0; k<i+1; k++)
			cout << " ";
		for(int j=0; j<boardSize; j++)
			cout << board[i][j] << " "; 
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

void AI_choice(char board[][12], int boardSize, int x, int y){
	random_device myrand;
	int randnum, randnum2;

	do{
		mt19937 rand(myrand());
	    uniform_int_distribution<mt19937::result_type> myrandforBoard(1,boardSize);

	    randnum = myrandforBoard(myrand);			// Random number for cell column number. 
	    randnum2 = myrandforBoard(myrand);			// Random number for cell row letter.
	}while(board[randnum-1][randnum2-1] != '.' || board[randnum-1][randnum2-1] == 'x' );

	cout << "Choice of AI is " << char (randnum2-1 + 'A') << randnum << endl;
	board[randnum-1][randnum2-1] = 'o';

}

void startGame_computer(char board[][12], int boardSize){
	string coord;
	int i, temp0, temp1;
	char turn='x';	//If turn=x it is x's turn;   if turn=o it is o's turn.

	cout << "You(x) starts..." << endl;

    while(check(board, boardSize) == 0 ){
    	printBoard(board, boardSize);
    	cout << turn << "'s turn.\n";

    	if(turn=='x'){
	    	cout << "Please enter the cell (For ex. F5):  ";
			cin >> coord;
			for (i=0; coord[i]; i++);		//Size of string is i's new value.
			while((int)coord[0]<65 || (int)coord[0]>=(65+boardSize) || (int)coord[1]<49 || (int)coord[1]>(48+boardSize)
				 || i>4 || ( i==3 && (((int)coord[1] - 48)*10 + (int)coord[2]-49) >= boardSize ) ){		//Wrong inputs.
				cout << "You entered wrong input. Try again: ";
				cin >> coord;
				for (i=0; coord[i]; i++);		//Size of string is i's new value.
			}

			temp0 = int (coord[0]) - 65;		//functional type-casting to integer.
			if(boardSize >= 10 && (int)coord[2] != 0)				// For 2 digit numbers.
				temp1 = ((int)coord[1] - 48)*10 + (int)coord[2]-49;
			else														// For 1 digit numbers.
				temp1 = coord[1] - 49;				//char to int.

			if(board[temp1][temp0] == '.')		//If cell is empty.
				board[temp1][temp0] = turn;
			else{								//If cell is not empty.
				cout << "THIS IS NOT AN EMPTY CELL. TRY AGAIN !!!\n";
				continue;
			}
		}
		else			// if it's o's turn it means AI will play.
			AI_choice(board, boardSize, temp1, temp0);
		turn = change_turn(turn);	// Change turn in every single game.
    }			//End of the game.

    if     (check(board, boardSize) == 2)	cout << "Winner is X\n"; 
	else if(check(board, boardSize) == 3)	cout << "Winner is O\n"; 
	printBoard(board, boardSize);
}

void startGame_2player(char board[][12], int boardSize){
	string coord;
	int i, temp0, temp1;
	char turn='x';	//If turn=x it is x's turn;   if turn=o it is o's turn.

	cout << "X starts..." << endl;

	while ( check(board, boardSize) == 0 ){
		printBoard(board, boardSize);
		cout << turn << "'s turn!\n";
		cout << "Please enter the cell (For ex. F5):  ";

		cin >> coord;
		for (i=0; coord[i]; i++);		//Size of string is i's new value.
		while((int)coord[0]<65 || (int)coord[0]>=(65+boardSize) || (int)coord[1]<49 || (int)coord[1]>(48+boardSize)
			 || i>4 || ( i==3 && (((int)coord[1] - 48)*10 + (int)coord[2]-49) >= boardSize ) ){		//Wrong inputs.
			cout << "You entered wrong input. Try again: ";
			cin >> coord;
			for (i=0; coord[i]; i++);		//Size of string is i's new value.
		}

		temp0 = int (coord[0]) - 65;		//functional type-casting to integer.
		if(boardSize >= 10 && (int)coord[2] != 0)				// For 2 digit numbers.
			temp1 = ((int)coord[1] - 48)*10 + (int)coord[2]-49;
		else														// For 1 digit numbers.
			temp1 = coord[1] - 49;				//char to int.
 
		if(board[temp1][temp0] == '.')		//If cell is not empty.
			board[temp1][temp0] = turn;
		else{
			cout << "THIS IS NOT AN EMPTY CELL. TRY AGAIN !!!\n";
			continue;
		}
		turn = change_turn(turn);			//Changing turn like x to o || o to x.
	}
	if     (check(board, boardSize) == 2)	cout << "Winner is X\n"; 
	else if(check(board, boardSize) == 3)	cout << "Winner is O\n"; 
	printBoard(board, boardSize);
}

int Ask(int boardSize){
	int input;

	cout << "Which one?\n";
	cout << "1) You VS Computer		2) Two Player Game: "; 
	while ( !(cin >> input) ){
		cout << "Try again: " ;
		cin.clear(),	cin.ignore(10000, '\n');		// To prevent infinite loop in reading.
	}

	while(input !=1 && input != 2){
		cout << "You entered wrong input. Try again: ";	
		while ( !(cin >> input) ){
			cout << "Try again: " ;
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
		cout << "Try again: " ;
		cin.clear(),	cin.ignore(10000, '\n');		// To prevent infinite loop in reading.
	}
	while(input<1 || input>7){
		cout << "Try again: ";	
		while ( !(cin >> input) ){
			cout << "Try again: " ;
			cin.clear(),	cin.ignore(10000, '\n');		// To prevent infinite loop in reading.
		}
	}

	boardSize = boardsize(input);
	return boardSize;
}