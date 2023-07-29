
#include "Book.hpp"

Book::Book()
{

}
const string& Book::GetIsbn()const
{
    return isbn ;
}
void Book::SetIsbn(const string& isbn)
{
    this->isbn = isbn ;

}
const string& Book::GetAuthor () const
{
    return author ;
}
void Book::SetAuthor (const string& author)
{
    this->author = author ;
}
void Book::SetTitle (const string& title)
{
    this->title = title ;
}

const string& Book::GetTitle ()
{
    return title ;
}

void Book::SetPages (const vector<string>& pages)
{
    this->pages = pages ;
}

const vector<string>& Book::GetPages () const
{
    return pages ;
}
string Book::ToString()
{
    return title;
}

void Book::Read()
{
        string str ;

        cout << "Enter ISBN : " ;
        cin  >> str ;
        SetIsbn(str) ;

        cout << "Enter Author Name : " ;
        cin  >> str ;
        SetAuthor(str) ;

        cout << "Enter Title : " ;
        cin >> str ;
        SetTitle(str) ;

        cout << "Enter How many pages : " ;
		int pages_count ;
		cin >> pages_count ;

		for(int page = 0 ; page< pages_count ; ++page)
        {
            cout << "Enter page # " << page + 1 << ": ";
			cin >> str;
            pages.push_back(str) ;
        }


}


BookReadingSession::BookReadingSession():book(nullptr)
{

}
BookReadingSession::BookReadingSession(Book* book) : book(book) , current_page(0)  , last_access_date(GetCurrentTimeDate())
{

}
 const Book* BookReadingSession::GetBook ()const
{
    return book ;
}


void BookReadingSession::NextPage()
{
    if(current_page <GetBook()->GetPages().size()-1)
    {
        ++current_page ;
    }

}
void BookReadingSession::PreviousPage()
{
    if(current_page > 1)
    {
        --current_page ;
    }
}

const string BookReadingSession::GetLastAccessDate () const
{
    return last_access_date ;
}
void BookReadingSession::ResetLastAccessDate ()
{
    last_access_date = GetCurrentTimeDate() ;
}
const int BookReadingSession::GetCurrentPage () const
{
    return current_page ;
}
string BookReadingSession::GetCurrentPageContent()
{
    return GetBook()->GetPages()[current_page] ;
}

string BookReadingSession::PageIdxStr()
{
    ostringstream oss ;
    oss<< "page " << GetCurrentPage() +1 << "/ " << book->GetPages().size() ;
    return oss.str() ;
}
string BookReadingSession::ToString ()
{
    ostringstream oss ;
    oss<<book->GetTitle() << " -"<< PageIdxStr() << "- LastAccess Date -" << GetLastAccessDate() ;
    return oss.str() ;
}
BookManger::BookManger()
{
    ;
}
BookManger::~BookManger()
{
    cout << "destructor :)" ;
    FreeLoadedData() ;
}
void BookManger::FreeLoadedData ()
{
for(auto pair : isbn_book_map)
{
    delete pair.second ;
}
isbn_book_map.clear() ;
}
void BookManger::LoadData ()
{
    //cout<<"BooksManager: LoadDatabase\n";
    FreeLoadedData() ;

    Book* book1 = new Book();
    book1->SetIsbn("00001");
    book1->SetAuthor("Ahmed");
    book1->SetTitle("C++ how to program");
    vector<string> pages1 = { "A C++", "B C++", "C C++", "D C++", "E C++" };
    book1->SetPages(pages1);
    AddBook(book1);

    Book* book2 = new Book();
    book2->SetIsbn("00002");
    book2->SetAuthor("Morad");
    book2->SetTitle("Intro to algo");
    vector<string> pages2 = { "A Algo", "B Algo", "C Algo", "D Algo", "E " };
    book2->SetPages(pages2);
    AddBook(book2);

    Book* book3 = new Book();
    book3->SetIsbn("00003");
    book3->SetAuthor("Morad");
    book3->SetTitle("Data Structures in C++");
    vector<string> pages3 = { "A Data", "B Data", "C Data", "D Data", "E Data" };
    book3->SetPages(pages3);
    AddBook(book3);

}
void BookManger::AddBook (Book *book)
{
    isbn_book_map[book->GetIsbn()] = book ;
}
const map<string, Book*>& BookManger::GetIsbnToBookMap() const
{
   return isbn_book_map;
}

