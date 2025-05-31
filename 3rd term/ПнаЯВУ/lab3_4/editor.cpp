#include "Header.h"
#include "editor.h"
#include "QA.h"

editor::editor(std::string id_, std::string username_, std::string password_, int lvl_) : user(id_, username_, password_, lvl_) {}
void editor::deleteAccount(user*& current_person, std::vector<user*>& people)
{

	for (int i = 0; i < people.size(); i++)
	{
		if (people[i]->getUSERNAME() == current_person->getUSERNAME())
		{
			people.erase(people.begin() + i);
			break;
		}
	}
	std::cout << "�������� �������� ��������� �������.\n�������� �� ����� ������ �� ��� ���� �������!\n������� �� ��� ���� � �������� ��������� ������!" << std::endl;

}
void editor::editQuestion(std::vector<QA>& pages)
{
	std::cout << "�������� ������, ������� ������ ���������������:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	int num;
	check(num, 1, pages.size());
	num--;
	std::cout << "������� ������������ �������:" << std::endl;
	std::string ask;
	std::getline(std::cin, ask);
	pages[num].setQuestion(ask);
	std::cout << "_______________________________________________________________" << std::endl;
}
void editor::editAnswer(std::vector<QA>& pages)
{
	std::cout << "�������� ������, ����� �� ������� �� ������ ���������:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	int num;
	check(num, 1, pages.size());
	num--;
	int num2;
	std::cout << "�������� �����, ������� �� ������ ���������:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	check(num2, 1, pages[num].getNumOfAnswers());
	num2--;
	std::cout << "������� ������������ �����:" << std::endl;
	std::string answer;
	std::getline(std::cin, answer);
	pages[num].setAnswer(answer, num2);
	std::cout << "_______________________________________________________________" << std::endl;
}
void editor::showUsers(std::vector<user*>& people)
{
	std::cout << "�� �� ������ ������� � ������ ����������." << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
}