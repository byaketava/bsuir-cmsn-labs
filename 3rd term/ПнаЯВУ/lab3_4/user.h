#pragma once
#include "Header.h"
#include "QA.h"

class user
{
protected:
	std::string id;
	std::string username;
	std::string password;
	int level;
public:
	user();
	user(std::string id_, std::string username_, std::string password_, int lvl);

	std::string  getID() const;
	std::string  getUSERNAME() const;
	std::string  getPASSWORD() const;
	int  getLEVEL() const;
	void setLEVEL(int a);

	void regUser(const std::vector<user*>& people);

	void showPages(std::vector<QA>& pages);
	void askQuestion(std::vector<QA>& pages);
	void addAnswer(std::vector<QA>& pages);
	virtual void deleteAccount(user*& current_person, std::vector<user*>& people);
	virtual void showUsers(std::vector<user*>& people);
	virtual ~user() = default;	// виртуальный деструктор необходим для базового класса
};