
#include <string>
using namespace std;

class Chess_piece {
private:
	int xPos;
	int yPos;
	string type;

public:
	// getters
	int x();
	int y();

	// setters
	int setX();
	int setY();


};