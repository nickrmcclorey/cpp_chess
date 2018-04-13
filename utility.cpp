#include <iostream>
#include <cstdlib>
#include <sstream>
#include "utility.h"

using namespace std;


int stoi(string num_s) {
	istringstream raw(num_s); // create a stream with raw in it
	int toReturn = 0; // declare the variable to return
	raw >> toReturn; // put the string number into the int variable
	return toReturn; // return int
}