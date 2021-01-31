import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import java.io.*; //For file handling
@SuppressWarnings("unused")

public class HexGameClass extends JFrame implements HexGame, ActionListener, Cloneable {
    /** GUI RELATED PRIVATES **/
    private static final long serialVersionUID = 1L;
    private JPanel panelHolder = new JPanel();
    private JPanel panel1 = new JPanel();
    private JPanel panel2 = new JPanel();
    private JPanel panel3 = new JPanel();
    private JLabel label = new JLabel("<html>Welcome to<br>HexGame<br>x's turn</html>");
    private CardLayout c = new CardLayout();
    private JTextField text1 = new JTextField("Choose how many player game you want: ");
    private JTextField text2 = new JTextField("Enter board size: (Between 6-12)");
    private JTextField board_size_text = new JTextField(10);
    private JRadioButton player1_RadioButton = new JRadioButton("1 Player Game", true);
    private JRadioButton player2_RadioButton = new JRadioButton("2 Players Game", true);
    private ButtonGroup radioGroup = new ButtonGroup();
    private JButton startGameButton = new JButton("Start Game");
    private JButton setSizeButton = new JButton("Set board size");
    private JButton loadButton = new JButton("LOAD");
    private JButton saveButton = new JButton("SAVE");
    private JButton undoButton = new JButton("UNDO");
    private JButton resetButton = new JButton("RESET");
    private JButton oldMove = new JButton(); // Holding old moves for undo.
    private JButton oldMove2 = new JButton(); // Holding old moves for undo in 1Player game.
    private JButton buttons[][] = new JButton[12][12];
    private GridLayout gridLayout = new GridLayout(3, 3); 
    private String errorMessage = "Please enter something between 6-12";

    /** NON GUI RELATED PRIVATES **/
    private char turn = 'x'; // Whose turn.
    private int boardSize = 5; // Board size
    private int how_many_player = 1; // How many players will be game

