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
		cout << x << "," << y << " is an invalid index" << endl;
		exit(0);
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

string Chessboard::get_AI_team() const {
	return this->AI_team;
}
void Chessboard::set_AI_team(string team) {
	this->AI_team = team;
}

// changes the turn
void Chessboard::changeTurn() {
	turn = (!strcmp("white", turn.c_str())) ? "black" : "white";
}


void Chessboard::setAt(int x, int y, ChessPiece toPlace) {
	board[x][y] = toPlace;
}

void Chessboard::move(int fromX, int fromY, int toX, int toY){
	
	// empty piece to replace spot left
	ChessPiece empty;

	// holds piece that is captured
	lastCaptured = this->at(toX, toY);

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
	string path = "saved_games/" + filename;

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

void Chessboard::makeJSONfile() const {
	this->makeJSONfile("current.json");
}


bool Chessboard::isValidIndex(const int &x, const int &y) const {
	if ((x > 7) || (x < 0) || (y > 7) || (y < 0)) {
		return false;
	}
	else {
		return true;
	}
}

// checks to see if a piece is vulnerable to being hit
bool Chessboard::isExposed(int xPos, int yPos, string friendly) {
	
	string enemy = (!strcmp(friendly.c_str(), "black")) ? "white" : "black";
	//cout << "inside isExposed with enemy being " << enemy << endl;
	//cout << "origin is " << xPos << "," << yPos << endl;

	int count = 0;
	for (int col = 0; col < 8; col++) {
		for (int row = 0; row < 8; row++) {
			count++;
			//cout << "col,row = " << col << "," << row << endl;
			if (this->at(col, row).isTeam(enemy) && this->isAllowedToMove(col, row, xPos, yPos)) {
				//cout << this->at(col,row).type() << " at " << col << "," << row << " can move to " << xPos << "," << yPos << endl;
				return true;
			}
		}
	}
	//cout << "returning false after looking at " << count << " different moves" << endl;
	return false;

}
 
vector<int> Chessboard::findDiagonal(int xPos, int yPos, int xDir, int yDir) const {
	
	int yAdjustor = yDir;
	int xAdjustor = xDir;
	while ((this->isValidIndex(xPos + xAdjustor, yPos + yAdjustor)) && (board[xPos + xAdjustor][yPos + yAdjustor].isEmpty())) {
		xAdjustor = (abs(xAdjustor) + 1) * xDir; 
		yAdjustor = (abs(yAdjustor) + 1) * yDir;
	}

	vector<int> toReturn;
	toReturn.push_back(xPos + xAdjustor);
	toReturn.push_back(yPos + yAdjustor);
	return toReturn;
}


bool Chessboard::check(string teamToEscape) {
	int kingX = -1, kingY = 1;
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {

			if (this->at(col, row).isKing() && this->at(col, row).isTeam(teamToEscape)) {
				kingX = col;
				kingY = row;
				break;
			}
		}
	}
	if (this->isExposed(kingX, kingY, teamToEscape))
		return true;
	else
		return false;
}

// check for checkmate on current board. Looks to see if current player has any options
// so if turn is white then it checks if white king is in check mate
bool Chessboard::checkmate(string teamToEscape) {

	if (lastCaptured.isKing())
		return true;

	// holds positions of king
	int kingX = -1, kingY = -1;

	// finds king and sets kingX and kingY
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			
			if (this->at(col,row).isKing() && this->at(col,row).isTeam(teamToEscape)) {
				kingX = col;
				kingY = row;
				break;
			}
		}
	}

	if (kingX == -1 || kingY == -1) {
		cout << "couldn't find the king" << endl;
		exit(0);
	}

	//cout << "king is at " << kingX << "," << kingY << endl;
	ChessPiece king = this->at(kingX, kingY);
	// checks to see if he's exposed on current spot
	if (!this->isExposed(kingX, kingY, king.team()))
		return false;
	
	Chessboard* tempBoard = new Chessboard;
	
	tempBoard->makeJSONfile();


	bool kingExposed;
	// checks all adjacent spots to see if he can move there and be safe
	for (int row = -1; row <= 1; row++) {
		for (int col = -1; col <= 1; col++) {
			*tempBoard = *this;
			// if he can move to that spot and isn't exposed on that spot, return false
			if (tempBoard->isAllowedToMove(kingX, kingY, kingX+col, kingY+row) ) {
				tempBoard->move(kingX, kingY, kingX + col, kingY + row);

				string enemy = (!strcmp(king.team().c_str(), "black")) ? "white" : "black";
				//cout << "inside isExposed with enemy being " << enemy << endl;
				//cout << "origin is " << xPos << "," << yPos << endl;

				int count = 0;
				for (int col = 0; col < 8; col++) {
					for (int row = 0; row < 8; row++) {
						count++;
						//cout << "col,row = " << col << "," << row << endl;
						if (this->at(col, row).isTeam(enemy) && this->isAllowedToMove(col, row, kingX, kingY) && this->isExposed(col,row,enemy)) {
							//cout << this->at(col,row).type() << " at " << col << "," << row << " can move to " << xPos << "," << yPos << endl;
							kingExposed = true;
						}
					}
				}
				//cout << "returning false after looking at " << count << " different moves" << endl;
				kingExposed = false;

				if (!kingExposed)
					return false;
				else
					return true;
			}
		}
	}

	delete tempBoard;
	// king has no more options return true
	return true;
}


