#include <stdio.h>
#include<Windows.h>
#include<conio.h>

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("<-0->");
	setcolor(2, 0);
}
void erase_ship(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("     ");
	setcolor(2, 4);
}

void draw_bullet(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("*");
}
void erase_bullet(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf(" ");
}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}


int main()
{
	setcolor(2, 4);
	setcursor(0);
	char ch = ' ';
	int x1 = 10, y1 = 10;
	int x2 = x1, y2 = y1;
	draw_ship(x1, y1);
	int status = 0;
	int fire = 0;
	int bulletleft = 5;
	do {
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 'a')
			{
				status = 1;
			}
			if (ch == 'd')
			{
				status = 2;
			}
			if (ch == 's')
			{
				status = 0;
			}
			if (ch == ' '&&bulletleft!=0&&fire==0)
			{
				fire = 1;
				bulletleft -= 1;
			}
		}
		if (status == 1)
		{
			erase_ship(x1, y1);
			draw_ship(--x1, y1);
		}
		if (status == 2)
		{
			erase_ship(x1, y1);
			draw_ship(++x1, y1);
		}
		if (status == 0)
		{
			erase_ship(x1, y1);
			draw_ship(x1, y1);
		}
		if (fire == 0)
		{
			x2 = x1 + 2;
		}
		if (fire == 1&&bulletleft>0)
		{
			erase_bullet(x2, y2);
			draw_bullet(x2, --y2);
			if (y2 < 1)
			{
				erase_bullet(x2, y2);
				fire = 0;
				y2 = 10;
			}

		}

		Sleep(100);
		fflush(stdin);
	} while (ch != 'x');
	return 0;
}
