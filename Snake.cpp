#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
using namespace std;

void gotoxy(int x, int y);

// Ẩn con trỏ nhấp nháy
void ShowCur(bool CursorVisibility) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}

struct Point {
    int x, y;
};

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
            if (i == 0) cout << "X";
            else cout << "o";
        }
    }

    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];

        switch (Huong) {
            case 0: A[0].x += 1; break;
            case 1: A[0].y += 1; break;
            case 2: A[0].x -= 1; break;
            case 3: A[0].y -= 1; break;
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

void VeTuong() {
    for (int i = 0; i < 80; i++) {
        gotoxy(i, 0); cout << "#";
        gotoxy(i, 24); cout << "#";
    }
    for (int i = 0; i < 25; i++) {
        gotoxy(0, i); cout << "#";
        gotoxy(79, i); cout << "#";
    }
}

int main() {
    ShowCur(0);

    CONRAN r;
    int Huong = 0;

    VeTuong();
    r.Ve();

    while (true) {
        if (_kbhit()) {
            int key = _getch();
            if (key == 0 || key == 224) { 
                key = _getch();
                switch (key) {
                    case 72: if (Huong != 1) Huong = 3; break;
                    case 80: if (Huong != 3) Huong = 1; break;
                    case 75: if (Huong != 0) Huong = 2; break;
                    case 77: if (Huong != 2) Huong = 0; break;
                }
            }
            else{
                switch(key){
                    case 'w': if (Huong != 1) Huong = 3; break;
                    case 's': if (Huong != 3) Huong = 1; break;
                    case 'a': if (Huong != 0) Huong = 2; break;
                    case 'd': if (Huong != 2) Huong = 0; break;
                }
            }
        }
        Point duoiCu = r.A[r.DoDai - 1];

        r.DiChuyen(Huong);

        if (r.A[0].x <= 0 || r.A[0].x >= 79 || r.A[0].y <= 0 || r.A[0].y >= 24) {
            gotoxy(35, 12); cout << "GAME OVER!";
            break;
        }

        gotoxy(r.A[0].x, r.A[0].y); cout << "X";
        gotoxy(r.A[1].x, r.A[1].y); cout << "o";

        // Xóa đuôi để rắn KHÔNG dài thêm
        gotoxy(duoiCu.x, duoiCu.y);
        cout << " ";

        Sleep(150);
    }

    gotoxy(0, 26);
    return 0;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}