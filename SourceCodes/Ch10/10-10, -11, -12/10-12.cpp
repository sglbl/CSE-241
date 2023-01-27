//Program to demonstrate the class PFArrayD.
#include <iostream>
using namespace std;

//Objects of this class are partially filled arrays of doubles.
class PFArrayD
{
public:
    PFArrayD( );
    //Initializes with a capacity of 50.

    PFArrayD(int capacityValue);

    PFArrayD(const PFArrayD& pfaObject);

    void addElement(double element);
    //Precondition: The array is not full.
    //Postcondition: The element has been added.

    bool full( ) const { return (capacity == used); }
    //Returns true if the array is full, false otherwise.

    int getCapacity( ) const { return capacity; }

    int getNumberUsed( ) const { return used; }

    void emptyArray( ){ used = 0; }
    //Empties the array.

    double& operator[](int index);
    //Read and change access to elements 0 through numberUsed - 1.

    PFArrayD& operator =(const PFArrayD& rightSide);

    ~PFArrayD( );
private:
    double *a; //for an array of doubles.
    int capacity; //for the size of the array.
    int used; //for the number of array positions currently in use.

};

void testPFArrayD( );
//Conducts one test of the class PFArrayD.

int main( )
{
    cout << "This program tests the class PFArrayD.\n";

    char ans;
    do
    {
        testPFArrayD( );
        cout << "Test again? (y/n) ";
        cin >> ans;
    }while ((ans == 'y') || (ans == 'Y'));

    return 0;
}

void testPFArrayD( )
{
    int cap;
    cout << "Enter capacity of this super array: ";
    cin >> cap;
    PFArrayD temp(cap);

    cout << "Enter up to " << cap << " nonnegative numbers.\n";
    cout << "Place a negative number at the end.\n";

    double next;
    cin >> next;
    while ((next >= 0) && (!temp.full( )))
    {
        temp.addElement(next);
        cin >> next;
    }

    cout << "You entered the following "
         << temp.getNumberUsed( ) << " numbers:\n";
    int index;
    int count = temp.getNumberUsed( );
    for (index = 0; index < count; index++)
        cout << temp[index] << " ";
    cout << endl;
    cout << "(plus a sentinel value.)\n";
}


PFArrayD::PFArrayD( ) :capacity(50), used(0)
{
    a = new double[capacity];
}

PFArrayD::PFArrayD(int size) :capacity(size), used(0)
{
    a = new double[capacity];
}

PFArrayD::PFArrayD(const PFArrayD& pfaObject)
  :capacity(pfaObject.getCapacity( )), used(pfaObject.getNumberUsed( ))
{
    a = new double[capacity];
    for (int i =0; i < used; i++)
        a[i] = pfaObject.a[i];
}

void PFArrayD::addElement(double element)
{
    if (used >= capacity)
    {
        cout << "Attempt to exceed capacity in PFArrayD.\n";
        exit(0);
    }
    a[used] = element;
    used++;
}

double& PFArrayD::operator[](int index)
{
    if (index >= used)
    {
        cout << "Illegal index in PFArrayD.\n";
        exit(0);
    }

    return a[index];
}

PFArrayD& PFArrayD::operator =(const PFArrayD& rightSide)
{
    if (capacity != rightSide.capacity)
    {
        delete [] a;
        a = new double[rightSide.capacity];
    }

    capacity = rightSide.capacity;
    used = rightSide.used;
    for (int i = 0; i < used; i++)
        a[i] = rightSide.a[i];

    return *this;
}

PFArrayD::~PFArrayD( )
{
    delete [] a;
}

