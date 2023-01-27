#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
	string text = "Call me at my desk phone (907) 867-5309 or my cell phone 907-350-3491.";
	string pattern = R"(\(?\d{3}\)?(-|\s)\d{3}(-|\s)\d{4})";
	regex reg(pattern);

	sregex_iterator cur_iterator(text.begin(), text.end(), reg);
	sregex_iterator end_iterator;
	while (cur_iterator != end_iterator)
	{
		cout << cur_iterator->str() << endl;
		cur_iterator++;
	}
	return 0;
}
