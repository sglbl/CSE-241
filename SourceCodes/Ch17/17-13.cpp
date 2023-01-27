#include <cstddef>
#include <iostream>
#include "17-13.h"

using namespace std;

void headInsert(DoublyLinkedIntNodePtr& head, int theData);
void deleteNode(DoublyLinkedIntNodePtr& head, DoublyLinkedIntNodePtr discard);

void headInsert(DoublyLinkedIntNodePtr& head, int theData)
{
 DoublyLinkedIntNode* newHead = new DoublyLinkedIntNode(theData, NULL, head);
 head->setPreviousLink(newHead);
 head = newHead;
}

void deleteNode(DoublyLinkedIntNodePtr& head, DoublyLinkedIntNodePtr discard)
{
	if (head == discard)
	{
		head = head->getNextLink( );
		delete head->getPreviousLink( );
		head->setPreviousLink(NULL);
	}
	else
	{
		DoublyLinkedIntNodePtr prev = discard->getPreviousLink( );
		DoublyLinkedIntNodePtr next = discard->getNextLink( );
		prev->setNextLink(next);
		if (next != NULL)
		{
			next->setPreviousLink(prev);
		}
		delete discard;
	}
}

/*
 * A short test program
 */
int main()
{
	DoublyLinkedIntNode* root = new DoublyLinkedIntNode(3,NULL,NULL);
	headInsert(root, 4);
	headInsert(root, 5);
	headInsert(root, 6);

	deleteNode(root, root->getNextLink()->getNextLink()->getNextLink());
	DoublyLinkedIntNode* i = root;
	while (i!=NULL)
	{
		cout << i->getData() << endl;
		i = i->getNextLink();
	}
}

