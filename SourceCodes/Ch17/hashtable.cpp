// This is the implementation file hashtble.cpp.
// This is the implementation of the class HashTable.

#include <string>
#include "listtools.h"
#include "hashtable.h"

using LinkedListSavitch::Node;
using LinkedListSavitch::search;
using LinkedListSavitch::headInsert;
using std::string;

namespace HashTableSavitch
{
   HashTable::HashTable()
   { 
    for (int i = 0; i < SIZE; i++)
    {
     hashArray[i] = NULL;
    }
   }

   HashTable::~HashTable()
   {
     for (int i=0; i<SIZE; i++)
     {
       Node<string> *next = hashArray[i];
       while (next != NULL)
       {
         Node<string> *discard = next;
	 next = next->getLink( );
	 delete discard;
       }
     }
   }

   int HashTable::computeHash(string s)
   {
    int hash = 0;
    for (int i = 0; i < s.length( ); i++) 
    {
     hash += s[i];
    }
    return hash % SIZE;	
   }

   bool HashTable::containsString(string target) const
   { 
    int hash = this->computeHash(target);
    Node<string>* result = search(hashArray[hash], target);
    if (result == NULL) 
       return false;
    else
       return true;
   }

   void HashTable::put(string s)
   {
    int hash = computeHash(s);
    if (search(hashArray[hash], s)==NULL)
    {
      // Only add the target if it's not in the list
      headInsert(hashArray[hash], s);
    }
   }

} // HashTableSavitch

