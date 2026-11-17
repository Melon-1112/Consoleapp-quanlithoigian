#include <iostream>
#include <iomanip>
#include "planner.h"
using namespace std;
void quanlychitieu() {
	system("chcp 65001>>nul");
	char tengiaodich[100][50];
	int soTien[100];
	int loai[100];
	int soluong = 0;
	int chon;
	do {
		cout << "\n============================================================\n";
		cout << "\n                    QUAN LY CHI TIEU                        \n";
		cout << "\n============================================================\n";
		cout << "\n                1.them khoan thu chi                        \n";
		cout << "\n                2. xem danh sach chi tieu:                  \n";
		cout << "\n                0.thoat:                                    \n";
		cout << "\n                chon chuc nang (0-2):                       \n";
		cout << "\n============================================================\n";
		cin >> chon;
		cin.ignore();
		if (chon == 1) {
			if (soluong >= 100) {
				cout << "\n ===================== DANH SACH DA DAY ===================\n";
				continue;
			}
			cout << "\n===================== NHAP TEN KHOAN TIEN (CHI;THU) ====================\n";
			// nhap chuoi co khoang trang
			cin.getline(tengiaodich[soluong], 50);
			// them kiem tra loai thu chi o day	
			cout << "==================== NHAP SO TIEN ====================\n";
			cin >> soTien[soluong];
			cout << "phan loai(1.thu;2.chi):";
			cin >> loai[soluong];
			// xoa bo nho dem 
			cin.ignore();
			// tang so luong len 1
			soluong++;
			cout << "==================== da them thanh cong ====================!\n";
		}
		else if (chon == 2) {
			int tongthu = 0;
			int tongchi = 0;
			cout << "\n ===================== DANH SACH GIAO DICH ===================\n";
			cout << left
				<< setw(6) << "stt"
				<< setw(20) << "ten giao dich"
				<< setw(10) << "loai"
				<< setw(10) << "so tien" << endl;
			cout << "------------------------------------------------\n";
			for (int i = 0; i < soluong;i++) {
				cout<<left
					<< setw(6) << i + 1
					<< setw(20) << tengiaodich[i]
					<< setw(10) << (loai[i] == 1 ? "thu" : "chi")
					<< setw(10) << soTien[i] <<"VND" << endl;
				if (loai[i] == 1) {
					tongthu += soTien[i];
				}
				else {
					tongchi += soTien[i];
				}
			}
			cout << " \n";
			cout << "tong thu : " << tongthu << "VND\n";
			cout << "tong chi : " << tongchi << "VND\n";
			cout << "con lai :" << (tongthu - tongchi) << "VND\n";
		}
	} while (chon != 0);
}