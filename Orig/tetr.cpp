
// ��������� ������.
// 1. �������� ������ �������. ������ �� ������� �������� �� �������. ���������.
// 2. �������� ������. ���������.
// 3. ������ ������������� ������������ ��� ������������� �����. ���������.
// 4. �������� ����������� �����. ���������.
// 5. deletelines, �������������� ���. ���������� �� �����������. ���������.
// 7. �������� ��� �������� �����. ���������.
// 8. ����� ������. ���������.
// 9. ������� �����. ���������: �������� ������������ ����� �������� ���������.
// 10. ����� �� ��������� ����� ������� ����� ����� �� ������� ������� ����. ���������.
// 11. ����� ������ ����� �������� �� ������� ���� ���� �����������. ���������.
// 14. ������� ����� ������ ������� �������. ���������.

// ������ � �������

// 6. ����������� �� �������� � ������ ��������� ������. �� �������������� ������.
// 12. ��������� ����� ����
// 13. ��������� ������� �� ������� ����� �� ����� ������� � ������� ������ �� ������ �������
// 15. � iscollision ��������� �������� �� ������ ������� �� y
// 16. ��� � ������� ������������ ����������� ������ ���� ������������(�� ����������� ���� �������������� ���),
// ����� ��� ���� �������� � ��������� �������(�� �����������).


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
vector <Point> bvec;

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

//bool isCollision(const vector <vector <int>>& vec2d)
//{
//	for (int i = 0; i < getSZ(); i++)
//	{
//		if (vec2d[getY(i)][getX(i)] == Border) // ������������� � ��������
//			return true;
//		if (vec2d[getY(i)][getX(i)] == Block) //  ������������� � ��� ������������� �������
//			return true;
//	}
//	return false;
//}



bool isCollision(const vector <vector <int>>& vec2d)
{
	for (int i = 0; i < getSZ(); i++)
	{
		if (getY(i) < 0) // ������������ � ������� ��������
			return true;
		if (getX(i) <= 0) // ������������ � ����� ��������
			return true;
		if (getX(i) >= 11) // ������������ � ����� ��������
			return true;
		if (vec2d[getY(i)][getX(i)] == Border) // ������������� � ��������
			return true;
		if (vec2d[getY(i)][getX(i)] == Block) //  ������������� � ��� ������������� �������
			return true;
	}
	return false;
}

bool ShiftLeft(vector <vector <int> >& vec)
{
	if (isCollision(vec))
	{
		MoveLeft();
		if (isCollision(vec))
		{
			MoveLeft();
			if (isCollision(vec))
			{
				return false;
			}
		}
	}
	return true;
}

bool ShiftRight(vector <vector <int> >& vec)
{
	if (isCollision(vec))
	{
		MoveRight();
		if (isCollision(vec))
		{
			MoveRight();
			if (isCollision(vec))
			{
				return false;
			}
		}
	}
	return true;
}

void save()
{
	bvec = vec1;
}

void undo()
{
	vec1 = bvec;
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

	int r = 0; // rand() % 3;
	switch (r)
	{
	case 0: // �����
		Push(4, 0);
		Push(5, 0);
		Push(6, 0);
		Push(7, 0);
		break;
	case 1:
		Push(4, 0);
		Push(5, 0);
		Push(4, 1);
		Push(5, 1);
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




// ������� �����
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
void TestInit()
{
	for (int i = 3; i < vec.size() - 1; i++)
	{
		for (int j = 0; j < vec[i].size(); j++) {
			if (j == 7)
				vec[i][j] = Block;
			if (j == 3)
				vec[i][j] = Block;
		}
		cout << endl;
	}
}

void showField(const vector <vector <int> >& vec)
{
	// ��� �������� � �������� ����������� 
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

void AnimateDelLines(const vector <int> &lines)
{

	if (lines.empty())
		return;

	for (int i = 1; i <= LINE; i++)
	{
		for (int j = 0; j < lines.size(); j++)
		{
			gotoxy(i, lines[j]);
			cout << " ";
		}
		Sleep(50);
	}	
}

void deletedLines(int width)
{

	vector <int> lines;

	// ����������� ����� ������� ����� ������� 
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
	
	AnimateDelLines(lines);
	
	// �������� ����� �� ������� 
	for (int i = 0; i < lines.size(); i++)
	{
		vec.erase(vec.begin() + lines[i]);
	}

	// ���������� ������ ����� ������ � ������ ������ ���������
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

				Show(); // ����� ������ ����������� ����� ��������� ����� 
				deletedLines(WIDTH);
				showField(vec);

				Spawn();
			}
			Show();
			Sleep(300);
		}
		ch = _getch();

		if (ch == 224)
		{
			ch = _getch();
			gotoxy(25, 25);
			cout << ch;
		}

		// ��������� ������� ������
		switch (ch)
		{
		case 77:
			Hide();
			MoveRight();
			if (isCollision(vec))
			{
				MoveLeft();
			}
		break;// ������

		case 80:
			y++;
		break;// ����

		case 72:
			Hide();
			RotateR();
			if (isCollision(vec))
			{
				RotateL();
			}
		break;// ������� �� �������

		case 32:
			Hide();
			RotateL();
			if (isCollision(vec))
			{
				RotateR();
			}
			break;// ������� ������ �������	

		case 75:
			Hide();
			MoveLeft();
			if (isCollision(vec))
			{
				MoveRight();
			}
		break;// �����

		}
	}

	return 0;
}

int run2()
{

	InitVec(vec, WIDTH, HEIGHT);

	//TestInit();

	showField(vec);

	Spawn();
	


	int ch = 0;
	int i = 0;

	int x = 5, y = 5;

	while (true)
	{
		//while (!_kbhit())
		{
			Hide();
			//MoveDown();
			if (isCollision(vec))
			{
				MoveUp();
				Fixed(vec);
				deletedLines(WIDTH);
				showField(vec);
				Spawn();
			}
			Show();
			//Sleep(300);
		}
		ch = _getch();

		if (ch == 224)
		{
			ch = _getch();
			gotoxy(25, 25);
			cout << ch;
		}

		// ��������� ������� ������
		switch (ch)
		{
		case 77:
			Hide();
			MoveRight();
			if (isCollision(vec))
			{
				MoveLeft();
			}
			break;// ������

		case 80:
			Hide();
			MoveDown();
			if (isCollision(vec))
			{
				MoveUp();
			}
			break;// ����

		case 72: // ����� ������� �� ������� �������
			Hide();
			save();

			RotateR();
			if (!ShiftLeft(vec))
			{
				undo();
				RotateR();
				if (!ShiftRight(vec))
				{
					undo();
				}
			}

			break;// ������� �� �������

		case 32:
			Hide();
			save();

			RotateL();
			if (!ShiftLeft(vec))
			{ 
				undo();
				RotateL();
				if (!ShiftRight(vec))
				{
					undo();
				}
			}
			break;// ������� ������ �������	

		case 75:
			Hide();
			MoveLeft();
			if (isCollision(vec))
			{
				MoveRight();
			}
			break;// �����

		}
	}

	return 0;
}


int main()
{
	//setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	run2();
	


	system("color 0f");
	_getch();
	return 0;
}