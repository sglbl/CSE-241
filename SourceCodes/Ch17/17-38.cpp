//Demonstration program for the Tree template class.
#include <iostream>
#include "tree.h"
#include "tree.cpp"
using std::cout;
using std::cin;
using std::endl;
using TreeSavitch::SearchTree;

int main( )
{
    SearchTree<int> t;

    cout << "Enter a list of nonnegative integers.\n"
         << "Place a negative integer at the end.\n";
    int next;
    cin >> next;
    while (next >= 0)
    {
        t.insert(next);
        cin >> next;
    }

    cout << "In sorted order: \n";
    t.inOrderShow( );
    cout << endl;

    return 0;
}