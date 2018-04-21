// file guard
#ifndef Chessboard_H
#define Chessboard_H

// this file contains the definition of chessboard

#include <vector>
#include "ChessPiece.h"

using namespace std;

class Chessboard {
private:
	
	ChessPiece board[8][8];
	string turn;
	bool AI_playing;
	string AI_team;
	

public:
	ChessPiece lastCaptured;

	// constructor
	Chessboard();
	Chessboard(string fileToImport); // could be a constructor to resume a game saved to a file 
	
	string getTurn() const;
	void changeTurn();
	bool AI_is_playing() const;
	void turn_AI_off();
	void turn_AI_on();
	string get_AI_team() const;
	void set_AI_team(string);
	void setAt(int, int, ChessPiece);

	// functions to check to see if pieces are allowed to move
	bool isAllowedToMove(int location_x, int location_y, int destination_x, int destination_y) const; // checks to see if a piece is allowed to move. could call other functions for specific pieces
	// each of the following functios would be called by the above function once the type of piece is known
	bool canMoveKing(int, int, int, int) const;
	bool canMoveQueen(int, int, int, int) const;
	bool canMoveRook(int, int, int, int) const;
	bool canMoveBishop(int, int, int, int) const;
	bool canMoveKnight(int, int, int, int) const;
	bool canMovePawn(int, int, int, int) const;

	bool checkmate(string); // check for checkmate
	bool check(string);

	// utility / mutators
	void move(int, int, int, int); // first two ints are location, last two ints are destination
	void move(vector<int> moveSet); // same as function above but ints are in vector
	ChessPiece at(int x, int y); // could use to index board
	void displayBoard() const; // used to display board for debugging
	bool isExposed(int xPos, int yPos, string);
	bool isValidIndex(const int &x, const int &y) const;
	vector<int> findDiagonal(int, int, int, int) const;
	vector<ChessPiece> allPieces() const;
	

	// functions to save, load and display game
	void loadGame(string file_to_import);
	void saveGame(string fileName) const;
	void newGame();
	void makeJSONfile(string) const;
	void makeJSONfile() const;


};

#endif