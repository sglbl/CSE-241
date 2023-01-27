#include <iostream>
using namespace std;

int* doubler(int a[], int size);
//Precondition; size is the size of the array a.
//All indexed variables of a have values.
//Returns: a pointer to an array of the same size as a in which
//each indexed variable is double the corresponding element in a.

int main( )
{
    int a[] = {1, 2, 3, 4, 5};
    int* b;

    b = doubler(a, 5);

    int i;
    cout << "Array a:\n";
    for (i = 0; i < 5; i++)
        cout << a[i] << " ";
    cout << endl;

    cout << "Array b:\n";
    for (i = 0; i < 5; i++)
        cout << b[i] << " ";
    cout << endl;

    delete[] b;
    return 0;
}

int* doubler(int a[], int size)
{
    int* temp = new int[size];

    for (int i =0; i < size; i++)
        temp[i] = 2*a[i];

    return temp;
}
