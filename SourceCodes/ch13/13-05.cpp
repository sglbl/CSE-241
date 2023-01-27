// Recursive program to determine if a string has an even number of 1's.
#include <iostream>
#include <string>

using namespace std;

// Function prototypes
bool evenNumberOfOnes(string s);
bool oddNumberOfOnes(string s);

// If the recursive calls end here with an empty string
// then we had an even number of 1's.
bool evenNumberOfOnes(string s)
{
	if (s.length() == 0)
		return true; // Is even
	else if (s[0]=='1')
		return oddNumberOfOnes(s.substr(1));
	else
		return evenNumberOfOnes(s.substr(1));
}

// if the recursive calls end up here with an empty string
// then we had an odd number of 1's.
bool oddNumberOfOnes(string s)
{
	if (s.length() == 0)
		return false;	// Not even
	else if (s[0]=='1')
		return evenNumberOfOnes(s.substr(1));
	else
		return oddNumberOfOnes(s.substr(1));
}

int main()
{
	string s = "10011";

	if (evenNumberOfOnes(s))
		cout << "Even number of ones." << endl;
	else
		cout << "Odd number of ones." << endl;

	return 0;
}