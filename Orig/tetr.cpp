
// 1. Контроль границ стакана. Фигура не должнга выходить из стакана. Выполнено.
// 2. Фиксация фигуры. Выполнено.
// 3. Фигура фиксировалась относительно уже установленных фигур. Выполнено.
// 4. Удаление заполненных рядов. Выполнено.
// 5. deletelines, оптимизировать код. Сравнивать на неравенство. Выполнено.
// 6. Рефакторинг кода, перемещение по хедерами и прочее упрощение работы. Не первостепенная задача.
// 7. Анимация при удалении рядов. 
// 8. Новые фигуры. Выполнено.
// 9. Оформление в отдельный метод добавление пустой строки в стакане
// 10. Поворот фигур. Следствие: Проверка столкновений после поворота


#include <iostream>
#include "Header.h"
#include <Windows.h>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <math.h>
using namespace std;

const int WIDTH = 10 + 2;
const int HEIGHT = 15 + 1;

const int Border = 1;
const int Empty = 0;
const int Block = 2;

const int LINE = 10;

const float PI = 3.1415;


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
int getX(int i)
{
	return vec1[i].x;
}

int getY(int i)
{
	return vec1[i].y;
}

int getSZ()
{
	return vec1.size();
}


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
	for (int i = 0; i < getSZ(); i++)
	{
		if (vec2d[getY(i)][getX(i)] == Border) // столконовение с границей
			return true;
		if (vec2d[getY(i)][getX(i)] == Block) //  столконовение с уже установленной фигурой
			return true;
	}
	return false;
}

void Fixed(vector <vector <int>>& vec2d)
{
	for (int i = 0; i < getSZ(); i++)
	{
		vec2d[getY(i)][getX(i)] = Block;
	}
}

void Spawn()
{
	vec1.clear();

	int r = rand() % 3;
	switch (r)
	{
	case 0:
		Push(4, 0);
		Push(5, 0);
		Push(4, 1);
		Push(5, 1);
		break;
	case 1:
		Push(4, 0);
		Push(5, 0);
		Push(6, 0);
		Push(7, 0);
		break;
	case 2:
		Push(4, 0);
		Push(5, 0);
		Push(6, 0);
		Push(6, 1);
		break;
	}
	
}

void RotateR()
{
	for (int i = 0; i < vec1.size(); i++)
	{
		int x = - (vec1[i].y - vec1[1].y) + vec1[1].x;
		int y = (vec1[i].x - vec1[1].x) + vec1[1].y;
		vec1[i].x = x;
		vec1[i].y = y;
	}
}

void RotateL()
{
	for (int i = 0; i < vec1.size(); i++)
	{
		int x = (vec1[i].y - vec1[1].y) + vec1[1].x;
		int y = -(vec1[i].x - vec1[1].x) + vec1[1].y;
		vec1[i].x = x;
		vec1[i].y = y;
	}
}




// Функции карты
vector <vector <int>> vec;



void InitVec(vector <vector <int> > & vec, int width, int height)
{
	vector<int> temp;
	temp.push_back(Border);
	for (int i = 1; i < width - 1; i++)
		temp.push_back(Empty);
	temp.push_back(Border);
	for (int i = 0; i < height - 1; i++)
		vec.push_back(temp);

	temp.clear();
	for (int i = 0; i < width; i++)
		temp.push_back(Border);

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
			if (vec[i][j] == Border) 
				cout << '#';
			if (vec[i][j] == Block)
				cout << '*';
			else if (vec[i][j] == Empty)
				cout << ' ';
		}
		cout << endl;
	}
}

void deletedLines(int width)
{

	vector <int> lines;

	// определение рядов которые нужно удалить 
	for (int i = vec.size() - 2; i >= 0; i--)
	{
		int d = 0;
		for (int j = 1; j < vec[i].size() - 1; j++) {
			if (vec[i][j] == Block)
			{
				d++;
			}
			else
			{
				break;
			}
		}
		if (d == LINE)
		{
			lines.push_back(i);
		}
	}
	
	
	// Удаление рядов из вектора 
	for (int i = 0; i < lines.size(); i++)
	{
		vec.erase(vec.begin() + lines[i]);
		//cout << lines[i] << " ";
	}

	// Добавление пустых рядов сверху в стакан взамен удаленных
	vector<int> temp;
	temp.push_back(Border);
	for (int i = 1; i < width - 1; i++)
		temp.push_back(Empty);
	temp.push_back(Border);

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

		case 72:
			Hide();
			RotateR();
		break;// поворот по часовой

		case 32:
			Hide();
			RotateL();
			break;// поворот против часовой	

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