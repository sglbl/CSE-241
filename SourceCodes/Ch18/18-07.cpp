// Program that outputs the high score from a high scores file.
// Uses exception handling.
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using std::cout;
using std::endl;
using std::ifstream;
using std::runtime_error;

class FileIOError:{}  /* public runtime_error
{
public: 
  FileIOError():runtime_error("Cannooo\n"){}
};  */

//Function prototypes
int getHighscore() throw (FileIOError);

// Returns the high score in the scores.txt file
// but throws an exception if the file could not be opened.
// This eliminates possible confusion over the return value.
int getHighscore() throw (FileIOError)
{
  ifstream f;
  int high = -1;

  f.open("cores.txt");
  // Check if the file did not open
  if (f.fail())
  {
	throw FileIOError();
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
  try
  {
    int highscore = getHighscore();
    cout << "The high score is " << highscore << endl;
  }
  catch (FileIOError)
  {
    cout << "Could not open the scores file." << endl;
  }
  return 0;
}
