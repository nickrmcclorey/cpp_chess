// file guard
#ifndef Chessboard_H
#define Chessboard_H

// this file contains the definition of chessboard
#include <vector>
#include "ChessPiece.h"

using namespace std;

class Chessboard {
private:
	// I think it would be more efficient to make the board
	// a 2d vector of pointers so there isn't empty spaces
	// that have to be filled with chess_pieces
	// I'm willing to change it if it bugs you
	ChessPiece* board[8][8];
	vector<ChessPiece> pieces;

public:

	// constructor
	Chessboard();
	Chessboard(string fileToImport); // could be a constructor to resume a game saved to a file 
	Chessboard(vector<ChessPiece> gameboard); //could be used to create a gameboard with pieces in a certain spot.

	// functions to check to see if pieces are allowed to move
	bool isAllowedToMove(int destination_x, int destination_y); // checks to see if a piece is allowed to move. could call other functions for specific pieces
	bool canMoveKing(int, int);
	bool canMoveQueen(int, int);
	bool canMoveRook(int, int);
	bool canMoveBishop(int, int);
	bool canMoveKnight(int, int);
	bool canMovePawn(int, int);

	bool checkmate(); // check for checkmate

	// utility / mutators
	void move(int, int); // used to move a piece
	ChessPiece& at(int x, int y); // could use to index board

	// we'll need to an operator overload for the = sign as there are pointers in the class.

};

#endif