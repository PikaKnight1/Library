#include <iostream>
#include <fstream>
using namespace std;

bool stringToFile (string filename, string text);
bool intToFile(string filename, int number);
bool boolToFile(string filename, bool boolean);

unsigned long readString(unsigned long pos, string * ret);
unsigned long readInt(unsigned long pos, int * ret);
unsigned long readBool(unsigned long pos, bool * ret);

int getLastID();