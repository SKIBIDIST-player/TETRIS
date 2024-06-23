#include "Header.h"
#include <Windows.h>

// Функции для проекта

void printSymbolASCII(const int code)
{
	SetConsoleOutputCP(866);
	std::cout << char(code);
	SetConsoleOutputCP(1251);
}
