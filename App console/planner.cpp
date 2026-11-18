#include "planner.h"
#include <limits> //cung cấp giá trị vô hạn (max) cho numeric_limits, đỡ phải set limit=))//
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>//<iostream> làm việc với bàn phím/màn hình (cin/cout), 
//còn <fstream> làm việc với file thay vào đó.
#include <filesystem>//Đường dẫn & hệ thống file 
#include <cstdlib>//Thư viện tiện ích C
using namespace std;
planner dsViec[100];   // mảng chứa tối đa 100 công việc
int soLuongViec = 0;  // số công việc hiện có trong mảng
//khai biến các hàm ở trên cùng => biến toàn cục, 
int mucDo;




// Hàm trả về đường dẫn tuyệt đối tới tệp "TimeZ.txt".
// Tệp này nằm trong thư mục AppData (Roaming) của tài khoản Windows đang đăng nhập.
// Kiểu trả về: filesystem::path — là kiểu đường dẫn của thư viện chuẩn <filesystem>.
filesystem::path layDuongDanFile()
{
    // appData: con trỏ wide-string sẽ được thư viện cấp phát để chứa giá trị biến môi trường.
    // nullptr nghĩa là hiện tại chưa có dữ liệu nào.
    wchar_t* appData = nullptr;

    // doDai: độ dài (số ký tự) của chuỗi mà thư viện sẽ ghi ra. Biến này là tham số ra,
    // nên sau khi gọi hàm ta sẽ biết chuỗi dài bao nhiêu.
    size_t doDai = 0;

    // Gọi _wdupenv_s để lấy giá trị biến môi trường "APPDATA".
    // Trên Windows, APPDATA trỏ tới: C:\Users\<Tên người dùng>\AppData\Roaming
    // Hàm trả về 0 nếu thành công, khác 0 nếu thất bại (ví dụ biến không tồn tại).
    if (_wdupenv_s(&appData, &doDai, L"APPDATA") != 0
        || appData == nullptr) // thêm kiểm tra con trỏ rỗng cho chắc chắn
    {
        // Nếu thất bại thì trả về một đường dẫn rỗng.
        // {} là cách viết ngắn để khởi tạo giá trị mặc định (path rỗng) của kiểu trả về.
        return {};
    }

    // Tạo đường dẫn bằng cách nối các thành phần bằng toán tử "/".
    // Toán tử "/" của filesystem::path tự động thêm dấu phân cách phù hợp với hệ điều hành.
    // Kết quả: C:\Users\<Tên người dùng>\AppData\Roaming\TimeZ\TimeZ.txt
    filesystem::path duongDan =
        filesystem::path(appData) / L"TimeZ" / L"TimeZ.txt";

    // Quan trọng: _wdupenv_s cấp phát bộ nhớ bằng malloc, nên ta PHẢI tự giải phóng.
    // Nếu quên dòng này sẽ bị rò rỉ bộ nhớ (memory leak).
    free(appData);

    // Trả đường dẫn đã tạo ra cho nơi gọi.
    return duongDan;
}


