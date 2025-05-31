#pragma once
#include <iostream>	// ввод-вывод
#include <cstdlib>	// rand
#include <memory>
#include <iomanip>	// манипуляторы
#include <string>	// строки
#include <fstream>	// файлы
#include <vector>	// массив
#include <sstream>	

// проверки на ввод
void check(int& num, int x, size_t y);
void check_word(std::string& n);
std::string generateRandomString(int length);
std::string generateRandomID();