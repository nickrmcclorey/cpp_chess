#ifndef utility_h
#define utility_h
using namespace std;

int toInt(char c);
int toInt(string num_s);
int askInteger(string prompt);
bool isInt(string input);
vector<int> moveFromUserString(string raw);
string removeSpaces(string);
vector<string> getGameNames();
void appendToGameNames(string);

#endif