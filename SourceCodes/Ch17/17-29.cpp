// This is the implementation file for Display 17.29.
// This is the implementation of the class Set.
// It is the same as the file set.cpp.

#include <iostream>
#include "listtools.h"
#include "set.h"
using std::cout;
using std::endl;
using LinkedListSavitch::Node;
using LinkedListSavitch::search;
using LinkedListSavitch::headInsert;

namespace SetSavitch
{
   template<class T>
   Set<T>::Set()
   {
    head = NULL;
   }

   template<class T>
   Set<T>::~Set()
   {
       Node<T> *toDelete = head;
       while (head != NULL)
       {
         head = head->getLink( );
	 delete toDelete;
	 toDelete = head;
       }
   }

   template<class T>
   bool Set<T>::contains(T target) const
   {
    Node<T>* result = search(head, target);
    if (result == NULL)
       return false;
    else
       return true;
   }

   template<class T>
   void Set<T>::output()
   {
       Node<T> *iterator = head;
       while (iterator != NULL)
       {
	 cout << iterator->getData( ) << " ";
         iterator = iterator->getLink( );
       }
       cout << endl;
   }


   template<class T>
   void Set<T>::add(T item)
   {
    if (search(head, item)==NULL)
    {
      // Only add the target if it's not in the list
      headInsert(head, item);
    }
   }

   template<class T>
   Set<T>* Set<T>::setUnion(const Set<T>& otherSet)
   {
    Set<T> *unionSet = new Set<T>();
    Node<T>* iterator = head;
    while (iterator != NULL)
    {
     unionSet->add(iterator->getData( ));
     iterator = iterator->getLink( );
    }
    iterator = otherSet.head;
    while (iterator != NULL)
    {
     unionSet->add(iterator->getData( ));
     iterator = iterator->getLink( );
    }
    return unionSet;
   }

   template<class T>
   Set<T>* Set<T>::setIntersection(const Set<T>& otherSet)
   {
    Set<T> *interSet = new Set<T>();
    Node<T>* iterator = head;
    while (iterator != NULL)
    {
       if (otherSet.contains(iterator->getData( )))
       {
       	interSet->add(iterator->getData( ));
       }
       iterator = iterator->getLink( );
    }
    return interSet;
   }
} // SetSavitch

