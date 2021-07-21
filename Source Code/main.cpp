#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <algorithm>

#include "fileOperations.h"
#include "book.h"
#include "menu.h"

using namespace std;


int main() {
    system("chcp 1250");
    setlocale( LC_ALL, "" );
    system("cls");

    int curID = getLastID();
    if (curID == 0) curID = 1;

    bool temp = false;
    while(!temp) temp = mainMenu(&curID);
    return 0;
}

