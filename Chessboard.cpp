#include <iostream>
#include "ChessPiece.h"
#include "Chessboard.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;


// should be used to set the initial positions of the pieces
Chessboard::Chessboard() {
    this->newGame();
}

// creates a new game with pieces in their default position
void Chessboard::newGame() {
	cout << "activated" << endl;
	for (int i = 0; i < 8; i++) {
		board[1][i].setType("pawn");
		board[1][i].setTeam("black");
		board[6][i].setType("pawn");
		board[6][i].setTeam("white");
	}

	
    for (int i = 0; i < 8; i++) {
		switch (i) {
		case 0:
			board[0][i].setType("rook");
			board[7][i].setType("rook");
			break;
		case 1:
			board[0][i].setType("knight");
			board[7][i].setType("knight");
			break;
		case 2:
			board[0][i].setType("bishop");
			board[7][i].setType("bishop");
			break;
		case 3:
			board[0][i].setType("queen");
			board[7][i].setType("queen");
			break;
		case 4:
			board[0][i].setType("king");
			board[7][i].setType("king");
			break;
		case 5:
			board[0][i].setType("bishop");
			board[7][i].setType("bishop");
			break;
		case 6:
			board[0][i].setType("knight");
			board[7][i].setType("knight");
			break;
		case 7:
			board[0][i].setType("rook");
			board[7][i].setType("rook");
			break;
		}


			board[0][i].setTeam("black");
			board[1][i].setTeam("black");
			board[7][i].setTeam("white");
			board[6][i].setTeam("white");
	}
    
	turn = "white";
}

// returns piece at location
ChessPiece Chessboard::at(int x, int y) {
	if ((x > 7) || (x < 0) || (y > 7) || (y < 0)){
		throw logic_error("Not valid Index");
	}
	
	ChessPiece toReturn = board[x][y];
	return toReturn;
}

// returns vector of all the non empty pieces
vector<ChessPiece> Chessboard::allPieces() const {

	// vector that will be returned
	vector<ChessPiece> toReturn;
	
	// nested loop that collects all non-empty spots on the board
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			// if spot isn't empty then...
			if (board[row][col].team() != "empty") {
				// append that piece to the list
				toReturn.push_back(board[row][col]);
			}
		}
	}

	return toReturn;
}

// returns the which players turn it is
string Chessboard::getTurn() const {
	return turn;
}

// changes the turn
void Chessboard::changeTurn() {
	turn = (strcmp("white", turn.c_str())) ? "black" : "white";
}


ChessPiece Chessboard::move(int fromX, int fromY, int toX, int toY) {
	
	// empty piece to replace spot left
	ChessPiece empty;
	// get the piece captured. this could be an empty piece
	ChessPiece captured_piece = board[toX][toY];
	// move the piece to its destination
	board[toX][toY] = board[fromX][fromY];
	// erease the spot the piece was in
	board[fromX][fromY] = empty;
	
}

void Chessboard::makeJSONfile(string filename) const {
	
	// file to store json text in
	ofstream outfile;

	// checkign to see if .json extension was forgotten in filename parameter
	if (filename.find(".json") == string::npos)
		filename.append(".json");

	// putting it in the saved games folder
	string path = "saved_games\\" + filename;

	// open the file with the path
	outfile.open(path.c_str());

	// check to see if it opened correctly 
	if (!outfile.is_open()) {
		cout << "Failed to opne file" << endl;
		exit(0);
	}

	// ==== outputting pieces object which contains all chess pieces ==== \\

	// opening bracket
	outfile << "{\n\t\"pieces\": [\n\t";

	// this string will contain the JSON data for the chess pieces. This will be put in outfile
	string object_data;
	int counter = 0; // for debugging purposed

	// going through each spot in the board
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {

			// if spot isn't empty then...
			if (board[row][col].isEmpty()) {
				// get the json text for that spot and put it in the outfile
				object_data.append(board[row][col].JSON_text(row, col));
				// add a comma
				object_data.append(",");
				counter++;
			}

		}
	}

	cout << "32 = " << counter << endl; // for debugging purposes

	// erease final comma as this comma will break the JSON validity
	object_data.at(object_data.size() - 1) = ' ';

	// put a cap on the pieces array and output the current turn
	outfile << object_data << "],\n\"turn\":\"" << turn << "\" \n}";
	
	//close file
	outfile.close();
	
}

bool Chessboard::isValidIndex(const int &x, const int &y) const {
	if ((x > 7) || (x < 0) || (y > 7) || (y < 0))
		return false;
	else
		return true;
	
}

// checks to see if a piece is vulnerable to being hit
bool Chessboard::isExposed(int xPos, int yPos) {
	ChessPiece candidate = this->at(xPos, yPos);
	string enemy = (strcmp(candidate.team().c_str(), "black")) ? "white" : "black";

	// looking for nearby kings
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (strcmp("king", this->at(row, col).type().c_str()))
				return true;
		}
	}

	// TODO: finish function
	// looking for knights
	if (this->isValidIndex(xPos, yPos) && strcmp(this->at(xPos + 1, yPos + 2).type().c_str(), "knight"))
		return true;

}
 
    
    //on top self, on teammate, off board
	bool Chessboard::isAllowedToMove(int location_x, int location_y, int destination_x, int destination_y) const{
        //TODO:: FINISH FUNCTION
        if ((location_x == destination_x) && (location_y == destination_y)) {
            return false;
        }
        
        return true;
    }
    
    bool Chessboard::canMoveKing(int x, int y) const{
        //TODO:: FINISH FUNCTION
        return true;
    }
    
