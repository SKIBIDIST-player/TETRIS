#include "Header.h"
#include <Windows.h>

// ������� ��� �������

void printSymbolASCII(const int code)
{
	SetConsoleOutputCP(866);
	std::cout << char(code);
	SetConsoleOutputCP(1251);
}
