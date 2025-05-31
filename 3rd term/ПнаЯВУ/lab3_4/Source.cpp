#include "Header.h"
#include "user.h"

void check(int& num, int x, size_t y)
{
	while (1)
	{
		std::cin >> num;
		if (!std::cin.fail() && num >= x && num <= y && std::cin.get() == '\n')
			break;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
		std::cout << "Да,да, да... Проверки наше всё!\nА теперь введите \033[1;5;35mАдЕкВаТнО\033[0m:" << std::endl;
	}
}
void check_word(std::string& n)
{
	while (1)
	{
		std::cout << "\033[1;36m";
		std::cin >> n;
		std::cout << "\033[0m";
		if (!std::cin.fail() && std::cin.get() == '\n')
			break;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
		std::cout << "Неверный ввод. Использовать знак пробела запрещено.\nПопробуйте ещё раз:" << std::endl;
	}
}


std::string generateRandomString(int length) 
{
	std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::string randomString;
	for (int i = 0; i < length; ++i) 
	{
		int randomIndex = rand() % characters.size();
		randomString += characters[randomIndex];
	}

	return randomString;
}
std::string generateRandomID()
{
	std::string characters = "0123456789";
	std::string randomString;
	for (int i = 0; i < 5; ++i)
	{
		int randomIndex = rand() % characters.size();
		randomString += characters[randomIndex];
	}
	return randomString;
}
