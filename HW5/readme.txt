Hello teacher, 
I created a game function in menu called 
"5) Load 5 saved games from my file to check easily. "
for you. So if you don't want create or open games orderly choose this option.
It loads EX1.TXT, EX2.TXT, EX3.TXT, EX4.TXT, EX5.TXT . And it is ready for your check.
( It will create objects with HexVector, HexArray1D, HexAdapter<deque> and HexAdapter<vector>. )
------------------------
"6) Check the games has errors with global function." will test the some errors in array.
------------------------
In game when you are playing,
if you write "SAVE NAME.TXT" , it saves NAME.TXT file.
if you write "LOAD NAME.TXT" , it loads NAME.TXT file. (if there is a file)
if you write "RBACK" , it goes back to main menu without deleting the this class obejct.
if you write "LMOVE",  it returns the last move cell's value and prints to screen.			//HW5
if you write "NOMOVES", it returns number of steps this board made.							//HW5
------------------------
If you load from file and choose "LMOVE", it shows the last move of the loaded game.
(Because old moves are stored in file)
------------------------
When you create empty Hex games in main menu, game names starts with 0. 
For example game0. After that, with order it continious to name game1, game2 etc.
------------------------
For ex. there are 3 games(game0, game1, game2). If game1 ends. game2 becomes game1.
-----------------------
Thank you for reading these.
Süleyman Gölbol
1801042656