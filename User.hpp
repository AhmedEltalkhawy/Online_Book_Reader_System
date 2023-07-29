#ifndef USER_H_
#define USER_H_

#include"Book.hpp"

class User
{
private :
    string name ;
    string user_name ;
    string password ;
    int user_id ;
    string email ;
    bool  is_library_admin   ;
    vector <BookReadingSession*> readingsession ;

public :
    User() ;
    ~User() ;
    void Read(const string &user_name) ;
    BookReadingSession* AddReadingSession (Book* book) ;
    const vector<BookReadingSession*>& GetReadingSession() const ;
    void SetUserName (const string& user_name) ;
    const string& GetUserName () const ;
    void SetName (const string& name) ;
    const string& GetName () const ;
    void SetPassword (const string& password) ;
    const string& GetPassword () const ;
    void SetEmail (const string& email) ;
    const string& GetEmail () const ;
    bool IsLibraryAdmin() const ;
    void SetIsLibraryAdmin(bool isLibraryAdmin) ;
    string ToString() const ;




};

class UsersManager
{
private :

    User *current_user = nullptr ;
    map<string , User*> usersname_map ;
    void FreeLoadedData () ;


public :
    UsersManager() ;
    ~UsersManager() ;
    void AccessSystem () ;
    void DoLogin () ;
    void DoSignUp () ;
    void LoadData () ;
    const map<string , User*> &GetUserNameMap () const ;
    const User* GetCurrentUser() const;
    BookReadingSession* AddReadingSession (Book *book) ;


};

class UserView
{
private :

    UsersManager &users_manager ;
    BookManger &books_manager ;


public :

    UserView(UsersManager &users_manager, BookManger &books_manager) ;
    ~UserView() ;
    void Display () ;
    void ViewProfile () ;
    void DisplaySession (BookReadingSession* session) ;
    void ListAvailableBooks() ;
    void ViewCurrentReadingSession () ;

};

class AdminView
{
private :

    UsersManager &users_manager ;
    BookManger &books_manager ;

public :

      AdminView (UsersManager  &users_manager , BookManger  &books_manager) ;
      void Display () ;
      void ViewProfile () ;
      void AddBook() ;
};


#endif // USER_H_
