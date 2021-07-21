#include <iostream>
using namespace std;


bool mainMenu(int * curID);
bool menuAddBook(int * id);
bool getINT(int * i);
bool menuViewBooks();
void menuSearchBooks();
void searchByTitle();
void searchByAuthor();
void searchByPublisher();
void searchBySignature();
void searchByYear();
void searchDeleted();
void menuDetailedBook();
void menuBackUp();
void menuRestore();

void QuitMenu(bool end);