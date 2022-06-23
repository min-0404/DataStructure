#include <iostream>
using namespace std;

// 전방 선언 해줘야 CPoint 클래스안에서 << 연산자의 friend 선언을 인식할 수 있음
template <typename T>
class CPoint;
template <typename T>
std::ostream& operator<<(std::ostream&, const CPoint<T>&);

template <typename T>
class CPoint{
    private:
        T xpos;
        T ypos;
    public:
        friend std::ostream& operator<< <T>(std::ostream&, const CPoint<T>&); // friend 선언해줘야 접근 가능
        CPoint(T x, T y): xpos(x), ypos(y) {}
        void Move(T a, T b);
};

// 연산자 오버로딩
template  <typename T >
std::ostream& operator<<(std::ostream& os, const CPoint <T >& c){
    os << "(" << c.xpos << "," << c.ypos << ")" << endl ;
    return os ;
}

template <typename T>
void CPoint<T>::Move(T a ,T b ){
    xpos += a;
    ypos += b;
}

int main() {
    CPoint<int> P1(1, 11);
    CPoint<double> P2(1.1, 2.2);

    P1.Move(8,13);
    P2.Move(8.97,20.39);
    cout << P1 << P2;
}