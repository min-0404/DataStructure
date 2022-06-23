#include "matrixa.h"
#include <iostream>

// 생성자
Matrix::Matrix(int a, int b, int c, int d){
    m[0][1] = a;
    m[0][2] = b;
    m[1][0] = c;
    m[1][1] = d;
}

// 전치행렬 만들기
void Matrix::Transpose(){
    
    for(int i = 0 ; i < 2; i ++){
        // 주대각선 위의 원소만 고려
        int std = (2 - 1) - i;
        for(int j = 0; j < std; j++){
            // temp 이용한 m[i][j] 와 m[j][i] 의 교환 스킬
            int temp = m[i][j]; 
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
    }
}

// 행랼 덧셈
Matrix Matrix::operator+ (const Matrix& a){
    Matrix b; // 더한 값 저정한 뒤 리턴할 객체

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            b.m[i][j] = m[i][j] + a.m[i][j];
        }
    }
    return b;
}

// 행렬 뺄셈
Matrix Matrix::operator- (const Matrix& a){
    Matrix b; // 뺀 값 저정한 뒤 리턴할 객체

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            b.m[i][j] = m[i][j] - a.m[i][j];
        }
    }
    return b;
}

// 행렬 곱셈
Matrix Matrix::operator*(const Matrix& a){
    Matrix b;

    // 행렬의 곱셈 알고리즘 -> 차후에 쉬트라쎈 알고리즘으로 개선법 배울 예정
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                b.m[i][j] = m[i][k] + a.m[k][j];
            }
        }
    }
    return b;
}

// 행렬 동일하게 만들기(대입 연산)
void Matrix::operator= (const Matrix &a){
    
    // 덧셈과 동일
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            m[i][j] = a.m[i][j];
        }
    }
}

// 행렬 출력
void Matrix::ShowMatrix(){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            cout << m[i][j] << " " ;
        cout << endl;
        }
    }
}
