import java.util.NoSuchElementException;

public class Iterator<E> {
    private int current;
    private boolean flag_illegalState = true;
    private E[] collect;
    private Collection<E> collection_to_pass;

    public Iterator(Collection<E> collection_to_pass2, E[] obj){
        collect = null;
        collect = obj;
        collection_to_pass = collection_to_pass2;
        current = 0; //Making current 0 again.
    }

	public boolean hasNext() {
        if(current == collect.length)
            return false;
        else
            return true;
    }

	public E next(){
        flag_illegalState = false;
        boolean flag = false;
        if(hasNext() == true){
            flag = true;
        }
        if(flag == false){
            flag_illegalState = true; //Because IllegalStateException only happens when next() is not called or last next() call.
            throw new NoSuchElementException();
        }
        return (E)collect[current++];
    }

    public void remove(){
        boolean flag_of_queue = false;
        if( collection_to_pass instanceof Queue  == true)
            flag_of_queue = true;
        if(flag_of_queue == true)   //Because Queue doesn't have a option to remove using iterator.
            throw new UnsupportedOperationException("Error happened because Iterator can't remove Queue element!!");
        if(flag_illegalState == true)
            throw new IllegalStateException("Without using next() method you cannot remove with iterator! It is a rule of Java.");
        try {
            collection_to_pass.remove( (E)collect[current] );
        }
        catch(IndexOutOfBoundsException ex) {
            System.out.println("Eroor catched in Iterator removing");
        }
        
    }

}