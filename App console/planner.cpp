#include "planner.h"
#include <limits> //cung cấp giá trị vô hạn (max) cho numeric_limits, đỡ phải set limit=))//
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
using namespace std;
planner dsViec[100];   // mảng chứa tối đa 100 công việc
int soLuongViec = 0;  // số công việc hiện có trong mảng
//khai biến các hàm ở trên cùng => biến toàn cục, 

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');   // xóa newline tồn đọng

        //nghĩa là khi nhập giá trị sau đó nhấn enter (enter được coi là một \n)
        //biến sẽ chỉ nhận giá trị và để lại \n trong buffer => skip đến biến tiếp theo
        //thành ra getline tiếp theo đọc trúng cái \n đó trong buffer => skip và không cho bạn nhập
        //lệnh này giúp biến bỏ qua dấu enter, các biến sau sẽ không bị skip//


        
        if (nhapNut == 0) {
            
            break; // Thoát menu quay về màn hình chính
        }
        else if (nhapNut == 1) {
            nhapPlan();
        }
        else if (nhapNut == 2) {
            xemCongViec();
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

void nhapPlan() { //Chức năng thêm công việc, tuii làmmmm//
    
  

    if (soLuongViec >= 100) {
        cout << "\nDa dat gioi han 100 cong viec, khong the them moi!\n";
        return;
    }
    cout << "======== THÊM CÔNG VIỆC ========\n";
    
    cout << " Nhập ngày (dd/mm/yy): ";// Thêm ngày vào phần tử soLuongViec (0) đầu tiên, với ten biến là "ngay"//
    getline(cin, dsViec[soLuongViec].ngay); //đọc một dòng văn bản hoàn chỉnh từ bàn phím, nhận khoảng trắng//
    
    cout << " Nhap ten cong viec: ";
    getline(cin, dsViec[soLuongViec].viec);
    
    cout << " Nhap gio bat dau (hh:mm): "; 
    getline(cin, dsViec[soLuongViec].gioBatDau);
    
    dsViec[soLuongViec].id = soLuongViec + 1;  // 0->1//
    //gán id cho từng công việc, vd:( 1 | Đi học)//
    
    soLuongViec++;
    cout << "\nDa them cong viec thanh cong!\n";
}

void xemCongViec()
{
  
    cout << " ============= Danh sách công việc =============\n";
    cout << "-------------------------------------------------\n";
    if (soLuongViec == 0)
    {
        cout << "Chua co cong viec nao trong danh sach.\n";
        return;
    }
    cout << "ID |       Ngay      | Gio bat dau | Ten cong viec\n";
    int i = 0; //tạo i để duyệt từ ô đầu tiên tới ô cuối cùng có dữ liệu công việc//
    while (i < soLuongViec)
    {
        cout << dsViec[i].id << "  |    " <<dsViec[i].ngay<< "    |    " << dsViec[i].gioBatDau << "    | " << dsViec[i].viec << "\n";
        i++;
    }



}