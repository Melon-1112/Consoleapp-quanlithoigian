#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
using namespace std;
//FUCKING AI AGENT
//SUY NGHI CODE THUC HIEN NHU THE NAO TRUOC KHI RUN!
void layTimer() {
    string ngay, gio;
    while (true) {
        time_t tgian = time(nullptr);
        tm localTime{};
        localtime_s(&localTime, &tgian);
        cout << put_time(&localTime, "%d/%m/%Y") << endl;
        //cin >> ;


        //cout << "Ngay hom nay: "<< put_time(&localTime, "%d/%m/%Y" ) << endl;
        //cout<< "Thoi gian: "<< put_time(&localTime ,"%H:%M")<< endl;

    }

}

//Giao dien chinh
int hehe() {

    return 0;


}
