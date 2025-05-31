#include "Header.h"
#include "Menu.h"
#include "user.h"
#include "editor.h"
#include "moderator.h"
#include "administrator.h"
#include "QA.h"

void Menu::show()
{
    std::cout << "_______________________________________________________________" << std::endl;
	std::cout << "Для дальнейшей работы \033[1;35mвойдите\033[0m или \033[1;35mзарегистрируйтесь\033[0m на сайте:" << std::endl;
	std::cout << "Для завершения работы с сайтом нажмите \033[1;35m0\033[0m" << std::endl;
	std::cout << "1. \033[1;36mВход\033[0m" << std::endl;
	std::cout << "2. \033[1;36mРегистрация\033[0m" << std::endl;
	std::cout << "_______________________________________________________________" << std::endl;
}
void Menu::enter(int option, std::vector<user*>& people, user*& current_user, std::vector<QA>&pages)
{
	switch (option)
	{
	case 1:
	{
		system("cls");
		std::cout << "Введите имя пользователя:" << std::endl;
		std::cout << "_______________________________________________________________" << std::endl;
		std::string name;
		int pos = -1;
		do
		{
			check_word(name);
			for (int i = 0; i < people.size(); i++)
			{
				if (people[i]->getUSERNAME() == name)
				{
					pos = i;
					break;
				}
				if (i == people.size() - 1 && pos < 0)
				{
					std::cout << "Пользователя с таким именем не существует.\nВведите другое имя пользователя:" << std::endl;
				}
			}
		} while (pos < 0);
		user* person = people[pos];
		std::cout << "\n\nВведите пароль:" << std::endl;
		std::cout << "_______________________________________________________________" << std::endl;
		std::string pass;
		do
		{
			check_word(pass);
			if (person->getPASSWORD() != pass)
			{
				std::cout << "Пароль неверный. Попробуйте ещё раз:" << std::endl;
			}
		} while (person->getPASSWORD() != pass);

		std::cout << "\n\nВход выполнен успешно!" << std::endl;
		current_user = person;
		useOfSite(current_user, people, pages);
		break;
	}
	case 2:
	{
		system("cls");
		user* person = new user();
		person->regUser(people);
		people.push_back(person);
		current_user = person;
		useOfSite(current_user, people, pages);
		break;
	}
	case 0:
	{
		system("cls");
		std::cout << "Начинается обновление базы данных пользователей..." << std::endl;
		std::ofstream file("users.txt", std::ios_base::out);	// перезапись файла
		if (file.is_open())
		{
			for (int i = 0; i < people.size(); i++)
			{
				file << people[i]->getID() << " " << people[i]->getUSERNAME() << " " << people[i]->getPASSWORD() << " " << people[i]->getLEVEL() << "\n";
			}
			std::cout << "База данных обновлена." << std::endl;
		}
		else
		{
			std::cout << "Произошли маленькие технические шоколадки..." << std::endl;
		}
		file.close();											// Закрытие файла
		std::cout << "_______________________________________________________________" << std::endl;
		std::cout << "Начинается обновление базы данных форума..." << std::endl;
		std::ofstream file_("site.txt", std::ios_base::out);	// перезапись файла
		if (file_.is_open())
		{
			for (int i = 0; i < pages.size(); i++)
			{
				file_ << pages[i].getQuestion() << "\n";
				for (int j = 0; j < pages[i].getNumOfAnswers(); j++)
				{
					file_ << pages[i].getAnswers(j) << "\n";
				}
				file_ << "\n";
			}
			std::cout << "База данных обновлена." << std::endl;
		}
		else
		{
			std::cout << "Произошли маленькие технические шоколадки..." << std::endl;
		}
		file_.close();											// Закрытие файла
		char a = 2;
		char b = 4;
		std::cout << "_______________________________________________________________" << std::endl;
		std::cout << "\t\t\t\033[1;5;35mРеЗюМе\033[0m\nЛабораторная работа выполнена в соответствии со всеми \nтребованиями.\nДополнительное задание также выполнено!!!" << std::endl;
		std::cout << "\nНо если это \033[1;35m" << b << "\033[0m not enough \033[1;35m" << b << "\033[0m , тогда что \033[1;35m" << b << "\033[0m enough \033[1;35m" << b << "\033[0m ?.." << std::endl;
		std::cout << "\n\n\t" << a << " Вы самый лучший лабник, правда " << a << std::endl;
		std::cout << "_______________________________________________________________" << std::endl;
		// очистка памяти от векторов
		for (auto ptr : people)
		{
			delete ptr;
		}
		exit(0);        //завершение программы
	}
	}
}
void Menu::readUsersFromFile(std::vector<user*>& people)
{
	std::ifstream file("users.txt"); // Открытие файла для чтения
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			// Считывание строк из файла
			// Создание строкового потока для разбора строки
			std::istringstream iss(line);
			std::string username, password, id;
			int lvl;

			if (iss >> id >> username >> password >> lvl)
			{
				switch (lvl)
				{
				case 1:
				{
					user* readyUser = new user(id, username, password, lvl);
					people.push_back(readyUser);
					break;
				}
				case 2:
				{
					user* readyUser = new editor(id, username, password, lvl);
					people.push_back(readyUser);
					break;
				}
				case 3:
				{
					user* readyUser = new moderator(id, username, password, lvl);
					people.push_back(readyUser);
					break;
				}
				case 4:
				{
					user* readyUser = new administrator(id, username, password, lvl);
					people.push_back(readyUser);
					break;
				}
				}
			}
		}
		file.close(); // Закрытие файла
	}
}

