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
	ChessPiece board[8][8];
	string turn;
	bool AI_playing;

public:

	// constructor
	Chessboard();
	Chessboard(string fileToImport); // could be a constructor to resume a game saved to a file 
	Chessboard(vector<ChessPiece> gameboard); //could be used to create a gameboard with pieces in a certain spot.

	string getTurn() const;
	bool AI_is_playing() const;
	void turn_AI_off();
	void turn_AI_on();

	// functions to check to see if pieces are allowed to move
	bool isAllowedToMove(int location_x, int location_y, int destination_x, int destination_y) const; // checks to see if a piece is allowed to move. could call other functions for specific pieces
	// each of the following functios would be called by the above function once the type of piece is known
	bool canMoveKing(int, int, int, int) const;
	bool canMoveQueen(int, int, int, int) const;
	bool canMoveRook(int, int, int, int) const;
	bool canMoveBishop(int, int, int, int) const;
	bool canMoveKnight(int, int, int, int) const;
	bool canMovePawn(int, int, int, int) const;

	bool checkmate() const; // check for checkmate

	// utility / mutators
	void move(int, int, int, int); // used to move a piece
	ChessPiece at(int x, int y); // could use to index board
	void displayBoard() const; // used to display board for debugging
	bool isExposed(int xPos, int yPos);
	bool isValidIndex(const int &x, const int &y) const;
	ChessPiece findDiagonal(int, int, int, int) const;
	void makeJSONfile(string) const;
	vector<ChessPiece> allPieces() const;
	void changeTurn();

	// functions we'd need to do a save, load game feature
	void loadGame(string file_to_import);
	void saveGame(string fileName) const;
	void newGame();


};

#endif