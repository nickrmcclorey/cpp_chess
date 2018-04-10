// fileguard
#ifndef ChessPiece_H
#define ChessPiece_H

#include <string>
using namespace std;



class ChessPiece {
private:
	
	string piece_type;
	string team_on; // strange name is so the getter can be named team()

public:
	// getters
	string team();
	string type();

	// setters
	void setTeam();
	void setType();

	// utility
	string JSON_text(int yPos, int xPos) const;
	
	//constructors
	ChessPiece();
	ChessPiece(string team_is_on, string type_of_piece);

};



#endif 
