#include <iostream>
#include <cstdlib>
#include "Chessboard.h"
#include "ChessPiece.h"
#include <cstring>
#include <sstream>
#include <string>

using namespace std;

// default constructor makes the piece "blank"
ChessPiece::ChessPiece(){
	team_on = "No team";
	piece_type = "empty"; 
}

// constructor setting the team and type
ChessPiece::ChessPiece(string team_its_on, string type) {
	team_on = team_its_on;
	piece_type = type;
}

// returns the team the piece belongs to
string ChessPiece::team() const{
	return team_on;
}

//returns the type of piece i.e. bishop, rook etc...
string ChessPiece::type() const {
	return piece_type;
}

// setters

// set the team of the chess piece
void ChessPiece::setTeam(string teamToSet) {
	this->team_on = teamToSet;
}

// set the type of the chess i.e. bishop, rook etc...
void ChessPiece::setType(string typeToSet) {
	this->piece_type = typeToSet;
}


// converts int to string
string toString(int num) {

	ostringstream raw;
	raw << num;
	return raw.str();
}


 
// this function takes in the x and y position as parameters and returns a string 
// in JSON format contianing information on its position, team and type
string ChessPiece::JSON_text(int xPos, int yPos) const {
	
	// get individual keys and values
	string teamInfo = "\"team\":\"" + this->team() + "\",\n";
	string piece_type = "\"type\":\"" + this->type() + "\",\n";
	string xPos_text = "\"xPos\":\"" + toString(xPos) + "\",\n";
	string yPos_text = "\"yPos\":\"" + toString(yPos) + "\"\n";	

	// combine stirngs from above and wrap it in curly brackets
	string toReturn = "{\n" + teamInfo + piece_type + xPos_text + yPos_text + "}";
	return toReturn;
}

bool ChessPiece::isEmpty() const{
	
	if (!strcmpi(piece_type.c_str(), "empty") )
		return true;
	else
		return false;
}

bool ChessPiece::isKing() const {
	if (!strcmpi(piece_type.c_str(), "king"))
		return true;
	else
		return false;
}

bool ChessPiece::isQueen() const {
	if (!strcmpi(piece_type.c_str(), "queen"))
		return true;
	else
		return false;
}

bool ChessPiece::isBishop() const {
	if (!strcmpi(piece_type.c_str(), "bishop"))
		return true;
	else
		return false;
}

bool ChessPiece::isKnight() const {
	if (!strcmpi(piece_type.c_str(), "knight"))
		return true;
	else
		return false;
}

bool ChessPiece::isRook() const {
	if (!strcmpi(piece_type.c_str(), "Rook"))
		return true;
	else
		return false;
}

bool ChessPiece::isPawn() const {
	if (!strcmpi(piece_type.c_str(), "pawn"))
		return true;
	else
		return false;
}

bool ChessPiece::isTeam(string team1) const {
	if (!strcmp(this->team().c_str(), team1.c_str()))
		return true;
	else
		return false;
}