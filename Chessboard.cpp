#include <iostream>
#include "ChessPiece.h"
#include "Chessboard.h"
#include "utility.h"
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
	//cout << "activated" << endl;
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

Chessboard::Chessboard(string fileToLoad) {
	this->loadGame(fileToLoad);
}


// returns piece at location
ChessPiece Chessboard::at(int x, int y) {
	if ((x > 7) || (x < 0) || (y > 7) || (y < 0)){
		// FIX ME throw logic_error("Not valid Index");
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

bool Chessboard::AI_is_playing() const {
	return AI_playing;
}

void Chessboard::turn_AI_on() {
	AI_playing = true;
}

void Chessboard::turn_AI_off() {
	AI_playing = false;
}

// changes the turn
void Chessboard::changeTurn() {
	turn = (strcmp("white", turn.c_str())) ? "black" : "white";
}


void Chessboard::move(int fromX, int fromY, int toX, int toY) {
	
	// empty piece to replace spot left
	ChessPiece empty;
	// get the piece captured. this could be an empty piece
	//essPiece captured_piece = board[toX][toY];
	// move the piece to its destination
	board[toX][toY] = board[fromX][fromY];
	// erease the spot the piece was in
	board[fromX][fromY] = empty;
	
}

void Chessboard::move(vector<int> moveSet) {
	this->move(moveSet.at(0), moveSet.at(1), moveSet.at(2), moveSet.at(3));
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
		cout << "Failed to open file" << endl;
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
			if (!board[row][col].isEmpty()) {
				// get the json text for that spot and put it in the outfile
				object_data.append(board[row][col].JSON_text(row, col));
				// add a comma
				object_data.append(",");
				counter++;
			}

		}
	}

	//cout << "32 = " << counter << endl; // for debugging purposes

	// erease final comma as this comma will break the JSON validity
	object_data.at(object_data.size() - 1) = ' ';

	// put a cap on the pieces array and output the current turn
	outfile << object_data << "],\n\"turn\" : \"" << turn << "\" \n}";
	
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
	

	if (this->at(xPos, yPos).isEmpty()) {
		return false;
	}

	ChessPiece candidate = this->at(xPos, yPos);
	string enemy = (!strcmp(candidate.team().c_str(), "black")) ? "white" : "black";
	
	// looking for nearby kings and pawns
	for (int row = -1; row <= 1 ; row++) {
		for (int col = -1; col <= 1; col++) {
			if (!isValidIndex(xPos + row, yPos + col))
				continue;

			ChessPiece temp = this->at(xPos + row, yPos + col);	
			if ((temp.isKing()) && temp.isTeam(enemy))
				return true;
		}
	}
	

	// looking for knights
	if (this->isValidIndex(xPos + 1, yPos + 2) && this->at(xPos + 1, yPos + 2).isKnight()) {
		return true;
	} else if (this->isValidIndex(xPos - 1, yPos + 2) && this->at(xPos - 1, yPos + 2).isKnight()) {
		return true;
	} else if (this->isValidIndex(xPos + 1, yPos - 2 ) && this->at(xPos + 1, yPos - 2).isKnight()) {
		return true;
	} else if (this->isValidIndex(xPos - 1, yPos - 2) && this->at(xPos - 1, yPos - 2).isKnight()) {
		return true;
	} else if (this->isValidIndex(xPos + 2, yPos + 1) && this->at(xPos + 2, yPos + 1).isKnight()) {
		return true;
	} else if (this->isValidIndex(xPos - 2, yPos + 1) && this->at(xPos - 2, yPos + 1).isKnight()) {
		return true;
	} else if (this->isValidIndex(xPos + 2, yPos - 1) && this->at(xPos + 2, yPos - 1).isKnight()) {
		return true;
	} else if (this->isValidIndex(xPos - 2, yPos - 1) && this->at(xPos - 2, yPos - 1).isKnight()) {
		return true;
	}

	//return false; // rest of function isn't finished
	//TODO: finish logic below

	// === looking for rooks === \\

	// going horizontal
	int adjustor = 1;
	// while valid index and haven't run into teammate
	while ((this->isValidIndex(xPos + adjustor, yPos)) && (board[xPos + adjustor][yPos].isEmpty())) {
		adjustor++;
	}
	// found invalid index or next piece in path. if this piece is a rook or queen
	if (this->isValidIndex(xPos + adjustor, yPos)) {
		ChessPiece attacker = board[xPos + adjustor][yPos];
		if ((attacker.isTeam(enemy)) && (attacker.isQueen() || attacker.isRook()))
			return true;
	}



	adjustor = -1;
	// while valid index and haven't run into teammate
	while ((this->isValidIndex(xPos + adjustor, yPos)) && (board[xPos + adjustor][yPos].isEmpty())) {
		adjustor--;
	}
	if (this->isValidIndex(xPos + adjustor, yPos)) {
		ChessPiece attacker = board[xPos + adjustor][yPos];
		if ((attacker.isTeam(enemy)) && (attacker.isQueen() || attacker.isRook()))
			return true;
	}
    

	// adjusting y position
	adjustor = 1;
	while ((this->isValidIndex(xPos, yPos + adjustor)) && (board[xPos][yPos + adjustor].isEmpty())) {
		adjustor++;
	}
	if (this->isValidIndex(xPos, yPos + adjustor)) {
		ChessPiece attacker = board[xPos][yPos + adjustor];
		if ((attacker.isTeam(enemy)) && (attacker.isQueen() || attacker.isRook()))
			return true;
	}



	adjustor = -1;
	while ((this->isValidIndex(xPos, yPos + adjustor)) && (board[xPos][yPos + adjustor].isEmpty())) {
		adjustor--;
	}
	if (this->isValidIndex(xPos, yPos + adjustor)) {
		ChessPiece attacker = board[xPos][yPos + adjustor];
		if ((attacker.isTeam(enemy)) && (attacker.isQueen() || attacker.isRook()))
			return true;
	}

	
	// === looking for bishops === \\
	

	vector <ChessPiece> attackers;
	attackers.push_back( this->findDiagonal(xPos, yPos, 1, 1));
	attackers.push_back( this->findDiagonal(xPos, yPos, -1, 1));
	attackers.push_back( this->findDiagonal(xPos, yPos, 1, -1));
	attackers.push_back( this->findDiagonal(xPos, yPos, -1, -1));

	for (int k = 0; k < attackers.size(); k++) {
		ChessPiece attacker = attackers.at(k);
		if ((attacker.isTeam(enemy)) && (attacker.isBishop() || attacker.isQueen()))
			return true;
	}

	// these are used to look the spots diagonally from the selected piece
	int yAdjustor = 1;
	int xAdjustor = 1;
	// find the first invalid index or another piece
	while ((this->isValidIndex(xPos + xAdjustor, yPos + yAdjustor)) && (board[xPos + xAdjustor][yPos + yAdjustor].isEmpty())) {
		xAdjustor++; 
		yAdjustor++; 
	} 
	// evaluate the next pieces in diagonal index
	if (this->isValidIndex(xPos + xAdjustor, yPos + yAdjustor)) {
		ChessPiece attacker = board[xPos + xAdjustor][yPos + yAdjustor];
		if ((attacker.isTeam(enemy)) && (attacker.isBishop() || attacker.isQueen()))
			return true;
	}


	yAdjustor = -1;
	xAdjustor = 1;
	while ((this->isValidIndex(xPos + xAdjustor, yPos + yAdjustor)) && (board[xPos + xAdjustor][yPos + yAdjustor].isEmpty())) {
		xAdjustor++;
		yAdjustor--;
	}
	if (this->isValidIndex(xPos + xAdjustor, yPos + yAdjustor)) {
		ChessPiece attacker = board[xPos + xAdjustor][yPos + yAdjustor];
		if ((attacker.isTeam(enemy)) && (attacker.isBishop() || attacker.isQueen()))
			return true;
	}


	yAdjustor = 1;
	xAdjustor = -1;
	while ((this->isValidIndex(xPos + xAdjustor, yPos + yAdjustor)) && (board[xPos + xAdjustor][yPos + yAdjustor].isEmpty())) {
		xAdjustor--;
		yAdjustor++;
	}
	if (this->isValidIndex(xPos + xAdjustor, yPos + yAdjustor)) {
		ChessPiece attacker = board[xPos + xAdjustor][yPos + yAdjustor];
		if ((attacker.isTeam(enemy)) && (attacker.isBishop() || attacker.isQueen()))
			return true;
	}

	yAdjustor = -1;
	xAdjustor = -1;
	while ((this->isValidIndex(xPos + xAdjustor, yPos + yAdjustor)) && (board[xPos + xAdjustor][yPos + yAdjustor].isEmpty())) {
		xAdjustor--;
		yAdjustor--;
	}
	if (isValidIndex(xPos + xAdjustor, yPos + yAdjustor)) {
		ChessPiece attacker = board[xPos + xAdjustor][yPos + yAdjustor];
		if ((attacker.isTeam(enemy)) && (attacker.isBishop() || attacker.isQueen()))
			return true;
	}

	// queen was checked when we were looking for rooks and queens

	return false;

}
 
