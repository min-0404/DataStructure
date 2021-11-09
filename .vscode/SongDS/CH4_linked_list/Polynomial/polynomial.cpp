#include "polynomial.h"

int main(void)
{
    Polynomial p1, p2, p3;
    Polynomial sum;
    int x;
    Polynomial::Term temp;
    for (int i = 0; i < 5; i++)
    {
        temp.Set(i+1, i+1);
        p1.InsertTerm(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.Set(i + 2, i + 2);
        p2.InsertTerm(temp);
    }
    cout << "p3 다항식 입력" << endl;

    cin >> p3;

        cout << "첫 번째 다항식" << endl << p1 << endl;

        cout << "두 번째 다항식" << endl << p2 << endl;

        cout << "세 번째 다항식" << endl << p3 << endl;

        sum = p1 + p2;

        cout << "첫 번째 두번째 다항식의 합" << endl << sum << endl;

        cout << "세 번째 다항식 계산" << endl;

        cout << "x의 값 입력: ";

        cin >> x;

        cout<< "계산값: "<< p3.Eval(x);

        return 0;

}