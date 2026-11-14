#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <ctime>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

void diChuyenCuaSo(int x, int y) {
    COORD viTri = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), viTri);
}
int layDongCuoi() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom;   // dòng cuối đang nhìn thấy
}
void layTimer() {
    while (true) {
    diChuyenCuaSo(0, layDongCuoi());
    time_t tgian = time(nullptr);
        tm localTime{};
        localtime_s(&localTime, &tgian);
        cout << "Ngay: " << put_time(&localTime, "%d/%m/%Y");
        cout << " Gio: " << put_time(&localTime, "%H:%M") << flush;

        this_thread::sleep_for(chrono::seconds(1));

        //if (_kbhit()) break;   // bấm phím bất kỳ để thoát
    }
}

int planner() {
    cout << "===============================PLANNER===============================\n";
    //cout << "(Nhan phim bat ky de thoat)\n";
    layTimer();
    return 0;
}