#pragma once
#include <iostream>
#include <cstdlib>
#include <memory>
#include <iomanip>
#include "Matrix.h"
using namespace std;

void menu();
void check(int& num, int x, int y);
void option1(int& size, unique_ptr<Matrix[]>& Array);
void option4(int size, Matrix* arr);
void showOne(Matrix* arr, int number);