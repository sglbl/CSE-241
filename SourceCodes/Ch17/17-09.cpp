#include <cstddef>
#include "17-04.cpp"


//Function Declaration

IntNodePtr search(IntNodePtr head, int target);
//Precondition: The pointer head points to the head of a 
//linked list. The pointer variable in the last node is NULL.
//If the list is empty, then head is NULL.
//Returns a pointer that points to the first node that contains the
//target. If no node contains the target, the function returns NULL.


//Function Definition

//Uses cstddef:
IntNodePtr search(IntNodePtr head, int target)
{
        IntNodePtr here = head;

        if (here == NULL) //if empty list
        {
            return NULL;
        }
        else
        {
            while (here->getData( ) != target && here->getLink( ) != NULL)
                here = here->getLink( );

            if (here->getData( ) == target)
                return here;
            else
                return NULL;
        }
}



