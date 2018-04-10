#include <iostream>
#include <cstdlib>
#include "ChessPiece.h"
#include "Chessboard.h"

using namespace std;

int main() {

	Chessboard x;
	ChessPiece piece1("white", "bishop");
	x.at(2, 2) = piece1;
	cout << "white = " << x.at(2,2).team();
	cout << x.at(9, 2).team();
	//string me = piece1.JSON_text(1, 4);
	//cout << me << endl;

	cout << "Working" << endl;

	system("pause");
	return 0;
}
