class DoublyLinkedIntNode
{
public:
    DoublyLinkedIntNode ( ){}
    DoublyLinkedIntNode (int theData, DoublyLinkedIntNode* previous,
 DoublyLinkedIntNode* next)
            : data(theData), nextLink(next), previousLink(previous) {}
    DoublyLinkedIntNode* getNextLink( ) const 
    		{ return nextLink; }
    DoublyLinkedIntNode* getPreviousLink( ) const 
    		{ return previousLink; }
    int getData( ) const 
    		{ return data; }
    void setData(int theData) 
    		{ data = theData; }
    void setNextLink(DoublyLinkedIntNode* pointer) 
    		{ nextLink = pointer; }
    void setPreviousLink(DoublyLinkedIntNode* pointer)
		{ previousLink = pointer; }
private:
    int data;
    DoublyLinkedIntNode *nextLink;
    DoublyLinkedIntNode *previousLink;
};

typedef DoublyLinkedIntNode* DoublyLinkedIntNodePtr;
