#pragma once
#include "user.h"

class moderator: 
	public user
{
public:
	using user::regUser;
	moderator(std::string id_, std::string username_, std::string password_, int lvl_);
	void deleteAccount(user*& current_person, std::vector<user*>& people) override;
	void showUsers(std::vector<user*>& people) override;
	void deleteQuestion(std::vector<QA>& pages);
	void deleteAnswer(std::vector<QA>& pages);
	void deleteUser(std::vector<user*>& people);
};