#include <iostream>
#include <cstdlib>
#include "ChessPiece.h"
#include "Chessboard.h"

using namespace std;

void testBoard() {
	Chessboard x;

	//x.move(7, 7, 3, 4);
	x.makeJSONfile("current.json");


	cout << x.at(7, 7).team() << endl;
	x.move(1, 1, 6, 6);
	cout << x.at(5, 5).type() << endl;
	x.makeJSONfile("current.json");
	
	x.move(6, 7, 3, 4);
	cout << "1 = " << x.isExposed(4, 1) << endl;
	cout << "through" << endl;
}


void testJSON() {
	ChessPiece piece1("white", "bishop");

	string me = piece1.JSON_text(1, 4);
	cout << me << endl;

	cout << "Working" << endl;

}

void testPiece() {
	ChessPiece test("black", "bishop");
	cout << "0 = " << test.isEmpty() << endl;
	cout << "1 = " << test.isBishop() << endl;
}

void testisExposed() {
	Chessboard x;

	x.move(7, 7, 3, 4);

	
	x.move(0, 4, 5, 2);
	cout << "0 = " << x.isExposed(4, 1) << endl;
	cout << "1 = " << x.isExposed(6, 2) << endl;
	
	x.move(7, 6, 4, 6);
	cout << "0 = " << x.isExposed(1, 5) << endl;
	x.move(4, 6, 3, 6);
	cout << "1 = " << x.isExposed(1, 5) << endl;
	x.makeJSONfile("current.json");

}


int main() {

	//x.makeJSONfile("current.json");

	testisExposed();
	
	system("pause");
	return 0;
}
