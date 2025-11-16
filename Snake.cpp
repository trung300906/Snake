#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void gotoxy(int x, int y);

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
            if (i == 0)
                cout << "O";
            else
                cout << "o";
        }
    }

    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];

        switch (Huong) {
            case 0: 
                A[0].x += 1; 
                break;
            case 1: 
                A[0].y += 1; 
                break;
            case 2: 
                A[0].x -= 1; 
                break;
            case 3: 
                A[0].y -= 1; 
                break;
        }
    }
};

int main() {
    CONRAN r;
    int Huong = 0; // 0: phải, 1: xuống, 2: trái, 3: lên

    while (true) {
        if (_kbhit()) {
            int key = _getch();

            if (key == 0 || key == 224) { // rắn di chuyển theo hướng mũi tên điều hướng
                key = _getch();
                switch (key) {
                    case 72: 
                        if (Huong != 1) 
                            Huong = 3; 
                        break;
                    case 80: 
                        if (Huong != 3) 
                            Huong = 1; 
                        break;
                    case 75: 
                        if (Huong != 0) 
                            Huong = 2; 
                        break; 
                    case 77: 
                        if (Huong != 2) 
                            Huong = 0; 
                        break;
                }
            } else { // WASD
                switch (key) {
                    case 'w': case 'W': 
                        if (Huong != 1) 
                            Huong = 3; 
                        break;
                    case 's': case 'S': 
                        if (Huong != 3) 
                            Huong = 1; 
                        break;
                    case 'a': case 'A': 
                        if (Huong != 0) 
                            Huong = 2; 
                        break;
                    case 'd': case 'D': 
                        if (Huong != 2) 
                            Huong = 0; 
                        break;
                }
            }
        }

        // Xóa đuôi rắn
        gotoxy(r.A[r.DoDai - 1].x, r.A[r.DoDai - 1].y);
        cout << " ";

        // Di chuyển và vẽ rắn
        r.DiChuyen(Huong);
        r.Ve();

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
