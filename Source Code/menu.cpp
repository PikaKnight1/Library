#include "menu.h"
#include "book.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

bool mainMenu(int * curID) {

    bool end = false;
    string choice = "";
    int choice_converted;
    cout << "Biblioteka C++ \nDost�pne opcje:" << endl;
    cout << " 1. Dodaj Ksi��k� \n 2. Wypisz ksi��ki \n 3. Wyszukaj ksi��k� \n 4. Usu� ksi��k�\n"
            " 5. Szczeg�owe informacje o ksi��ce\n 6. Stw�rz kopi� zapasow�\n 7. Przywr�� kopi� zapasow� \n 0. Wyjd�" << endl;

    while (!(istringstream(choice) >> choice_converted)) {

        cout << "Wpisz jedn�, poprawn� opcj� z powy�szej listy: " << endl;
        getline(cin, choice);
    }
    switch (choice_converted) {
        case 0:
            cout << "Dzi�kujemy za skorzystanie z programu!" << endl;
            end = 1;
            break;
        case 1:
            menuAddBook(curID);
            end = 0;
            break;
        case 2:
            menuViewBooks();
            end = 0;
            break;
        case 3:
            menuSearchBooks();
            end = 0;
            break;
        case 4:
            deleteBook(curID);
            end = 0;
            break;
        case 5:
            menuDetailedBook();
            break;
        case 6:
            menuBackUp();
            break;
        case 7:
            menuRestore();
            break;
        default:
            cout << "\n\nNieprawid�owa opcja. Spr�buj ponownie!\n\n" << endl;
            break;
    }
    QuitMenu(end);
    return end;
}
bool getINT(int * i) {
    string zd; int j; bool fail = false;

    while (!(istringstream(zd) >> j)) {
        if (fail) cout << "Podana dana nie jest liczb�, b�d� wychodzi poza zakres. Spr�buj ponownie!\n";
        getline(cin, zd);
        fail = true;
    }
    *i = j;
    return true;
}
bool menuAddBook(int * id) {
    Book book;
    string tmp; int temp;
    cout << "Kreator dodawania ksi��ki: " << endl;
    cout << "Podaj tytu� ksi��ki: " << endl;
    getline(cin,tmp);
    book.setTitle(tmp);
    cout << "Podaj autora ksi��ki: " << endl;
    getline(cin,tmp);
    book.setAuthor(tmp);
    cout << "Podaj sygnatur� ksi��ki: " << endl;
    getline(cin,tmp);
    book.setSignature(tmp);
    cout << "Podaj numer ISBN ksi��ki: " << endl;
    getline(cin,tmp);
    book.setIsbn(tmp);
    cout << "Podaj wydawc� ksi��ki: " << endl;
    getline(cin,tmp);
    book.setPublisher(tmp);
    cout << "Podaj rok wydania ksi��ki: " << endl;
    getINT(&temp);
    book.setReleaseYear(temp);
    cout << "Podaj liczb� stron ksi��ki: " << endl;
    getINT(&temp);
    book.setPages(temp);
    book.setID(*id);
    *id = *id +1;
    book.setActive();
    bookToFile(book, "libra.bin") ;
    return true;
}
bool menuViewBooks() {
    cout << "Wszystkie ksi��ki obecne w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu�" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;

    long pos = 0;
    while(true) {
        Book bookTMP;
        ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
        if (pos >= ULONG_MAX) break;
        pos = bookFromFile(&bookTMP, "libra.bin", pos);
        if (bookTMP.getActive() && !bookTMP.getDeleted() && bookTMP.getID() != 0) cout << setw(5) << bookTMP.getID() << setw(30) << bookTMP.getTitle() << setw(30) << bookTMP.getAuthor() << setw(30) << bookTMP.getPublisher() <<  endl;
    }

    return true;
}
void menuSearchBooks() {
    string choice = "";
    string temporary;
    int choice_converted;
    Book bookTMP;
    long pos = 0;
    size_t found;

    cout << "\nWybierz po czym chcesz wyszukiwa�:" << endl;
    cout << "1. Tytu� \n2. Autor \n3. Wydawnictwo\n4. Sygnatura\n5. Rok wydania \n6. Ksi��ki usuni�te z bazy\n0. Wyjdz" << endl;

    while (!(istringstream(choice) >> choice_converted)) {
        cout << "Wpisz jedn�, poprawn� opcj� z powy�szej listy: ";
        getline(cin, choice);
    }

    switch (choice_converted) {
        case 1:
            searchByTitle();
            break;
        case 2:
            searchByAuthor();
            break;
        case 3:
            searchByPublisher();
            break;
        case 4:
            searchBySignature();
            break;
        case 5:
            searchByYear();
            break;
        case 6:
            searchDeleted();
            break;
        case 0:
            break;
        default:
            cout << "B��dny numer, wracam do menu g��wnego..." << endl;
            break;
    }
}
void searchByTitle() {
    string choice, temporary;
    long pos;

    cout << "Podaj tytu� / fragment tytu�u ksi��ki, kt�r� poszukujesz: " << endl;
    getline (cin, choice);
    cout << "Wszystkie ksi��ki spe�niaj�ce warunek w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu�" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
    while(true) {
        Book bookTMP;

        ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
        if (pos >= ULONG_MAX) break;
        pos = bookFromFile(&bookTMP, "libra.bin", pos);
        if (!bookTMP.getDeleted() && bookTMP.getActive() && bookTMP.getID() != 0) {
            if(bookTMP.getTitle().find(choice) != std::string::npos)
                cout << setw(5) << bookTMP.getID() << setw(30) << bookTMP.getTitle() << setw(30)
                     << bookTMP.getAuthor() << setw(30) << bookTMP.getPublisher() << endl;
        }
    }

}
void searchByAuthor() {
    string choice, temporary;
    long pos;

    cout << "Podaj nazwisko / fragment nazwiska autora, kt�rego ksi��ki poszukujesz: " << endl;
    getline (cin, choice);
    cout << "Wszystkie ksi��ki spe�niaj�ce warunek w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu�" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
    while(true) {
        Book bookTMP;
        ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
        if (pos >= ULONG_MAX) break;
        pos = bookFromFile(&bookTMP, "libra.bin", pos);
        if (!bookTMP.getDeleted() && bookTMP.getActive() && bookTMP.getID() != 0) {
            if(bookTMP.getAuthor().find(choice) != std::string::npos)
                cout << setw(5) << bookTMP.getID() << setw(30) << bookTMP.getTitle() << setw(30)
                     << bookTMP.getAuthor() << setw(30) << bookTMP.getPublisher() << endl;
        }
    }

}
void searchByPublisher() {
    string choice, temporary;
    long pos;

    cout << "Podaj nazw� / fragment nazwy wydawnictwa, kt�rego ksi��ki poszukujesz: " << endl;
    getline (cin, choice);
    cout << "Wszystkie ksi��ki spe�niaj�ce warunek w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu�" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
    while(true) {
        Book bookTMP;

        ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
        if (pos >= ULONG_MAX) break;
        pos = bookFromFile(&bookTMP, "libra.bin", pos);
        if (!bookTMP.getDeleted() && bookTMP.getActive() && bookTMP.getID() != 0) {
            if(bookTMP.getPublisher().find(choice) != std::string::npos)
                cout << setw(5) << bookTMP.getID() << setw(30) << bookTMP.getTitle() << setw(30)
                     << bookTMP.getAuthor() << setw(30) << bookTMP.getPublisher() << endl;
        }
    }

}
void searchBySignature() {
    string choice, temporary;
    long pos;

    cout << "Podaj sygnatur� ksi��ki, kt�r� poszukujesz: " << endl;
    getline (cin, choice);
    cout << "Wszystkie ksi��ki spe�niaj�ce warunek w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu�" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
    while(true) {
        Book bookTMP;

        ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
        if (pos >= ULONG_MAX) break;
        pos = bookFromFile(&bookTMP, "libra.bin", pos);
        if (!bookTMP.getDeleted() && bookTMP.getActive() && bookTMP.getID() != 0) {
            if(bookTMP.getSignature().find(choice) != std::string::npos)
                cout << setw(5) << bookTMP.getID() << setw(30) << bookTMP.getTitle() << setw(30)
                     << bookTMP.getAuthor() << setw(30) << bookTMP.getPublisher() << endl;
        }
    }

}
void searchByYear() {
    string choice, temporary;
    long pos;
    int i;

    cout << "Podaj rok, z kt�rego ksi�zki chcesz zobaczy�: " << endl;
    getINT(&i);
    cout << "Wszystkie ksi��ki spe�niaj�ce warunek w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu�" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
    while(true) {
        Book bookTMP;

        ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
        if (pos >= ULONG_MAX) break;
        pos = bookFromFile(&bookTMP, "libra.bin", pos);
        if (!bookTMP.getDeleted() && bookTMP.getActive() && bookTMP.getID() != 0) {
            if(bookTMP.getReleaseYear() == i)
                cout << setw(5) << bookTMP.getID() << setw(30) << bookTMP.getTitle() << setw(30)
                     << bookTMP.getAuthor() << setw(30) << bookTMP.getPublisher() << endl;
        }
    }

}
void searchDeleted() {
    string choice, temporary;
    long pos;
    int i;

    cout << "Poni�sze ksi��ki zosta�y usuni�te z bazy: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu�" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
    while(true) {
        Book bookTMP;

        ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
        if (pos >= ULONG_MAX) break;
        pos = bookFromFile(&bookTMP, "libra.bin", pos);
        if (bookTMP.getDeleted() && bookTMP.getActive() && bookTMP.getID() != 0) {
                cout << setw(5) << bookTMP.getID() << setw(30) << bookTMP.getTitle() << setw(30)
                     << bookTMP.getAuthor() << setw(30) << bookTMP.getPublisher() << endl;
        }
    }

}
void menuDetailedBook() {
    int id, pos = 0;
    Book bookTMP;
    cout << "Podaj ID ksi��ki, o kt�rej chcesz otrzyma� szczeg�owe informacje:" << endl;
    getINT(&id);

    while(true) {
        ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
        if (pos >= ULONG_MAX) break;
        pos = bookFromFile(&bookTMP, "libra.bin", pos);

        if (bookTMP.getID() != 0 && bookTMP.getID() == id) {
            cout << setw(30) << "ID: " << bookTMP.getID() << endl;
            cout << setw(30) << "Tytu�: " << bookTMP.getTitle() << endl;
            cout << setw(30) << "Autor: " << bookTMP.getAuthor() << endl;
            cout << setw(30) << "Wydawca: " << bookTMP.getPublisher() << endl;
            cout << setw(30) << "Sygnatura: " << bookTMP.getSignature() << endl;
            cout << setw(30) << "ISBN: " << bookTMP.getIsbn() << endl;
            cout << setw(30) << "Rok wydania: " << bookTMP.getReleaseYear() << endl;
            cout << setw(30) << "Liczba stron: " << bookTMP.getPages() << endl;
            cout << setw(30) << "Ksi��ka zosta�a usuni�ta?: ";
            if (bookTMP.getDeleted()) cout << "TAK " << endl;
            else cout << "NIE " << endl;
        }
    }
}
void menuBackUp() {
    cout << "Tworz� kopi� zapasow�..." << endl;
    CopyFile("libra.bin","libra.backup",TRUE);         //tworz� kopi� zapasow� pliku
    cout << "Utworzono kopi� zapasow� bazy danych.\nPlik: libra.backup, znajduj�cy si� w folderze programu" << endl;
}
void menuRestore() {
    cout << "Program odzyska dane z pliku libra.backup, znajduj�cego si� w folderze programu." << endl;
    cout << "UWAGA! Spowoduje to utrat� danych dodawanych lub edytowanych od ostatniej kopii zapasowej" << endl;
    cout << "Wpisz T je�li chcesz przywr�ci� starsz� wersj� bazy. Wpisz cokolwiek innego, by anulowa�" << endl;
    string s;
    cin >> s;
    fstream fileStream;
    fileStream.open("libra.backup");
    if(fileStream.fail()) cout << "B��d! Nie znaleziono pliku z kopi� zapasow�!" << endl;
    else {
        if (s == "T" || s == "t") {
            DeleteFile("libra.bin");
            CopyFile("libra.backup", "libra.bin", TRUE);
            cout << "Przywr�cono dane...";
        } else cout << "Anulowano przywracanie...";
    }
    QuitMenu(0);
}

void QuitMenu(bool end) {
    if (!end) cout << "\n Wci�nij Enter by wr�ci� do menu..." << endl;
    else cout << "\n Wci�nij Enter by wyj��..." << endl;
    string temporary;
    getline(cin,temporary );
}