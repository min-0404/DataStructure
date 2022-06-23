#include "maxheap.h"
#include <fstream>

int main(int argc, char** argv)
{
    int N, data;
    MaxHeap<int> H;

    if(argc != 2)
    {
        cerr << "wrong argument count"<< endl;
        return 1;  
    }

    fstream fin(argv[1]);  // fstream 의 객체 fin 선언하고, argv[1]값 저장해줌

    if(! fin) // 만약 fin 이 0 이면
    {
        cerr << argv[1] << "open failed" << endl;
        return 1;
    }

    fin >> N; // fin의 값을 N에 넣어줌
    for(int i = 0;  i< N; i ++)
    {
        fin >> data; // fin의 값을 차례대로 data에 넣어줌
        H.Push(data); // data의 값을 객체 H에 넣어줌
    }

    cout << H;

    while(! H.IsEmpty() ) //H가 텅 빌때까지
    {
        cout << H.Top(); // 값을 출력해줌
        H.Pop();
    }

    cout << endl;

    fin.close();
    
    return 0;
}