// Hàm lưu danh sách công việc xuống tệp "TimeZ.txt".
// Trả về true nếu lưu thành công, false nếu gặp lỗi.
// Dùng biến toàn cục soLuongViec (số lượng công việc) và dsViec (mảng công việc).
bool luuCongViec()
{
    // Lấy đường dẫn tuyệt đối của tệp cần lưu (do hàm layDuongDanFile() tạo ra).
    filesystem::path duongDan = layDuongDanFile();

    // Nếu đường dẫn rỗng nghĩa là lấy AppData thất bại → không thể lưu, dừng lại.
    if (duongDan.empty())
    {
        return false;
    }

    // Tạo thư mục cha (thư mục "TimeZ") nếu chưa tồn tại.
    // Tham số "loi" là error_code: nhận mã lỗi thay vì ném exception (ném lỗi có thể làm chương trình
    // bị dừng đột ngột khi người dùng chỉ muốn báo lỗi thôi).
    error_code loi;
    filesystem::create_directories(duongDan.parent_path(), loi);

    // Nếu có lỗi khi tạo thư mục (ví dụ: không có quyền ghi) → dừng.
    if (loi)
    {
        return false;
    }

    // Mở tệp để ghi.
    // ofstream = output file stream (dòng ghi). Tệp có sẵn sẽ bị ghi đè (truncate).
    // ofstream nhận được filesystem::path nên không cần chuyển đổi sang wstring thủ công.
    ofstream file(duongDan);

    // is_open() kiểm tra tệp đã mở thành công hay chưa.
    // Mở thất bại khi: tệp đang bị khóa, sai đường dẫn, không có quyền ghi...
    if (!file.is_open())
    {
        return false;
    }

    // Duyệt qua từng công việc trong danh sách và ghi ra tệp, mỗi công việc 1 dòng.
    for (int i = 0; i < soLuongViec; i++)
    {
        // Dấu ' ' giữa các trường: dấu phân cách giữa các cột dữ liệu.
        // quoted(...) đặt dấu " quanh giá trị, để giữ nguyên cả khoảng trắng bên trong chuỗi.
        //   ví dụ: viec = "Học C++" sẽ được ghi là: "Học C++"
        //   nhờ vậy khi đọc lại bằng >> và quoted sẽ phân biệt được dấu " với khoảng trắng.
        // quoted lấy từ <iomanip>.
        file 
            
            << quoted(dsViec[i].ngay) << ' '
            << quoted(dsViec[i].gioBatDau) << ' '
            << quoted(dsViec[i].viec) << ' '
            << quoted(dsViec[i].uuTien) << ' '
            << dsViec[i].tick << '\n';
        // '\n' kết thúc dòng (xuống dòng).
    }

    // Đóng tệp để chắc chắn dữ liệu trong bộ đệm được ghi xuống đĩa.
    // (Khi đối tượng ofstream bị hủy thì tệp cũng tự đóng, nhưng gọi tường minh rõ ràng hơn.)
    file.close();

    // fail() trả về true nếu có lỗi ghi (ví dụ: ổ đĩa đầy, tệp bị khóa).
    // Đảo ngược lại để trả về true khi KHÔNG có lỗi.
    return !file.fail();
}



