// Program to demonstrate use of the Set class

#include <iostream>
#include <string>
#include "listtools.cpp"		// Your compiler may compile separately
#include "set.h"
#include "set.cpp"				// Your compiler may compile separately
using std::cout;
using std::endl;
using std::string;
using namespace SetSavitch;

int main()
{
	Set<string> round;   // Round things
	Set<string> green;   // Green things

	round.add("peas");   // Sample data for both sets
	round.add("ball");
	round.add("pie");
	round.add("grapes");
	green.add("peas");
	green.add("grapes");
	green.add("garden hose");
	green.add("grass");

	cout << "Contents of set round: ";
      	round.output();
	cout << "Contents of set green: ";
       	green.output();

	cout << "ball in set round? " <<
		round.contains("ball") << endl;
	cout << "ball in set green? " <<
		green.contains("ball") << endl;

	cout << "ball and peas in same set? ";
	if ((round.contains("ball") && round.contains("peas")) ||
	    (green.contains("ball") && green.contains("peas")))
	    cout << "  true" << endl;
	else
            cout << "  false" << endl;

	cout << "pie and grass in same set? ";
	if ((round.contains("pie") && round.contains("grass")) ||
	    (green.contains("pie") && green.contains("grass")))
	    cout << "  true" << endl;
	else
            cout << "  false" << endl;

	cout << "Union of green and round: " << endl;
	Set<string> *unionset = round.setUnion(green);
	unionset->output();
	delete unionset;

	cout << "Intersection of green and round: " << endl;
	Set<string> *interset = round.setIntersection(green);
	interset->output();
	delete interset;

	return 0;
}


