#include <iostream>
#include <cstdlib>
#include "ChessPiece.h"
#include "Chessboard.h"

using namespace std;

int main() {

	Chessboard num1;
	ChessPiece piece1("white","bishop");
	string me = piece1.JSON_text(1, 4);
	cout << me << endl;

	cout << "Working" << endl;

	system("pause");
	return 0;
}
