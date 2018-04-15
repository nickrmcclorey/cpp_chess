#include <iostream>
#include <cstdlib>
#include "ChessPiece.h"
#include "Chessboard.h"
#include "utility.h"
#include <cstring>
#include <fstream>


using namespace std;

void testBoard() {
	Chessboard x;

	//x.move(7, 7, 3, 4);
	x.makeJSONfile("current.json");


	cout << x.at(7, 7).team() << endl;
	x.move(1, 1, 6, 6);
	cout << x.at(5, 5).type() << endl;
	x.makeJSONfile("current.json");
	
	x.move(6, 7, 3, 4);
	cout << "1 = " << x.isExposed(4, 1) << endl;
	cout << "through" << endl;
}


void testJSON() {
	ChessPiece piece1("white", "bishop");

	string me = piece1.JSON_text(1, 4);
	cout << me << endl;

	cout << "Working" << endl;

}

void testPiece() {
	ChessPiece test("black", "bishop");
	cout << "0 = " << test.isEmpty() << endl;
	cout << "1 = " << test.isBishop() << endl;
}

void testisExposed() {
	Chessboard x;

	x.move(7, 7, 3, 4);

	
	x.move(0, 4, 5, 2);
	cout << "0 = " << x.isExposed(4, 1) << endl;
	cout << "1 = " << x.isExposed(6, 2) << endl;
	
	x.move(7, 6, 4, 6);
	cout << "0 = " << x.isExposed(1, 5) << endl;
	x.move(4, 6, 3, 6);
	cout << "1 = " << x.isExposed(1, 5) << endl;

	x.move(0, 0, 3, 0);
	cout << "1 = " << x.isExposed(3, 0) << endl;
	cout << "0 = " << x.isExposed(3, 6) << endl;
	x.makeJSONfile("current.json");

	x.move(7, 5, 5, 4);
	cout << "1 = " << x.isExposed(1, 0) << endl;
	cout << "0 = " << x.isExposed(0, 1) << endl;

	cout << "blackpawn = " << x.at(1, 1).team() << x.at(1, 1).type() << endl;
	x.makeJSONfile("current.json");
}

void testImport() {
	Chessboard x;
	cout << "empty = " << x.at(3, 4).type() << endl;
	x.loadGame("current.json");
	cout << "whiterook = " << x.at(3, 4).team() << x.at(3, 4).type() << endl;
}


Chessboard importGame() {
	// contains names of all the saved games
	ifstream infile;
	infile.open("game_names.txt");

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

	// holds the index in gameNames that corresponds to the game the user wants to open
	int gameIndex = 0;
	while (gameIndex > gameNames.size()) {
		// display current options and prompt for choice
		cout << "What game would you like to resume?" << endl;
		for (int k = 0; k < gameNames.size(); k++) {
			cout << "[" << ++k << "] " << gameNames.at(k) << endl;
		}
		
		// we need this because getline returns a string
		string gameToImport;
		// get the number entered by user
		getline(cin, gameToImport);
		// convert it to an integer
		gameIndex = stoi(gameToImport);

		// make sure index is valid
		if (gameIndex > gameNames.size())
			cout << "That's not a valid option" << endl;
		else
			break;
	}
	
	// load game with chessboard object passed in as parameter
	Chessboard importedGame(gameNames.at(gameIndex));
	// return game with loaded data
	return importedGame;

}


void playChess(Chessboard game) {
	
}

// main menu used to set up game
void mainMenu() {
	while (true) {

		Chessboard game;
		int option;
		string userChoice;
		cout << "Chess" << endl << endl;

		// ask whether user want to start new game or load a saved game
		while (option > 3 || option < 0) {

			// show options
			cout << "[1] New Game" << endl;
			cout << "[2] Load Existing Game" << endl;
			cout << "[3] Exit" << endl;

			// get input
			getline(cin, userChoice);
			option = stoi(userChoice);

			// do what the user wants
			if (option > 3 || option < 0) {
				cout << "invalid option" << endl;
				continue;
			}
			else if (option == 2) {
				game = importGame();

			}
			else if (option == 3) {
				return; // return to int main()
			}
		}

		// ask whether user wants to play with ai or two player
		while (option > 2 || option < 0) {

			// display options
			cout << "[1] Play with two players" << endl;
			cout << "[2] Play with A.I." << endl;

			// get input
			getline(cin, userChoice);
			option = stoi(userChoice);

			// turn AI on or off
			if (option > 2 || option < 0) {
				cout << "That's an invalid option" << endl;
			}
			else if (option == 1) {
				game.turn_AI_off();
			}
			else if (option == 2) {
				game.turn_AI_on();
			}
		}

		playChess(game);
	}
}

int main() {

	//x.makeJSONfile("current.json");

	testisExposed();
	//testImport();

	system("pause");
	return 0;
}
