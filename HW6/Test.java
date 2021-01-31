import java.util.InputMismatchException; //For catching exceptions
import java.util.Scanner;                //For scanning number from user

@SuppressWarnings("rawtypes")
public class Test{
    public static void main(String[] args){
        menu();
    }

    static void menu(){
        boolean loopFlag = true, loopFlag2 = true;
        int choose = 0;
        Scanner scanner = new Scanner(System.in);
        System.out.println("SULEYMAN GOLBOL'S OWN COLLECTION");
        while(loopFlag == true){
            try{
                System.out.println("\n1) Try HashSet Test for Integers\n2) Try HashSet Test for Strings");
                System.out.println("3) Try LinkedList Test for Integers\n4) Try LinkedList Test for Strings");
                System.out.println("5) Try ArrayList Test for Integers\n6) Try ArrayList Test for Strings");
                System.out.println("7) Test Errors.\n8) Exit.");
                System.out.print("Please enter from menu: ");
                choose = scanner.nextInt(); //Getting choose from user
                scanner.nextLine(); //If wrong input, don't give error.
            }
            catch(InputMismatchException e){
                System.out.println("Input is " + e.getMessage() + "\nTry Again!");
                scanner.nextLine();
                continue;        
            }
            
            switch(choose){
                case 1:
                    HashSetTest_Integer(); //Testing HashSet for Integers
                    break;
                case 2:
                    HashSetTest_String(); //Testing HashSet for Strings
                    break;
                case 3:
                    LinkedListTest_Integer(); //Testing LinkedList for Integers
                    break;
                case 4:
                    LinkedListTest_String(); //Testing LinkedList for Strings
                    break;
                case 5:
                    ArrayListTest_Integer(); //Testing ArrayList for Integers
                    break;
                case 6:
                    ArrayListTest_String(); //Testing ArrayList for Strings
                    break;
                case 7:
                    loopFlag2 = false;
                    loopFlag = false;
                    break;
                case 8:
                    System.out.println("Good bye!!");
                    loopFlag = false;
                    break;
                default:
                    System.out.println("Error! Try again!");
            }   //End of switch-case
        }   //End of loop
        if(loopFlag2 == false)
            Test_and_See_Errors(); //Testing Reproducing errors.
        scanner.close();
    }   //End of menu

    static void LinkedListTest_Integer(){
        System.out.println("\nTESTING LINKEDLIST ON INTEGERS");
        LinkedList<Integer> ex2 = new LinkedList<Integer>();
        ex2.add(12);
        ex2.add(36);
        ex2.add(13);
        System.out.println( "ex2 is " + ex2.toString() );
        
        LinkedList<Integer> ex1 = new LinkedList<Integer>();
        System.out.println("ADDING TO COLLECTION WITH ADD()");
        ex1.add(12);
        ex1.add(14);
        ex1.add(23);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("ADDING THE SAME NUMBER");      
        ex1.add(14);

        System.out.println("USING CONTAINS(77)");
        System.out.println( ex1.contains(77) );

        System.out.println( "ex1 is " + ex1.toString() );

        System.out.println("USING POLL() ELEMENT() OFFER() ");
        System.out.println("Poll() " + ex1.poll() );
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("Element() " + ex1.element() );
        System.out.println("Offer(59) " + ex1.offer(59) );

        System.out.println("USING ISEMPTY()");
        System.out.println( ex1.isEmpty() );

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("REMOVING AND ADDING OTHER ELEMENT");
        ex1.remove(14);
        ex1.add(38);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING SIZE\nSize is " + ex1.size() );

        System.out.println("USING ITERATOR");
        System.out.println( "ex1 is " + ex1.toString() );

        Iterator<Integer> iter = ex1.iterator();
        System.out.println("USING NEXT() ON ITERATOR");
        System.out.println( iter.next() );
        /*System.out.println("USING REMOVE() ON ITERATOR");
        iter.remove(); */
        System.out.println( "ex1 is " + ex1.toString() );

        ex1.add(12);
        Iterator iter2 = ex1.iterator();
        System.out.println("ITERING ON LINKEDLIST TO SEE EVERY ELEMENT ( I added 12 )");
        while(iter2.hasNext()){
            System.out.print( iter2.next() + " ");
        }System.out.println();

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println( "ex2 is " + ex2.toString() );
        System.out.println("USING REMOVEALL() with ex1 and ex2");
        ex1.removeAll(ex2);
        System.out.println( "ex1 is (AFTER REMOVEALL) " + ex1.toString() );
        System.out.println("USING RETAINALL() with ex1 and ex2");
        ex1.retainAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING ADDALL");
        ex1.addAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING CONTAINSALL with ex1 and ex2");
        System.out.println( ex1.containsAll(ex2) );
        System.out.println("USING CLEAR()");
        ex1.clear();
        System.out.println( "ex1 is " + ex1.toString() );

    }


