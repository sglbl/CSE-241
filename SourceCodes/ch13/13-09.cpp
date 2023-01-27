//Program to demonstrate the recursive function for binary search.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
const int ARRAY_SIZE = 10;


void search(const int a[], int lowEnd, int highEnd,
                           int key, bool& found, int& location);
//Precondition: a[lowEnd] through a[highEnd] are sorted in increasing 
//order.
//Postcondition: If key is not one of the values a[lowEnd] through 
//a[highEnd], then found == false; otherwise a[location] == key and 
//found == true.

int main( )
{
    int a[ARRAY_SIZE];
    const int finalIndex = ARRAY_SIZE - 1;

    int i;
    for (i = 0; i < ARRAY_SIZE; i++)
        a[i] = 3*i;
    cout << "Array conatins:\n";
    for (i = 0; i < ARRAY_SIZE; i++)
        cout << a[i] << " ";
    cout << endl;

    int key, location;
    bool found;
    cout << "Enter number to be located: ";
    cin >> key;
    search(a, 0, finalIndex, key, found, location);

    if (found)
        cout << key << " is in index location "
             << location << endl;
    else
        cout << key << " is not in the array." << endl;

    return 0;
}

void search(const int a[], int lowEnd, int highEnd,
                           int key, bool& found, int& location)
{
    int first = lowEnd;
    int last = highEnd;
    int mid;

    found = false;//so far
    while ( (first <= last) && !(found) )
    {
        mid = (first + last)/2;
        if (key == a[mid])
        {
            found = true;
            location = mid;
        }
        else if (key < a[mid])
        {
            last = mid - 1;
        }
        else if (key > a[mid])
        {
            first = mid + 1;
        }
    }
}
