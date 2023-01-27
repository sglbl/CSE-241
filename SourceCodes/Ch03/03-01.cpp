//Computes the size of a dog house that can be purchased
//given the user’s budget.
#include <iostream>
#include <cmath>
using namespace std;

int main( )
{
    const double COST_PER_SQ_FT = 10.50;
    double budget, area, lengthSide;

    cout << "Enter the amount budgeted for your dog house $";
    cin >> budget;

    area = budget/COST_PER_SQ_FT;
    lengthSide = sqrt(area);

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
       cout << "For a price of $" << budget << endl
         << "I can build you a luxurious square dog house\n"
         << "that is " << lengthSide
         << " feet on each side.\n";

    return 0;
}