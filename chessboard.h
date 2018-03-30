
// this file contains the definition of chessboard
#include <vector>

using namespace std;

class Chessboard {
private:
	// I think it would be more efficient to make the board
	// a 2d vector of pointers so there isn't empty spaces
	// that have to be filled with chess_pieces
	// I'm willing to change it if it bugs you
	Chess_piece* board[8][8];
	vector<Chess_piece> pieces;

public:

	// constructor
	Chessboard();
	int function1();


};