// Hàm đọc danh sách công việc từ tệp "TimeZ.txt" và nạp vào bộ nhớ.
// Sau khi hàm này chạy xong:
//   - soLuongViec chứa số lượng công việc đã đọc được
//   - dsViec[] chứa nội dung của các công việc đó
void docCongViec()
{
    // Lấy đường dẫn tuyệt đối của tệp cần đọc (giống hàm lưu).
    filesystem::path duongDan = layDuongDanFile();

    // Không lấy được đường dẫn (lỗi môi trường) → không có gì để đọc, thoát hàm.
    if (duongDan.empty())
    {
        return;
    }

    // Mở tệp để đọc.
    // ifstream = input file stream (dòng đọc). Khác ofstream (dòng ghi) ở phía trên.
    ifstream file(duongDan);

    // Lần đầu chạy chưa có tệp thì bỏ qua, coi như chưa có công việc nào.
    // is_open() trả về false nếu tệp không tồn tại hoặc không mở được.
    if (!file.is_open())
    {
        return;
    }

    // Reset bộ đếm về 0 trước khi đọc, để tránh cộng dồn với dữ liệu cũ đang có trong bộ nhớ.
    soLuongViec = 0;

    // cv là một biến tạm để chứa công việc đang đọc.
    // planner là kiểu struct mô tả một công việc; {} khởi tạo tất cả các trường về 0 / rỗng.
    planner cv{};

    // Vòng lặp đọc từng dòng một cho tới khi:
    //   1) hết dữ liệu (file >> ... thất bại), HOẶC
    //   2) đã đọc đủ 100 công việc (giới hạn kích thước mảng dsViec),
    //   3) hoặc dữ liệu trong tệp bị sai định dạng (thiếu trường, thiếu dấu " ...).
    while (soLuongViec < 100 && (file >> ws))
    {
        // Tệp hiện tại bắt đầu bằng ngày trong ngoặc kép; tệp cũ có thêm id.
        cv.id = soLuongViec + 1;
        if (file.peek() != '"' && !(file >> cv.id)) {
            break;
        }
        if (!(file >> quoted(cv.ngay) >> quoted(cv.gioBatDau)
                   >> quoted(cv.viec) >> quoted(cv.uuTien) >> cv.tick)) {
            break;
        }

        // Lưu công việc vừa đọc vào mảng, tại vị trí soLuongViec.
        dsViec[soLuongViec] = cv;

        // Tăng bộ đếm để sang công việc tiếp theo.
        soLuongViec++;
    }
}













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


        
        switch (nhapNut) {
        case 0:
            break; // Thoat switch

        case 1:
            nhapPlan();
            break;

        case 2:
            xemCongViec();
            break;

        case 3:
            cout << "Chuc nang sap xep dang phat trien!\n";
            break;

        default:
            cout << "Khong ton tai chuc nang!\n";
            break;
        }

        cout << "\nNhan Enter de tiep tuc...";
        system("pause > nul");
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
    cout << endl << "Cac gia tri thu tu uu tien " << "[1].IMPORTAIN \t" << "[2].NECESSARY \t" << "[3].UN-NECESSARY" << endl;
    cout << "Nhap muc do uu tien: ";
    cin >> mucDo;
    if (mucDo == 1) {
        dsViec[soLuongViec].uuTien = "IMPORTAIN";
    }
    else if (mucDo == 2) {
        dsViec[soLuongViec].uuTien = "NECESSARY";
    }
    else if (mucDo == 3) {
        dsViec[soLuongViec].uuTien = "UN-NECESSARY";
    }
    
    cout << endl;
    
    dsViec[soLuongViec].id = soLuongViec + 1;  // 0->1//
    //gán id cho từng công việc, vd:( 1 | Đi học)//
    
    soLuongViec++;
    system("cls");

    if (luuCongViec())
    {
        cout << "\nDa them va luu cong viec thanh cong!\n";
    }
    else
    {
        cout << "\nDa them vao danh sach, nhung luu file that bai!"
            << "\nCong viec moi co the mat khi thoat app.\n";
    }
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
    cout << "STT | MUC DO UU TIEN | Ngay | Gio bat dau | Ten cong viec\n"<< endl;

    int i = 0;
    while (i < soLuongViec)
    {
        cout 
            << i + 1 << " | " << dsViec[i].uuTien << " | "
            << dsViec[i].ngay << " | "
            <<" " << dsViec[i].gioBatDau << "      | "
            << dsViec[i].viec << "\n";

        i++;
    
    }
    
    
}
int giaTriUuTien(string uuTien) {
    if (uuTien == "IMPORTAIN") {
        return 1;
    }
    else if (uuTien == "NECESSARY") {
        return 2;
    }
    else if (uuTien == "UN-NECESSARY") {
        return 3;
    }

    return 4;
}
//Thuat toan sap xep
void selectionSort() {
    int min;
    for (int i = 0; i < soLuongViec - 1; i++) {
        min = i;
        for (int j = i + 1;j < soLuongViec; j++) {
            if (giaTriUuTien(dsViec[j].uuTien) < giaTriUuTien(dsViec[i].uuTien)) {
                min = j;
            }
        }
        if (min != i) {
            planner tam = dsViec[i];
            dsViec[i] = dsViec[min];
            dsViec[min] = tam;

        }

    }


}

// Kiem tra nam nhap vao co bang nam hien tai khong.
bool kiemTraNam(int nam) {
    time_t tgian = time(nullptr);
    tm lt = {};
    if (localtime_s(&lt, &tgian) != 0) {
        return false;
    }

    int namHienTai = lt.tm_year + 1900;
    bool namHopLe = (nam == namHienTai);
    return namHopLe;
}

void xoaCongViec() {
    xemCongViec();
    if (soLuongViec == 0) return;

    cout << "Nhap STT cong viec can xoa (0 de huy): ";
    string dong;
    if (!getline(cin, dong)) return;

    istringstream nhap(dong);
    int stt;
    char kyTuThua;
    if (!(nhap >> stt) || (nhap >> kyTuThua) || stt < 0 || stt > soLuongViec) {
        cout << "STT khong hop le.\n";
        return;
    }
    if (stt == 0) return;

    // Dịch các công việc phía sau sang trái một vị trí.
    for (int i = stt - 1; i < soLuongViec - 1; i++) {
        dsViec[i] = dsViec[i + 1];
        dsViec[i].id = i + 1;
    }
    soLuongViec--;
    dsViec[soLuongViec] = planner{};

    if (luuCongViec()) {
        cout << "Da xoa cong viec.\n";
    } else {
        cout << "Da xoa trong danh sach dang mo, nhung luu tep that bai.\n";
    }
}
