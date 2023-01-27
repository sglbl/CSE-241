// This is the header file for Display 17.28.  This is the interface
// for the class Set, which is a class for a generic set.
// It is the same as the file set.h.

#ifndef SET_H
#define SET_H

#include "listtools.h"
using LinkedListSavitch::Node;

namespace SetSavitch
{
  template<class T>
  class Set
  {
   public:
        Set(); // Initialize empty set

        // Normally a copy constructor and overloaded assignment
        // operator would be included.  They have been omitted
        // to save space.

        virtual ~Set();  // Destructor destroys set

        bool contains(T target) const;
        // Returns true if target is in the set, false otherwise

        void add(T item);
        // Adds a new element to the set

	void output();
	// Outputs the set to the console

	Set<T>* setUnion(const Set<T>& otherSet);
        // Union calling object's set with otherSet
	// and return a pointer to the new set

	Set<T>* setIntersection(const Set<T>& otherSet);
	// Intersect calling object's set with otherSet
	// and return a pointer to the new set
   private:
        Node<T> *head;
  }; // Set
} // SetSavitch
#endif // SET_H
