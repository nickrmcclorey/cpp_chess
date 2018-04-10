#include <iostream>
#include "ChessPiece.h"
#include "Chessboard.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;


// should be used to set the initial positions of the pieces
Chessboard::Chessboard() {
    this->newGame();
}

void Chessboard::newGame() {
	cout << "activated" << endl;
	for (int i = 0; i < 8; i++) {
		board[1][i].setType("pawn");
		board[1][i].setTeam("black");
		board[6][i].setType("pawn");
		board[6][i].setTeam("white");
	}

	
    for (int i = 0; i < 8; i++) {
		switch (i) {
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
		}


			board[0][i].setTeam("black");
			board[1][i].setTeam("black");
			board[7][i].setTeam("white");
			board[6][i].setTeam("white");
	}
    
	turn = "white";
}

ChessPiece& Chessboard::at(int x, int y) {
	if ((x > 7) || (x < 0) || (y > 7) || (y < 0)){
		throw logic_error("Not valid Index");
	}
	
	return board[x][y];
}

vector<ChessPiece> Chessboard::allPieces() const {

	// vector that will be returned
	vector<ChessPiece> toReturn;
	
	// nested loop that collects all non-empty spots on the board
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			// if spot isn't empty then...
			if (board[row][col].team() != "empty") {
				// append that piece to the list
				toReturn.push_back(board[row][col]);
			}
		}
	}

	return toReturn;
}

void Chessboard::makeJSONfile(string filename) const {
	
	ofstream outfile;
	if (filename.find(".json") == string::npos)
		filename.append(".json");

	string path = "saved_games\\" + filename;

	outfile.open(path.c_str());

	if (!outfile.is_open()) {
		cout << "Failed to opne file" << endl;
		exit(0);
	}

	// outputting pieces object which contains all chess pieces
	outfile << "{\n\t\"pieces\": [\n\t";

	// will contain the JSON data for the pieces. This will be put in outfile
	string object_data;
	int counter = 0;
	// going through each spot in the board
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {

			// if spot isn't empty then...
			if (board[row][col].isEmpty()) {
				// get the json text for that spot and put it in the outfile
				object_data.append(board[row][col].JSON_text(row, col));
				// add a comma
				object_data.append(",");
				counter++;
			}

		}
	}

	cout << "32 = " << counter << endl;
	// erease final comma as this comma will break the JSON validity
	object_data.at(object_data.size() - 1) = ' ';

	// put a cap on the pieces array and tell it what turn it is
	outfile << object_data << "],\n\"turn\":\"" << turn << "\" \n}";
	
	//close file
	outfile.close();
	
}

 
    
    //on top self, on teammate, off board
    bool Chessboard::isAllowedToMove(int location_x, int location_y, int destination_x, int destination_y) const{
        //TODO:: FINISH FUNCTION
        if (location_x == destination_x && location_y == destination_y){
            return false;
        }
        
        return true;
    }
    
    bool Chessboard::canMoveKing(int x, int y) const{
        //TODO:: FINISH FUNCTION
        return true;
    }
    
