#include <iostream>
#include <cstdlib>
#include "ChessPiece.h"
#include "Chessboard.h"

using namespace std;

int main() {

	Chessboard x;
	
	x.move(7, 7, 3, 4);
	x.makeJSONfile("current.json");
	

	cout << x.at(7, 7).team() << endl;
	x.move(0, 0, 7, 7);
	cout << x.at(7, 7).team() << endl;

	return 0;
	ChessPiece piece1("white", "bishop");
	
	string me = piece1.JSON_text(1, 4);
	cout << me << endl;

	cout << "Working" << endl;

	system("pause");
	return 0;
}
