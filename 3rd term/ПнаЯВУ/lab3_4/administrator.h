#pragma once
#include "user.h"
#include "editor.h"
#include "moderator.h"
class administrator :
    public user
{
public:
    using user::regUser;
    administrator(std::string id_, std::string username_, std::string password_, int lvl_);
    void deleteAccount(user*& current_person, std::vector<user*>& people) override;
    void showUsers(std::vector<user*>& people) override;
    void deleteUserBoss(std::vector<user*>& people);
    void upgradeLevel(std::vector<user*>& people);
};