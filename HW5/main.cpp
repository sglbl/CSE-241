#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <deque> 
#include "HexAdapter.cpp"
#include "HexAdapter.h"
#include "AbstractHex.h"
#include "HexVector.h"
#include "HexArray1D.h"
using namespace std;
using namespace hexname;

int AbstractHex::runningGames = 0;	//static variable inside Hex's private part.

//Helpers to main just to prevent code repeating.
int show_runningGames(int &i, int &j, bool flag, vector<AbstractHex*> hexgames);  //Finds which games are running.
int menu_for_derived(int flag);		//Asks user which class you want to use to create object.
bool global_to_check(int size, AbstractHex** hexgames_to_check);

int main(){
	bool flag=true;
	int i,j, value, is_done;	//If is_done == 0 -> close, 1 -> open , if 2 -> game over.
	int choice, choice2, choice3, sum;
	int derived_to_use;			//You will choose which derived class for using.
	string filename;

	vector<AbstractHex*> hexgames = { };			//Creating an empty Hex vector.
	// This is not vector<Hex> hexgames; because when I do that, anytime I call copy constructor in hexgame.cpp
	// It calls destructor to destruct my object. But with this I don't need to worry copied object's destructors.
	//I can delete them anytime(like in case 7/ line: 125)

	cout << "Welcome to the Multiple Hex Game of Suleyman Golbol!\n";
	while(flag){
		cout << "\nPlease select from menu.\n";
		cout << "1) Create a new empty game and play\n";
		cout << "2) Open a game from a file directly and play\n";
		cout << "3) Open a game that already running.\n";
		cout << "4) Compare 2 different running games.(with operator== and operator() )\n";
		cout << "5) Load 5 saved games from my file to check easily. \n";
		cout << "6) Check the games has errors with global function.\n7) Exit game\nSelect: ";
		while( !(cin >> choice) )
			{ cerr << "Try again: ";	cin.clear();  cin.ignore(10000, '\n');	}	// To prevent infinite loop in wrong input.

		switch(choice){
			case 1:
				is_done = 0;
				derived_to_use = menu_for_derived(1);
				if     (derived_to_use == 1)	hexgames.push_back( new HexVector()  );
				else if(derived_to_use == 2)	hexgames.push_back( new HexArray1D() );
				else if(derived_to_use == 3)	hexgames.push_back( new HexAdapter<vector>() );
				else if(derived_to_use == 4)	hexgames.push_back( new HexAdapter<deque>() );
				if(hexgames.back()->playGame(is_done) == false)	//False means game over so popback
					hexgames.pop_back();
				break;
			case 2:
				derived_to_use = menu_for_derived(2);
				cout << "Enter filename: ";
				cin >> filename;
				is_done=1;
				if	   (derived_to_use == 1)	hexgames.push_back( new HexVector(is_done,  filename) );
				else if(derived_to_use == 2)	hexgames.push_back( new HexArray1D(is_done, filename) );
				else if(derived_to_use == 3)	hexgames.push_back( new HexAdapter<vector>(is_done, filename) );
				else if(derived_to_use == 4)	hexgames.push_back( new HexAdapter<deque>(is_done, filename) );
				try	{ hexgames.back()->readFromFile(filename); }		//Loading game from file
				catch(const Errors& myerror){
					cerr << myerror.what();
				}
				//If is_done -1 That means entered file couldn't found so I should remove from vector.
				if(is_done != -1){
				 	if(hexgames[ AbstractHex::getRunningGames() -1 ]->playGame(is_done)== false) //False means game over so popback
				 		hexgames.pop_back(); //If game ends.
				}
				if(is_done == -1)	hexgames.pop_back();
				break;

			case 3:
				i=0, j=0, choice2=0;
				if(show_runningGames(i, j, true, hexgames) == 0)	break; 
				cout << "Game names starts with 0. Choice one of these (For game0 write 0): ";
				while( !(cin >> choice2) || choice2<0 || choice2>i || (hexgames[choice2]->getIsDone() != 0 && hexgames[choice2]->getIsDone() != 1) ){
					cerr << "Try again: " ;
					cin.clear(),	cin.ignore(10000, '\n');		// To prevent infinite loop in reading.
				}
				//If is_done == 0 -> close, 1 -> open , if 2 -> game over.
				is_done=1;		//Because it is opening game again.
				if(hexgames[choice2]->playGame(is_done) == false )	
					hexgames.erase( hexgames.begin() + choice2); //If game ends, find and remove from vector.
				break;

			case 4:
				i=0, j=0, choice2=0, choice3=0;
				if(show_runningGames(i, j, true, hexgames) == 0) { cout<< "Not enough running games.(At least 2 games) Try later."; break; }
				if(j<2)  							   		     { cout<< "Not enough running games.(At least 2 games) Try later."; break; }

				cout << "Choice first game from above (For ex for game0 write 0): ";
				while( !(cin >> choice2) || choice2<0 || choice2>i || (hexgames[choice2]->getIsDone() != 0 && hexgames[choice2]->getIsDone() != 1) )
					{ cerr << "Try again: " ;	cin.clear(),	cin.ignore(10000, '\n'); }
				cout << "Choice second game from above (For ex for game0 write 0): ";
				while( !(cin >> choice3) || choice3<0 || choice3>i || (hexgames[choice3]->getIsDone() != 0 && hexgames[choice3]->getIsDone() != 1) )
					{ cerr << "Try again: " ;	cin.clear(),	cin.ignore(10000, '\n'); }

				value = (*hexgames[choice2] == *hexgames[choice3]) ;	//Comparing with bool operator==

				if(value==true)
					cout << "game"<<choice2<<" and game"<< choice3 <<" are same\n";
				if(value==false)
					cout << "game"<<choice2<<" and game"<< choice3 <<" are not same\n";
				break;

			case 5:
				cout << "Five games automatically loaded from files.\n";
				is_done=1;	//The game has been already played so don't ask user boardsize etc.
				hexgames.push_back( new HexVector(is_done, "EX1.TXT") );
				hexgames.back()->readFromFile( "EX1.TXT" );		//Loading game from file.
				hexgames.push_back( new HexArray1D(is_done, "EX2.TXT") );
				hexgames.back()->readFromFile( "EX2.TXT" );		//Loading game from file.
				hexgames.push_back( new HexArray1D(is_done, "EX3.TXT") );
				hexgames.back()->readFromFile( "EX3.TXT" );		//Loading game from file.
				hexgames.push_back( new HexAdapter<vector>(is_done, "EX4.TXT") );
				hexgames.back()->readFromFile( "EX4.TXT" );		//Loading game from file.
				hexgames.push_back( new HexAdapter<deque>(is_done, "EX5.TXT") );
				hexgames.back()->readFromFile( "EX5.TXT" );		//Loading game from file.
				break;

			case 6:
				{
					is_done = 3;
					AbstractHex* games_to_check[6] ={		//Creating games with errors (to check)
														new HexVector(is_done),
														new HexArray1D(is_done),
														new HexAdapter<vector>(is_done),
														new HexAdapter<deque>(is_done),
														new HexVector(is_done, "DOESNT_EXIST.TXT"), //doesn't exist
														new HexVector(is_done, "EX6_ERROR.TXT")
													};
					if( global_to_check( 6, games_to_check ) == true) cout << "No errors found.\n";
					else 	cout << "Global function found errors.\n";
					break;
				}
			case 7:
					cout << "Goodbye. Thanks for playing Suleyman Golbol's Hex Game.\n";
					sum = hexgames.size();
					for(int i=0; i<sum; i++)
						delete hexgames[i];
					return 0;
		
			default:
				cerr << "Wrong input. Try again: \n";
		}

	}

	return 0;
}	//End of main function.

