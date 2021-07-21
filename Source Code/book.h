#include <iostream>
#include <windows.h>

using namespace std;

class Item{
public:
    void setID(int id);
    int getID();
    void setSignature(string signature);
    string getSignature();
    void setAuthor(string author);
    string getAuthor() ;
    void setTitle(string title);
    string getTitle();
    void setIsbn(string isbn);
    string getIsbn();
    void setPublisher(string publisher);
    string getPublisher();
    void setReleaseYear(int releaseYear);
    int getReleaseYear();
    void setDeleted();
    bool getDeleted();
    void setActive();
    void setDeactive();
    bool getActive();

    Item():id(-1),signature("-1"),author("-1"),title("-1"),
           isbn("-1"),publisher("-1"),releaseYear(-1),deleted(false),active(false){};

private:
    int id;
    string signature;
    string author;
    string title;
    string isbn;
    string publisher;
    int releaseYear;
    bool deleted;
    bool active;
};

class Book: public Item {
public:
    void setPages(int pages);
    int getPages();

    Book():pages(-1) {};
private:
    int pages;
};

class Magazines: public Item {
public:
    void setIssueNmb(int issue);
    int getIssueNmb();
private:
    int issue;
};

void addBook();
void deleteBook(int * curID);
void bookToFile(Book book, string filename);
unsigned long bookFromFile(Book * book, string filename, unsigned long pos );
