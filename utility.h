#ifndef utility_h
#define utility_h
using namespace std;

int stoi(char c);
int stoi(string &num_s);
#define strcmpi strcmp
vector<int> moveFromUserString(string raw);
vector<string> getGameNames();
void appendToGameNames(string);

#endif