bool global_to_check(int size, AbstractHex** games_to_check){	// It will check some errors.
	AbstractHex::Cell temp;
	char status;
	for(int i=0; i<size; i++){  //Checking all indexes in array.
		if( games_to_check[i]->current_length() > 26 || games_to_check[i]->current_length() < 6 )
			return false;
		// If program reaches here size is true, now cheking board.
		for(int y=0; y< games_to_check[i]->current_length(); y++)
			for(int x=0; i<games_to_check[i]->current_length(); i++){
				temp = games_to_check[i]->operator()(x,y);
				status = temp.getStatus();
				if(status != 'x' && status != 'o' && status != '.')
					return false;
			}
	}
	return true;
}

int menu_for_derived(int flag){
	int choose;
	bool adapter=false;
	cout<< "1) HexVector\n2) HexArray1D\n3) HexAdapter\n" << "Which one you want to use to create this object? ";
	if(flag==1)			//Starting a new game.
		while(adapter==false){
			while( !(cin >> choose) )	{ cerr << "Try again: "; cin.clear(); cin.ignore(100, '\n'); }
			switch(choose){
				case 1: return 1;
				case 2: return 2;
				case 3: adapter = true; break;
				default: cout << "Error. Choose again: ";
			}
		}
	else if(flag==2)	//Opening game from file.
		while(adapter==false){
			while( !(cin >> choose) )	{ cerr << "Try again: "; cin.clear(); cin.ignore(100, '\n'); }
			switch(choose){
				case 1: return 1;
				case 2: return 2;
				case 3: adapter = true; break;
				default: cout << "Error. Try again: ";
			}
		}
	//If you reach here, that means you will choose a adapter class.
	cout << "1) Vector\n2) Deque\nWhich STL class dou you want to choose for new HexAdapter object?: ";
	while( !(cin >> choose) )	{ cerr << "Try again: "; cin.clear(); cin.ignore(100, '\n'); }
	switch(choose){
		case 1: return 3;    
		case 2: return 4;  
		default: cout << "Error. Try again: "; 
	}

	return 1;
}

int show_runningGames(int &i, int &j, bool flag, vector<AbstractHex*> hexgames){  //Finds active games.
	if(flag==true) cout << "Running games are: " << AbstractHex::getRunningGames() << endl;
	do{
		if(AbstractHex::getRunningGames() == 0)	return 0;
		if(hexgames[i]->getIsDone() == 0 || hexgames[i]->getIsDone() == 1){
			if(flag==true) cout << "game"<< i <<" is running.\n";
			j++;
			if(j==AbstractHex::getRunningGames())	break;
		} ++i;
	}while(1);
	if(AbstractHex::getRunningGames() == 0)	return 0;
	return 1;
}