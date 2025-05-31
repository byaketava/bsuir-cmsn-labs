#include "Header.h"
#include "user.h"
#include "QA.h"

user::user() :id("unknown"), username("unknown"), password("unknown"), level(0) {}
user::user(std::string id_, std::string username_, std::string password_, int lvl) : id(id_), username(username_), password(password_), level(lvl) {}

std::string user::getID() const
{
	return this->id;
}
std::string user::getUSERNAME() const
{
	return this->username;
}
std::string user::getPASSWORD() const
{
	return this->password;
}
int user::getLEVEL() const
{
	return this->level;
}
void user::setLEVEL(int a)
{
	this->level = a;
}

void user::regUser(const std::vector<user*>&people)
{
	std::cout << "������� ��� ������������:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	std::string name;
	check_word(name);
	for (int i = 0; i < people.size(); i++)
	{
		if (people[i]->getUSERNAME() == name)
		{
			std::cout << "������������ � ����� ������ ��� ����������.\n������� ������ ��� ������������." << std::endl;
			check_word(name);
		}
	}
	

	std::cout << "\n\n������� ������:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	std::string pass;
	check_word(pass);
	std::string ID = generateRandomID();
	this->username = name;
	this->password = pass;
	this->id = ID;
	this->level = 1;

	std::cout << "\n\n�� ������� ���������������� �� �����!" << std::endl;
	std::cout << "���� ��� ������������: " << name << std::endl;
	std::cout << "��� ������: " << pass << std::endl;
	std::cout << "��� id: " << ID << std::endl;
}

void user::showPages(std::vector<QA>& pages)
{
	int cnt = 0;
	// ������� ���������� �� �����
	std::cout << "���������� ������:\n" << std::endl;
	for (auto& page : pages)
	{
		cnt++;
		std::cout << cnt << ". " << page.getQuestion() << std::endl;
		if (page.getNumOfAnswers() == 0)
			std::cout << "����� ��� �� ������� �� ������ ������. ������ �������!" << std::endl;
		else
			for (int i = 0; i < page.getNumOfAnswers(); i++)
				std::cout << "	" << i + 1 << ") " << page.getAnswers(i) << std::endl;
		std::cout << std::endl;
	}
	std::cout << "_______________________________________________________________" << std::endl;
}
void user::showUsers(std::vector<user*>& people)
{
	std::cout << "�� �� ������ ������� � ������ ����������." << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
}
void user::askQuestion(std::vector<QA>& pages)
{
	std::cout << "������� ���� ������:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	std::string ask;
	std::getline(std::cin, ask);
	QA faq;
	faq.setQuestion(ask);
	pages.push_back(faq);
	std::cout << "_______________________________________________________________" << std::endl;
}
void user::addAnswer(std::vector<QA>& pages)
{
	std::cout << "�������� ������, �� ������� ������ ��������:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	int num;
	check(num, 1, pages.size());
	num--;
	std::cout << "������� ��� �����:" << std::endl;
	std::string answer;
	std::getline(std::cin, answer);
	pages[num].setAnswers(answer);
	std::cout << "_______________________________________________________________" << std::endl;
}
void user::deleteAccount(user*& current_person, std::vector<user*>& people)
{
	for (int i = 0; i < people.size(); i++)
	{
		if (people[i]->getUSERNAME() == current_person->getUSERNAME())
		{
			people.erase(people.begin() + i);
			break;
		}
	}
	std::cout << "�������� �������� ��������� �������.\n�������� �� ����� ������ �� ��� ���� �������!" << std::endl;
}