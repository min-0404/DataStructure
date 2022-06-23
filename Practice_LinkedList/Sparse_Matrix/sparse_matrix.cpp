#include "sparse_matrix.h"

int main(void)
{
    Matrix m;
    cin >> m;
    
    cout << endl << "희소행렬 출력" << endl;
    cout << "(행, 열, 값)" << endl;
    cout << m;

    return 0;
}