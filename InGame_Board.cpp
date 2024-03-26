#include "InGame.h"

extern char** matrix;
extern int matrix_size;

int board_x = 5;
int board_y = 5;

void InGame::DrawGameBoard(int size = 5)
{
	// Draw top line
    matrix_size = size;
    size += 2;

    Cursor(board_x + 4, board_y + 2);
	putchar(201);
	for (int i = 4; i < size * 8 - 3; i++)
	{
		Sleep(5);
		putchar(205);
	}
	putchar(187);
	
	// Draw right line
	for (int i = 3; i < size * 4 - 2; i++)
	{
		Sleep(10);
		Cursor(size * 8 + board_x - 2, i + board_y);
		putchar(186);
	}
	Cursor(size * 8 + board_x - 2, size * 4 + board_y - 2);
	putchar(188);
	
	// Draw bottom line
	for (int i = 1; i < size * 8 - 6; i++)
	{
		Cursor(size * 8 + board_x - i - 2, size * 4 + board_y - 2);
		Sleep(5);
		putchar(205);
	}
	Cursor(board_x + 4, size * 4 + board_y - 2);
	putchar(200);
	
	// Draw left line
	for (int i = 1; i < size * 4 - 4; i++)
	{
		Sleep(10);
		Cursor(board_x + 4, size * 4 + board_y - i - 2); 
		putchar(186);
	}

	// Draw vertical lines
	for (int i = 4; i < (size - 1) * 4; i++)
	{
		for (int j = 8; j < size * 8; j += 8)
		{
			if (i % 4 != 0)
			{
				Cursor(j + board_x + 1, i + board_y);
				putchar(179);
			}
		}
		Sleep(10);
	}
	
	// Draw horizontal lines
	for (int i = 8; i < (size - 1) * 8; i++)
	{
		for (int j = 4; j < size * 4; j += 4)
		{
			Cursor(i + board_x + 1, j + board_y);
			if (i % 8 == 0)
				//putchar(197);
				putchar(32);
			else
				putchar(196);
		}
		Sleep(5);
	}

    size -= 2;
    InGame::CreateMatrix(size);

    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
        {
            Cursor(8*j + board_x + 5, 4*i + board_y + 2);
            cout << matrix[i][j];
        }
}

void InGame::DeleteSquare(int x, int y)
{
    Cursor(8*y + board_x + 5, 4*x + board_y + 2);
    cout << " ";

    if (matrix[x - 1][y] == '.')
    {
        Cursor(8*y + board_x + 2, 4*x + board_y);
        cout << "       ";
    }

    if (matrix[x + 1][y] == '.')
    {
        Cursor(8*y + board_x + 2, 4*x + board_y + 4);
        cout << "       ";
    }

    if (matrix[x][y - 1] == '.')
        for (int i = 1; i < 4; i++)
        {
            Cursor(8*y + board_x + 1, 4*x + board_y + i);
            cout << " ";
        }

    if (matrix[x][y + 1] == '.')
        for (int i = 1; i < 4; i++)
        {
            Cursor(8*y + board_x + 9, 4*x + board_y + i);
            cout << " ";
        }
}

void InGame::drawTime(int size = 5)
{
    int x = board_x + 4 + (size + 2) * 8 - 4 - 4 + 1 + 5;
    int y = board_y + 2;
    Cursor(x + 1, y);
	putchar(218);
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		putchar(196);
	}
	putchar(191);
	
	// Draw right line
	for (int i = 1; i < size + size / 2 - 1; i++)
	{
		Cursor(size * 4 + size / 2 + x + 1, i + y);
		putchar(179);
	}
	Cursor(size * 4 + size / 2 + x + 1, size + size / 2 - 1 + y);
	putchar(217);
	
	// Draw bottom line
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		Cursor(size * 4 + size / 2 + x - i + 1, size + size / 2 - 1 + y);
		putchar(196);
	}
	Cursor(x + 1, size + size / 2 - 1 + y);
	putchar(192);
	
	// Draw left line 
	for (int i = 1; i < size + size / 2 - 1; i++)
	{
		Cursor(x + 1, size + size / 2 - 1 + y - i); 
		putchar(179);
	}  


    Cursor(x + (size * 4 + size / 2) / 2, y + 1);
    cout << "Time";
	Cursor(size * 4 + x - size * 4 + 1, y + 2);
	putchar(195);
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		Cursor(size * 4 + size / 2 + x - i + 1, y + 2);
		putchar(196);
	}
	Cursor(size * 4 + size / 2 + x - 0 + 1, y + 2);
	putchar(180);
    // Time t;
    // while(1)
    // {
    //     CountingTime(x + 8, y + 4, t);
    //     if(t.hour == 0 && t.minute == 0 && t.second == -1)
    //     {
    //         Cursor(x + 7, y + 4);
    //         cout << "You lose!!!";
    //         break;
    //     }
    // }
}

void InGame::drawGuide(int size = 5)
{
    int x = board_x + 4 + (size + 2) * 8 - 4 - 4 + 1 + 5;
    int y = board_y + 2 + size + size / 2 - 1 + 2;
    Cursor(x + 1, y);
	putchar(218);
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		putchar(196);
	}
	putchar(191);
	
	// Draw right line
	for (int i = 1; i < size * 2 + size; i++)
	{
		Cursor(size * 4 + size / 2 + x + 1, i + y);
		putchar(179);
	}
	Cursor(size * 4 + size / 2 + x + 1, size * 2 + size + y);
	putchar(217);
	
	// Draw bottom line
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		Cursor(size * 4 + size / 2 + x - i + 1, size * 2 + size + y);
		putchar(196);
	}
	Cursor(x + 1, size * 2 + size + y);
	putchar(192);
	
	// Draw left line 
	for (int i = 1; i < size * 2 + size ; i++)
	{
		Cursor(x + 1, size * 2 + size + y - i); 
		putchar(179);
	}  

    Cursor(x + (size * 4 + size / 2) / 2 - 1, y + 1);
    cout << "Guide";
	Cursor(size * 4 + x - size * 4 + 1, y + 2);
	putchar(195);
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		Cursor(size * 4 + size / 2 + x - i + 1, y + 2);
		putchar(196);
	}
	Cursor(size * 4 + size / 2 + x - 0 + 1, y + 2);
	putchar(180);
    
    Cursor(x + 2, y + 3);
    cout << "H: Hint";
    Cursor(x + 2, y + 3 + size / 2);
    cout << "Enter: Choose";
    Cursor(x + 2, y + 3 + size / 2 + size / 2);
    cout << "Backspace: Remove";
    Cursor(x + 2, y + 3 + size / 2 + size / 2 + size / 2);
	cout << "L: Load";
    Cursor(x + 2, y + 3 + size / 2 + size / 2 + size / 2 + size / 2);
    cout << "Esc: Escape";
}