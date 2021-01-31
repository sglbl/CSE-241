#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <fstream>
#include "hexgame.h"
using namespace std;
using namespace hexname;

int Hex::runningGames = 0;	//static variable inside Hex's private part.

int show_runningGames(int &i, int &j, bool flag, vector<Hex*> hexgames){ //Helper to main just to prevent code repeating.
	if(flag==true) cout << "Running games are: " << Hex::getRunningGames() << endl;
	do{
		if(Hex::getRunningGames() == 0)	return 0;
		if(hexgames[i]->getIsDone() == 0 || hexgames[i]->getIsDone() == 1){
			if(flag==true) cout << "game"<< i <<" is running.\n";
			j++;
			if(j==Hex::getRunningGames())	break;
		} ++i;
	}while(1);
	if(Hex::getRunningGames() == 0)	return 0;
	return 1;
}

int main(){
	bool flag=true;
	int i,j, value, is_done;	//If is_done == 0 -> close, 1 -> open , if 2 -> game over.
	int choice, choice2, choice3, sum;
	string filename;

	vector<Hex*> hexgames = { };			//Creating an empty Hex vector.
	// This is not vector<Hex> hexgames; because when I do that, anytime I call copy constructor in hexgame.cpp
	// It calls destructor to destruct my object. But with this I don't need to worry copied object's destructors.
	//I can delete them anytime(like in case 7/ line: 125)

	cout << "Welcome to the Multiple Hex Game of Suleyman Golbol!\n";
	while(flag){
		cout << "\nPlease select from menu.\n";
		cout << "1) Create a new empty game and play\n";
		cout << "2) Open a game from a file directly and play\n";
		cout << "3) Open a game that already running.\n";
		cout << "4) Show the total marked cells of a game.\n";
		cout << "5) Compare marked cells of 2 different running games.\n";
		cout << "6) Load 5 saved games from my file to check easily. \n";
		cout << "7) Exit game\nSelect: ";
		while( !(cin >> choice) )
			{ cerr << "Try again: ";	cin.clear();  cin.ignore(10000, '\n');	}	// To prevent infinite loop in wrong input.

		switch(choice){
			case 1:
				is_done = 0;
				hexgames.push_back( new Hex() );
				if(hexgames[ Hex::getRunningGames() -1 ]->playGame(is_done) == false)	//False means game over so popback
					hexgames.pop_back();
				break;	
			case 2:
				cout << "Enter filename: ";
				cin >> filename;
				is_done=1;
				hexgames.push_back( new Hex(is_done, filename) );
				//If is_done -1 That means entered file couldn't found so I should remove from vector.
				if(is_done != -1){
				 	if(hexgames[ Hex::getRunningGames() -1 ]->playGame(is_done)== false) //False means game over so popback
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
				is_done=1;		//Because it is opening again.
				hexgames[choice2]->playGame(is_done);
				break;

			case 4:
				i=0, j=0, choice2=0, sum=0;
				if(show_runningGames(i, j, false, hexgames) == 0)	break; 
				if(i==0 && Hex::getRunningGames() == 1)	i++;
				for(int k=0; k<i; k++)
					if(hexgames[k]->getIsDone() != 0 || hexgames[k]->getIsDone() != 1){	//Finding a running game to compute all games.
						for(int m=0; m<=i; m++)
							if( hexgames[m]->getIsDone() == 0 || hexgames[m]->getIsDone() == 1 ){
								if(m != k)	sum += Hex::markedCells( *hexgames[m] );
								else	    sum += Hex::markedCells( *hexgames[k] );
							}
						break;
					}
				cout <<"Marked cells of all games are " << sum << endl;
				break;

			case 5:
				i=0, j=0, choice2=0, choice3=0;
				if(show_runningGames(i, j, true, hexgames) == 0) { cout<< "Not enough running games.(At least 2 games) Try later."; break; }
				if(j<2)  							   		     { cout<< "Not enough running games.(At least 2 games) Try later."; break; }

				cout << "Choice first game from above (For ex for game0 write 0): ";
				while( !(cin >> choice2) || choice2<0 || choice2>i || (hexgames[choice2]->getIsDone() != 0 && hexgames[choice2]->getIsDone() != 1) )
					{ cerr << "Try again: " ;	cin.clear(),	cin.ignore(10000, '\n'); }
				cout << "Choice second game from above (For ex for game0 write 0): ";
				while( !(cin >> choice3) || choice3<0 || choice3>i || (hexgames[choice3]->getIsDone() != 0 && hexgames[choice3]->getIsDone() != 1) )
					{ cerr << "Try again: " ;	cin.clear(),	cin.ignore(10000, '\n'); }
				value = (*hexgames[choice2] == *hexgames[choice3]) ;
				if(value==false)  
					cout << "game"<<choice3<<"(has "<< Hex::markedCells(*hexgames[choice3]) 
						 <<" cells) has more marked cells than game"<< choice2 <<"(has "<<Hex::markedCells(*hexgames[choice2])<<" cells)\n";
				if(value==true)
					cout << "game"<<choice2<<"(has "<< Hex::markedCells(*hexgames[choice2])
						 <<" cells) has more or equal marked cells than game"<< choice3 <<"(has "<<Hex::markedCells(*hexgames[choice3])<<" cells)\n";
				break;

			case 6:
				cout << "Five games automatically loaded from files.\n";
				is_done=3;	//Just to say to constructor "Don't play game just upload it to my vector."
				hexgames.push_back( new Hex(is_done, "EX1.TXT") );
				hexgames.push_back( new Hex(is_done, "EX2.TXT") );
				hexgames.push_back( new Hex(is_done, "EX3.TXT") );
				hexgames.push_back( new Hex(is_done, "EX4.TXT") );
				hexgames.push_back( new Hex(is_done, "EX5.TXT") );
				break;

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
}