ChessPiece Chessboard::findDiagonal(int xPos, int yPos, int xDir, int yDir) const {
	ChessPiece toReturn;
	int yAdjustor = yDir;
	int xAdjustor = xDir;
	while ((this->isValidIndex(xPos + xAdjustor, yPos + yAdjustor)) && (board[xPos + xAdjustor][yPos + yAdjustor].isEmpty())) {
		xAdjustor = (abs(xAdjustor) + 1) * xDir;
		yAdjustor = (abs(yAdjustor) + 1) * yDir;
	}
	if (isValidIndex(xPos + xAdjustor, yPos + yAdjustor)) {
		toReturn = board[xPos + xAdjustor][yPos + yAdjustor];
		
	}

	return toReturn;
}


void Chessboard::saveGame(string filename) const {
	if (filename.find("current_game")) {
		cout << "cant't use that filename to save game" << endl;
		exit(0);
	} else {
		this->makeJSONfile(filename);
	}
}

string textInside(string quotes, string raw) {
	// check to make sure both quotes actually exist
	if (raw.find(quotes.at(0)) == string::npos || raw.find(raw.at(1)) == string::npos) {
		cout << "quotes don't exist" << endl;
		cout << raw << endl;
		exit(0);
	}
	
	// find the opening quote and cut off everything before that
	raw = raw.substr(raw.find(quotes.at(0))+1);
	// return everything up to the terminating character
	return raw.substr(0, raw.find(quotes.at(1)));

}

