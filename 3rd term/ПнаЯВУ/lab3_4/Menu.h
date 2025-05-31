#pragma once
#include "Header.h"
#include "Menu.h"
#include "user.h"
#include "moderator.h"
#include "editor.h"
#include "administrator.h"
#include "QA.h"

class Menu
{
public:
	void show();
	void enter(int option, std::vector<user*>& people, user*& current_user, std::vector<QA>& pages);
	void readUsersFromFile(std::vector<user*>& people);
};

void useOfSite(user*& person, std::vector<user*>& users_, std::vector<QA>& site_);