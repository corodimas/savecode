#include<stdio.h>
#include<windows.h>
#include<time.h>

#define scount 80
#define screen_x 80
#define screen_y 25

int positionx = 0, positiony = 0, hitcount = 0;

HANDLE wHnd;
HANDLE rHnd;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD characterPos = { 0,0 };
COORD bufferSize = { screen_x,screen_y };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
COORD star[scount];
DWORD fdwMode;

int setConsole(int x, int y)
{
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
    SetConsoleScreenBufferSize(wHnd, bufferSize);
    return 0;
}

int setMode()
{
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(rHnd, fdwMode);
    return 0;
}

void clear_buffer() {
    for (int y = 0; y < screen_y; y++)
    {
        for (int x = 0; x < screen_x; x++)
        {
            consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
            consoleBuffer[x + screen_x * y].Attributes = 7;
        }
    }
}
void fill_data_to_buffer() {
    for (int y = 0; y < screen_y; y++)
    {
        for (int x = 0; x < screen_x; x++)
        {
            consoleBuffer[x + screen_x * y].Char.AsciiChar = 'A';
            consoleBuffer[x + screen_x * y].Attributes = 7;
        }
    }
}
void fill_buffer_to_console()
{
    WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos, &windowSize);
}



void star_fall()
{
    for (int i = 0; i < scount; i++)
    {
        if (star[i].Y == positiony && (star[i].X == positionx || star[i].X == positionx + 1 || star[i].X == positionx + 2 || star[i].X == positionx + 3 || star[i].X == positionx + 4))
        {
            star[i] = { (rand() % screen_x),1 };
            hitcount++;
        }
        else if (star[i].Y >= screen_y - 1)
        {
            star[i] = { (rand() % screen_x),1 };
        }
        else
        {
            star[i] = { star[i].X,star[i].Y + 1 };
        }
    }
}
void init_star()
{
    for (int i = 0; i < scount; i++)
    {
        star[i].X = rand() % screen_x;
        star[i].Y = rand() % screen_y;
        consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar = '*';
        consoleBuffer[star[i].X + screen_x * star[i].Y].Attributes = 7;
    }
}

void fill_star_to_buffer()
{
    for (int i = 0; i < scount; i++)
    {
        consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar = '*';
        consoleBuffer[star[i].X + screen_x * star[i].Y].Attributes = 7;
    }
}

void draw_ship(int x, int y, int Color)
{
    char ship[] = "<-0->";
    for (int i = 0; i < 5; i++)
    {
        consoleBuffer[x + i + screen_x * y].Char.AsciiChar = ship[i];
        consoleBuffer[x + i + screen_x * y].Attributes = Color;
    }
}

int main() {
    srand(time(NULL));
    bool Game_status = true;
    int Color = 7;
    DWORD Nevent = 0;
    DWORD NeventRead = 0;
    setConsole(screen_x, screen_y);
    setMode();
    init_star();
    
    while (Game_status)
    {
        clear_buffer();
        star_fall();
        fill_star_to_buffer();
        draw_ship(positionx, positiony, Color);
        GetNumberOfConsoleInputEvents(rHnd, &Nevent);
        if (hitcount >= 10)
            Game_status = false;
        if (Nevent != 0)
        {
            INPUT_RECORD* eventBuffer = new INPUT_RECORD[Nevent];
            ReadConsoleInput(rHnd, eventBuffer, Nevent, &NeventRead);
            for (DWORD i = 0; i < NeventRead; ++i)
            {
                if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true)
                {
                    if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                    {
                        Game_status = false;
                    }
                    else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c')
                    {
                        Color = rand() % 256;
                    }
                }
                else if (eventBuffer[i].EventType == MOUSE_EVENT)
                {
                    if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                    {
                        Color = rand() % 256;
                    }
                    positionx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
                    positiony = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
                }
            }
            delete[] eventBuffer;
        }
        fill_buffer_to_console();
        Sleep(100);
    }
    return 0;
}
