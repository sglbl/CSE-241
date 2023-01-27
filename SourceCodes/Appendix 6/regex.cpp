#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
	string text1 = "word1 word2";
	string text2 = "OnlyOneWord";
	string pattern = R"(\w+\s\w+)";
	regex reg(pattern);

	if (regex_match(text1, reg))
		cout << "Text1 matches pattern" << endl;
	else
		cout << "Text1 does not match pattern" << endl;

	if (regex_match(text2, reg))
		cout << "Text2 matches pattern" << endl;
	else
		cout << "Text2 does not match pattern" << endl;
	return 0;
}