void useOfSite(user*& person, std::vector<user*>& users_, std::vector<QA>& site_)
{
	int task;
	switch (person->getLEVEL())
	{
	case 1:
	{
		std::cout << "_______________________________________________________________" << std::endl;
		std::cout << "Добро пожаловать, пользователь " << person->getUSERNAME() << "!\n" << std::endl;
		do
		{
			std::cout << "Выберите действие ниже:" << std::endl;
			std::cout << "1. Просмотреть форум." << std::endl;
			std::cout << "2. Задать вопрос." << std::endl;
			std::cout << "3. Добавить ответ на вопрос." << std::endl;
			std::cout << "4. Удалить аккаунт." << std::endl;
			std::cout << "5. Выйти из аккаунта." << std::endl;
			check(task, 1, 5);
			switch (task)
			{
			case 1:
			{
				system("cls");
				person->showPages(site_);
				break;
			}
			case 2:
			{
				system("cls");
				person->askQuestion(site_);
				person->showPages(site_);
				break;
			}
			case 3:
			{
				system("cls");
				person->showPages(site_);
				person->addAnswer(site_);
				person->showPages(site_);
				break;
			}
			case 4:
			{
				system("cls");
				person->deleteAccount(person, users_);
				break;
			}
			case 5:
			{
				system("cls");
				std::cout << "Вы вышли из аккаунта.\nС нетерпением ждём вашего возвращения!\n" << std::endl;
				break;
			}
			}
		} while (task != 4 && task != 5);
		break;
	}
	case 2:
	{
		editor* worker = dynamic_cast<editor*>(person);
		std::cout << "_______________________________________________________________" << std::endl;
		std::cout << "Добро пожаловать, редактор " << person->getUSERNAME() << "!\n" << std::endl;
		do
		{
			std::cout << "Выберите действие ниже:" << std::endl;
			std::cout << "1. Просмотреть форум." << std::endl;
			std::cout << "2. Задать вопрос." << std::endl;
			std::cout << "3. Добавить ответ на вопрос." << std::endl;
			std::cout << "4. Удалить аккаунт." << std::endl;
			std::cout << "5. Выйти из аккаунта.\n" << std::endl;
			std::cout << "6. Редактировать вопрос." << std::endl;
			std::cout << "7. Редактировать ответ." << std::endl;
			check(task, 1, 7);
			switch (task)
			{
			case 1:
			{
				system("cls");
				person->showPages(site_);
				break;
			}
			case 2:
			{
				system("cls");
				person->askQuestion(site_);
				person->showPages(site_);
				break;
			}
			case 3:
			{
				system("cls");
				person->showPages(site_);
				person->addAnswer(site_);
				person->showPages(site_);
				break;
			}
			case 4:
			{
				system("cls");
				person->deleteAccount(person, users_);
				break;
			}
			case 5:
			{
				system("cls");
				std::cout << "Вы вышли из аккаунта.\nС нетерпением ждём вашего возвращения!\n" << std::endl;
				break;
			}
			case 6:
			{
				system("cls");
				worker->showPages(site_);
				worker->editQuestion(site_);
				worker->showPages(site_);
				break;
			}
			case 7:
			{
				system("cls");
				worker->showPages(site_);
				worker->editAnswer(site_);
				worker->showPages(site_);
				break;
			}
			}
		} while (task != 4 && task != 5);
		break;
	}
	case 3:
	{
		moderator* worker = dynamic_cast<moderator*>(person);
		std::cout << "_______________________________________________________________" << std::endl;
		std::cout << "Добро пожаловать, модератор " << person->getUSERNAME() << "!\n" << std::endl;
		do
		{
			std::cout << "Выберите действие ниже:" << std::endl;
			std::cout << "1. Просмотреть форум." << std::endl;
			std::cout << "2. Задать вопрос." << std::endl;
			std::cout << "3. Добавить ответ на вопрос." << std::endl;
			std::cout << "4. Удалить аккаунт." << std::endl;
			std::cout << "5. Выйти из аккаунта.\n" << std::endl;
			std::cout << "6. Удалить вопрос." << std::endl;
			std::cout << "7. Удалить ответ." << std::endl;
			std::cout << "8. Удалить пользователя." << std::endl;
			check(task, 1, 8);
			switch (task)
			{
			case 1:
			{
				system("cls");
				person->showPages(site_);
				break;
			}
			case 2:
			{
				system("cls");
				person->askQuestion(site_);
				person->showPages(site_);
				break;
			}
			case 3:
			{
				system("cls");
				person->showPages(site_);
				person->addAnswer(site_);
				person->showPages(site_);
				break;
			}
			case 4:
			{
				system("cls");
				person->deleteAccount(person, users_);
				break;
			}
			case 5:
			{
				system("cls");
				std::cout << "Вы вышли из аккаунта.\nС нетерпением ждём вашего возвращения!\n" << std::endl;
				break;
			}
			case 6:
			{
				system("cls");
				worker->showPages(site_);
				worker->deleteQuestion(site_);
				worker->showPages(site_);
				break;
			}
			case 7:
			{
				system("cls");
				worker->showPages(site_);
				worker->deleteAnswer(site_);
				worker->showPages(site_);
				break;
			}
			case 8:
			{
				system("cls");
				worker->showUsers(users_);
				worker->deleteUser(users_);
				break;
			}
			}
		} while (task != 4 && task != 5);
		break;
	}
	case 4:
	{
		
		administrator* worker = dynamic_cast<administrator*>(person);
		std::cout << "_______________________________________________________________" << std::endl;
		std::cout << "Добро пожаловать, администратор " << person->getUSERNAME() << "!\n" << std::endl;
		do
		{
			std::cout << "Выберите действие ниже:" << std::endl;
			std::cout << "1. Просмотреть форум." << std::endl;
			std::cout << "2. Задать вопрос." << std::endl;
			std::cout << "3. Добавить ответ на вопрос." << std::endl;
			std::cout << "4. Удалить аккаунт." << std::endl;
			std::cout << "5. Выйти из аккаунта.\n" << std::endl;
			std::cout << "6. Изменить права пользователя." << std::endl;
			std::cout << "7. Удалить пользователя." << std::endl;
			check(task, 1, 7);
			switch (task)
			{
			case 1:
			{
				system("cls");
				person->showPages(site_);
				break;
			}
			case 2:
			{
				system("cls");
				person->askQuestion(site_);
				person->showPages(site_);
				break;
			}
			case 3:
			{
				system("cls");
				person->showPages(site_);
				person->addAnswer(site_);
				person->showPages(site_);
				break;
			}
			case 4:
			{
				system("cls");
				person->deleteAccount(person, users_);
				break;
			}
			case 5:
			{
				system("cls");
				std::cout << "Вы вышли из аккаунта.\nС нетерпением ждём вашего возвращения!\n" << std::endl;
				break;
			}
			case 6:
			{
				system("cls");
				worker->showUsers(users_);
				worker->upgradeLevel(users_);
				break;
			}
			case 7:
			{
				system("cls");
				worker->showUsers(users_);
				worker->deleteUserBoss(users_);
				break;
			}
			}
		} while (task != 5);
		break;
	}
	}
}