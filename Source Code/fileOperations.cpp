#include <iostream>
#include <fstream>
#include <iomanip>
#include "book.h"

using namespace std;

bool stringToFile (string filename, string text) {

    ofstream file(filename,  std::ios::out | std::ios::binary | std::ios::app);

    unsigned int stringLength = text.length();

    if(file.is_open()) file.write( (char*)( &stringLength ), sizeof( stringLength ) );
    else return false;
    if(file.is_open()) file.write( text.c_str(), text.length() );
    if(file.is_open()) file.close();
    return true;
}

bool intToFile(string filename, int number) {
    ofstream file(filename,  std::ios::out | std::ios::binary | std::ios::app);
    if(file.is_open())file.write( (char*)( &number ), sizeof( int ) );
    else return false;
    return true;

}

bool boolToFile(string filename, bool number) {
    bool ret = true;
    if (number == true) ret = intToFile(filename,1);
    else intToFile(filename,0);
    return ret;
}


unsigned long readString(unsigned long pos, string * ret) {
    string ref;
    unsigned int stringLength;

    ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
    file.seekg(pos);

    file.read( (char*)( &stringLength ), sizeof( stringLength ) );
    ref.resize( stringLength );
    file.read( (char*)ref.c_str(), stringLength );
    pos = file.tellg();
    file.close();

    if(!ref.empty()) *ret = ref;
    return pos;
}

unsigned long readInt(unsigned long pos, int * ret) {
    int ref;
    ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
    file.seekg(pos);
    file.read( (char*)( &ref ), sizeof( int ) );
    pos = file.tellg();
    file.close();

    if(!ref == 0)    *ret = ref;
    return pos;
}


unsigned long readBool(unsigned long pos, bool * ret) {
    int tmp = false;
    pos = readInt(pos,&tmp);
    *ret = tmp;
    return pos;
}

int getLastID() {
    int id = 0;
    long pos = 0;
    Book bookTMP;

    while(true) {
        ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
        if (pos >= ULONG_MAX) break;
        pos = bookFromFile(&bookTMP, "libra.bin", pos);
        if (bookTMP.getID() > 0) id = bookTMP.getID();
    }
    return id+1;

}