    static void LinkedListTest_String(){
        System.out.println("\nTESTING LINKEDLIST ON STRINGS");
        LinkedList<String> ex2 = new LinkedList<String>();
        ex2.add("Suleyman");
        ex2.add("Golbol");
        ex2.add("No1801042656");
        System.out.println( "ex2 is " + ex2.toString() );
        
        LinkedList<String> ex1 = new LinkedList<String>();
        System.out.println("ADDING TO COLLECTION");
        ex1.add("Jackson");
        ex1.add("Ben10");
        ex1.add("Teller");
        System.out.println( "ex1 is " + ex1.toString() );

        System.out.println("ADDING THE SAME STRING");
        ex1.add("Ben10");
        System.out.println("USING CONTAINS()");
        System.out.println( ex1.contains("KEVIN11") );

        System.out.println( "ex1 is " + ex1.toString() );

        System.out.println("USING POLL() ELEMENT() OFFER() ");
        System.out.println("Poll() " + ex1.poll() );
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("Element() " + ex1.element() );
        System.out.println("Offer(Kevin11) " + ex1.offer("Kevin11") );

        System.out.println("USING ISEMPTY()");
        System.out.println( ex1.isEmpty() );

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("REMOVING AND ADDING OTHER ELEMENT");
        System.out.println("Remove" + ex1.remove("Teller") );
        System.out.println("Add" +  ex1.add("Micheal")   );
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING SIZE\nSize is " + ex1.size() );

        System.out.println("USING ITERATOR");
        System.out.println( "ex1 is " + ex1.toString() );

        Iterator<String> iter = ex1.iterator();
        System.out.println("USING NEXT() ON ITERATOR");
        System.out.println( iter.next() );
        /*System.out.println("USING REMOVE() ON ITERATOR");
        iter.remove(); */
        System.out.println( "ex1 is " + ex1.toString() );

        System.out.println("ADDING Suleyman TO ITERATOR ");
        ex1.add("Suleyman");
        Iterator iter2 = ex1.iterator();
        System.out.println("ITERING ON LINKEDLIST TO SEE EVERY ELEMENT (I added Suleyman)");
        while(iter2.hasNext()){
            System.out.print( iter2.next() + " ");
        }System.out.println();

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println( "ex2 is " + ex2.toString() );
        System.out.println("USING REMOVEALL() with ex1 and ex2");
        ex1.removeAll(ex2);
        System.out.println( "ex1 is (AFTER REMOVEALL) " + ex1.toString() );
        System.out.println("USING RETAINALL() with ex1 and ex2");
        ex1.retainAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING ADDALL");
        ex1.addAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING CONTAINSALL with ex1 and ex2");
        System.out.println( ex1.containsAll(ex2) );
        System.out.println("USING CLEAR()");
        ex1.clear();
        System.out.println( "ex1 is " + ex1.toString() );
    }


    static void ArrayListTest_Integer(){
        System.out.println("\nTESTING ARRAYLIST ON INTEGERS");
        ArrayList<Integer> ex2 = new ArrayList<Integer>();
        ex2.add(12);
        ex2.add(36);
        ex2.add(13);
        System.out.println( "ex2 is " + ex2.toString() );
        
        ArrayList<Integer> ex1 = new ArrayList<Integer>();
        System.out.println("ADDING TO COLLECTION");
        ex1.add(12);
        ex1.add(14);
        ex1.add(23);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("ADDING THE SAME NUMBER");
        
        ex1.add(14);
        System.out.println("USING CONTAINS()");
        System.out.println( ex1.contains(77) );

        System.out.println("USING GET()");
        System.out.println( ex1.get(1) );

        System.out.println("USING ISEMPTY()");
        System.out.println( ex1.isEmpty() );

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("REMOVING AND ADDING OTHER ELEMENT");
        ex1.remove(14);
        ex1.add(38);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING SIZE\nSize is " + ex1.size() );

        System.out.println("USING ITERATOR");
        System.out.println( "ex1 is " + ex1.toString() );

        Iterator<Integer> iter = ex1.iterator();
        System.out.println("USING NEXT() ON ITERATOR");
        iter.next();
        System.out.println("USING REMOVE() ON ITERATOR");
        iter.remove();
        System.out.println( "ex1 is " + ex1.toString() );

        ex1.add(66);
        Iterator iter2 = ex1.iterator();
        System.out.println("ITERING ON ARRAYLIST TO SEE EVERY ELEMENT ( I added 66 )");
        while(iter2.hasNext()){
            System.out.print( iter2.next() + " ");
        }System.out.println();

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println( "ex2 is " + ex2.toString() );
        System.out.println("USING REMOVEALL() with ex1 and ex2");
        ex1.removeAll(ex2);
        System.out.println( "ex1 is (AFTER REMOVEALL) " + ex1.toString() );
        System.out.println("USING RETAINALL() with ex1 and ex2");
        ex1.retainAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING ADDALL");
        ex1.addAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING CONTAINSALL with ex1 and ex2");
        System.out.println( ex1.containsAll(ex2) );
        System.out.println("USING CLEAR()");
        ex1.clear();
        System.out.println( "ex1 is " + ex1.toString() );
    }


