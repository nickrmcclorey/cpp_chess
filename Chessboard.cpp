#include <iostream>
#include "ChessPiece.h"
#include "Chessboard.h"
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;


// should be used to set the initial positions of the pieces
Chessboard::Chessboard() {
	
}


void Chessboard::newGame() {
	for (int i = 0; i < 8; i++) {
		board[1][i].setType("pawn");
		board[1][i].setTeam("black");
		board[6][i].setType("pawn");
		board[6][i].setTeam("white");
	}
}

	/*
    for (int i = 0; i < 8; i++) {
        switch (i)
            case 0:
                board[0][i].setType("rook");
                board[7][i].setType("rook");
                break;
            case 1:
                board[0][i].setType("knight");
                board[7][i].setType("knight");
                break;
            case 2:
                board[0][i].setType("bishop");
                board[7][i].setType("bishop");
                break;
            case 3:
                board[0][i].setType("queen");
                board[7][i].setType("queen");
                break;
            case 4:
                board[0][i].setType("king");
                board[7][i].setType("king");
                break;
            case 5:
                board[0][i].setType("bishop");
                board[7][i].setType("bishop");
                break;
            case 6:
                board[0][i].setType("knight");
                board[7][i].setType("knight");
                break;
            case 7:
                board[0][i].setType("rook");
                board[7][i].setType("rook");
                break;
        
        board[0][i].setTeam("black");
        board[7][i].setTeam("white");
    }
    
}








*/