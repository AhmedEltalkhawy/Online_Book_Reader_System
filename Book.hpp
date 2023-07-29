
#ifndef BOOK_H_
#define BOOK_H_
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int ReadInt(int low , int high) ;
int ShowReadMenu (const vector<string> &choices) ;
string GetCurrentTimeDate() ;





class Book
{
private :

    string isbn ;
    string title ;
    string author ;
    int pagenumber ;
    vector <string> pages ;

public :

    Book() ;
    void Read () ;
    const string &GetIsbn()const ;
    void SetIsbn(const string& isbn) ;
    const string& GetAuthor() const ;
    void SetAuthor (const string& author) ;
    void SetTitle (const string& title) ;
    const string& GetTitle () ;
    void  SetPages (const vector<string>& pages) ;
    const vector<string>& GetPages () const ;
    string ToString() ;

};
class BookReadingSession
{
private :

    Book* book ;
    int current_page ;
    string last_access_date ;

public :

    BookReadingSession() ;
    BookReadingSession(Book* book) ;
    void NextPage() ;
    void PreviousPage() ;
    const  Book* GetBook ()const ;
    const string GetLastAccessDate () const ;
    void ResetLastAccessDate () ;
    const int GetCurrentPage () const ;
    string GetCurrentPageContent() ;
    string PageIdxStr() ;
    string ToString () ;

};
class BookManger
{
private :
    map<string , Book*> isbn_book_map ;
    void FreeLoadedData () ;
public :
    BookManger() ;
    ~BookManger() ;
    void LoadData () ;
    void AddBook (Book *book) ;
    const map<string, Book*>& GetIsbnToBookMap() const ;



};


#endif // BOOK_H_
