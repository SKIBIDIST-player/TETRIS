
// 1. Контроль границ стакана. Фигура не должнга выходить из стакана. Выполнено
// 2. Фиксация фигуры. Выполнено
// 3. Фигура фиксировалась относительно уже установленных фигур. Выполнено
// 4. Удаление заполненных рядов. Выполнено
// 5. deletelines, оптимизировать код. Сравнивать на неравенство 
// 6. Рефакторинг кода, перемещение по хедерами и прочее упрощение работы.
// 7. Анимация при удалении рядов. 
 

#include <iostream>
#include "Header.h"
#include <Windows.h>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <vector>
using namespace std;

const int WIDTH = 10 + 2;
const int HEIGHT = 15 + 1;

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

struct Point
{
	int x;
	int y;
};

vector <Point> vec1;
void Push(int x, int y)
{
	Point temp;
	temp.x = x;
	temp.y = y;
	vec1.push_back(temp); 
}

void Show()
{
	for (int i = 0; i < vec1.size(); i++)
	{
		gotoxy(vec1[i].x, vec1[i].y);
		cout << "*";
	}
}

void Hide()
{
	for (int i = 0; i < vec1.size(); i++)
	{
		gotoxy(vec1[i].x, vec1[i].y);
		cout << ' ';
	}
}

void MoveDown()
{
	for (int i = 0; i < vec1.size(); i++)
	{
		vec1[i].y++;
	}
}

void MoveUp()
{
	for (int i = 0; i < vec1.size(); i++)
	{
		vec1[i].y--;
	}
}

void MoveLeft()
{
	for (int i = 0; i < vec1.size(); i++)
	{
		vec1[i].x--;
	}
}

void MoveRight()
{
	for (int i = 0; i < vec1.size(); i++)
	{
		vec1[i].x++;
	}
}

bool isCollision(const vector <vector <int>>& vec2d)
{
	for (int i = 0; i < vec1.size(); i++)
	{
		if (vec2d[vec1[i].y][vec1[i].x] == 1) // столконовение с границей
			return true;
		if (vec2d[vec1[i].y][vec1[i].x] == 2) //  столконовение с уже установленной фигурой
			return true;
	}
	return false;
}

void Fixed(vector <vector <int>>& vec2d)
{
	for (int i = 0; i < vec1.size(); i++)
	{
		vec2d[vec1[i].y][vec1[i].x] = 2;
	}
}

void Spawn()
{
	vec1.clear();
	Push(4, 0);
	Push(5, 0);
	Push(4, 1);
	Push(5, 1);
}

// Функции карты
vector <vector <int>> vec;

void InitVec(vector <vector <int> > & vec, int width, int height)
{
	vector<int> temp;
	temp.push_back(1);
	for (int i = 1; i < width - 1; i++)
		temp.push_back(0);
	temp.push_back(1);
	for (int i = 0; i < height - 1; i++)
		vec.push_back(temp);

	temp.clear();
	for (int i = 0; i < width; i++)
		temp.push_back(1);

	vec.push_back(temp);
}

//void showField()
//{
//	
//	for (int i = 0; i < 20; i++)
//	{
//		printSymbolASCII(179);
//		cout << endl;
//	}
//	printSymbolASCII(192);
//	for (int i = 0; i < 25; i++) {
//		
//		printSymbolASCII(196);
//	}
//	printSymbolASCII(217);
//	for (int i = 0; i < 20; i++)
//	{
//		gotoxy(26, i);
//		printSymbolASCII(179);
//	}
//}


void showField(const vector <vector <int> >& vec)
{
	// Для откладки и проверки целостности 
	for (int i = 0; i < vec.size(); i++)
	{
		gotoxy(26, i);
		cout << i << " ";
		if (i < 10)
			cout << " ";
		for (int j = 0; j < vec[i].size(); j++) {
			cout << vec[i][j];
		}
		cout << endl;
	}

	gotoxy(0, 0);
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++) {
			if (vec[i][j] == 1) 
				cout << '#';
			if (vec[i][j] == 2)
				cout << '*';
			else if (vec[i][j] == 0)
				cout << ' ';
		}
		cout << endl;
	}
}

void deletedLines(int width)
{

	vector <int> lines;

	for (int i = vec.size() - 2; i >= 0; i--)
	{
		int d = 0;
		for (int j = 1; j < vec[i].size() - 1; j++) {
			if (vec[i][j] == 2)
			{
				d++;
			}
		}
		if (d == 10)
		{
			lines.push_back(i);
		}
	}
	
	
	for (int i = 0; i < lines.size(); i++)
	{
		vec.erase(vec.begin() + lines[i]);
		//cout << lines[i] << " ";
	}

	vector<int> temp;
	temp.push_back(1);
	for (int i = 1; i < width - 1; i++)
		temp.push_back(0);
	temp.push_back(1);

	for (int i = 0; i < lines.size(); i++)
		vec.insert(vec.begin(), temp);
}

int run()
{
	
	InitVec(vec, WIDTH, HEIGHT);

	showField(vec);

	Spawn();
	/*Push(4, 0);
	Push(5, 0);
	Push(4, 1);
	Push(5, 1);*/


	int ch = 0;
	int i = 0;

	int x = 5, y = 5;

	while (true)
	{
		while (!_kbhit())
		{
			Hide();
			MoveDown();
			if (isCollision(vec))
			{
				MoveUp();
				Fixed(vec);
				deletedLines(WIDTH);
				showField(vec);
				Spawn();
			}
			Show();
			Sleep(200);
		}
		ch = _getch();

		if (ch == 224)
		{
			ch = _getch();
			gotoxy(25, 25);
			cout << ch;
		}

		// обработка нажатых клавиш
		switch (ch)
		{
		case 77:
			Hide();
			MoveRight();
			if (isCollision(vec))
			{
				MoveLeft();
			}
		break;// вправо

		case 80:
			y++;
		break;// вниз

		//case 72:
		//	y--;
		//break;// вверх

		case 75:
			Hide();
			MoveLeft();
			if (isCollision(vec))
			{
				MoveRight();
			}
		break;// влево

		}
	}

	return 0;
}

int main()
{
	//setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	run();
	


	system("color 0f");
	_getch();
	return 0;
}