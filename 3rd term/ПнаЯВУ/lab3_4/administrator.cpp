#include "administrator.h"

administrator::administrator(std::string id_, std::string username_, std::string password_, int lvl_) :
	user(id_, username_, password_, lvl_) {}
void administrator::deleteAccount(user*& current_person, std::vector<user*>& people)
{
	std::cout << "Вы администратор сайта, без вас он не будет функционировать.\nВаш аккаунт не был удалён.\nСпасибо за ваш труд в качестве администратора форума!" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
}
void administrator::showUsers(std::vector<user*>& people)
{
	std::cout << "Вы имеете полный доступ к данной информации.\nСписок пользователей, редакторов и модераторов форума:\n" << std::endl;
	int cnt = 0;
	int chely = 0;
	// Выводим информацию на экран
	for (auto& chel : people)
	{
		if (people[cnt]->getLEVEL() != 4)
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
void administrator::upgradeLevel(std::vector<user*>& people)
{
	std::cout << "Введите имя пользователя, права которого хотите изменить:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	std::string name;
	check_word(name);
	int i;
	for (i = 0; i < people.size(); i++)
	{
		if (people[i]->getUSERNAME() == name && people[i]->getLEVEL() < 4)
		{
			std::cout << "\nВыберите новый уровень прав:" << std::endl;
			std::cout << "1. Базовый пользователь." << std::endl;
			std::cout << "2. Редактор." << std::endl;
			std::cout << "3. Модератор." << std::endl;
			std::cout << "4. Администратор." << std::endl;
			int choice;
			check(choice, 1, 4);
			switch (choice)
			{
			case 1:
			{
				user* creep = new user(people[i]->getID(), people[i]->getUSERNAME(), people[i]->getPASSWORD(), choice);
				people.erase(people.begin() + i);
				people.push_back(creep);
				break;
			}
			case 2:
			{
				editor* creep = new editor(people[i]->getID(), people[i]->getUSERNAME(), people[i]->getPASSWORD(), choice);
				people.erase(people.begin() + i);
				people.push_back(creep);
				break;
			}
			case 3:
			{
				moderator* creep = new moderator(people[i]->getID(), people[i]->getUSERNAME(), people[i]->getPASSWORD(), choice);
				people.erase(people.begin() + i);
				people.push_back(creep);
				break;
			}
			case 4:
			{
				administrator* creep = new administrator(people[i]->getID(), people[i]->getUSERNAME(), people[i]->getPASSWORD(), choice);
				people.erase(people.begin() + i);
				people.push_back(creep);
				break;
			}
			}
			std::cout << "\nУровень прав пользователя успешно изменён.\nНадеемся вы действовали осознанно!" << std::endl;
			std::cout << "_______________________________________________________________" << std::endl;
			break;
		}
	}
	if (i == people.size())
	{
		std::cout << "\nПользователя с таким именем не существует." << std::endl;
		std::cout << "_______________________________________________________________" << std::endl;
	}
}
void administrator::deleteUserBoss(std::vector<user*>& people)
{
	std::cout << "Введите имя пользователя, которого хотите удалить:" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
	std::string name;
	check_word(name);
	int i;
	for (i = 0; i < people.size(); i++)
	{
		if (people[i]->getUSERNAME() == name && people[i]->getLEVEL() < 4)
		{
			people.erase(people.begin() + i);
			std::cout << "Пользователь успешно удалён.\nНадеемся вы удалили его за дело, а не просто так..." << std::endl;
			std::cout << "_______________________________________________________________" << std::endl;
			break;
		}
	}
	if (i == people.size())
	{
		std::cout << "Пользователя ниже вас уровнем с таким именем не существует." << std::endl;
		std::cout << "_______________________________________________________________" << std::endl;
	}
}