    static void ArrayListTest_String(){
        System.out.println("\nTESTING ARRAYLIST ON STRINGS");
        ArrayList<String> ex2 = new ArrayList<String>();
        ex2.add("Suleyman");
        ex2.add("Golbol");
        ex2.add("No1801042656");
        System.out.println( "ex2 is " + ex2.toString() );
        
        ArrayList<String> ex1 = new ArrayList<String>();
        System.out.println("ADDING TO COLLECTION");
        ex1.add("Jackson");
        ex1.add("Ben10");
        ex1.add("Teller");
        System.out.println( "ex1 is " + ex1.toString() );

        System.out.println("ADDING THE SAME STRING");
        ex1.add("Ben10");
        System.out.println("USING CONTAINS()");
        System.out.println( ex1.contains("KEVIN11") );

        System.out.println("USING GET()");
        System.out.println( ex1.get(1) );

        System.out.println("USING ISEMPTY()");
        System.out.println( ex1.isEmpty() );

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("REMOVING AND ADDING OTHER ELEMENT");
        System.out.println( ex1.remove("Teller") );
        System.out.println( ex1.add("Micheal")   );
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING SIZE\nSize is " + ex1.size() );

        System.out.println("USING ITERATOR");
        System.out.println( "ex1 is " + ex1.toString() );

        Iterator<String> iter = ex1.iterator();
        System.out.println("USING NEXT() ON ITERATOR");
        iter.next();
        System.out.println("USING REMOVE() ON ITERATOR");
        iter.remove();
        System.out.println( "ex1 is " + ex1.toString() );

        System.out.println("ADDING Suleyman TO ITERATOR ");
        ex1.add("Suleyman");
        Iterator iter2 = ex1.iterator();
        System.out.println("ITERING ON ARRAYLIST TO SEE EVERY ELEMENT");
        while(iter2.hasNext()){
            System.out.print( iter2.next() + " ");
        }System.out.println();

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println( "ex2 is " + ex2.toString() );
        System.out.println("USING REMOVEALL() with ex1 and ex2");
        ex1.removeAll(ex2);
        System.out.println( "ex1 is (AFTER REMOVEALL) " + ex1.toString() );
        System.out.println("USING RETAINALL() with ex1 and ex2");
        ex1.retainAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING ADDALL");
        ex1.addAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING CONTAINSALL with ex1 and ex2");
        System.out.println( ex1.containsAll(ex2) );
        System.out.println("USING CLEAR()");
        ex1.clear();
        System.out.println( "ex1 is " + ex1.toString() );
    }


    static void HashSetTest_String(){
        System.out.println("\nTESTING HASHSET ON STRINGS");
        HashSet<String> ex2 = new HashSet<String>();
        ex2.add("Suleyman");
        ex2.add("Golbol");
        ex2.add("No1801042656");
        System.out.println( "ex2 is " + ex2.toString() );
        
        HashSet<String> ex1 = new HashSet<String>();
        System.out.println("ADDING TO COLLECTION");
        ex1.add("Jackson");
        ex1.add("Teller");
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("ADDING THE SAME NAME (Which won't be add)");
        ex1.add("Ben10");
        ex1.add("Ben10");
        System.out.println("USING CONTAINS()");
        System.out.println( ex1.contains("KEVIN11") );

        System.out.println("USING ISEMPTY()");
        System.out.println( ex1.isEmpty() );

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("REMOVING AND ADDING OTHER ELEMENT");
        ex1.remove("Teller");
        ex1.add("Micheal");
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING SIZE\nSize is " + ex1.size() );

        System.out.println("USING ITERATOR");
        System.out.println( "ex1 is " + ex1.toString() );

        Iterator<String> iter = ex1.iterator();
        System.out.println("USING NEXT() ON ITERATOR");
        iter.next();
        System.out.println("USING REMOVE() ON ITERATOR");
        iter.remove();
        System.out.println( "ex1 is " + ex1.toString() );

        System.out.println("ADDING Suleyman TO ITERATOR ");
        ex1.add("Suleyman");
        Iterator iter2 = ex1.iterator();
        System.out.println("ITERING ON HASHSET TO SEE EVERY ELEMENT WITH HASNEXT");
        while(iter2.hasNext()){
            System.out.print( iter2.next() + " ");
        }System.out.println();

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println( "ex2 is " + ex2.toString() );
        System.out.println("USING REMOVEALL() with ex1 and ex2");
        ex1.removeAll(ex2);
        System.out.println( "ex1 is (AFTER REMOVEALL) " + ex1.toString() );
        System.out.println("USING RETAINALL() with ex1 and ex2");
        ex1.retainAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING ADDALL");
        ex1.addAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING CONTAINSALL with ex1 and ex2");
        System.out.println( ex1.containsAll(ex2) );
        System.out.println("USING CLEAR()");
        ex1.clear();
        System.out.println( "ex1 is " + ex1.toString() );
    }


