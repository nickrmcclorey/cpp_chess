#include <iostream>
#include <cstdlib>
#include "ChessPiece.h"
#include "Chessboard.h"
#include "utility.h"
#include <cstring>
#include <fstream>


using namespace std;

void testBoard() {
	cout << "testing board" << endl;
	Chessboard x;

	//x.move(7, 7, 3, 4);
	x.makeJSONfile("current.json");


	cout << x.at(7, 7).team() << endl;
	x.move(1, 1, 6, 6);
	cout << x.at(5, 5).type() << endl;
	x.makeJSONfile("current.json");
	
	x.move(6, 7, 3, 4);
	cout << "1 = " << x.isExposed(4, 1, x.at(3,4).team()) << endl;
	cout << "through" << endl;
}


void testIsAllowedToMove() {
	cout << "testing isAllowedToMove functionn" << endl;
	Chessboard game_board;
	
	// testing knight
	cout << "knight" << endl;
	cout << "1 = " << game_board.isAllowedToMove(0, 1, 2, 2) << endl;
	cout << "0 = " << game_board.isAllowedToMove(0, 1, 2, 1) << endl;
	cout << "0 = " << game_board.isAllowedToMove(0, 1, 3, 1) << endl;
	
	// testing bishop
	game_board.move(0, 2, 2, 2);
	cout << "bishop" << endl;
	cout << "0 = " << game_board.isAllowedToMove(2, 2, 4, 3) << endl;
	cout << "1 = " << game_board.isAllowedToMove(2, 2, 6, 6) << endl;
	cout << "1 = " << game_board.isAllowedToMove(2, 2, 4, 4) << endl;

	// testing rook
	cout << "rook" << endl;
	cout << "0 = " << game_board.isAllowedToMove(0, 7, 2, 7) << endl;
	game_board.move(0, 7, 2, 7);
	cout << "1 = " << game_board.isAllowedToMove(2, 7, 6, 7) << endl;

	cout << "0 = " << game_board.isAllowedToMove(1, 1, 1, 1) << endl;
	cout << "0 = " << game_board.isAllowedToMove(1, 2, 2, 2) << endl;
	cout << "0 = " << game_board.isAllowedToMove(1, 2, 10, 1) << endl;

	// testing queen
	cout << "queen" << endl;
	game_board.move(0, 3, 3, 3);
	cout << "0 = " << game_board.isAllowedToMove(3, 3, 5, 6) << endl;
	cout << "1 = " << game_board.isAllowedToMove(3, 3, 5, 5) << endl;
	cout << "0 = " << game_board.isAllowedToMove(3, 3, 7, 7) << endl;
	cout << "1 = " << game_board.isAllowedToMove(3, 3, 6, 6) << endl;

	// testing pawns
	cout << "pawn" << endl;
	cout << "1 = " << game_board.isAllowedToMove(1, 0, 2, 0) << endl;
	cout << "0 = " << game_board.isAllowedToMove(1, 5, 2, 6) << endl;
	cout << "0 = " << game_board.isAllowedToMove(1, 0, 2, 1) << endl;
	game_board.move(7, 7, 2, 1);
	cout << "1 = " << game_board.canMovePawn(1, 0, 2, 1) << endl;
	cout << game_board.at(2, 1).team();

	// testing kings
	cout << "king" << endl;
	cout << "0 = " << game_board.isAllowedToMove(0, 4, 1, 4) << endl;
	cout << "0 = " << game_board.isAllowedToMove(0, 4, 0, 2) << endl;
	cout << "1 = " << game_board.isAllowedToMove(0, 4, 0, 3) << endl;
	game_board.move(0, 4, 4, 1);
	cout << "1 = " << game_board.isAllowedToMove(4, 1, 5, 2) << endl;
	cout << "1 = " << game_board.isAllowedToMove(4, 1, 3, 1) << endl;
	cout << "0 = " << game_board.isAllowedToMove(4, 1, 4, 3) << endl;
	game_board.move(4, 1, 6, 3);
	cout << "1 = " << game_board.isAllowedToMove(7, 4, 6, 3);

	game_board.makeJSONfile("current.json");
	game_board.makeJSONfile("test.json");
}

void testCheckmate() {

	Chessboard game;
	cout << "0 = " << game.checkmate("black") << endl;
	game.move(7, 4, 2, 5);
	game.move(0, 7, 3, 7);
	cout << "1 = " << game.checkmate("white") << endl;
	game.move(3, 7, 4, 7);
	cout << "0 = " << game.checkmate("white") << endl;


	game.makeJSONfile();
}

void testJSON() {
	cout << "printing json text for white bishop" << endl << endl;
	ChessPiece piece1("white", "bishop");

	string me = piece1.JSON_text(1, 4);
	cout << me << endl;

	cout << "Working" << endl;

}

