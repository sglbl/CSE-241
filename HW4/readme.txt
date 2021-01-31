Hello teacher, 
I created a game function in menu called 
"6) Load 5 saved games from my file to check easily. "
for you. So if you don't want create or open games orderly you can check my function.
It loads EX1.TXT, EX2.TXT, EX3.TXT, EX4.TXT, EX5.TXT . And it is ready for your check.
------------------------
In game when you are playing,
if you write "LOAD NAME.TXT" , it loads NAME.TXT file.
if you write "SAVE NAME.TXT" , it saves NAME.TXT file.
if you write "RBACK" , it goes back to main menu without deleting the this class obejct.
------------------------
When you create empty Hex games in main menu, game names starts with 0. 
For example game0. After that, with order it continious to name game1, game2 etc.
------------------------
Valgrind results  
HEAP SUMMARY: 
in use at exit: 0 bytes in 0 blocks
All heap blocks were freed -- no leaks are possible 
(You can check with "make valgrind" command, because I created a command for this in my makefile)
------------------------
/********** ASKED IN PDF ********/////

Cell is public  ✓	hexgame.h line 23

Cell **hexCells	✓	hexgame.h line 153

unparameted play() function returns Cell and plays computer. ✓ hexgame.cpp Line 174
parameted play(Cell &c) takes cell position and plays user.	 ✓ hexgame.cpp Line 196
(Second function doesn't return Cell because in pdf, it writes return Cell just for first one play() not for second play(Cell&))

UNDO Feature  ✓ hexgame.cpp Line 238
-- for pre  decrement.   ✓ hexgame.cpp Line 578
-- for post decrement.   ✓ hexgame.cpp Line 589
(Becuase of you didn't say there should be Two undos like undo1 and undo2
I made 1 player game as predecrement and 2 player game as post decrement)

Overload stream insertion  operator			 ✓	hexgame.h line 142
Overload stream extraction operator			 ✓	hexgame.h line 144
Overload stream insertion  operator for file ✓	hexgame.h line 138
Overload stream extraction operator for file ✓	hexgame.h line 140

Function returns score (Just in one player game) ✓	hexgame.cpp line 283
(In ONE PLAYER GAME
If x wins 100 points,
Every connected one 5 or 10 points(changes to the tactic),
In beginning x starts with 0 point,
If x doesn't have connection to a cell in first column, point is also zero. (Because point mechanism starts with first column)

Overloaded == operator ✓	hexgame.h line 136

Using nullptr	 ✓	hexgame.h line 153
Using explicit	 ✓	hexgame.h line 86

Big Three(Copy constructor, assignment operator and destructor) ✓	hexgame.h line 79

-------------------------
Thank you for reading these.
Süleyman Gölbol
1801042656