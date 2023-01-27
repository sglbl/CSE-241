//Program to demonstrate the recursive function for binary search.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
const int ARRAY_SIZE = 10;


void search(const int a[], int first, int last,
                    int key, bool& found, int& location);
//Precondition: a[first] through a[last] are sorted in increasing order.
//Postcondition: if key is not one of the values a[first] through a[last], 
//then found == false; otherwise a[location] == key and found == true.


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

void search(const int a[], int first, int last,
                          int key, bool& found, int& location)
{
    int mid;
    if (first > last)
    {
        found = false;
    }
    else
    {
        mid = (first + last)/2;

        if (key == a[mid])
        {
            found = true;
            location = mid;
        }
        else if (key < a[mid])
        {
            search(a, first, mid - 1, key, found, location);
        }
        else if (key > a[mid])
        {
            search(a, mid + 1, last, key, found, location);
        }
    }
}
