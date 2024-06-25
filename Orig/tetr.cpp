
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
// 12. ��������� ����� ����
// 13. ��������� ������� �� ������� ����� �� ����� ������� � ������� ������ �� ������ �������. ���������.
// 14. ������� ����� ������ ������� �������. ���������.
// 15. � iscollision ��������� �������� �� ������ ������� �� y. ��������.
// 16. ��������� ��� �� ������ run2 � run. ���������.
// 17. �������� ������� ����. ���������.
// 20. ���� � ����. ���������.
// 22. ������ ������. ���������.


// ������ � �������

// 6. ����������� �� �������� � ������ ��������� ������. �� �������������� ������.
// 18. �������� ������� �������.
// 19. ������� �� ������ � �������. � ����������� �������� ������� ������.
// 21. �������� ������������ �����. 


#include <iostream>
#include "Header.h"
#include <Windows.h>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <math.h>
#include <ctime>
using namespace std;

enum ConsoleColor
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GRAY = 7,
	DARKGRAY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

const int WIDTH = 10 + 2;
const int HEIGHT = 15 + 1;

const int Border = 1;
const int Empty = 0;
const int Block = 2;

const int LINE = 10;

const float PI = 3.1415;

const int SLEEP_TIME = 50;

int countTact = 0;
const int COUNT_TACT_FOR_NOT_MOVE_F = 5;

int score = 0;
int kind = 3;

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ������������� ���� ������ � ���� � �������.

void setColor(int background, int text)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)(background << 4) | text);
}


struct Point
{
	int x;
	int y;
};

// ������
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
	switch (kind)
	{
	case 0:
		setColor(BLACK, RED);
		break;
	case 1:
		setColor(BLACK, BLUE);
		break;
	case 2:
		setColor(BLACK, GREEN);
		break;
	}

	for (int i = 0; i < vec1.size(); i++)
	{
		gotoxy(vec1[i].x, vec1[i].y);
		printSymbolASCII(249);
	}
	setColor(BLACK, WHITE);
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

bool allowMove()
{
	if (countTact < COUNT_TACT_FOR_NOT_MOVE_F)
	{
		countTact++;
		return false;
	}
	countTact = 0;
	return true;

}

void Spawn()
{
	vec1.clear();
	srand(time(0));

	kind = rand() % 3;
	switch (kind)
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

void Hide_Cursor()
{
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);

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

void gameover()
{
	gotoxy(10, 25);
	cout << "GAME OVER";
	system("pause");
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
				printSymbolASCII(178);
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

int deletedLines(int width)
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

	AnimateDelLines(lines);
	return lines.size();
}

void IncScore(int lines)
{
	switch (lines)
	{
	case 1:
		score += 1;
		break;
	case 2:
		score += 3;
		break;
	case 3:
		score += 8;
		break;
	case 4:
		score += 15;
		break;
	}
}

void Showscore()
{
	gotoxy(30, 20);
	cout << "����: " << score;
}

int run()
{
	Hide_Cursor();
	InitVec(vec, WIDTH, HEIGHT);
	showField(vec);
	Showscore();

	Spawn();


	int ch = 0;
	int i = 0;

	int x = 5, y = 5;

	while (true)
	{
		while (!_kbhit())
		{
			Hide();

			if (allowMove())
			{
				MoveDown();
			}

			if (isCollision(vec))
			{
				MoveUp();
				Fixed(vec);

				Show(); // ����� ������ ����������� ����� ��������� ����� 
				int lines = deletedLines(WIDTH);
				IncScore(lines);
				Showscore();

				showField(vec);

				Spawn();
				// �������� �� ����� ����
				if (isCollision(vec))
				{
					Show();
					gameover();
					return 0;
				}
			}
			Show();
			Sleep(SLEEP_TIME);
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


				Show();
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

	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);


	run();
	


	system("color 0f");
	_getch();
	return 0;
}