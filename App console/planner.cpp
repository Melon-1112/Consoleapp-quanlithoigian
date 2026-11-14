#include "planner.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
using namespace std;

// Hàm lấy và in ngày giờ hiện tại
void layTimer() {
    time_t tgian = time(nullptr);
    tm lt{};
    localtime_s(&lt, &tgian);
    cout << put_time(&lt, "%d/%m/%Y");
}

// Giao diện Task Manager lặp vô tận (infinity loop)
int giaoDienPlan() {
    int nhapNut;

    while (true) {
        system("cls"); // Xóa màn hình mỗi lần lặp lại để cập nhật giờ mới

        // In tiêu đề kèm ngày giờ kế bên
        cout << "============ TASK MANAGER | ";
        layTimer();
        cout << " ============\n";

        cout << R"(
[1] Them cong viec
[2] Xem danh sach cong viec
[3] Sap xep theo uu tien
[0] Thoat
)";
        cout << "\nChon chuc nang: ";
        cin >> nhapNut;

        
        if (nhapNut == 0) {
            
            break; // Thoát menu quay về màn hình chính
        }
        else if (nhapNut == 1) {
            nhapPlan();
        }
        else if (nhapNut == 2) {
            cout << "Chuc nang xem danh sach dang phat trien!\n";
        }
        else if (nhapNut == 3) {
            cout << "Chuc nang sap xep dang phat trien!\n";
        }
        else {
            cout << "Khong ton tai chuc nang!\n";
        }

        cout << "\nNhan Enter de tiep tuc...";
        system("pause > nul"); // Dừng màn hình chờ người dùng bấm phím
    }

    return 0;
}

void nhapPlan() {
    planner dsViec[100];
    cout << "Da goi ham nhap cong viec!\n";
}
