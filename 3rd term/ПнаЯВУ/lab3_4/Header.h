#pragma once
#include <iostream>	// ����-�����
#include <cstdlib>	// rand
#include <memory>
#include <iomanip>	// ������������
#include <string>	// ������
#include <fstream>	// �����
#include <vector>	// ������
#include <sstream>	

// �������� �� ����
void check(int& num, int x, size_t y);
void check_word(std::string& n);
std::string generateRandomString(int length);
std::string generateRandomID();