#include <iostream>
using namespace std;

template <typename T>
T add(T x, T y){
    return x + y;
}

int main(){
    int intX = 1;
    int intY = 2;

    double dbX = 3.3;
    double dbY = 4.4;

    float fX = 09.24;
    float fY = 10.07;

    cout << add(intX, intY) << endl;
    cout << add(dbX, dbY) << endl;
    cout << add(fX, fY) << endl;
}