import javax.swing.*;

public class HexGameTest {
    public static void main(String args[]){
        HexGameClass game0 = new HexGameClass();
        game0.setBoardSize(10);
        HexGameClass game1 = (HexGameClass)game0.clone();   //Using clone()
        game1.setBoardSize(5);

        System.out.println("BoardSize in game0 = "+game0.getBoardSize());
        System.out.println("BoardSize in game1 = "+game1.getBoardSize());
        if(game0.getBoardSize() != game1.getBoardSize())   
            System.out.println("Sizes are not same! Clone method works");

        game1.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        game1.setSize( 1050, 650 ); // set frame size
        game1.setLocationRelativeTo(null);
        game1.setVisible( true );
        game1.setResizable(false); // Making not resizable
    }   //End of main
}   //End of class