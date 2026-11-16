#include <iostream>
#include <limits>
#include <windows.h>
#include "planner.h"
#include "healer.h"
using namespace std;

void typingEffect(string text) {
    for (int i = 0; i < text.length(); i++) {
        cout << text[i];
        cout.flush();
        Sleep(100);
    }

}

int main()
{
    
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    int Connect;

    cout << "\x1B[1;32m" << R"ART(
//            ,----,                                        
//          ,/   .`|                                         ,----, 
//        ,`   .'  :                  ____                 .'   .`| 
//      ;    ;     / ,--,           ,'  , `.            .'   .'   ; 
//    .'___,/    ,',--.'|        ,-+-,.' _ |          ,---, '    .' 
//    |    :     | |  |,      ,-+-. ;   , ||          |   :     ./  
//    ;    |.';  ; `--'_     ,--.'|'   |  || ,---.    ;   | .'  /   
//    `----'  |  | ,' ,'|   |   |  ,', |  |,/     \   `---' /  ;    
//        '   :  ; '  | |   |   | /  | |--'/    /  |    /  ;  /     
//        |   |  ' |  | :   |   : |  | ,  .    ' / |   ;  /  /--,   
//        '   :  | '  : |__ |   : |  |/   '   ;   /|  /  /  / .`|   
//        ;   |.'  |  | '.'||   | |`-'    '   |  / |./__;       :   
//        '---'    ;  :    ;|   ;/        |   :    ||   :     .'    
//                 |  ,   / '---'          \   \  / ;   |  .'       
//                  ---`-'                  `----'  `---'           
//                                                                  

    )ART" << "\x1B[0m\n";
    typingEffect("Welcome to TimeZ - Dong hanh giup ban quan li ca nhan hieu qua");
    // Hien thi ngay gio hien tai
    cout << endl <<"Hom nay:";
    layTimer();
    cout << "\n";
    bool chay = true; //thêm vòng lặp, fix lỗi thêm công việc xong -> kết thúc chương trình//
    while (chay)
    {
        //system("cls");
        cout << "\x1B[1;32m---------------------------------------------------------------\n"
            << " 1. Tạo 1 Plan cá nhân" << endl
            << " 2. Xem danh sách công việc" << endl
            << " 3. Đến quản lí calories " << endl
            << " 0. Thoát \n\x1B[0m\n "<< endl;

        cout << "Nhap chuc nang ban chon: ";
        cin >> Connect;
        cin.ignore(1000, '\n'); //giống numeric_limits, nhưng cái này không bị xung đột với windows.h =)))//
        switch (Connect) {
        case 1:
            system("cls");
            nhapPlan(); //hàm thêm công việc
            break;
        case 2:
            xemCongViec();   //xem danh sách
            break;
        case 3:
            giaoDienHeal();
            break;
        case 0:
            chay = false;
            break;
        default:
            cout << "Khong ton tai chuc nang\n";
        }

        if (chay) {
            cout << "\nNhan Enter de tiep tuc...";
            system("pause > nul");   // pause tự đọc Enter, không cần ignore
        }

    }
    return 0;
}
