// Program that outputs the high score from a high scores file.
// Does not use exception handling.
#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::endl;
using std::ifstream;

//Function prototypes
int getHighscore();  

// Returns the high score in the scores.txt file
int getHighscore()
{
  ifstream f;
  int high = -1;

  f.open("scores.txt");
  // Check if the file did not open
  if (f.fail())
  {
	cout << "File could not be opened." << endl;
	return -1;
  }
  int num;
  // Scan through each number in the file and return the largest
  f >> high;
  while (f >> num)
  {
	if (num > high)
		high = num;
  }
  f.close();
  return high;
}

int main()
{
  int highscore = getHighscore();
  cout << "The high score is " << highscore << endl;
  return 0;
}
