#include "System.hpp"

void OnlineReaderSystem::LoadData()
{
    users_manager->LoadData() ;
    books_manager->LoadData() ;

}

OnlineReaderSystem::OnlineReaderSystem():books_manager(new BookManger()), users_manager(new UsersManager())
{


}

OnlineReaderSystem::~OnlineReaderSystem()
{
    cout << "Destuctor: OnlineReaderSystem\n";

    if (books_manager != nullptr)
    {
        delete books_manager;
        books_manager = nullptr;
    }
    if (users_manager != nullptr)
    {
        delete users_manager;
        users_manager = nullptr;
    }
}
void OnlineReaderSystem::Run ()
{
    LoadData() ;
    while(true)
    {
        users_manager->AccessSystem() ;
        if(users_manager->GetCurrentUser()->IsLibraryAdmin())
        {
            AdminView view (*users_manager, *books_manager) ;
            view.Display() ;

        }
        else
        {
            UserView view(*users_manager, *books_manager);
            view.Display();
        }

    }


}

