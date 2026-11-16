#include<iostream>
#include<string>
#include"healer.h"
#include<iomanip>
#include<limits>
#include<vector>
using namespace std;
vector<WorkoutSession> danhSachBai;
vector<MealEntry> danhSachMon;
void giaoDienHeal() {
    int nhapNut;
    while (true) {
        system("cls"); // Xóa màn hình mỗi lần lặp lại để cập nhật giờ mới

        // In tiêu đề kèm ngày giờ kế bên
        cout << "============ CALORIES MANAGER =========== ";
        cout << "\n"
            << "[1] Them bai tap hang ngay\n"
            << "[2] Them bua an hang ngay\n"
            << "[3] Danh sach bai tap hang ngay\n"
            << "[4] Danh sach bua an hang ngay\n"
            << "[5] De xuat phuong an\n"
            << "[0] Thoat\n";
        cout << "Chon chuc nang: ";
        cin >> nhapNut;
        cin.ignore();
        switch (nhapNut)
        {
        case 0:
            return;
        case 1:
        {
            WorkoutSession bt;
            nhapBaiTap(bt);
            danhSachBai.push_back(bt); // Thêm vào cuối  danh sách
            break;
        }
        case 2:
        {
            MealEntry ba;
            nhapBuaAn(ba);
            danhSachMon.push_back(ba); // Thêm vào cuối  danh sách
            break;
        }
        case 3:
            danhSachBaiTap(danhSachBai);
            break;
        case 4:
            danhSachBuaAn(danhSachMon);
            break;
        case 5:
        {
            int caloNap = tongCaloVao(danhSachMon);
            int caloTieu = tongCaloRa(danhSachBai);
            deXuatPhuongAn(caloNap, caloTieu);
            break;
        }
        default:
            cout << "Khong co trong chuong trình";
        }
        cout << "\nNhan Enter de tiep tuc...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
        cin.get(); // Chờ người dùng nhấn Enter
    }
}
int tongCaloRa(const vector<WorkoutSession>& ds) {
    int tong = 0;
    for (const auto& baiTap : ds) { // Duyệt qua từng phần tử trong vector
        tong += baiTap.caloriesRa;
    }
    return tong;
}

int tongCaloVao(const vector<MealEntry>& ds) {
    int tong = 0;
    for (const auto& monAn : ds) {
        tong += monAn.caloriesVao;
    }
    return tong;
}
void nhapBaiTap(WorkoutSession& bt) {
    cout << "\n===== NHAP BAI TAP =====\n";
    cout << "Ten bai tap: ";
    getline(cin, bt.tenBaiTap);
    do {
        cout << "So hiep: ";
        cin >> bt.soHiep;
    } while (bt.soHiep <= 0);
    do {
        cout << "So lan moi hiep: ";
        cin >> bt.soLan;
    } while (bt.soLan <= 0);
    do {
        cout << "Thoi gian tap (phut): ";
        cin >> bt.thoiGianTap;
    } while (bt.thoiGianTap <= 0);
    do {
        cout << "Calories tieu hao: ";
        cin >> bt.caloriesRa;
    } while (bt.caloriesRa < 0);
}
void nhapBuaAn(MealEntry& ba) {
    cout << "\n===== NHAP BUA AN =====\n";
    cout << "Ten mon an: ";
    getline(cin, ba.tenMon);
    do {
        cout << "Calories nap vao: ";
        cin >> ba.caloriesVao;
    } while (ba.caloriesVao < 0);

    do {
        cout << "Khoi luong (gram): ";
        cin >> ba.khoiLuong;
    } while (ba.khoiLuong <= 0);
}
void danhSachBaiTap(const vector<WorkoutSession>& ds) {
    if (ds.empty()) {
        cout << "Danh sach trong.\n";
        return;
    }
    cout << "   \n===== DANH SACH BAI TAP =====\n";
    cout << left << setw(5) << "STT"
        << setw(25) << "Ten bai tap"
        << setw(8) << "Hiep"
        << setw(8) << "Lan"
        << setw(12) << "Thoi gian"
        << setw(10) << "Calories" << endl;
    int tongPhut = 0, tongCalo = 0;
    for (size_t i = 0; i < ds.size(); i++) {
        cout << left << setw(5) << i + 1
            << setw(25) << ds[i].tenBaiTap
            << setw(8) << ds[i].soHiep
            << setw(8) << ds[i].soLan
            << setw(12) << ds[i].thoiGianTap
            << setw(10) << ds[i].caloriesRa << endl;
        tongPhut += ds[i].thoiGianTap;
        tongCalo += ds[i].caloriesRa;
    }
    cout << "Tong thoi gian: " << tongPhut << " phut\n";
    cout << "Tong calories tieu hao: " << tongCalo << endl;
}
void danhSachBuaAn(const vector<MealEntry >& ds) {
    if (ds.empty()) {
        cout << "Danh sach trong.\n";
        return;
    }
    cout << "\n===== DANH SACH BUA AN =====\n";
    cout << left << setw(5) << "STT"
        << setw(25) << "Ten mon"
        << setw(15) << "Khoi luong(g)"
        << setw(10) << "Calories" << endl;

    int tongCalo = 0;
    double tongKhoiLuong = 0;
    for (size_t i = 0; i < ds.size(); i++) {
        cout << left << setw(5) << i + 1
            << setw(25) << ds[i].tenMon
            << setw(15) << ds[i].khoiLuong
            << setw(10) << ds[i].caloriesVao << endl;
        tongCalo += ds[i].caloriesVao;
        tongKhoiLuong += ds[i].khoiLuong;
    }
    cout << "Tong khoi luong: " << tongKhoiLuong << " g\n";
    cout << "Tong calories nap vao: " << tongCalo << endl;
}
void deXuatPhuongAn(int caloNap, int caloTieu)
{
    int luaChon;
    int chenhLech = caloNap - caloTieu;
    cout << "\n DE XUAT PHUONG AN \n";
    cout << "1. Tang can\n";
    cout << "2. Giam can\n";
    cout << "3. Giu nguyen\n";
    cout << "Chon muc tieu: ";
    cin >> luaChon;
    switch (luaChon)
    {
    case 1:
        cout << "\nMUC TIEU: TANG CAN\n";

        if (chenhLech < 0)
        {
            cout << "Calo nap vao dang thap hon nhu cau uoc tinh.\n";
            cout << "Can xem lai viec an uong va bo sung dinh duong.\n";
        }
        else if (chenhLech == 0)
        {
            cout << "Calo nap vao dang bang nhu cau uoc tinh.\n";
        }
        else
        {
            cout << "Calo nap vao dang cao hon nhu cau uoc tinh.\n";
        }
        break;

    case 2:
        cout << "\nMUC TIEU: GIAM CAN\n";

        if (chenhLech > 0)
        {
            cout << "Calo nap vao dang cao hon nhu cau uoc tinh.\n";
            cout << "Nen xem lai chat luong va su can bang bua an.\n";
        }
        else if (chenhLech == 0)
        {
            cout << "Calo nap vao dang bang nhu cau uoc tinh.\n";
        }
        else
        {
            cout << "Calo nap vao dang thap hon nhu cau uoc tinh.\n";
        }
        cout << "Khong tu y cat giam calo hoac bo bua.\n";
        break;

    case 3:
        cout << "\nMUC TIEU: GIU NGUYEN\n";

        cout << "Chenh lech calo: " << chenhLech << endl;
        cout << "Duy tri an uong day du va van dong phu hop.\n";
        break;
    default:
        cout << "Lua chon khong hop le!\n";
        break;
    }
}