void testPiece() {
	cout << "testing pieces" << endl;
	ChessPiece test("black", "bishop");
	cout << "0 = " << test.isEmpty() << endl;
	cout << "1 = " << test.isBishop() << endl;
	test.setType("knight");
	cout << "1 = " << test.isKnight() << endl;
	Chessboard x;
	cout << "1 = " << x.at(0, 0).isRook() << endl;
	cout << "rook = " << x.at(0, 0).type() << endl;
	cout << "1 = " << x.at(0, 3).isQueen() << endl;
	test.setType("pawn");
	cout << "1 = " << test.isPawn() << endl;
	test.setType("king");
	cout << "1 = " << test.isKing() << endl;
	cout << "0 = " << test.isQueen() << endl;
	test.setType("queen");
	cout << "1 = " << test.isQueen() << endl;


}

void testisExposed() {
	/*cout << "Testing is exposed" << endl;
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
	x.makeJSONfile("current.json");*/
}
Chessboard importGame();
void testFileIO() {
	Chessboard original;
	original.move(0, 0, 3, 5);
	original.makeJSONfile("testImportExport.json");
	original.makeJSONfile("current");

	Chessboard importedBoard;
	importedBoard = importGame();
	cout << original.at(3, 5).team() << original.at(3, 5).type() << " = " << importedBoard.at(3, 5).team() << importedBoard.at(3, 5).type() << endl;

}


Chessboard importGame() {
	
	vector<string> gameNames = getGameNames();
	// holds the index in gameNames that corresponds to the game the user wants to open
	int gameIndex = 0;
	while (true) {
		// display current options and prompt for choice
		cout << "What game would you like to resume?" << endl;
		for (int k = 0; k < gameNames.size(); k++) {
			cout << "[" << k + 1 << "] " << gameNames.at(k) << endl;
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
	
	// use Chessboard constructor to create board with data from json file
	Chessboard importedGame(gameNames.at(gameIndex-1));
	// return game with loaded data
	return importedGame;

}


// this function asks the user for their next move
// it ensure the move they enter is valid and then return a 
// vector that corresponds to the moves to pass into the .move() function
vector<int> getMoveVec(Chessboard game) {
	vector<int> moveVec(4, -1);
	do {
		
		cout << "Enter your move. It's currently " << game.getTurn() << endl;
		cout << "type \"menu\" for more options" << endl;

		string userInput;
		getline(cin, userInput);

		moveVec = moveFromUserString(userInput);
		cout << moveVec.at(0) << moveVec.at(1) << moveVec.at(2) << moveVec.at(3) << endl;
		if (moveVec.at(0) == -1 || (!game.isAllowedToMove(moveVec.at(0), moveVec.at(1), moveVec.at(2), moveVec.at(3)))) {
		
			cout << "That isn't a valid move" << endl;
			continue;
		} else {
			// move the piece and update the json file
			game.move(moveVec);
			game.makeJSONfile("current.json");

			// ask if they are sure about the move
			cout << "Board has been updated\nAre you sure this is your move?" << endl;
			cout << "[1] yes" << endl;
			cout << "[2] no" << endl;
			getline(cin, userInput);

			if (strcmp(userInput.c_str(), "1")) {
				break;
			} else {
				// reverse the move by switching the destination and current position
				game.move(moveVec.at(2), moveVec.at(3), moveVec.at(0), moveVec.at(1));
				// update JSON file
				game.makeJSONfile("current.json");
				continue;
			}
		}
		// there is a break statement to escape loop
	} while (true);

	return moveVec;
}

// plays the game of chess
void playChess(Chessboard game) {

	do {

		// this function will also make sure user enters in a move thats follows the rules of chess
		vector<int> moveVec = getMoveVec(game);

		cout << "moving piece" << endl;
		game.move(moveVec);

		// switch the turn
		game.changeTurn();

		// update the gameboard
		game.makeJSONfile("current.json");

	} while (!game.checkmate(game.getTurn()));

	cout << "Game Over" << endl << game.getTurn() << " lost" << endl;

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

		option = 1;
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
				cout << "What team are you on?" << endl;
				getline(cin, userChoice);
				while (strcmp(userChoice.c_str(), "white") || strcmp(userChoice.c_str(), "black")) {
					cout << "That's not a team" << endl;
					cout << "What team are you on?" << endl;
					getline(cin, userChoice);
				}

				game.set_AI_team(userChoice);
			}
		}

		playChess(game);
	}
}

int main() {
	
	mainMenu();
	//testCheckmate();
	//appendToGameNames("test");
	//testPiece();
	//testIsAllowedToMove();

	return 0;
}
