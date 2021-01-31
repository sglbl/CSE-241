@SuppressWarnings("unchecked")
public class HashSet<E> implements Set<E> {
    private E[] obj;

    @Override
    public Iterator<E> iterator() {
        Iterator<E> myOwnIter= new Iterator<>( (HashSet<E>)this, obj);
        return myOwnIter;
    }

    @Override
    public String toString(){       //Function to print. (Overriding from Object class)
        String thisCol = "[ ";
        int i=0;
        while(i < size() ){
            thisCol += obj[i] + " ";
            i++;
        }
    
        return thisCol + "]";
    }

    @Override
    public boolean add(E e) {
        int i;
        if( size() == 0 ){
            obj = (E[])new Object[size()+1];
            obj[0] = e;
            return true;
        }
        for(E i2: obj){  //If there is same element don't add it.
            if(e == i2)
                return false;
        }

        E[] temp = (E[])new Object[size() + 1]; //Copying to temp and adding e.
        i=0;
        while( i++ < size() )
            temp[i-1] = obj[i-1];
        temp[size()] = e;

        int size = size();

        obj = (E[])new Object[size + 1];
        i=0;
        while( i++ < size() )
            obj[i-1] = temp[i-1];
        
        return true;
    }

    @Override
    public void clear() {
        //System.out.println("Clearing");
        obj = null;
    }

    @Override
    public boolean contains(E e) {
        int size = size();
        int i=0;
        while( i++ < size ){
            if(e == obj[i-1])   
                return true;
        }
        return false;
    }

    @Override
    public boolean isEmpty() {
        if(size() == 0)
            return true;
        return false;
    }

    @Override
    public boolean remove(E e){
        int size = size();
        int i_temp = -1;

        for(int i=0; i<size; i++)
            if(obj[i] == e)
                i_temp = i;
        if(i_temp == -1)    //That means couldn't find e, so return false.
            return false; 

        Object[] temp = new Object[size()];
        for(int i=0; i<size; i++)
            temp[i] = obj[i];
        clear();    //Clearing object
        for(int i=0; i<size; i++){  //Adding without the deleted one.
            if(i == i_temp) 
                continue;
            add( (E) temp[i] );
        }

        return true;
    }

    @Override
    public boolean addAll(Collection<E> c) { //Adding everything in c collection to my obj.
        Iterator<E> iterator;
        try{    
            for(iterator = c.iterator(); iterator.hasNext(); add( iterator.next() ) ) 
                {/* BODY INTENTIONALLY EMPTY */ }  //Calling iterator() function. It will return new Iterator()
        }
        catch(UnsupportedOperationException ex){
            throw new UnsupportedOperationException("Unsupoorted operation happened!!");
        }
        return true;
    }

    @Override
    public boolean containsAll(Collection<E> c) {
        Iterator<E> iterator;
        boolean containing = true;
        try{     //Calling iterator() function. It will return new Iterator()
            for(iterator = c.iterator(); iterator.hasNext(); containing = contains( iterator.next() ) ) {
                if(containing == false)
                    break;
            }
        }
        catch(UnsupportedOperationException ex){
            throw new UnsupportedOperationException("Unsupoorted operation happened!!");
        }
        
        return true;
    }

    @Override
    public boolean removeAll(Collection<E> c) {
        int size = size();
        int i=0;
        try{
            while( i++ < size ){
                if(c.contains( obj[i-1] ) == true ){  //If contain same things with c, delete from obj.
                    remove( obj[i-1] );
                    i--;
                    size = size();
                }
            }
        }
        catch(UnsupportedOperationException ex){
            throw new UnsupportedOperationException("Unsupoorted operation happened!!");
        }
        return true;
    }

    @Override
    public boolean retainAll(Collection<E> c) {
        int size = size();
        int i=0;
        try{
            while( i++ < size ){
                if(c.contains( obj[i-1] ) == false ){  //If doesn't contain same things with c, delete from obj.
                    remove( obj[i-1] );
                    i--;
                    size = size();
                }
            }
        }
        catch(UnsupportedOperationException ex){
            throw new UnsupportedOperationException("Unsupoorted operation happened!!");
        }
        return true;
    }

    @Override
    public int size() {
        try{
            return obj.length;
        }
        catch(NullPointerException e){  //If null(empty)
            return 0;
        }
    }

}   //End of class