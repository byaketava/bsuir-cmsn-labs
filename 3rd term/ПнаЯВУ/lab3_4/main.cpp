#include "Header.h"
#include "Menu.h"
#include "user.h"
#include "moderator.h"
#include "editor.h"
#include "administrator.h"
#include "QA.h"


int main()
{
	srand((unsigned int)time(NULL));
	setlocale(0, "");

    Menu menu;
    user *person;
    std::vector<user*> users;
    std::vector<QA> site;

    menu.readUsersFromFile(users);
    readSiteFromFile(site);
    int option;
    do 
    {
        menu.show(); 
        check(option, 0, 2);
        menu.enter(option, users, person, site);
    } while (option != 0);
	return 0;
}