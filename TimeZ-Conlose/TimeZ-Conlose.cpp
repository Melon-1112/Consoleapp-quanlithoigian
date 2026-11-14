#include <iostream>
using namespace std;

int main()
{
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

Welcome to TimeZ - Noi giup ban quan li cuoc song de dang hon
1. Cai dat thoi khoa bieu trong ngay
    )" << "\x1B[0m" << endl;
    cout << "Nhap chuc nang ban chon: ";
    cin >> Connect;
    switch (Connect) {
    case 1:
        system("code -r Thoikhoabieu.cpp");
        break;

    }





    return 0;
}