string valueFromKey(string key, string raw) {
	//find the key
	key = raw.substr(raw.find(key));
	// find the colon after the key
	string value = key.substr(key.find(":") + 1);
	// find the value after the colon and return the text inside the quotes
	return textInside("\"\"", value);
}

void Chessboard::loadGame(string filename) {
	
	// input file
	ifstream infile;
	// prepend the saved_games folder to the filename to get the path
	string path = "saved_games\\" + filename;
	infile.open(path.c_str());

	//check to make sure it opens correctly;
	if (!infile.is_open()) {
		cout << "failed to open file" << endl;
		exit(0);
	}

	// holds the entire file
	string raw;
	
	while (!infile.eof()) {
		// holds one line
		string wholeLine;
		// get the line and store it in a string
		getline(infile,wholeLine);
		// append a new line to raw
		raw.append("\n");
		// put in the new line
		raw.append(wholeLine);

		
	}

	// contains text inside the "pieces" array in the JSON file
	string pieces = textInside("[]", raw);
	
	// holds one object in the json file
	string object;

	int counter = 0;
	do {
		// get the information for one chess piece
		object = textInside("{}",pieces);
		
		// declare the new chess piece an initialize it with values from the object
		ChessPiece newPiece(valueFromKey("team", object), valueFromKey("type", object));
		
		// get the x and y positions of the piece
		int xPos = stoi(valueFromKey("xPos",object));
		int yPos = stoi(valueFromKey("yPos", object));

		// put the piece on the board
		board[xPos][yPos] = newPiece;

		// cut off the previous object
		pieces = pieces.substr(pieces.find("}") + 1);
		//cout << pieces << "\n\n\n\n\n";
		
		// the last element of the array doesn't have a comma. this is how we know when to stop
	} while (!(pieces.find(",") == string::npos));
	
		
	// murder the infile
	infile.close();

}

    
    //on top self, on teammate, off board
	bool Chessboard::isAllowedToMove(int location_x, int location_y, int destination_x, int destination_y) const{
        //TODO:: FINISH FUNCTION
        if ((location_x == destination_x) && (location_y == destination_y)) {
			cout << "invalid index" << endl;
			exit(0);
        }
        
        return true;
    }
    
    bool Chessboard::canMoveKing(int location_x, int location_y, int destination_x, int destination_y) const{
        //TODO:: FINISH FUNCTION
        if (location_x == destination_x && location_y == destination_y){
			return false;        	
        }
        else if(!isValidIndex(location_x, location_y) && !isValidIndex(destination_x, destination_y)){
        	return false;
        }
        else if (abs(location_x - destination_x)<=1 && (abs(location_y - destination_y)<=1)){
        	return true;
        }
        else{
        	return false;
        }
    }
    
