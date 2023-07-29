#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "User.hpp"
#include "Book.hpp"

class OnlineReaderSystem
{
private :

    UsersManager *users_manager ;
    BookManger   *books_manager ;
    void LoadData() ;

public :
    OnlineReaderSystem()  ;
    ~OnlineReaderSystem() ;
    void Run () ;



};
#endif // SYSTEM_H_
