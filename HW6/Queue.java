public interface Queue<E> extends Collection<E> {

    boolean offer(E e);
    //Inserts the specified element into this queue
    @Override
    boolean add(E e);
    //Inserts the specified element into this queue
    E poll();
    //Retrieves and removes the head of this queue, or throws if this queue is empty.
    E element();
    //Retrieves, but does not remove, the head of this queue.


}
