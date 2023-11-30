#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <cmath>
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

using namespace std;

const int maxN = 4;

struct board
{
    int val;
    bool was;
};

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

void TextColor(int x)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

ii pos(board a[][maxN])
{
    int i = rand() % (maxN * maxN);
    while (a[i / maxN][i % maxN].val)
        i = rand() % (maxN * maxN);
    return mp(i / maxN, i % maxN);
}

void init(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
        for (int j = 0; j < maxN; j++)
            a[i][j].val = 0;

    for (int i = 0; i < maxN - 1; i++)
    {
        ii p = pos(a);
        a[p.f][p.s].val = 2;
    }
}
void doSpace(int x)
{
    int cnt = 0;
    if (!x)
        cnt++;
    while (x > 0)
    {
        x /= 10;
        cnt++;
    }
    for (int i = 0; i < 10 - cnt; i++)
        cout << ' ';
}
void display(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        doSpace(20);
        for (int j = 0; j < maxN; j++)
        {
            if (a[i][j].val)
                TextColor((int)(log(a[i][j].val) / log(2)) % 15);
            else
                TextColor(7);

            cout << a[i][j].val;
            doSpace(a[i][j].val);
        }
        cout << endl
             << endl;
    }
    TextColor(7);
}

bool canMove(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        for (int j = 0; j < maxN; j++)
        {
            if (!a[i][j].val)
                return true;
            if (i > 0)
                if (a[i][j].val == a[i - 1][j].val)
                    return true;
            if (j > 0)
                if (a[i][j].val == a[i][j - 1].val)
                    return true;
        }
    }
    return false;
}

void leftShift(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        for (int j = 0; j < maxN - 1; j++)
        {
            if (!a[i][j].val)
            {
                int J = j;
                while (!a[i][J + 1].val && J + 1 < maxN - 1)
                    J += 1;
                swap(a[i][j], a[i][J + 1]);
            }
        }
    }
}

void rightShift(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        for (int j = maxN - 1; j > 0; j--)
        {
            if (!a[i][j].val)
            {
                int J = j;
                while (!a[i][J - 1].val && J - 1 > 0)
                    J -= 1;
                swap(a[i][j], a[i][J - 1]);
            }
        }
    }
}

void upShift(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        for (int j = i; j < maxN; j++)
        {
            swap(a[i][j], a[j][i]);
        }
    }

    leftShift(a);

    for (int i = 0; i < maxN; i++)
    {
        for (int j = i; j < maxN; j++)
        {
            swap(a[i][j], a[j][i]);
        }
    }
}

void downShift(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        for (int j = i; j < maxN; j++)
        {
            swap(a[i][j], a[j][i]);
        }
    }

    rightShift(a);

    for (int i = 0; i < maxN; i++)
    {
        for (int j = i; j < maxN; j++)
        {
            swap(a[i][j], a[j][i]);
        }
    }
}

void leftSet(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        for (int j = 0; j < maxN - 1; j++)
        {
            if (a[i][j].val == a[i][j + 1].val)
            {
                a[i][j].val *= 2;
                a[i][j + 1].val = 0;
            }
        }
    }
}

void rightSet(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        for (int j = maxN - 1; j > 0; j--)
        {
            if (a[i][j].val == a[i][j - 1].val)
            {
                a[i][j].val *= 2;
                a[i][j - 1].val = 0;
            }
        }
    }
}

void upSet(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        for (int j = 0; j < maxN - 1; j++)
        {
            if (a[j][i].val == a[j + 1][i].val)
            {
                a[j + 1][i].val *= 2;
                a[j][i].val = 0;
            }
        }
    }
}

void downSet(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        for (int j = maxN - 1; j > 0; j--)
        {
            if (a[j][i].val == a[j - 1][i].val)
            {
                a[j - 1][i].val *= 2;
                a[j][i].val = 0;
            }
        }
    }
}
void move(board a[][maxN], int &type)
{
    while (!type)
    {
        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (key == 'a' || key == 'A') // Di chuyển trái
                type = 1;
            if (key == 'd' || key == 'D') // Di chuyển phải
                type = 2;
            if (key == 'w' || key == 'W') // Di chuyển lên
                type = 3;
            if (key == 's' || key == 'S') // Di chuyển xuống
                type = 4;
        }
    }
}

bool emptyCell(board a[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        for (int j = 0; j < maxN; j++)
            if (!a[i][j].val)
                return true;
    }
    return false;
}

void displayDirect(int type)
{
    gotoxy(0, 2);
    char direct[3][3];

    if (type == 1)
    {
        strcpy(direct[0], "   ");
        strcpy(direct[1], "<--");
        strcpy(direct[2], "   ");
    }

    if (type == 2)
    {
        strcpy(direct[0], "   ");
        strcpy(direct[1], "-->");
        strcpy(direct[2], "   ");
    }

    if (type == 3)
    {
        strcpy(direct[0], " ^ ");
        strcpy(direct[1], " | ");
        strcpy(direct[2], "   ");
    }

    if (type == 4)
    {
        strcpy(direct[0], " | ");
        strcpy(direct[1], " V ");
        strcpy(direct[2], "   ");
    }

    for (int i = 0; i < 3; i++)
    {
        doSpace(10);
        for (int j = 0; j < 3; j++)
        {
            cout << direct[i][j];
        }
        cout << endl;
    }
}

void cpyArr(board des[][maxN], board source[][maxN])
{
    for (int i = 0; i < maxN; i++)
    {
        for (int j = 0; j < maxN; j++)
            des[i][j] = source[i][j];
    }
}
void process(board a[][maxN])
{
    board b[maxN][maxN];
    cout << "Auto mode ? (Press Y/N)";
    char key = ' ';
    while (1)
    {
        key = getch();
        if (toupper(key) == 'Y' || toupper(key) == 'N')
            break;
    }

    system("cls");

    gotoxy(0, 5);
    display(a);

    while (canMove(a))
    {
        int type = 0;
        if (toupper(key) == 'N')
            move(a, type);
        else
        {
            type = (rand() % 4) + 1;
            cpyArr(b, a);
        }

        if (type == 1)
        {
            leftShift(a);
            leftSet(a);
            leftShift(a);
        }
        if (type == 2)
        {
            rightShift(a);
            rightSet(a);
            rightShift(a);
        }
        if (type == 3)
        {
            upShift(a);
            upSet(a);
            upShift(a);
        }
        if (type == 4)
        {
            downShift(a);
            downSet(a);
            downShift(a);
        }

        if (emptyCell(a))
        {
            ii p = pos(a);
            a[p.f][p.s].val = 2;
        }

        displayDirect(type);

        if (toupper(key) == 'Y')
        {
            gotoxy(0, 1);
            // doSpace(10);
            // cout << "( Press any key for auto play or ! to play by yourself)";
            // char tmp;
            // tmp = getch();
            // if (tmp == '!')
            // {
            //     key = 'N';
            //     system("cls");
            //     cpyArr(a, b);
            // }
        }
        gotoxy(0, 5);
        display(a);
    }
    cout << "Game over!\n";
    key = getch();
    return;
}

int main()
{
    srand(time(0));
    board a[maxN][maxN];
    init(a);
    process(a);
    return 0;
}