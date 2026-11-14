#include <iostream>
#include <windows.h>
#include "planner.h"
using namespace std;

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

Welcome to TimeZ - Đồng hành giúp bạn quản lí cá nhân hiệu quả
    )ART" << "\x1B[0m\n";

    // Hien thi ngay gio hien tai
    cout << "Hom nay:";
    layTimer();
    cout << "\n";

    cout << "\x1B[1;32m---------------------------------------------------------------\n"
         << "1. Tạo 1 Plan cá nhân\n\x1B[0m\n";
    cout << "Nhap chuc nang ban chon: ";
    cin >> Connect;
    switch (Connect) {
    case 1:
        system("cls");
        giaoDienPlan();
        
        break;
    default:
        cout << "Khong ton tai chuc nang\n";
    }

    return 0;
}
