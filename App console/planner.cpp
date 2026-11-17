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

bool gioHopLe(string gio) // hh:mm phai co dung 5 ky tu. 
{
    
    if (gio.length() != 5)
    {
        return false;

    }
    if (gio[2] != ':') // ở giữa giờ và phút phải là ":"
    {
        return false;
    }
    for (int i = 0; i < 5; i++) //cho i duyệt từ vị trí 0->4, xem có phải chac chan là số không
    {
        if (i != 2)// hx:mx -> phải hợp lệ , và bỏ qua vị trí của ":"
        {
            if (gio[i] < '0' || gio[i] > '9') //phép so sánh mã ASCII . 0 là 48 và 9 là 57 trong bảng mã ascii . Nằm ngoài khoảng đó trong mã ascii thì không còn là số nữa -> false
            {
                return false;
            }
        }
    }
    int h = (gio[0] - '0') * 10 + (gio[1] - '0'); // chuyển 2 kí tự của hh thành 2 số (int)
    //'0' ở trong ascii là 48 
    //vd:  08:30 ->  [0][1][2][3][4]
    // (48-48)*10+(56 - 48) = 08 ( đã chuyển 08 string sang 08 int)
    int p = (gio[3] - '0') * 10 + (gio[4] - '0'); // chuyển 2 kí tự của mm thành 2 số (int)
    //vd: 08:30 ->  [0][1][2][3][4]
    // (51-48)*10+(48-48) = 30 (đã chuyển 30 string sang 30 int)


    if (h > 23 || p > 59) //số giờ phải nhỏ hơn 23 và số phút phải nhỏ hơn 59
    {
        return false;
    }

    return true;

}



bool ngayHopLe(string ngayNhap)
{
    // dd/mm/yyyy phai co dung 10 ky tu.
    if (ngayNhap.length() != 10)
    {
        return false;
    }
    // Kiem tra hai dau '/'. nếu kí tự khác = false
    if (ngayNhap[2] != '/' || ngayNhap[5] != '/') {
        return false;
    }
    // ngoai hai dau '/' tat ca phai la chu so, khác = false
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5) {
            if (ngayNhap[i] < '0' || ngayNhap[i] > '9') {
                return false;
            }
        }
    }
    // tách ngày tháng năm,từ string sang int. vd 19/06/2008 =)))
    int ngay = (ngayNhap[0] - '0') * 10 + (ngayNhap[1] - '0');
    //(49-48)*10+(57-48)=19
    int thang = (ngayNhap[3] - '0') * 10 + (ngayNhap[4] - '0');
    //(48=48)*10+(54-48)=06
    int nam = (ngayNhap[6] - '0') * 1000 + (ngayNhap[7] - '0') * 100 + (ngayNhap[8] - '0') * 10 + (ngayNhap[9] - '0');
    //(50-48)*1000+(48-48)*100+(48-48)*10+(56-48)=2008
        
    if (nam < 1) // Khong chap nhan nam 0000.
    {
        return false;
    }

    if (thang < 1 || thang > 12) // tháng phải hợp lệ
    {
        return false;
    }

    // tháng có 31 ngày
    int ngayToiDa = 31;

    // riêng 4 tháng này có 30 ngày
    if (thang == 4 || thang == 6 ||
        thang == 9 || thang == 11) {
        ngayToiDa = 30;
    }
    // xử lý riêng tháng 2, nhức đầu vicieo
    if (thang == 2) {
        ngayToiDa = 28;

        if (nam % 400 == 0 ||(nam % 4 == 0 && nam % 100 != 0)) 
            //Chia hết cho 4 thì nhuận, trừ khi chia hết cho 100 mà không chia hết cho 400.
        {
            
            ngayToiDa = 29;
        }
    }

    if (ngay < 1 || ngay > ngayToiDa) // ngày phải hợp lệ như nãy h đa xét
    {
        return false;
    }

    return true;


}







void nhapPlan() { //Chức năng thêm công việc, tuii làmmmm//
    
  

    if (soLuongViec >= 100) {
        cout << "\nDa dat gioi han 100 cong viec, khong the them moi!\n";
        return;
    }
    cout << "\x1B[1;33m======== THÊM CÔNG VIỆC ========\x1B[0m\n";
    
    while (true) {
        cout << " Nhap ngay (dd/mm/yyyy): ";

        if (!getline(cin, dsViec[soLuongViec].ngay)) 
        //Đọc không được nữa thì bỏ cuộc, không có gì để hỏi thêm. (EOF)
        //Đọc được mà sai thì hỏi lại.
        {
            return;
        }
        //nếu không dính EOF, thì tiếp tục chạy
       
        string ngayNhap;
        ngayNhap = dsViec[soLuongViec].ngay;
        ngayHopLe(ngayNhap);
        if (ngayHopLe(ngayNhap))
        {
            break;
        }
        //gán giá trị trong mảng sang cho ngayNhap, sau đó gọi kiểm tra ngayNhap
        //nếu hợp lệ => thoát loop



        cout << " Ngay khong hop le, vui long nhap lai!\n";
    }

    cout << " Nhap ten cong viec: ";
    getline(cin, dsViec[soLuongViec].viec);
    
    while (true) {
        cout << " Nhap gio bat dau (hh:mm): ";

        if (!getline(cin, dsViec[soLuongViec].gioBatDau)) {
            return;
        }

        string gio;
        gio = dsViec[soLuongViec].gioBatDau;
        gioHopLe(gio);
        if (gioHopLe(gio))
        {
            break;
        }
       

       
        cout << " Gio khong hop le, vui long nhap lai!\n";
    }
    
    dsViec[soLuongViec].id = soLuongViec + 1;  // 0->1//
    //gán id cho từng công việc, vd:( 1 | Đi học)//
    
    soLuongViec++;
    system("cls");
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
