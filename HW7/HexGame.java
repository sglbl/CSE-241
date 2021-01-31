/*
 * @author Suleyman_Golbol_1801042656
 */
public interface HexGame {
    void addBoardToGame();
    //Creating game buttons and adding them to panel.
    void addToPanel3();
    //In game panel, adding a panel which contains load,save,undo and reset buttons.
    void setBoardSize(int size);
    //Setting board size
    int getBoardSize();
    //Getting board size
    void play(int row, int column);
    //Playing of user
    void play();
    //Playing of computer
    void askUser();
    //Adding to gridlayout panel the user board related asking buttons.
    char change_turn();
    //Changing turn between 'x' and 'o'
    int isEnd();
    //Checking who win
    boolean is_valid_move(int x, int y, char letter);
    //Checking if that move is valid for recursive algorith
    int check_full(int x, int y, int[][] visitedplaces, char check, int score);
    //Recursive algorithm for if someone has finished the game.
    void makeLettersCapital(char check, int[][] visitedplaces);
    //When game ends, make all letters capital.
    void readFromFile(String file);
    //Reading from file when read button is clicked.
    void writeToFile(String file);
    //Writing to file when load button is clicked.
}