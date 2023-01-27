//Program to demonstrate the functions newLine and getInput.
#include <iostream>
using namespace std;

void newLine( );
//Discards all the input remaining on the current input line.
//Also discards the '\n' at the end of the line.

void getInt(int& number);
//Sets the variable number to a
//value that the user approves of.

int main( )
{
    int n;

    getInt(n);
    cout << "Final value read in = " << n << endl
         << "End of demonstration.\n";

    return 0;
}

//Uses iostream:
void newLine( )
{
    char symbol;
    do
    {
        cin.get(symbol);
    } while (symbol != '\n');
}

//Uses iostream:
void getInt(int& number)
{
    char ans;
    do
    {
        cout << "Enter input number: ";
        cin >> number;
        cout << "You entered " << number
             << " Is that correct? (yes/no): ";
        cin >> ans;
        newLine( );
    } while ((ans == 'N') || (ans == 'n'));
}
