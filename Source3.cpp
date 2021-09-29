#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include <thread>
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); printf(" <-0-> ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("^");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void draw_star(int x, int y)
{
	gotoxy(x, y); printf("*");
}
void clear_star(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
int main()
{
	srand(time(NULL));
	char ch = '.';
	int x = 38, y = 20;
	int bx, by, i;
	int sx, sy, j;
	int bullet = 0;
	int check = 1;
	draw_ship(x, y);
	do {
		for (int j = 0; j < 20 && check == 1; j++)
		{
			sx = rand() % 100;
			sy = rand() % 10;
			char checkstar = cursor(sx, sy);
			while (checkstar == '*')
			{
				while (sx < 10 && sx>70)
				{

					sx = rand() % 100;
				}
				while (sy < 2 && sx>5)
				{
					sx = rand() % 10;
				}
				checkstar = cursor(sx, sy);
			}
			draw_star(sx, sy);
		}
		check = 0;
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a'&&x>0) { draw_ship(--x, y); }
			if (ch == 's'&&x<80) { draw_ship(++x, y); }
			if (bullet != 1 && ch == ' ') { bullet = 1; bx = x + 3; by = y - 1; }
			fflush(stdin);
		}
		if (bullet == 1) {
			char hit = cursor(bx, by - 2);
			
			clear_bullet(bx, by);
			if (by == 2|| hit=='*') 
			{ 
				bullet = 0;
				clear_star(bx, by - 2);
			}
			else { draw_bullet(bx, --by); }
			Beep(700, 100);
		}
		
		Sleep(100);
	} while (ch != 'x');
	return 0;
}
