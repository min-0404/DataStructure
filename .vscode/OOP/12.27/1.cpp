#include <iostream>
using namespace std;

int g = 20; // 전역 변수
int add(int x, int y)
{
    return x + y;
}

int main()
{
    int a, b, sum;
    cout << "두 정수를 입력하세요";
    cin >> a >> b;
    sum = a + b;
    cout << "합은" << sum << endl;
    return 0;
}


