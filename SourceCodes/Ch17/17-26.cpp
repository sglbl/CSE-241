// Program to demonstrate use of the HashTable class.
// Same as hashmain.cpp.

#include <string>
#include <iostream>
#include "listtools.cpp"	// Your compiler may compile separately
#include "hashtable.h"
#include "hashtable.cpp"	// Your compiler may compile separately
using std::string;
using std::cout;
using std::endl;
using HashTableSavitch::HashTable;

int main()
{
	HashTable h;

	cout << "Adding dog, cat, turtle, bird" << endl;
	h.put("dog");
	h.put("cat");
	h.put("turtle");
	h.put("bird");
	cout << "Contains dog? "
		<< h.containsString("dog") << endl;
	cout << "Contains cat? "
		<< h.containsString("cat") << endl;
	cout << "Contains turtle? "
		<< h.containsString("turtle") << endl;
	cout << "Contains bird? "
		<< h.containsString("bird") << endl;

	cout << "Contains fish? "
		<< h.containsString("fish") << endl;
	cout << "Contains cow? "
		<< h.containsString("cow") << endl;

	return 0;
}


