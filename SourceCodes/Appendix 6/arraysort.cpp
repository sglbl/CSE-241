#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

int main()
{
 array<int,6> a = {5, 2, 4};
 cout << "Size of array: " << a.size() << endl;
 cout << "Element 0: " << a[0] << endl;
 cout << "Setting index 4 to 100." << endl;
 a[4] = 100;

 std::sort(a.begin(), a.end());

 cout << "After sort, array contains: " << endl;
 for (int element : a)
   cout << element << endl;

 return 0;
}

