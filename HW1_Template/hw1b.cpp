#include <iostream>
using namespace std;

template <typename T>
class CPoint{
    private:
        T xpos;
        T ypos;
    public:
        CPoint(T x, T y): xpos(x), ypos(y) {}
        void Move(T a, T b);
        void Print();
};

template <typename T>
void CPoint<T>::Move(T a, T b){
    xpos += a;
    ypos += b;
}

template <typename T>
void CPoint<T>::Print(){
    cout << "(" << xpos << "," << ypos << ")" << endl;
}


int main(){
    CPoint<int> P1(1,2);
    CPoint<double> P2(1.1, 2.2);
    
    P1.Move(2,3);
    P2.Move(2.2, 3.3);
    
    P1.Print();
    P2.Print();
}