#include <iostream>
using namespace std;

class Matrix; // 전방 선언

struct Triple
{
    int row;
    int col;
    int val;
};

class MatrixNode
{
private:
    MatrixNode* right; //행
    MatrixNode* down; //열
    bool isHead; // 불린 값으로 해당 노드가 원소노드인지, 헤더노드 인지 파악
    union
    {
        MatrixNode* next;
        Triple triple;
    };
public:
    MatrixNode() //디폴트 생성자
    {}
    MatrixNode(bool b, Triple* t) // 원소노드 및 매트릭스 헤더노드 생성자
    {
        isHead = b;
        if (isHead)
            right = down = next = this;
        else
            triple = *t;
    }
    friend class Matrix;
    friend istream &operator>>(istream &is, Matrix &m);
    friend ostream &operator<<(ostream &os, Matrix &m);
};
MatrixNode *av = 0; //~Matrix를 위한

class Matrix
{
private:
    MatrixNode* headNode;
public:
    Matrix() //디폴트 생성자
    {}
    ~Matrix()
    {
        if(!headNode)
            return;
        MatrixNode* x = headNode->right;
        headNode->right = av;
        av = headNode;
        while (x != headNode)
        {
            MatrixNode *y = x->right;
            x->right = av;
            av = y;
            x = x->next;
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
    Triple s;
    int count = 1;
    cout << "행, 열, 0이 아닌 항 개수" << endl; //매트릭스 헤더노드 만들어주기
    is >> s.row >> s.col >> s.val;
    
    int p = matrix.max(s.row, s.col); //행개수와 열개수 중 큰 값으로 헤더노드 개수 결정
    matrix.headNode = new MatrixNode(false, &s);

    if (p == 0) //행이나 열 개수 중 하나라도 0이라면
    {
        matrix.headNode->right = matrix.headNode;
            return is;
    }

    MatrixNode** head = new MatrixNode*[p]; //max(col, row)만큼 배열 생성
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);
        
    int currentRow = 0;
    MatrixNode *last = head[0]; //해당 열 중 마지막 노드

    for (int i = 0; i < s.val; i++) //triple 입력
    {
        Triple t;
        cout << count++ << "번째 행, 열, 원소 입력";
        is >> t.row >> t.col >> t.val;
        if (t.row > currentRow) //해당 열 끝
        {
            last->right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }
        last = last->right = new MatrixNode(false, &t); //새로운 노드 행에 추가
        head[t.col]->next = head[t.col]->next->down = last; //새로운 노드 열에 추가
    }
    
    last->right = head[currentRow]; //마지막 행 종료
    for (int i = 0; i < s.col; i++)
        head[i]->next->down = head[i]; //마지막 열 종료

    //headNode와 head 연결
    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1]; //head끼리 연결

        head[p - 1]->next = matrix.headNode;

        matrix.headNode->right = head[0];

        delete[]head;

        return is;

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