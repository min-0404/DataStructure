#include <iostream>
using namespace std;

int main()
{
    int score;
    cout << "점수입력:";
    cin >> score;
    int div = score /10; // div는 꼭 정수이어야만 한다!!!(swithc문의 규칙)
    switch(div){
        case 10: // break 없음
        case 9:
            cout << "A학점입니다";
            break;
        case 8:
            cout << "B학점입니다";
            break;
        case 7:
            cout << "C학점입니다";
            break;
        case 6:
            cout << "F학점입니다";
            break;
    }
    
}

