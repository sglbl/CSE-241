//Program to demonstrate the iterative version of writeVertical.
#include <iostream>
using std::cout;
using std::endl;

void writeVertical(int n);
//Precondition: n >= 0.
//Postcondition: The number n is written to the screen vertically
//with each digit on a separate line.

int main( )
{
    cout << "writeVertical(3):" << endl;
    writeVertical(3);

    cout << "writeVertical(12):" << endl;
    writeVertical(12);

    cout << "writeVertical(123):" << endl;
    writeVertical(123);

    return 0;
}

//Uses iostream:
void writeVertical(int n)
{
    int nsTens = 1;
    int leftEndPiece = n;
    while (leftEndPiece > 9)
    {
        leftEndPiece = leftEndPiece/10;
        nsTens = nsTens*10;
    }
    //nsTens is a power of ten that has the same number 
    //of digits as n. For example, if n is 2345, then 
    //nsTens is 1000.
 
    for (int powerOf10 = nsTens;
           powerOf10 > 0; powerOf10 = powerOf10/10)
    {
        cout << (n/powerOf10) << endl;
        n = n%powerOf10;
    }
}
