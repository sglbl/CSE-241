//Reads three numbers from the file infile.txt and writes the sum to the file outfile.txt. 
#include <fstream>
#include <iostream>
#include <cstdlib> //for exit
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

int main( )
{
    ifstream inStream;
    ofstream outStream;

    inStream.open("infile.txt");
    if (inStream.fail( ))
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    outStream.open("outfile.txt");
    if (outStream.fail( ))
    {
        cout << "Output file opening failed.\n";
        exit(1);
    }

    int first, second, third;
    inStream >> first >> second >> third;
    outStream << "The sum of the first 3\n"
               << "numbers in infile.txt\n"
               << "is " << (first + second + third) << endl;

    inStream.close( );
    outStream.close( );
    return 0;
}

