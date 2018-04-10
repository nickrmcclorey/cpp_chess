#include <iostream>
#include <cstdlib>
#include "Chessboard.h"
#include "ChessPiece.h"
#include <sstream>
#include <string>

using namespace std;

ChessPiece::ChessPiece(){
	team_on = "No team";
	piece_type = "empty"; 
}

ChessPiece::ChessPiece(string team_its_on, string type) {
	team_on = team_its_on;
	piece_type = type;
}

string ChessPiece::team() const{
	return this->team_on;
}

string ChessPiece::type() const {
	return this->piece_type;
}

void ChessPiece::setTeam(string teamToSet) {
	this->team_on = teamToSet;
}

void ChessPiece::setType(string typeToSet) {
	this->piece_type = typeToSet;
}

string toString(int num) {

	ostringstream raw;
	raw << num;
	return raw.str();
}

string ChessPiece::JSON_text(int xPos, int yPos) const {
	
	string teamInfo = "\"team\":\"" + team_on + "\",\n";
	string piece_type = "\"type\":\"" + piece_type + "\",\n";
	string xPos_text = "\"xPos\":\"" + toString(xPos) + "\",\n";
	string yPos_text = "\"yPos\":\"" + toString(yPos) + "\"\n";

	string toReturn = "{\n" + teamInfo + piece_type + xPos_text + yPos_text + "}\n";
	return toReturn;
}