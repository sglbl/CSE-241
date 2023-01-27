//Program to demonstrate a reverse iterator.
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::vector<char>::iterator;
using std::vector<char>::reverse_iterator;

int main( )
{
    vector<char> container;

    container.push_back('A');
    container.push_back('B');
    container.push_back('C');

    cout << "Forward:\n";
    iterator p;
    for (p = container.begin( ); p != container.end( ); p++)
        cout << *p << " ";
    cout << endl;

    cout << "Reverse:\n";
    reverse_iterator rp;
    for (rp = container.rbegin( ); rp != container.rend( ); rp++)
        cout << *rp << " ";
    cout << endl;

    return 0;
}
