#include <iostream>
#include <windows.h>
#include <filesystem>
#include <iomanip>
#include "book.h"
#include "fileOperations.h"
#include "menu.h"

using namespace std;
void Item::setID(int id){
    this->id = id;
}
int Item::getID() {
    return id;
}

void Item::setSignature(string signature) {
    this->signature = signature;
}
string Item::getSignature() {
    return signature;
}
void Item::setAuthor(string author){
    this->author = author;
}
string Item::getAuthor(){
    return author;
}
void Item::setTitle(string title){
    this->title = title;
}
string Item::getTitle(){
    return title;
}
void Item::setIsbn(string isbn){
    this->isbn = isbn;
}
string Item::getIsbn() {
    return isbn;
}
void Item::setPublisher(string publisher){
    this->publisher = publisher;
}
string Item::getPublisher(){
    return publisher;
}
void Item::setReleaseYear(int releaseYear){
    this->releaseYear = releaseYear;
}
int Item::getReleaseYear(){
    return releaseYear;
}
void Item::setDeleted(){
    this->deleted = true;
}
bool Item::getDeleted(){
    return deleted;
}
void Item::setActive(){
    this->active = true;
}
void Item::setDeactive(){
    this->active = false;
}

bool Item::getActive(){
    return active;
}

void Book::setPages(int pages){
    this->pages = pages;
}
int Book::getPages(){
    return pages;
}

void Magazines::setIssueNmb(int issue){
    this->issue = issue;
}
int Magazines::getIssueNmb(){
    return issue;
}

void addBook() {
    Book book;
    string tmp;
    cout << "Witam w kreatorze dodawania ksi¹¿ki!" << endl;
    cout << "Podaj sygnaturê:" << endl;
    getline(cin, tmp);
    book.setSignature(tmp);

}

void bookToFile(Book book, string filename) {
    intToFile(filename,book.getID());
    stringToFile(filename,book.getSignature());
    stringToFile(filename,book.getAuthor());
    stringToFile(filename,book.getTitle());
    stringToFile(filename,book.getIsbn());
    stringToFile(filename,book.getPublisher());
    intToFile(filename,book.getReleaseYear());
    boolToFile(filename,book.getDeleted());
    boolToFile(filename,book.getActive());
    intToFile(filename,book.getPages());
}
unsigned long bookFromFile(Book * book, string filename, unsigned long pos ) {
    long posi = pos;
    int temp; string tempo; bool tempor;
    posi = readInt(posi,&temp);
    book->setID(temp);
    posi = readString(posi, &tempo);
    book->setSignature(tempo);
    posi = readString(posi, &tempo);
    book->setAuthor(tempo);
    posi = readString(posi, &tempo);
    book->setTitle(tempo);
    posi = readString(posi, &tempo);
    book->setIsbn(tempo);
    posi = readString(posi, &tempo);
    book->setPublisher(tempo);
    posi = readInt(posi,&temp);
    book->setReleaseYear(temp);
    posi = readBool(posi,&tempor);
    if(tempor) book->setDeleted();
    posi = readBool(posi,&tempor);
    if(tempor) book->setActive();
    posi = readInt(posi,&temp);
    book->setPages(temp);
    return posi;
}

void deleteBook(int * curID) {
    CopyFile("libra.bin","libra.bin.bak",TRUE);         //tworzê kopiê zapasow¹ pliku

    int id = *curID;

    Book book;
    int del = -1;
    cout << "Podaj ID ksi¹¿ki, któr¹ chcesz usun¹æ" << endl;

    getINT(&del);

    long posi = 0, oldposi = 0, idPos = 0;

    bool found = false;

    while(true) {
        if(posi >= ULONG_MAX) break;
        oldposi = posi;
        posi = bookFromFile(&book, "libra.bin",posi);
        if(del == book.getID()) {
            idPos = oldposi;
            found = true;
        }
    }

    int ret; string ret2;
    idPos = readInt(idPos,&ret); //pomijam id

    //pomijam stringi
    for (int i = 0; i < 5; i++)     idPos = readString(idPos, &ret2);
    //pomijam inta z roku wydania
    idPos = readInt(idPos,&ret);
    //mam pozycjê boola mojego, który jest... intem
    readInt(idPos, &ret);

    int nnn = 1;
    if (found) {
        ofstream file("libra.bin", std::ios::out | std::ios::in | std::ios::binary);
        file.seekp(idPos);
        if (file.is_open())file.write((char *) (&nnn), sizeof(int));
    }


    if(!found) cout << "Nie znaleziono ksi¹¿ki o takim ID";

    //jeœli wszystko zadzia³a³o, nie pojawi³ siê ¿aden b³¹d, usuwany jest plik .bak
    DeleteFile("libra.bin.bak");
}