    static void HashSetTest_Integer(){
        System.out.println("\nTESTING HASHSET ON INTEGERS");
        HashSet<Integer> ex2 = new HashSet<Integer>();
        ex2.add(12);
        ex2.add(36);
        ex2.add(13);
        System.out.println( "ex2 is " + ex2.toString() );
        
        HashSet<Integer> ex1 = new HashSet<Integer>();
        System.out.println("ADDING TO COLLECTION");
        ex1.add(12);
        ex1.add(23);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("ADDING THE SAME NUMBER (Which won't be add)");
        ex1.add(14);
        ex1.add(14);
        System.out.println("USING CONTAINS()");
        System.out.println( ex1.contains(77) );

        System.out.println("USING ISEMPTY()");
        System.out.println( ex1.isEmpty() );

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("REMOVING AND ADDING OTHER ELEMENT");
        ex1.remove(14);
        ex1.add(38);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING SIZE\nSize is " + ex1.size() );

        System.out.println("USING ITERATOR");
        System.out.println( "ex1 is " + ex1.toString() );

        Iterator<Integer> iter = ex1.iterator();
        System.out.println("USING NEXT() ON ITERATOR");
        iter.next();
        System.out.println("USING REMOVE() ON ITERATOR");
        iter.remove();
        System.out.println( "ex1 is " + ex1.toString() );

        ex1.add(66);
        Iterator iter2 = ex1.iterator();
        System.out.println("ITERING ON HASHSET TO SEE EVERY ELEMENT ( I added 66 )");
        while(iter2.hasNext()){
            System.out.print( iter2.next() + " ");
        }System.out.println();

        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println( "ex2 is " + ex2.toString() );
        System.out.println("USING REMOVEALL() with ex1 and ex2");
        ex1.removeAll(ex2);
        System.out.println( "ex1 is (AFTER REMOVEALL) " + ex1.toString() );
        System.out.println("USING RETAINALL() with ex1 and ex2");
        ex1.retainAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING ADDALL");
        ex1.addAll(ex2);
        System.out.println( "ex1 is " + ex1.toString() );
        System.out.println("USING CONTAINSALL with ex1 and ex2");
        System.out.println( ex1.containsAll(ex2) );
        System.out.println("USING CLEAR()");
        ex1.clear();
        System.out.println( "ex1 is " + ex1.toString() );
    }


    static void Test_and_See_Errors(){
        int choose2 = 0;
        Scanner scanner2 = new Scanner(System.in);
        try{
            System.out.println("\n1) See example error in HashSet\n2) See example error in LinkedList");
            System.out.print("3) See example error in ArrayList\nPlease enter from menu: ");
            choose2 = scanner2.nextInt(); //Getting choose from user
            scanner2.close();
        }
        catch(InputMismatchException e){
            System.out.println("Input is " + e.getMessage());
            scanner2.nextLine();
        }
        
        switch(choose2){   //SOME EXAMPLES OF ERRORS
            case 1:
                HashSet<Integer> ex1 = new HashSet<Integer>();
                ex1.add(12); ex1.add(23);   ex1.add(14);
                System.out.println( "ex1 is " + ex1.toString() );
                Iterator<Integer> iter = ex1.iterator();
                System.out.println("USING ITERATOR");
                System.out.println("USING REMOVE() WITHOUT USING NEXT() ON ITERATOR(Which should give error)");
                iter.remove();
                break;
            case 2:
                System.out.println("\nTESTING LINKEDLIST ON STRINGS");
                LinkedList<String> ex2 = new LinkedList<String>();
                System.out.println("\nPOLL() WITHOUT ADD ANYTHING ( Which will give error)");
                ex2.poll();    
                break;
            case 3:
                System.out.println("\nTESTING ARRAYLIST WITHOUT ADDING ANYTHING (Which will give error)");
                ArrayList<Integer> ex3 = new ArrayList<Integer>();
                System.out.println( ex3.get(71) );
                break;
            default:
                System.out.println("Wrong input!");
        }
    
        
    }


} //End of Test class.