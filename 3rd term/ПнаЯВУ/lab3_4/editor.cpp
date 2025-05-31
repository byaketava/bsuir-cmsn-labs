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
	std::cout << "Удаление аккаунта выполнено успешно.\nНадеемся вы нашли ответы на все ваши вопросы!\nСпасибо за ваш труд в качестве редактора форума!" << std::endl;

}
void editor::editQuestion(std::vector<QA>& pages)
{
	std::cout << "Выберите вопрос, который хотите отредактировать:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	int num;
	check(num, 1, pages.size());
	num--;
	std::cout << "Введите исправленный вариант:" << std::endl;
	std::string ask;
	std::getline(std::cin, ask);
	pages[num].setQuestion(ask);
	std::cout << "_______________________________________________________________" << std::endl;
}
void editor::editAnswer(std::vector<QA>& pages)
{
	std::cout << "Выберите вопрос, ответ на который вы хотите исправить:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	int num;
	check(num, 1, pages.size());
	num--;
	int num2;
	std::cout << "Выберите ответ, который вы хотите исправить:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	check(num2, 1, pages[num].getNumOfAnswers());
	num2--;
	std::cout << "Введите исправленный ответ:" << std::endl;
	std::string answer;
	std::getline(std::cin, answer);
	pages[num].setAnswer(answer, num2);
	std::cout << "_______________________________________________________________" << std::endl;
}
void editor::showUsers(std::vector<user*>& people)
{
	std::cout << "Вы не имеете доступа к данной информации." << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
}