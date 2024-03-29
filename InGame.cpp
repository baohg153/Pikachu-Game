#include "InGame.h"
#include <thread>
#include <atomic>
#include <mutex>

extern char** matrix;
extern int matrix_size;
extern int board_x;
extern int board_y;
extern Point HintA;
extern Point HintB;

int tracker = 0;

std::mutex cursorMutex;
atomic<bool> thread1Finished(false);

void threadMove() {
    int x1 = 1, y1 = 1, x2 = 1, y2 = 1, count = 0;
    while (1)
    {
        if (thread1Finished) {
            break;
        }
        
        if(HintA.x == -1 || (matrix[HintA.x][HintA.y] == '.' && matrix[HintB.x][HintB.y] == '.'))
        {
            while(InGame::AutomaticallyFinding(matrix_size, matrix_size) == false)
            {
                random_device rd;
                InGame::ShuffleBoard(matrix_size, matrix_size, rd());

                // cursorMutex.lock(); 
                for (int i = 1; i <= matrix_size; i++)
                {
                    for (int j = 1; j <= matrix_size; j++)
                    {
                        std::lock_guard<std::mutex> lock(cursorMutex);
                        Cursor(8*j + board_x + 5, 4*i + board_y + 2);
                        if(matrix[i][j] != '.')
                        {
                            std::cout << matrix[i][j];
                            Sleep(200);
                        }
                    }
                }
                // cursorMutex.unlock();              
            }
        }

        x1 = x2;
        y1 = y2;

        if (matrix[x1][y1] != '.')
            InGame::SquareCursor(x1, y1, WHITE);
        
        //Chọn (x1, y1)
        while (1)
        {
            int button = ConsoleInput();

            if (matrix[x1][y1] != '.')
                InGame::DeleteSquareCursor(x1, y1);

            //Kiểm tra phím mũi tên
            if (button == 2)
                x1 = (x1 + matrix_size - 2) % matrix_size + 1;
            else if (button == -2)
                x1 = x1 % matrix_size + 1;
            else if (button == -3)
                y1 = (y1 + matrix_size - 2) % matrix_size + 1;
            else if (button == 3)
                y1 = y1 % matrix_size + 1;

            //Kiểm tra phím Enter
            else if (button == 1 && matrix[x1][y1] != '.')
            {
                InGame::SquareCursor(x1, y1, WHITE);
                break;
            }

            //Kiểm tra phím Esc
            else if (button == 0)
            {
                thread1Finished = true;
                tracker = 1;
                return;
            }
            // Move Suggestion
            else if(button == 10)
            {
                InGame::SquareCursor(HintA.x, HintA.y, GREEN);
                InGame::SquareCursor(HintB.x, HintB.y, GREEN);       
            }

            if (matrix[x1][y1] != '.')
                InGame::SquareCursor(x1, y1, WHITE);
        }

        //Chọn (x2, y2)
        x2 = x1;
        y2 = y1;
        while (1)
        {
            int button = ConsoleInput();

            if ((x2 != x1 || y2 != y1) && matrix[x2][y2] != '.')
                InGame::DeleteSquareCursor(x2, y2);

            //Kiểm tra phím mũi tên
            if (button == 2)
                x2 = (x2 + matrix_size - 2) % matrix_size + 1;
            else if (button == -2)
                x2 = x2 % matrix_size + 1;
            else if (button == -3)
                y2 = (y2 + matrix_size - 2) % matrix_size + 1;
            else if (button == 3)
                y2 = y2 % matrix_size + 1;

            //Kiểm tra phím Enter
            else if (button == 1 && (x2 != x1 || y2 != y1))
            {
                InGame::SquareCursor(x2, y2, WHITE);
                break;
            }

            //Kiểm tra phím Backspace
            else if (button == -1)
            {
                x2 = -1;
                break;
            }

            //Kiểm tra phím Esc
            else if (button == 0)
            {
                thread1Finished = true;
                tracker = 1;
                return;
            }
            // Move Suggestion
            else if(button == 10)
            {
                InGame::SquareCursor(HintA.x, HintA.y, GREEN);
                InGame::SquareCursor(HintB.x, HintB.y, GREEN);       
            }

            if (matrix[x2][y2] != '.')
                InGame::SquareCursor(x2, y2, WHITE);
        }
        if (x2 == -1)
        {
            x2 = x1;
            y2 = y1;
            continue;
        }
        
        if (InGame::CheckPath(x1, y1, x2, y2, matrix[x1][y1], 2, -1, -1))
        {
            matrix[x1][y1] = '.';
            matrix[x2][y2] = '.';

            InGame::SquareCursor(x1, y1, GREEN);
            InGame::SquareCursor(x2, y2, GREEN);

            Sleep(50);
            
            InGame::DeleteSquareCursor(x1, y1);
            InGame::DeleteSquareCursor(x2, y2);

            InGame::DeleteSquare(x1, y1);
            InGame::DeleteSquare(x2, y2);
            count += 2;
        }
        else
        {
            InGame::SquareCursor(x1, y1, RED);
            InGame::SquareCursor(x2, y2, RED);

            Sleep(50);

            InGame::DeleteSquareCursor(x1, y1);
            InGame::DeleteSquareCursor(x2, y2);
        }

        if (count == matrix_size * matrix_size)
        {
            thread1Finished = true;
            Sleep(1000);
            InGame::DrawFinish(matrix_size);
            break;
        }
    }
}


void threadTime() {
    Time t;
    int x = 5 + 4 + (matrix_size + 2) * 8 - 4 - 4 + 1 + 5;
    int y = 5 + 2;

    while(1)
    {
        if (thread1Finished) {
            break;
        }
        InGame::CountingTime(x + (matrix_size * 4 + matrix_size / 2) / 2 - 2, y + 2 + (matrix_size + matrix_size / 2  - 3) / 2, t);
        if(t.hour == 0 && t.minute == 0 && t.second == -1)
        {
            Cursor(x + (matrix_size * 4 + matrix_size / 2) / 2 - 3, y + 2 + (matrix_size + matrix_size / 2  - 3) / 2);
            thread1Finished = true;
            std::cout << "You lose!!!";
            break;
        }
    }
}




void Classic::ClassicGame(int size)
{
    system("cls");

    InGame::DrawGameBoard(size, 2 * size - 2);
    InGame::DrawTime(size);
    InGame::DrawGuide(size);
    InGame::CreateBackground(size);
    HintA.x = -1;
    HintA.y = -1;
    HintB.x = -1;
    HintB.y = -1;

    thread t1(threadMove);
    Sleep(500);
    thread t2(threadTime);

    t1.join();
    t2.join();

    DeleteMatrix();
    DeleteBackground();

    if (thread1Finished) {
        thread1Finished = false;
    }
    if(tracker)
    {
        tracker = 0;
        return;
    }
}

void Classic::Easy()
{
    Classic::ClassicGame(4);
}

void Classic::Medium()
{
    Classic::ClassicGame(6);
}

void Classic::Hard()
{
    Classic::ClassicGame(8);
}




