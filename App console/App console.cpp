#include <iostream>
#include <windows.h>
using namespace std;

int planner();
int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    int Connect;

    cout << "\x1B[1;32m" << R"(
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
---------------------------------------------------------------
1. Tạo 1 Plan cá nhân
    )" << "\x1B[0m" << endl;
    cout << "Nhap chuc nang ban chon: ";
    cin >> Connect;
    switch (Connect) {
    case 1:
        planner();
        break;
    default:
        cout << "Khong ton tai chuc nang";

    }





    return 0;
}


