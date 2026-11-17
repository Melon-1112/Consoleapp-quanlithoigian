#pragma once
#pragma once
#include <string>
#include <vector>

struct UserProfile {
    std::string ten;
    std::string gioiTinh;
    int tuoi;
    double  chieuCao;
    double canNang;
};
struct WorkoutSession {
    std::string tenBaiTap;
    int soHiep;
    int soLan;        // số lần mỗi hiệp
    int thoiGianTap;  // phút
    int caloriesRa;
};

struct MealEntry {
    std::string tenMon;
    std::string buaAn;   // sáng / trưa / tối / phụ
    int caloriesVao;
    double khoiLuong;
};
struct DailyCalories {
    std::string date;       // định dạng YYYY-MM-DD để dễ sắp xếp, so sánh
    std::vector<WorkoutSession> baiTap;
    std::vector<MealEntry> buaAn;
};
void giaoDienHeal();
int tongCaloRa(const std::vector<WorkoutSession>& ds);
int tongCaloVao(const std::vector<MealEntry>& ds);
void nhapBaiTap(WorkoutSession& bt);
void nhapBuaAn(MealEntry& ba);
void danhSachBaiTap(const std::vector<WorkoutSession>& ds);
void danhSachBuaAn(const std::vector<MealEntry>& ds);
void deXuatPhuongAn(int caloNap, int caloTieu);
void quanlychitieu();    // quản lý chi tiêu //
