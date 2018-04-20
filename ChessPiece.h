// fileguard
#ifndef ChessPiece_H
#define ChessPiece_H

#include <string>
using namespace std;



class ChessPiece {
private:
	
	string piece_type;
	string team_on; // strange name is so the getter can be named team()
	bool has_moved;

public:
	// getters
	string team() const;
	string type() const;
	bool hasMoved() const;

	// setters
	void setTeam(string);
	void setType(string);
	void moved();
	
	// utility
	string JSON_text(int yPos, int xPos) const;
	bool isEmpty() const;
	bool isKing() const;
	bool isQueen() const;
	bool isBishop() const;
	bool isKnight() const;
	bool isRook() const;
	bool isPawn() const;
	bool isTeam(string) const;

	//constructors
	ChessPiece();
	ChessPiece(string team_is_on, string type_of_piece);

};



#endif 
