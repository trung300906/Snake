#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

void gotoxy(int x, int y);
void ShowCur(bool CursorVisibility) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}

struct Point { int x, y; };

class CONRAN {
public:
    Point A[100];
    int DoDai;

    CONRAN() {
        DoDai = 3;
        A[0] = {10, 10};
        A[1] = {9, 10};
        A[2] = {8, 10};
    }

    void Ve() {
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << (i == 0 ? "X" : "o");
        }
    }

    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];

        switch (Huong) {
            case 0: A[0].x++; break;
            case 1: A[0].y++; break;
            case 2: A[0].x--; break;
            case 3: A[0].y--; break;
        }
    }

    void TangDoDai() {
        DoDai++;
    }

    bool TuChamVaoThan() {
        for (int i = 1; i < DoDai; i++)
            if (A[0].x == A[i].x && A[0].y == A[i].y)
                return true;
        return false;
    }
};

Point TaoQua() {
    Point q;
    q.x = rand() % 78 + 1;
    q.y = rand() % 23 + 1;
    return q;
}

int main() {
    ShowCur(0);
    srand(time(0));

    CONRAN r;
    int Huong = 0;
    r.Ve();

    Point qua = TaoQua();
    gotoxy(qua.x, qua.y); cout << "x";

    while (true) {
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
                case 'w': if (Huong != 1) Huong = 3; break;
                case 's': if (Huong != 3) Huong = 1; break;
                case 'a': if (Huong != 0) Huong = 2; break;
                case 'd': if (Huong != 2) Huong = 0; break;
            }
        }

        Point duoiCu = r.A[r.DoDai - 1];
        r.DiChuyen(Huong);

        // Kiểm tra ăn mồi
        if (r.A[0].x == qua.x && r.A[0].y == qua.y) {
            r.TangDoDai(duoiCu);
            qua = TaoQua();
            gotoxy(qua.x, qua.y); cout << "x";
        } else {
            gotoxy(duoiCu.x, duoiCu.y);
            cout << " ";
        }
        if (r.TuChamVaoThan()) {
            gotoxy(35, 12); cout << "GAME OVER!";
            break;
        }
        gotoxy(r.A[0].x, r.A[0].y); cout << "X";
        gotoxy(r.A[1].x, r.A[1].y); cout << "o";

        Sleep(150);
    }

    return 0;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}