#include "moderator.h"

moderator::moderator(std::string id_, std::string username_, std::string password_, int lvl_) : user(id_, username_, password_, lvl_) {}
void moderator::deleteAccount(user*& current_person, std::vector<user*>& people)
{

	for (int i = 0; i < people.size(); i++)
	{
		if (people[i]->getUSERNAME() == current_person->getUSERNAME())
		{
			people.erase(people.begin() + i);
			break;
		}
	}
	std::cout << "Удаление аккаунта выполнено успешно.\nНадеемся вы нашли ответы на все ваши вопросы!\nСпасибо за ваш труд в качестве модератора форума!" << std::endl;
}
void moderator::showUsers(std::vector<user*>& people)
{
	std::cout << "Вы имеете ограниченный доступ к данной информации.\nСписок пользователей форума:\n" << std::endl;
	int cnt = 0;
	int chely=0;
	// Выводим информацию на экран
	for (auto& chel : people)
	{
		if (people[cnt]->getLEVEL() == 1)
		{
			std::cout << people[cnt]->getUSERNAME() << std::endl;
			chely++;
		}
		cnt++;
	}
	if (chely == 0)
		std::cout << "Пользователей ниже вас уровнем не существует" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
}
void moderator::deleteQuestion(std::vector<QA>& pages)
{
	std::cout << "Выберите вопрос, который хотите удалить:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	int num;
	check(num, 1, pages.size());
	num--;
	pages.erase(pages.begin() + num);
	std::cout << "Вопрос был удалён с форума." << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
}
void moderator::deleteAnswer(std::vector<QA>& pages)
{
	std::cout << "Выберите вопрос, ответ на который хотите удалить:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	int num;
	check(num, 1, pages.size());
	num--;
	std::cout << "Выберите ответ, который хотите удалить:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	int num2;
	check(num2, 1, pages[num].getNumOfAnswers());
	num2--;

	pages[num].deleteAnswer(num2);
	std::cout << "Вопрос был удалён с форума." << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
}
void moderator::deleteUser(std::vector<user*>& people)
{
	std::cout << "Введите имя пользователя, которого хотите удалить:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	std::string name;
	std::getline(std::cin, name);
	int i;
	for (i = 0; i < people.size(); i++)
	{
		if (people[i]->getUSERNAME() == name&&people[i]->getLEVEL() == 1)
		{
			people.erase(people.begin() + i);
			std::cout << "Пользователь успешно удалён.\nНадеемся вы удалили его за дело, а не просто так..." << std::endl;
			std::cout << "_______________________________________________________________" << std::endl;
			break;
		}
	}
	if (i == people.size())
	{
		std::cout << "Пользователя с таким именем не существует." << std::endl;
		std::cout << "_______________________________________________________________" << std::endl;
	}
}