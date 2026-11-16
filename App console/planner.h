#pragma once
#include <string>

// Cấu trúc một công việc
struct planner {
    int id;
    std::string viec;
    std::string ngay;      // ngày làm việc, ví dụ "15/11/2026"// mục đích mỗi việc gắn với mỗi ngày cụ thể//
    std::string gioBatDau; // giờ bắt đầu, ví dụ "08:30"
    std::string uuTien;
    bool tick;
};
//Khai bao ham
void typingEffect();
void layTimer();
int giaoDienPlan();
void nhapPlan();
void xemCongViec();      // xem công việc hiện có //
