#include"User.hpp"
User::User() : is_library_admin(false)
{

}
User::~User()
{
    for(auto& it :readingsession)
    {
        delete it ;
    }
    readingsession.clear() ;
}

BookReadingSession* User::AddReadingSession (Book* book)
{
    BookReadingSession* newsession = new BookReadingSession(book) ;
    readingsession.push_back(newsession) ;
    return newsession ;

}
const vector<BookReadingSession*>& User::GetReadingSession() const
{
    return readingsession ;
}
void User::SetUserName (const string& user_name)
{
    this->user_name = user_name ;
}
const string& User::GetUserName () const
{
    return user_name ;
}
void User::SetName (const string& name)
{
    this->name = name ;
}
const string& User::GetName () const
{
    return name ;
}
void User::SetPassword (const string& password)
{
    this->password = password ;
}
const string& User::GetPassword () const
{
    return password ;
}
void User::SetEmail (const string& email)
{
    this->email = email ;
}
const string& User::GetEmail () const
{
    return email ;
}
bool User::IsLibraryAdmin() const
{
    return is_library_admin;
}
void User::SetIsLibraryAdmin(bool isLibraryAdmin)
{
    is_library_admin = isLibraryAdmin;
}

void User::Read (const string &user_name)
{

    SetUserName(user_name) ;
    string str ;

    cout << "Enter Name : " ;
    cin >> str ;
    SetName(str) ;

    cout << "Enter Password : " ;
    cin >> str ;
    SetPassword(str) ;

    cout << "Enter Email : " ;
    cin >> str ;
    SetEmail(str) ;
}
string User::ToString() const
{
    ostringstream oss;
    oss << "Name: " << name;
    if (IsLibraryAdmin())
        oss << " | Admin";
    oss << "\n";
    oss << "Email: " << email << "\n";
    oss << "User name: " << user_name << "\n";
    return oss.str();
}


UsersManager::UsersManager()
{
    ;
}
UsersManager::~UsersManager()
{
    cout << "destructor :)" ;
    FreeLoadedData() ;
}

void UsersManager::DoLogin ()
{
    cout << "login :) \n" ;
    string user_name, pass;
    while(1)
    {
        cout <<"Enter user user_name & password: ";
        cin >> user_name >> pass;

        if(!usersname_map.count(user_name))
        {
            cout<< "invalid user name or password try again :) \n" ;
            continue ;
        }
        User* exist_user = usersname_map[user_name] ;
        if (exist_user->GetPassword() != pass)
        {
           cout<< "invalid user name or password try again :) \n" ;
            continue ;
        }
        current_user = exist_user ;
        break ;
    }



}
void UsersManager::DoSignUp()
{
     cout << "SignUP \n" ;
    string user_name ;

    while(true)
    {
        cout<<"Enter user name :" ;
        cin >> user_name ;
        if(usersname_map.count(user_name))
        {
            cout<< "this user name is exist enter another one \n" ;
            continue ;
        }
        break ;
    }
    current_user = new User() ;
    current_user->Read(user_name) ;
    usersname_map[user_name] = current_user ;

}

void UsersManager::AccessSystem ()
{
    int choice = ShowReadMenu({"Login" , "SignUp"}) ;
    if(choice == 1)
    {
        DoLogin() ;
    }
    else
    {
        DoSignUp() ;
    }
}
void UsersManager::LoadData ()
{
    FreeLoadedData() ;
    //cout << "User Manger Load Data Base : \n" ;

    User* user1 = new User() ;
    user1->SetUserName("Ahmed_11") ;
    user1->SetIsLibraryAdmin(true) ;
    user1->SetPassword("111") ;
    user1->SetEmail("ahmedeltalkhawy962@gmail.com") ;
    user1->SetName("AhmedEltalkhawy") ;
    usersname_map[user1->GetUserName()] = user1 ;

    User* user2 = new User() ;
    user2->SetUserName("malak_11") ;
    user2->SetIsLibraryAdmin(false) ;
    user2->SetPassword("111") ;
    user2->SetEmail("malakeltalkhawy962@gmail.com") ;
    user2->SetName("MalakEltalkhawy") ;
    usersname_map[user2->GetUserName()] = user2;

}
const map<string , User*> &UsersManager::GetUserNameMap () const
{
    return usersname_map ;
}
const User* UsersManager::GetCurrentUser() const
{
    return current_user;
}
BookReadingSession*UsersManager:: AddReadingSession (Book *book)
{
    return current_user->AddReadingSession(book) ;
}
void UsersManager::FreeLoadedData ()
{
    for(auto pair : usersname_map)
    {
        delete pair.second ;
    }
    current_user = nullptr ;
    usersname_map.clear() ;
}


