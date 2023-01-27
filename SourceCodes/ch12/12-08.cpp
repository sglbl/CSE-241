//Program to create a file called cplusad.txt which is identical to the file cad.txt,
//except that all occurrences of 'C' are replaced by "C++". Assumes that the uppercase
//letter 'C' does not occur in cad.txt, except as the name of the C programming language.
#include <fstream>
#include <iostream>
#include <cstdlib>
using std::ifstream;
using std::ofstream;
using std::cout;

void addPlusPlus(ifstream& inStream, ofstream& outStream);
//Precondition: inStream has been connected to an input file with open.
//outStream has been connected to an output file with open.
//Postcondition: The contents of the file connected to inStream have been
//copied into the file connected to outStream, but with each 'C' replaced
//by "C++". (The files are not closed by this function.)

int main( )
{
    ifstream fin;
    ofstream fout;

    cout << "Begin editing files.\n";

    fin.open("cad.txt");
    if (fin.fail( ))
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    fout.open("cppad.txt");
    if (fout.fail( ))
    {
        cout << "Output file opening failed.\n";
        exit(1);
    }

    addPlusPlus(fin, fout);

        fin.close( );
    fout.close( );

    cout << "End of editing files.\n";
    return 0;
}

void addPlusPlus(ifstream& inStream, ofstream& outStream)
{
    char next;

    inStream.get(next);
    while (! inStream.eof( ))
    {
        if (next == 'C')
            outStream << "C++";
        else
            outStream << next;

        inStream.get(next);
    }
}
