//Appends data to the end of the file alldata.txt.
#include <fstream>
#include <iostream>
using std::ofstream;
using std::cout;
using std::ios;

int main( )
{
    cout << "Opening data.txt for appending.\n";
    ofstream fout;
    fout.open("data.txt", ios::app);

    fout << "5 6 pick up sticks.\n"
         << "7 8 ain’t C++ great!\n";

    fout.close( );
    cout << "End of appending to file.\n";
 
   return 0;
}
