public interface Collection<E> {
        Iterator<E> iterator();
        //Returns an iterator over the collection
        boolean add(E e);
        //Ensures that this collection contains the specified element
        boolean addAll(Collection<E> c);
        //Adds all of the elements in the specified collection to this collection
        void clear();
        //Removes all of the elements from this collection
        boolean contains(E e);
        //Returns true if this collection contains the specified element.
        boolean containsAll(Collection<E> c);
        //Returns true if this collection contains all of the elements in the specified collection.
        boolean isEmpty();
        //Returns true if this collection contains no elements. 
        boolean remove(E e);
        //Removes a single instance of the specified element from this collection, if it is present
        boolean removeAll(Collection<E> c);
        //Removes all of this collection's elements that are also contained in the specified collection
        boolean retainAll(Collection<E> c);
        //Retains only the elements in this collection that are contained in the specified collection
        int size();
        //Returns the number of elements in this collection.

}