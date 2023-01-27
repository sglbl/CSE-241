#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
	string text = "Call me at (907) 867-5309";
	string pattern = R"(\(?\d{3}\)?(-|\s)\d{3}(-|\s)\d{4})";
	regex reg(pattern);

	if (regex_search(text, reg))
		cout << "Phone number found" << endl;
	return 0;
}
