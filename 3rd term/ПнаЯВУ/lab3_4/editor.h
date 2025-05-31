#pragma once
#include "user.h"
#include "QA.h"

class editor :
    public user
{
public:
    using user::regUser;
    editor(std::string id_, std::string username_, std::string password_, int lvl_);
    void deleteAccount(user*& current_person, std::vector<user*>& people) override;
    void showUsers(std::vector<user*>& people) override;
    void editQuestion(std::vector<QA>& pages);
    void editAnswer(std::vector<QA>& pages);
};