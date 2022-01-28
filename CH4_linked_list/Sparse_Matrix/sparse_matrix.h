#include <iostream>
using namespace std;

class Matrix; // 전방 선언

struct Triple
{
    int row;
    int col;
    int val;
};

struct MatrixNode
{
    MatrixNode* down;
    MatrixNode* right;
    bool head;
    union
    {
        MatrixNode* next;
        Triple triple;
    };
    MatrixNode(bool b, Triple* t) // 생성자
    {
        head = b;
        if(b)
            right = down = this;
        else
            triple = *t;
    }
    MatrixNode* next(bool, Triple*); // 멤버함수
};

MatrixNode* av = 0; // available linked list 준비

class Matrix
{
private:
    MatrixNode* headNode;
public:
    Matrix() {}
    ~Matrix()
    {
        if(!headNode)
            return;
        MatrixNode* x = headNode->right;
        headNode->right = av;
        av = headNode;
        while (x != headNode)
        {
            MatrixNode* y = x->right;
            x -> right = av;
            av = y;
            x = x -> next;
        }
    }
    int max(int a, int b)
    {
        if (a > b)
            return a;
        else
            return b;
    }
    friend istream &operator>>(istream &is, Matrix &m);
    friend ostream &operator<<(ostream &os, Matrix &m);
};


istream &operator>>(istream& is, Matrix& matrix)
{
    // 메타 헤더(headNode) 만들어주기
    Triple s;
    is >> s.row >> s.col >> s.val;
    int p = matrix.max(s.row, s.col);
    matrix.headNode = new MatrixNode(false, &s);

    //행이나 열 개수 중 하나라도 0이라면
    if (p == 0) 
    {
        matrix.headNode->right = matrix.headNode;
        return is;
    }

    // 헤더 노드들을 저장하는 배열 만들어주기 
    MatrixNode** head = new MatrixNode*[p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);
        
    int currentRow = 0; // 현재 작업하고 있는 행을 의미함
    MatrixNode* last = head[0]; //일단 last라는 변수는 뭘까? Circular니깐 마지막과 처음노드를 연결시켜주기 위해 쓰는 변수

    // 원소노드 만들어주기
    for(int i = 0; i < s.val; i++)
    {
        Triple t;
        is >> t.row >> t.col >> t.val;
        if(t.row > currentRow) // 현재 작업하고 있는 행이 바뀌면
        {
            last -> right = head[currentRow];
        }
        last = last -> right = new MatrixNode(false, &t); // 입력받은 Triple 정보를 바탕으로 현재 작업하고 있는 행에 새로운 원소 노드 만들어줌

        MatrixNode* cp = head[t.col];
        while(cp -> down != head[t.col])
            cp = cp -> down;
        cp -> down = last;
        last -> down = head[t.col];
    }
    last -> right = head[currentRow];

    //headNode와 head 연결
    for (int i = 0; i < p - 1; i++)
    {
        head[p - 1] -> next = matrix.headNode;
        matrix.headNode -> right = head[0];
        delete[]head;
        return is;
    }

}

ostream &operator<<(ostream &os, Matrix &m)

{
    MatrixNode *headNode = m.headNode->right;
    while (headNode != m.headNode) //원형 리스트이므로 m.headNode에 도달하면 끝
    {
        for (MatrixNode *cur = headNode->right; cur != headNode; cur = cur->right)
        os << "(" << cur->triple.row << ", " << cur->triple.col << ", " << cur->triple.val << ")" << endl;
        headNode = headNode->next;
    }
    return os;
}