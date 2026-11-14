#pragma once
#include <string>

// Cấu trúc một công việc
struct planner {
    int id;
    std::string viec;
    std::string uuTien;
    bool tick;
};

// Khai báo các hàm
void layTimer();
int giaoDienPlan();
void nhapPlan();
