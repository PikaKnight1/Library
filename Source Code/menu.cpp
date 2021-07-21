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
    cout << "Biblioteka C++ \nDostêpne opcje:" << endl;
    cout << " 1. Dodaj Ksi¹¿kê \n 2. Wypisz ksi¹¿ki \n 3. Wyszukaj ksi¹¿kê \n 4. Usuñ ksi¹¿kê\n"
            " 5. Szczegó³owe informacje o ksi¹¿ce\n 6. Stwórz kopiê zapasow¹\n 7. Przywróæ kopiê zapasow¹ \n 0. WyjdŸ" << endl;

    while (!(istringstream(choice) >> choice_converted)) {

        cout << "Wpisz jedn¹, poprawn¹ opcjê z powy¿szej listy: " << endl;
        getline(cin, choice);
    }
    switch (choice_converted) {
        case 0:
            cout << "Dziêkujemy za skorzystanie z programu!" << endl;
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
            cout << "\n\nNieprawid³owa opcja. Spróbuj ponownie!\n\n" << endl;
            break;
    }
    QuitMenu(end);
    return end;
}
bool getINT(int * i) {
    string zd; int j; bool fail = false;

    while (!(istringstream(zd) >> j)) {
        if (fail) cout << "Podana dana nie jest liczb¹, b¹dŸ wychodzi poza zakres. Spróbuj ponownie!\n";
        getline(cin, zd);
        fail = true;
    }
    *i = j;
    return true;
}
bool menuAddBook(int * id) {
    Book book;
    string tmp; int temp;
    cout << "Kreator dodawania ksi¹¿ki: " << endl;
    cout << "Podaj tytu³ ksi¹¿ki: " << endl;
    getline(cin,tmp);
    book.setTitle(tmp);
    cout << "Podaj autora ksi¹¿ki: " << endl;
    getline(cin,tmp);
    book.setAuthor(tmp);
    cout << "Podaj sygnaturê ksi¹¿ki: " << endl;
    getline(cin,tmp);
    book.setSignature(tmp);
    cout << "Podaj numer ISBN ksi¹¿ki: " << endl;
    getline(cin,tmp);
    book.setIsbn(tmp);
    cout << "Podaj wydawcê ksi¹¿ki: " << endl;
    getline(cin,tmp);
    book.setPublisher(tmp);
    cout << "Podaj rok wydania ksi¹¿ki: " << endl;
    getINT(&temp);
    book.setReleaseYear(temp);
    cout << "Podaj liczbê stron ksi¹¿ki: " << endl;
    getINT(&temp);
    book.setPages(temp);
    book.setID(*id);
    *id = *id +1;
    book.setActive();
    bookToFile(book, "libra.bin") ;
    return true;
}
bool menuViewBooks() {
    cout << "Wszystkie ksi¹¿ki obecne w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu³" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;

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

    cout << "\nWybierz po czym chcesz wyszukiwaæ:" << endl;
    cout << "1. Tytu³ \n2. Autor \n3. Wydawnictwo\n4. Sygnatura\n5. Rok wydania \n6. Ksi¹¿ki usuniête z bazy\n0. Wyjdz" << endl;

    while (!(istringstream(choice) >> choice_converted)) {
        cout << "Wpisz jedn¹, poprawn¹ opcjê z powy¿szej listy: ";
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
            cout << "B³êdny numer, wracam do menu g³ównego..." << endl;
            break;
    }
}
void searchByTitle() {
    string choice, temporary;
    long pos;

    cout << "Podaj tytu³ / fragment tytu³u ksi¹¿ki, któr¹ poszukujesz: " << endl;
    getline (cin, choice);
    cout << "Wszystkie ksi¹¿ki spe³niaj¹ce warunek w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu³" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
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

    cout << "Podaj nazwisko / fragment nazwiska autora, którego ksi¹¿ki poszukujesz: " << endl;
    getline (cin, choice);
    cout << "Wszystkie ksi¹¿ki spe³niaj¹ce warunek w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu³" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
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

    cout << "Podaj nazwê / fragment nazwy wydawnictwa, którego ksi¹¿ki poszukujesz: " << endl;
    getline (cin, choice);
    cout << "Wszystkie ksi¹¿ki spe³niaj¹ce warunek w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu³" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
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

    cout << "Podaj sygnaturê ksi¹¿ki, któr¹ poszukujesz: " << endl;
    getline (cin, choice);
    cout << "Wszystkie ksi¹¿ki spe³niaj¹ce warunek w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu³" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
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

    cout << "Podaj rok, z którego ksi¹zki chcesz zobaczyæ: " << endl;
    getINT(&i);
    cout << "Wszystkie ksi¹¿ki spe³niaj¹ce warunek w bibliotece: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu³" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
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

    cout << "Poni¿sze ksi¹¿ki zosta³y usuniête z bazy: " << endl;
    cout << setw(5) << "ID" << setw(30) << "Tytu³" << setw(30) << "Autor"<< setw(30) << "Wydawca" << endl;
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
    cout << "Podaj ID ksi¹¿ki, o której chcesz otrzymaæ szczegó³owe informacje:" << endl;
    getINT(&id);

    while(true) {
        ifstream file("libra.bin", std::ios::in | std::ios::binary); // loading file
        if (pos >= ULONG_MAX) break;
        pos = bookFromFile(&bookTMP, "libra.bin", pos);

        if (bookTMP.getID() != 0 && bookTMP.getID() == id) {
            cout << setw(30) << "ID: " << bookTMP.getID() << endl;
            cout << setw(30) << "Tytu³: " << bookTMP.getTitle() << endl;
            cout << setw(30) << "Autor: " << bookTMP.getAuthor() << endl;
            cout << setw(30) << "Wydawca: " << bookTMP.getPublisher() << endl;
            cout << setw(30) << "Sygnatura: " << bookTMP.getSignature() << endl;
            cout << setw(30) << "ISBN: " << bookTMP.getIsbn() << endl;
            cout << setw(30) << "Rok wydania: " << bookTMP.getReleaseYear() << endl;
            cout << setw(30) << "Liczba stron: " << bookTMP.getPages() << endl;
            cout << setw(30) << "Ksi¹¿ka zosta³a usuniêta?: ";
            if (bookTMP.getDeleted()) cout << "TAK " << endl;
            else cout << "NIE " << endl;
        }
    }
}
void menuBackUp() {
    cout << "Tworzê kopiê zapasow¹..." << endl;
    CopyFile("libra.bin","libra.backup",TRUE);         //tworzê kopiê zapasow¹ pliku
    cout << "Utworzono kopiê zapasow¹ bazy danych.\nPlik: libra.backup, znajduj¹cy siê w folderze programu" << endl;
}
void menuRestore() {
    cout << "Program odzyska dane z pliku libra.backup, znajduj¹cego siê w folderze programu." << endl;
    cout << "UWAGA! Spowoduje to utratê danych dodawanych lub edytowanych od ostatniej kopii zapasowej" << endl;
    cout << "Wpisz T jeœli chcesz przywróciæ starsz¹ wersjê bazy. Wpisz cokolwiek innego, by anulowaæ" << endl;
    string s;
    cin >> s;
    fstream fileStream;
    fileStream.open("libra.backup");
    if(fileStream.fail()) cout << "B³¹d! Nie znaleziono pliku z kopi¹ zapasow¹!" << endl;
    else {
        if (s == "T" || s == "t") {
            DeleteFile("libra.bin");
            CopyFile("libra.backup", "libra.bin", TRUE);
            cout << "Przywrócono dane...";
        } else cout << "Anulowano przywracanie...";
    }
    QuitMenu(0);
}

void QuitMenu(bool end) {
    if (!end) cout << "\n Wciœnij Enter by wróciæ do menu..." << endl;
    else cout << "\n Wciœnij Enter by wyjœæ..." << endl;
    string temporary;
    getline(cin,temporary );
}