// fileguard
#ifndef ChessPiece_H
#define ChessPiece_H

#include <string>
using namespace std;



class ChessPiece {
private:
	int xPos;
	int yPos;
	string type;
	string team_on; // strange name is so the getter can be named team()

public:
	// getters
	int x() ;
	int y();
	string team();

	// setters
	void setX(int);
	void setY(int);
	void setXY(int, int); // set both the x and the y at the same time
	string JSON_text(int yPos, int xPos) const;
	
	ChessPiece(string team_is_on, string type_of_piece);

};



#endif 
