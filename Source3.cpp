#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include <thread>
int score = 0;
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
void display_score(int x, int y)
{
	gotoxy(x, y); printf("Score: %d",score);
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
	int jack = 0;
	draw_ship(x, y);
	display_score(80, 1);
	do {
		for (jack; jack < 20 && check == 1; jack++)
		{
			sx = rand() % 100;
			sy = rand() % 10;
			char checkstar = cursor(sx, sy);
			/*while (checkstar == '*')
			{
				
				checkstar = cursor(sx, sy);
			}*/
			while (sx < 10 || sx>70)
			{
				sx = rand() % 100;
			}
			while (sy < 2 || sy>5)
			{
				sy = rand() % 10;
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
			if (by == 2) 
			{ 
				bullet = 0;
			}
			else if (hit == '*')
			{
				clear_star(bx, by - 2);
				bullet = 0;
				jack -= 1;
				check = 1;
				score += 1;
				display_score(80, 1);
				Beep(700, 100);
			}
			else { draw_bullet(bx, --by); }
		}

		
		Sleep(100);
	} while (ch != 'x');
	return 0;
}
