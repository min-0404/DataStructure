#ifndef MAT RIX_H
#define MAT RIX_H
#include <iostream>
using namespace std;

class Matrix{
    public:
        Matrix(int a= 0, int b= 0, int c= 0, int d= 0);
        ~Matrix() {}
        void ShowMatrix();
        void Transpose();
        Matrix operator+ (const Matrix& a);
        Matrix operator- (const Matrix& a);
        Matrix operator*(const Matrix& a);
        void operator= (const Matrix& a);
    private:
        int m[2][2];
};

#endif