void Chessboard::saveGame(string filename) const {
	if (filename.find("current_game") != string::npos) {
		cout << "can't use that filename to save game" << endl;
		
	} else {
		// save this game in a json file
		this->makeJSONfile(filename);
		// append the games name to game_names.txt so we can find it later
		appendToGameNames(filename);
	}
}

// is given a set of quotes (i.e [] () {} "") and returns all the text inside the quotes 
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

// gets the value from a JSON value given the variable to look for
string valueFromKey(string key, string raw) {
	//find the key
	key = raw.substr(raw.find(key));
	// find the colon after the key
	string value = key.substr(key.find(":") + 1);
	// find the value after the colon and return the text inside the quotes
	return textInside("\"\"", value);
}

void Chessboard::loadGame(string filename) {
	
	if (filename.find(".json") == string::npos)
		filename.append(".json");

	// JSON file with board info in it
	ifstream infile;
	// prepend the saved_games folder to the filename to get the path
	string path = "saved_games/" + filename;
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
		int xPos = toInt(valueFromKey("xPos",object));
		int yPos = toInt(valueFromKey("yPos", object));

		// put the piece on the board
		board[xPos][yPos] = newPiece;

		// cut off the previous object
		pieces = pieces.substr(pieces.find("}") + 1);
		//cout << pieces << "\n\n\n\n\n";
		
		// the last element of the array doesn't have a comma. this is how we know when to stop
	} while (!(pieces.find(",") == string::npos));
	
	this->turn = valueFromKey("turn", raw);

	// murder the infile
	infile.close();

}

    
    //on top self, on teammate, off board
	bool Chessboard::isAllowedToMove(int location_x, int location_y, int destination_x, int destination_y) const{
        //TODO:: FINISH FUNCTION
		
        if (!isValidIndex(location_x, location_y) || !isValidIndex(destination_x, destination_y)) {
			//cout << "invalid index" << endl;
			return false;
        }
        else if(board[location_x][location_y].isTeam(board[destination_x][destination_y].team())){
			//cout << location_x << "," << location_y << " moving to team mate at " << destination_x << "," << destination_y << endl;
			return false;
        }
        else if((location_x == destination_x) && (location_y == destination_y)){
        	return false; 
        }
        else if (board[location_x][location_y].isKing()){
        	if (canMoveKing(location_x, location_y, destination_x, destination_y)){
        		return true;
        	}
        }
        else if (board[location_x][location_y].isQueen()){
        	if (canMoveQueen(location_x, location_y, destination_x, destination_y)){
        		return true;
        	}
        }
        else if (board[location_x][location_y].isBishop()){
        	if (canMoveBishop(location_x, location_y, destination_x, destination_y)){
        		return true;
        	}
        }
        else if (board[location_x][location_y].isKnight()){
        	if (canMoveKnight(location_x, location_y, destination_x, destination_y)){
        		return true;
        	}
        }
        else if (board[location_x][location_y].isPawn()){
        	if (canMovePawn(location_x, location_y, destination_x, destination_y)){
        		return true;
        	}
        }
        else if (board[location_x][location_y].isRook()){
        	if (canMoveRook(location_x, location_y, destination_x, destination_y)){
				
        		return true;
       		}
			
        }	
        return false;
	}
    
    bool Chessboard::canMoveKing(int location_x, int location_y, int destination_x, int destination_y) const{
		//cout << "inside can move King trying to move from" << location_x << "," << location_y << " to " << destination_x << "," << destination_y << endl;
        if (location_x == destination_x && location_y == destination_y){
			return false;        	
        }
        else if(!isValidIndex(location_x, location_y) || !isValidIndex(destination_x, destination_y)){
        	return false;
        }
        else if (abs(location_x - destination_x) <= 1 && (abs(location_y - destination_y) <= 1)){
        	return true;
        }
        else{
        	return false;
        }
    }
    
    bool Chessboard::canMoveQueen(int location_x, int location_y, int destination_x, int destination_y) const{
    	
    	if (canMoveRook(location_x, location_y, destination_x, destination_y)||canMoveBishop(location_x, location_y, destination_x, destination_y)){
    		return true;
        }
        else{
        	return false;
        }
    }

	bool Chessboard::canMoveRook(int location_x, int location_y, int destination_x, int destination_y) const{
		if (location_y==destination_y && destination_x<location_x){
			if (findDiagonal(location_x, location_y, -1, 0)[0]<=destination_x){
				return true;
			}
		}
		else if(location_y==destination_y && destination_x>location_x){
			if (findDiagonal(location_x, location_y, 1, 0)[0]>=destination_x){
				return true;
			}
		}
		else if(location_x==destination_x && destination_y<location_y){
			if (findDiagonal(location_x, location_y, 0, -1)[1]<=destination_y){
				return true;
			}
		}
		else if(location_x==destination_x && destination_y>location_y){
			if (findDiagonal(location_x, location_y, 0, 1)[1]>=destination_y){
				return true;
			}
		}
		else{
			return false;
		}
	}

	bool Chessboard::canMoveBishop(int location_x, int location_y, int destination_x, int destination_y) const{
		if (abs(location_x-destination_x)==abs(location_y-destination_y)){
			//First quadrant
			if (destination_x>location_x && destination_y>location_y){
				if (findDiagonal(location_x, location_y, 1, 1)[0]>=destination_x && findDiagonal(location_x, location_y, 1, 1)[1]>=destination_y){
					return true;
				}
			}
			//Second quadrant
			else if(destination_x<location_x && destination_y>location_y){
				if (findDiagonal(location_x, location_y, -1, 1)[0]<=destination_x && findDiagonal(location_x, location_y, -1, 1)[1]>=destination_y){
					return true;
				}
			}
			//Third quadrant
			else if(destination_x<location_x && destination_y<location_y){
				if (findDiagonal(location_x, location_y, -1, -1)[0]<=destination_x && findDiagonal(location_x, location_y, -1, -1)[1]<=destination_y){
					return true;
				}
			}
			//Fourth quadrant
			else if(destination_x>location_x && destination_y<location_y){
				if (findDiagonal(location_x, location_y, 1, -1)[0]>=destination_x && findDiagonal(location_x, location_y, 1, -1)[1]<=destination_y){
					return true;
				}
			}	
		}
		return false;
	}
	
	bool Chessboard::canMoveKnight(int location_x, int location_y, int destination_x, int destination_y) const{
		if (location_x!=destination_x && location_y!=destination_y){
			if (abs(location_x - destination_x) > 2 || abs(location_y - destination_y) > 2)
				return false;
			
			if (abs(location_x-destination_x) + abs(location_y-destination_y) == 3 ){
				return true;
			}
		}

		return false;

	}
	
	bool Chessboard::canMovePawn(int location_x, int location_y, int destination_x, int destination_y) const{
		if (board[location_x][location_y].isTeam("black")){
			
			if (destination_x == location_x+1 && (destination_y == location_y+1 || destination_y == location_y-1) && board[destination_x][destination_y].isTeam("white")){
				return true;
			}
			else if(destination_x == location_x+1 && destination_y == location_y){
				return true;
			}
			else if(destination_x == location_x+2 && destination_y == location_y && !board[location_y][location_x].hasMoved() && board[destination_x][destination_y].isEmpty()){
				return true;
			}
			else{
				return false;
			}
		}
		else if (board[location_x][location_y].team() == "white"){
			if (destination_x == location_x-1 && (destination_y == location_y+1 || destination_y == location_y-1)){
				return true;
			}
			else if(destination_x == location_x-1 && destination_y == location_y){
				return true;
			}
			else if(destination_x == location_x-2 && destination_y == location_y && !board[location_y][location_x].hasMoved() && board[destination_x][destination_y].isEmpty()){
				return true;
			}
			else{
				return false;
			}
		}
		return false;
	}
