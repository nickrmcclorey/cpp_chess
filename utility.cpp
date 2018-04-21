#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "utility.h"

using namespace std;


int stoi(char numInChar) {
	// create string
	string toReturn;
	// append the char
	toReturn.push_back(numInChar);
	// use other stoi function to convert string to int and return this
	return stoi(toReturn);
}

int stoi(string &num_s) {
	istringstream raw(num_s); // create a stream with raw in it
	int toReturn = 0; // declare the variable to return
	raw >> toReturn; // put the string number into the int variable
	return toReturn; // return int
}

// removes spaces from a given string. this is used in the moveFromUserString function
string removeSpaces(string copy) {

	for (int k = 0; k < copy.length(); k++) {
		char toCompare = copy.at(k);
		if (toCompare == 32) { // 32 is asc code for space
			copy.erase(k, 1);

			k = 0;
		}

		if ((copy.at(0) == 32) && (copy.length() == 1)) { // 32 is asc code for space
			return "";
			copy.erase(0, 1);

			k = 0;
		}

	}

	return copy;
}

/* this function will translate user input. it returns a vector corresponding to the move the user wants to do
   the format is {fromX, fromY, toX, toY} where fromX is the x position of the piece the user wants to move,
   fromY is the y position of the piece the user wants to move and toX and toY are the coordinates of the spot the user wants to move to
   This function also converts from the displayed index to the real index. For example, the displayed board goes from 1 to 8 while the indeces are from 0 to 7
   this function will handle that conversion. This function returns an array of -1's if the input cannot be understood  */
vector<int> moveFromUserString(string raw) {
	// remove spaces to make it easier to work with
	raw = removeSpaces(raw);
	// convert everything to upper case
	for (int k = 0; k < raw.size(); k++) {
		raw.at(k) = tolower(raw.at(k));
	}


	
	vector<int> toReturn(4,-1);
	vector<int> empty (4, -1);
	if (raw.size() != 6) {
		//cout << raw << " is " << raw.size() << " long" << endl;
		return toReturn;
	}


	// selecting needed characters while ignoring expresions like "to"
	string refined;
	refined.push_back(raw.at(0));
	refined.push_back(raw.at(1));
	refined.push_back(raw.at(4));
	refined.push_back(raw.at(5));


	// find the spot the user wants to move from
	for (int k = 0; k < 2; k++) {
		
		// if character is a valid number then...
		if (refined.at(k) > '0' && refined.at(k) <= '8')
			// put its numeric value in the return array
			toReturn.at(1) = stoi(refined.at(k)) - 1;
		// if character is a letter
		else if (refined.at(k) >= 'a' && refined.at(k) <= 'h')
			toReturn.at(0) = refined.at(k) - 'a';
		else
			return empty;

	}
	
	// find the spot the user wants to move to
	for (int k = 2; k < 4; k++) {
		
		if (refined.at(k) > '0' && refined.at(k) <= '8')
			toReturn.at(3) = stoi(refined.at(k)) - 1;
		else if (refined.at(k) >= 'a' && refined.at(k) <= 'h')
			toReturn.at(2) = refined.at(k) - 'a';
		else
			return empty;

	}


	// make sure all spots have been filled
	for (int k = 0; k < toReturn.size(); k++) {
		if (toReturn.at(k) == -1)
			return empty;
	}
	
	return toReturn;

}

vector<string> getGameNames() {
	//cout << "Entered getGameNames" << endl;
	// contains names of all the saved games
	ifstream infile;
	
	infile.open("saved_games\\game_names.txt");

	// check to make sure file opened
	if (!infile.is_open()) {
		cout << "failed to find names of games." << endl;
		exit(0);
	}

	// temporarily holds each game name
	string wholeLine;
	// holds the names for all the games
	vector<string> gameNames;
	while (!infile.eof()) {
		// get each game name and...
		getline(infile, wholeLine);
		// ... put it in the gameNames vector
		gameNames.push_back(wholeLine);
	}
	infile.close();
	return gameNames;
}

void appendToGameNames(string toAppend) {

	if (toAppend.find(".json") == string::npos)
		toAppend.append(".json");

	vector<string> gameNames = getGameNames();
	gameNames.push_back(toAppend);
	
	ofstream outfile;
	outfile.open("saved_games\\game_names.txt");

	if (!outfile.is_open()) {
		cout << "faled to open file" << endl;
		exit(0);
	}

	for (int k = 0; k < gameNames.size()-1; k++) {
		outfile << gameNames.at(k) << endl;
	}
	outfile << gameNames.back();

}


bool isInt(string input) {
	for (int k = 0; k < input.size(); k++) {
		char letter = input.at(k);
		if (letter > '9' || letter < '0')
			return false;
	}
	return true;
}


int askInteger(string prompt) {
	string userInput;


	do {
		cout << endl;
		cout << prompt;
		userInput;
		getline(cin, userInput);

		userInput = removeSpaces(userInput);
		if (!isInt(userInput))
			cout << "response wasn't understood" << endl;
		else
			break;

	} while (!isInt(userInput));

	return stoi(userInput);
}