    // CONSTRUCTOR
    public HexGameClass() {
        super("HexGame by Suleyman Golbol!!"); // Title of the game.

        setSizeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                String message = "";
                try{
                    message = String.format("Entered board size is %s", board_size_text.getText());
                    boardSize = Integer.parseInt(board_size_text.getText());
                    if (boardSize > 12 || boardSize < 6) {
                        message = "Error! Please enter board size something between 6-12\n";
                        boardSize = 5; // Making boardSize something not in range.
                    }
                    JOptionPane.showMessageDialog(null, message);
                }
                catch(NumberFormatException n){
                    message = "Error! Please enter board size something between 6-12\n";
                    JOptionPane.showMessageDialog(null, message);
                }
            }
        });
        panel1.setLayout(gridLayout);   // Panel uses grid layout.

        askUser(); // Asking input values like boardsize and how many player game.
        panel1.add(player1_RadioButton);
        panel1.add(player2_RadioButton); // Adding buttons to panel.
        panel1.add(text2); // Adding to the frame.
        panel1.add(board_size_text); // board size handling asking user
        panel1.add(setSizeButton);
        panel1.add(startGameButton);

        startGameButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent act) {
                if (boardSize < 6 || boardSize > 12) {
                    JOptionPane.showMessageDialog(null, errorMessage);
                    return;
                }
                addBoardToGame();
                c.show(panelHolder, "2");
            }
        });
        // Using Panelholder.
        panelHolder.setLayout(c);
        panelHolder.add(panel1, "1");
        panelHolder.add(panel2, "2");
        c.show(panelHolder, "1");
        add(panelHolder);   //Adding panel to frame.
    }
    
    @Override
    public Object clone() {
        try {
            HexGameClass clonedObject = (HexGameClass)super.clone(); 
            return new HexGameClass();
            //no need super.clone() because we returning new object
        }
        catch(CloneNotSupportedException e){
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void addBoardToGame() {
        panel2.setLayout(null);
        panel2.setBackground(new Color(251, 195, 134));

        int x = 24, y = 20;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                buttons[i][j] = new JButton(".");
                buttons[i][j].addActionListener(this); // registerimg to the listener.
                buttons[i][j].setBounds(x, y, 46, 46);
                panel2.add(buttons[i][j]); // Adding the buttons to the JFrame.
                x += 47;
            }
            y += 47;
            x = (i + 2) * 24;
        }
        addToPanel3(); // Adding SAVE,LOAD,BACK buttons.
    }

    @Override
    public void addToPanel3(){  //Adding to panel for undo,load,reset and save.
        panel3.setLayout(null);
        panel3.setBackground(new Color(101,76,47));
        panel3.setBounds(880, 20, 150, 500);

        loadButton.setBounds(883, 23, 145, 55);             //Load button's placement
        loadButton.addActionListener(new ActionListener(){  //Load button's action listener if clicked
            @Override
            public void actionPerformed(ActionEvent act){
                JFileChooser file = new JFileChooser();
                file.setCurrentDirectory( new File(".") );  //Setting current directory.
                int isOpen = file.showOpenDialog(null);  //Selecting file form computer.
                if(isOpen == 0){    //That means it is opened.
                    readFromFile( file.getSelectedFile().getAbsolutePath() );
                }

            }
        } );

        saveButton.setBounds(883, 83, 145, 55);            //Save button's placement
        saveButton.addActionListener(new ActionListener(){  //Save button's action listener if clicked
                @Override
                public void actionPerformed(ActionEvent act){
                    JFileChooser file = new JFileChooser();
                    file.setCurrentDirectory( new File(".") );  //Setting current directory.
                    int isOpen = file.showSaveDialog(null);  //Selecting file form computer.
                    if(isOpen == 0){    //That means it is opened.
                        writeToFile( file.getSelectedFile().getAbsolutePath() );
                    }
                    
                }
        } );

        undoButton.setBounds(883, 143, 145, 55);            //Undo button's placement
        undoButton.addActionListener(new ActionListener(){  //Undo button's action listener if clicked
            @Override
            public void actionPerformed(ActionEvent act){
                if(oldMove.getText() != "."){
                    oldMove.setText(".");
                    oldMove.setForeground(new Color(0,0,0));
                    oldMove2.setText(".");
                    oldMove2.setForeground(new Color(0,0,0));
                    turn = change_turn();
                    if(how_many_player == 1) turn = change_turn();
                    label.setText(turn + "'s turn");
                }
            }
        } );

        resetButton.setBounds(883, 203, 145, 55);           //Reset button's placement
        resetButton.addActionListener(new ActionListener(){ //Reset button's action listener if clicked
            @Override
            public void actionPerformed(ActionEvent act){
                for(int i=0; i<boardSize; i++)
                    for(int j=0; j<boardSize; j++){
                        buttons[i][j].setForeground(new Color(0,0,0));
                        buttons[i][j].setText(".");
                    }
                turn = 'x';
                label.setText(turn + "'s turn");
            }
        } );

        label.setFont(new Font("Verdana", Font.BOLD, 15));  //Label's size and style.
        label.setForeground(new Color(204,255,0));          //Label color gray.
        label.setBounds(913, 353, 145, 55);                 //Label's placement.
        //Adding all them to panel.
        panel2.add(loadButton);
        panel2.add(saveButton);
        panel2.add(undoButton);
        panel2.add(resetButton);
        panel2.add(label);
        panel2.add(panel3, BorderLayout.EAST);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        for(int i=0; i<boardSize; i++){
            for(int j=0; j<boardSize; j++){
                if( e.getSource() == buttons[i][j] ){
                    if(turn == 'x'){        //x playing
                        if(buttons[i][j].getText().equals(".")){
                            if(how_many_player == 2 && isEnd() == 0)    
                                play(i,j); //User plays if 2 players game.
                            else if(how_many_player == 1 && isEnd() == 0){
                                play(i,j); //User plays if 1 player game.
                                if(isEnd() != 0) return;
                                play();    //Computer plays if 1 player game.
                            }
                        }
                    }
                    else{       //o playing in 2 players game.
                        if(buttons[i][j].getText().equals(".") && isEnd() == 0 ){
                            play(i,j);
                        }
                    }
                }

            }
        }
    }

    @Override
    public void askUser(){
        text1.setEditable( false );     //Question texts are non editable text.
        text2.setEditable( false );
        panel1.add(text1);
        add(player1_RadioButton);   
        add(player2_RadioButton);   //Adding buttons to JFrame

        radioGroup.add( player1_RadioButton );
        radioGroup.add( player2_RadioButton );
        //These will work when click on the radio buttons.
        player1_RadioButton.addItemListener( new Handler_for_RadioButton() );
        player2_RadioButton.addItemListener( new Handler_for_RadioButton() );
    }
    //Inner class for radio button handling
    private class Handler_for_RadioButton implements ItemListener{
        public void itemStateChanged( ItemEvent e ){
            if(e.getSource() == player1_RadioButton)
                how_many_player = 1;
            else if(e.getSource() == player2_RadioButton) 
                how_many_player = 2;
        } 
    }

    @Override
    public void play(int row, int column) { // Play of computer
        label.setText(change_turn() + "'s turn"); // x played, sp show that it's turn of o
        if (turn == 'x')
            buttons[row][column].setForeground(new Color(255, 4, 3));
        else if (turn == 'o')
            buttons[row][column].setForeground(new Color(1, 2, 253));
        buttons[row][column].setText(Character.toString(turn));
        oldMove = buttons[row][column];
        if (isEnd() != 0) {
            if (turn == 'x')
                label.setText("<html>X WON<br>Game over<html>"); // Using html for new line in JLabel
            if (turn == 'o')
                label.setText("<html>O WON<br>Game over<html>"); // Using html for new line in JLabel
            return;
        }
        turn = change_turn();
    }

    @Override
    public void play() { // Play of computer
        Random random = new Random();
        int randnum, randnum2;
        do {
            randnum = 1 + random.nextInt(boardSize); // Random number for cell column number.
            randnum2 = 1 + random.nextInt(boardSize); // Random number for cell row letter.
        } while (!(buttons[randnum - 1][randnum2 - 1].getText().equals(".")));

        buttons[randnum - 1][randnum2 - 1].setForeground(new Color(1, 2, 253));
        buttons[randnum - 1][randnum2 - 1].setText("o"); // Set status to 'o'.
        label.setText("x's turn"); // o played, sp show that it's turn of x
        turn = change_turn();
        oldMove2 = buttons[randnum - 1][randnum2 - 1]; // Put this value for Undo.
        if (isEnd() != 0) {
            label.setText("<html>O WON<br>Game over<html>");
            return;
        }
    }

    @Override
    public char change_turn(){
        char flag = 'x';
        if(turn=='x')	flag = 'o';
        return flag;
    }

    @Override
    public int isEnd(){
        int[][] visitedplaces = new int[13][13];
        for(int i=0; i<13; i++)
            for(int j=0; j<13; j++)
                visitedplaces[i][j] = 0;
        int score = 0;
        for(int m=0; m<boardSize; m++){
            //Checking x if wom
            for(int i=0; i<boardSize; i++)
                for(int j=0; j<boardSize; j++)
                    visitedplaces[i][j]=0;
            if(buttons[m][0].getText().equals("x") || buttons[m][0].getText().equals("X"))
                if( check_full(0, m, visitedplaces, 'x', score) == 2)	return 2;
    
            //Checking o if won
            for(int i=0; i<boardSize; i++)
                for(int j=0; j<boardSize; j++)
                    visitedplaces[i][j]=0;
    
            if(buttons[0][m].getText().equals("o") || buttons[0][m].getText().equals("O"))
                if( check_full(m, 0, visitedplaces, 'o', score) == 2)	return 3;
        }
    
        return 0;
    }

    @Override
    public boolean is_valid_move(int x, int y, char letter){
        if( x>=0 && y>=0 && x<boardSize && y<boardSize && (buttons[y][x].getText().equals( Character.toString(letter) )
             || buttons[y][x].getText().equals( Character.toString(letter-32) ) ) )	
            return true;
    
        return false;
    }

    @Override
    public int check_full(int x, int y, int[][] visitedplaces, char check, int score){
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
                if (visitedplaces[m][boardSize-1] == 0 && (buttons[m][boardSize-1].getText().equals("x") || buttons[m][boardSize-1].getText().equals("X")) )
                    { makeLettersCapital('x', visitedplaces); score=100; return 2; }
        }
        
        if(check=='o' && y == boardSize-1 ){
            for(int m=0; m<boardSize; m++)
                if (visitedplaces[boardSize-1][m] == 0 && (buttons[boardSize-1][m].getText().equals("o") || buttons[boardSize-1][m].getText().equals("O")) )
                    { makeLettersCapital('o', visitedplaces); 	return 2; }
        }
                
        else{
                //Recursively finding if it wins with Backtrack technique.
                if( y>=1 && x>=0 )
                    if(visitedplaces[y-1][x+1]==0 && is_valid_move(x+1, y-1, check) == true){
                        visitedplaces[y][x] = 1;
                        score+=5;
                        if (check_full(x+1, y-1, visitedplaces, check, score) != 0) return 2;
                    }
                if( y>=0 && x>=0 )
                    if(visitedplaces[y][x+1]==0 && is_valid_move(x+1, y, check) == true){
                        visitedplaces[y][x] = 1;
                        score+=5;
                        if (check_full(x+1, y, visitedplaces, check, score) != 0) return 2;
                    }
                if( y>=0 && x>=0 )
                    if(visitedplaces[y+1][x]==0 && is_valid_move(x, y+1, check) == true){
                        visitedplaces[y][x] = 1;
                        score+=5;
                        if (check_full(x, y+1, visitedplaces, check, score) != 0) return 2;
                    }
                if( y>=0 && x>=1 )
                    if(visitedplaces[y+1][x-1]==0 && is_valid_move(x-1, y+1, check) == true){
                        score+=5;
                        visitedplaces[y][x] = 1;
                        if (check_full(x-1, y+1, visitedplaces, check, score) != 0) return 2;
                    }
                if( y>=0 && x>=1 )
                    if(visitedplaces[y][x-1]==0 && is_valid_move(x-1, y, check) == true){
                        visitedplaces[y][x] = 1;
                        score+=5;
                        if (check_full(x-1, y, visitedplaces, check, score) != 0) return 2;
                    }
                if( y>=1 && x>=0 )
                    if(visitedplaces[y-1][x]==0 && is_valid_move(x, y-1, check) == true){
                        visitedplaces[y][x] = 1;
                        score+=5;
                        if (check_full(x, y-1, visitedplaces, check, score) != 0) return 2;
                    }			
    
                visitedplaces[y][x]=0;
            }
        return 0;
    }
       
    @Override
    public void makeLettersCapital(char check, int[][] visitedplaces){
        if(check=='x')
            for(int y = 0; y < boardSize; ++y)
                for(int x = 0; x < boardSize; ++x)
                    if( visitedplaces[y][x]==1 ){
                        buttons[y][x].setText("X");
                        if(x==boardSize-2 && buttons[y][boardSize-1].getText().equals("x"))		
                            buttons[y][boardSize-1].setText("X");
                        if(y>=1)
                            if(x==boardSize-2 && buttons[y-1][boardSize-1].getText().equals("x"))
                                buttons[y-1][boardSize-1].setText("X");
                    }
        if(check=='o')
            for(int y = 0; y < boardSize; ++y)
                for(int x = 0; x < boardSize; ++x)
                    if( visitedplaces[y][x]==1 ){
                        buttons[y][x].setText("O");
                        if(y==boardSize-2 && buttons[boardSize-1][x].getText().equals("o"))		
                            buttons[boardSize-1][x].setText("O"); 
                        if(x>=1)
                            if(y==boardSize-2 && buttons[boardSize-1][x-1].getText().equals("o"))
                                    buttons[boardSize-1][x-1].setText("O");
                    }
    }

    @Override
    public void readFromFile(String file){
        String readedLine = "";
        BufferedReader bufferString;
        int oldBoardSize = boardSize;
        try {
            bufferString= new BufferedReader( new FileReader(file) );
            readedLine = bufferString.readLine();   //Reading boardSize
            if     (readedLine.length() == 1)    boardSize = (int)readedLine.charAt(0) - 48;
            else if(readedLine.length() == 2)    boardSize = ((int)readedLine.charAt(0) - 48)*10 + ((int)readedLine.charAt(1) -48);

            readedLine = bufferString.readLine();   //Reading how many player game
            how_many_player = (int)readedLine.charAt(0)-48;

            readedLine = bufferString.readLine();   //Reading whose turn
            turn = readedLine.charAt(0);

            if(oldBoardSize > boardSize){   //Removing from screen the unnecssary buttons.
                for (int i = 0; i < oldBoardSize; i++)  
                    for (int j = 0; j < oldBoardSize; j++)
                        if(i>=boardSize || j>=boardSize)
                            buttons[i][j].setVisible(false);
            }

            int x = 24, y = 20;
            for (int i = 0; i < boardSize; i++) {               //RESET all the button cells.
                for (int j = 0; j < boardSize; j++) {
                    if(j>=oldBoardSize || i>=oldBoardSize){
                        buttons[i][j] = new JButton(".");
                        buttons[i][j].addActionListener(this); // registerimg to the listener.
                        buttons[i][j].setBounds(x, y, 46, 46);
                        panel2.add(buttons[i][j]); // Adding the buttons to the JFrame.
                    }
                    x += 47;
                }
                y += 47;
                x = (i + 2) * 24;
            }
            
            for(int i=0; i<boardSize; i++){  //Reading board cells
                readedLine = bufferString.readLine();
                for(int j=0; j<boardSize; j++){
                    buttons[i][j].setText( Character.toString( readedLine.charAt(j) ) );
                    if     (buttons[i][j].getText().equals("x")) buttons[i][j].setForeground( new Color(255,4,3) );
                    else if(buttons[i][j].getText().equals("o")) buttons[i][j].setForeground( new Color(1,2,253) );
                    else if(buttons[i][j].getText().equals(".")) buttons[i][j].setForeground( new Color(0,0,0) );
                    
                }
            }    

            readedLine = bufferString.readLine();   //Reading oldMove
            oldMove = buttons[ (int)readedLine.charAt(1) -49][ (int)readedLine.charAt(0) - 65];
            oldMove.setText( Character.toString(readedLine.charAt(2)) );
            if     ( Character.toString(readedLine.charAt(2)).equals("x")) oldMove.setForeground( new Color(255,4,3) ); //red
            else if( Character.toString(readedLine.charAt(2)).equals("o")) oldMove.setForeground( new Color(1,2,253) ); //blue

            if(how_many_player == 1){   //Reading oldMove2 for 1 player game(both computer and user)
                readedLine = bufferString.readLine();
                oldMove2 = buttons[ (int)readedLine.charAt(1) -49][ (int)readedLine.charAt(0) - 65];
                oldMove2.setText( Character.toString(readedLine.charAt(2)) );
                if     ( Character.toString(readedLine.charAt(2)).equals("x")) oldMove2.setForeground( new Color(255,4,3) ); //red
                else if( Character.toString(readedLine.charAt(2)).equals("o")) oldMove2.setForeground( new Color(1,2,253) ); //blue
            }
            bufferString.close();
        }  //End of try
        catch (IOException e) {
            e.printStackTrace();
        }   //End of catch
    }      //End of method

    @Override
    public void writeToFile(String file){   //Writing to file
        int y=-1, x=-1, y2=-1, x2=-1;
        BufferedWriter bufferString;
        try {
            bufferString= new BufferedWriter( new FileWriter(file) );
            bufferString.write( Integer.toString(boardSize) );      /*Writing boardSize */ bufferString.write("\n");
            bufferString.write( Integer.toString(how_many_player) ); /*Writing how many player game */ bufferString.write("\n");
            bufferString.write( Character.toString(turn) );   /*Writing whose turn */ bufferString.write("\n");

            for(int i=0; i<boardSize; i++){ //Writing cell states
                for(int j=0; j<boardSize; j++){
                    bufferString.write( buttons[i][j].getText() );
                }
                bufferString.write("\n");
            }

            for(int i=0; i<boardSize; i++){ //Writing old move
                for(int j=0; j<boardSize; j++){
                    if(oldMove == buttons[i][j] ){
                        y = i;
                        x = j;
                    }
                    if(how_many_player == 1 && oldMove2 == buttons[i][j] ){
                        y2 = i;
                        x2 = j;
                    }
                }
            }

            bufferString.write( Character.toString((char)(x + 65)) + (y+1) + oldMove.getText() );   //Writing old move(For ex:  A1x)
            bufferString.write("\n");  
            if(how_many_player==1) 
                bufferString.write( Character.toString((char)(x2 + 65)) + (y2+1) + oldMove2.getText() );   //Writing old move2(computers move too)

            bufferString.close();
        }  //End of try
        catch (IOException e) {
            e.printStackTrace();
        }   //End of catch
    }  //End of method

    public void setBoardSize(int size){
        boardSize = size;
    }

    public int getBoardSize(){
        return boardSize;
    }

}   //End of class.