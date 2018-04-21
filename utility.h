#ifndef utility_h
#define utility_h
using namespace std;

int stoi(char c);
int stoi(string &num_s);

vector<int> moveFromUserString(string raw);
string removeSpaces(string);
vector<string> getGameNames();
void appendToGameNames(string);

#endif