#include <iostream>
#include <windows.h>
#include "planner.h"
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
    cout << endl<<"Hom nay:";
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
