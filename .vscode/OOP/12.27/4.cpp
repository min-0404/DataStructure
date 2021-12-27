#include <iostream>
using namespace std;

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    int a = 1;
    int b = 2;
    swap(a, b); // iostream 클래스에 이미 swap함수 정의되어 있어서 굳이 주소 넣지 않아도 변경 가능
    //swap(&a, &b);
    cout << a << " " << b << endl;
    return 0;
}