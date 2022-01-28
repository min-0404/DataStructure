#include <iostream>
#include <fstream>
using namespace std;

class ENode
{
private:
    int data;
    ENode* link;
    ENode* link2; //link와 똑같은 역할을 하는 link2
    //link2가 없을 경우 동적할당한 메모리를 반환할 때 문제가 생긴다(몇몇 데이터들이 제거되지 않는다)
public:
    ENode(int d = 0)
    {
        data = d;
        link = 0;
    }
    friend void Equivalence();
};

void Equivalence() 
{
    ifstream inFile("equiv.txt", ios::in);
    if (!inFile)
    {
        cout << "파일을 열 수 없습니다" << endl;
        return;
    }
    int i, j, n;
    inFile >> n;
    
    ENode** first = new ENode*[n]; // first 배열을 위한 동적 할당(n개의 ENode포인터 변수를 저장할 수 있는 공간 )
    bool* out = new bool[n]; //out 배열을 위한 동적 할당(n개의 불린 값을 저장할 수 있는 공간)
    for (i = 0; i < n; i++) //first배열은 0으로 초기화, out배열은 false로 초기화
    {
        first[i] = 0;
        out[i] = false;
    }


    while (inFile.good()) //파일 끝이 아닐 때까지
    {
        inFile >> i >> j;
        ENode* x = new ENode(j); //first[i]에 j 추가
        x->link = first[i];
        x->link2 = first[i]; //복사해놓는다
        first[i] = x;
        
        ENode* y = new ENode(i); //first[j]에 i 추가
        y->link = first[j];
        y->link2 = first[j]; //복사해놓는다
        first[j] = y;
    }
    
    for (i = 0; i < n; i++)
    {
        if (out[i] == false)
        {
            cout << endl << "새로운 클래스: " << i;
            out[i] = true; //true 로 바꿔줌
            ENode* x = first[i];
            ENode* top = 0; //스택 초기화
            while (1) //같은 클래스에 있는 노드들을 찾는다
            {
                while (x) //x가 0일 때까지
                {
                    j = x->data;
                    if (out[j] == false)
                    {
                        cout << ", " << j;
                        out[j] = true;
                        ENode* y = x->link;
                        x->link = top;
                        top = x;
                        x = y;
                    }
                    else
                        x = x->link;
                }
                if (!top)
                    break; //스택이 비었을 경우 빠져나온다
                else
                {
                    x = first[top->data];
                    top = top->link;
                }
            }
        }
    }
    cout << endl;
    cout << endl << "동적할당한 first[i] 반환 " << endl;
    for (i = 0; i < n; i++)
    {
        while (first[i])
        {
            if (first[i]->data<0) //data가 존재하지 않을 때 빠져나온다
            {

                              cout << "0";

                              break;

                       }

                       cout << first[i]->data;

                       ENode *delNode = first[i];

                       first[i] = delNode->link2;

                       if (first[i])

                              cout << " -> ";

                       delete delNode;

               }

               cout << endl;

        }

        delete[]first;

        delete[]out;

}