UserView::UserView(UsersManager &users_manager, BookManger &books_manager) : users_manager(users_manager) ,books_manager(books_manager)
{

}
UserView::~UserView()
{

}

void UserView::Display()
{
    const User* user = users_manager.GetCurrentUser() ;
    cout<< "\nHello " << "-" << user->GetName() << " | user view \n\n" ;
    vector <string> menu ;
    menu.push_back("View Profile");
    menu.push_back("List & Select from My Reading History");
    menu.push_back("List & Select from Available Books");
    menu.push_back("Logout");
    while(true)
    {
        int choice = ShowReadMenu(menu) ;
        if (choice == 1)
        {
            ViewProfile() ;
        }
        else if (choice == 2)
        {
            ViewCurrentReadingSession() ;
        }
        else if (choice == 3)
        {
           ListAvailableBooks() ;
        }
        else
            break ;
    }

}

void UserView::ViewProfile ()
{
    const User *user = users_manager.GetCurrentUser() ;
    cout <<"\n" << user->ToString() << "\n\n";
}

void UserView::DisplaySession (BookReadingSession* session)
{
    vector<string> menu;
    menu.push_back("Next Page");
    menu.push_back("Previous Page");
    menu.push_back("Stop Reading");

    while (true)
    {
        cout << "Current Page: " << session->PageIdxStr() << "\n\n";
        cout << "page content : " <<session->GetCurrentPageContent() << "\n\n";

        int choice = ShowReadMenu(menu);
        if (choice == 1)
            session->NextPage();
        else if (choice == 2)
            session->PreviousPage();
        else
            break;
    }
    session->ResetLastAccessDate();

}

void UserView::ListAvailableBooks()
{
    const map<string , Book*> &isbn_book_map =  books_manager.GetIsbnToBookMap() ;
  cout << "\nOur current book collection:\n\n";
  int idx = 0 ;
  for( auto it = isbn_book_map.begin(); it != isbn_book_map.end(); ++it)
  {
      cout << ++idx << " " << it->second->ToString() << "\n" ;
  }
  cout<<"\n" ;
  if (idx == 0)
  {
      cout<< "No Books exists" ;
  }
  else
  {
      cout << "which book want to read : " ;
      int choice = ReadInt(1 , idx) ;
      idx = 0 ;
      for (const auto &it : isbn_book_map)
      {
          if(++idx == choice)
          {
              BookReadingSession *session = users_manager.AddReadingSession(it.second) ;
              DisplaySession(session) ;
              break ;
          }
      }
  }

}

void UserView::ViewCurrentReadingSession ()
{
      const vector <BookReadingSession*> &readingsession = users_manager.GetCurrentUser()->GetReadingSession() ;
      int i = 0 ;
      for(i= 0 ; i < readingsession.size() ; ++i)
      {
          cout << readingsession[i]->ToString() ;
      }
      if (i == 0)
      {
          cout << "\n No history. List books and start having fun\n" ;
      }
      else
      {
          cout << "\nWhich session to open? \n" ;
          int choice = ReadInt(1 , i) ;
          DisplaySession(readingsession[choice - 1]) ;
      }
}



AdminView::AdminView (UsersManager  &users_manager , BookManger  &books_manager) : users_manager(users_manager) ,books_manager(books_manager)
{

}

void AdminView::Display ()
{
    const User *user = users_manager.GetCurrentUser() ;
    cout<< "\nHello " << "-"<< user->GetName()<< " | Admin view \n\n" ;
    vector<string> menu;
    menu.push_back("View Profile");
    menu.push_back("Add Book");
    menu.push_back("Logout");

    while (true)
    {

        int choice = ShowReadMenu(menu);
        if (choice == 1)
        {
           ViewProfile();
        }

        else if (choice == 2)
        {
            AddBook();
        }

        else
        {
            break ;
        }

    }
}

void AdminView::ViewProfile ()
{
    const User *user = users_manager.GetCurrentUser() ;
    cout <<"\n" << user->ToString() << "\n\n";
}
void AdminView::AddBook()
{
    Book* book = new Book () ;
    book->Read() ;
    books_manager.AddBook(book) ;
}
