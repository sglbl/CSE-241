
// This is the header file hashtable.h.  This is the interface
// for the class HashTable, which is a class for a hash table
// of strings.

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "listtools.h"
using LinkedListSavitch::Node;
using std::string;

namespace HashTableSavitch
{
  const int SIZE = 10;

  class HashTable
  {
   public:
        HashTable(); // Initialize empty hash table

        // Normally a copy constructor and overloaded assignment
        // operator would be included.  They have been omitted
        // to save space.

        virtual ~HashTable();  // Destructor destroys hash table

        bool containsString(string target) const;
        // Returns true if target is in the hash table,
        // false otherwise

        void put(string s);
        // Adds a new string to the hash table

   private:
        Node<string> *hashArray[SIZE];
        static int computeHash(string s);   // Compute hash value for string
  }; // HashTable
} // HashTableSavitch
#endif // HASHTABLE_H

