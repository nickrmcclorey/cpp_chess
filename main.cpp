#include <iostream>
#include <cstdlib>
#include "ChessPiece.h"
#include "Chessboard.h"

using namespace std;

int main() {

	Chessboard x;
	
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			cout << row << "," << col << " =" << endl;
			cout << x.at(row,col).team() << x.at(row,col).type() << endl;
		}
	}

	
	x.makeJSONfile("current.json");
	

	cout << x.at(0, 7).team() << endl;
	cout << x.at(7, 7).team() << endl;

	return 0;
	ChessPiece piece1("white", "bishop");
	
	string me = piece1.JSON_text(1, 4);
	cout << me << endl;

	cout << "Working" << endl;

	system("pause");
	return 0;
}
