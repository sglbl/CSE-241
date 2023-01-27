#include <iostream>
#include <cstdlib>
using namespace std;

int main( )
{
    cout << "Hello Out There!\n";
    exit(1);

    cout << "This statement is pointless,\n"
         << "because it will never be executed.\n"
         << "This is just a toy program to illustrate exit.\n";

    return 0;
}