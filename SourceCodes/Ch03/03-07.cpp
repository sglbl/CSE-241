#include <iostream>
using namespace std;

void iceCreamDivision(int number, double totalWeight);
//Outputs instructions for dividing totalWeight ounces of ice cream among
//number customers. If number is 0, only an error message is output.

int main( )
{
    int number;
    double totalWeight;

    cout << "Enter the number of customers: ";
    cin >> number;
    cout << "Enter weight of ice cream to divide (in ounces): ";
    cin >> totalWeight;

    iceCreamDivision(number, totalWeight);

    return 0;
}

void iceCreamDivision(int number, double totalWeight)
{
    double portion;

    if (number == 0)
    {
        cout << "Cannot divide among zero customers.\n";
        return;
    } 
    portion = totalWeight/number;
    cout << "Each one receives " 
         << portion << " ounces of ice cream." << endl;
}
