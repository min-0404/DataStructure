#include <iostream>
using namespace std;
class DblList; //전방선언

class DblListNode
{
private:
    int data;
    DblListNode *left, *right;
public:
    DblListNode(int element = 0, DblListNode *lNode = NULL, DblListNode *rNode = NULL) :data(element), left(lNode), right(rNode)
    {}
    friend class DblList;
    friend ostream &operator<<(ostream &os, DblList &d);
};

class DblList
{
private:
    DblListNode *first;
public:
    DblList() //생성자: 더미노드(first) 만들어놓는 것이 포인트
    {
        first = new DblListNode; //더미노드
        first->left = first;
        first->right = first;
    }
    ~DblList() //소멸자 : 더미노드 부터 시작해서 쭉 돌면서 노드들 삭제
    {
        DblListNode *delNode = first; //위치를 기억해두어야한다
        DblListNode *delNextNode = first->right;
        while (1)
        {
            if (delNextNode -> data >= 0) //dummynode의 데이터 0, 그 외 양수
            {
                delete delNode;
                delNode = delNextNode;
                delNextNode = delNextNode->right;
            }
            else
            {
                delete delNode;
                break;

            }
        }
    }
    void Insert(DblListNode* p, DblListNode* x = NULL) //x노드 "오른쪽"에 p노드 삽입
    {
        if (x == NULL) //x가 입력되지 않은 경우 -> first의 왼쪽에 삽입해주자
        {
            p->left = first->left;
            p->right = first;
            first->left->right = p;
            first->left = p;
        }
        else
        {
            p -> left = x;
            p -> right = x -> right;
            x -> right -> left = p;
            x -> right = p;

        }

    }
    void Delete(DblListNode *x)
    {
        if (x == first)
            cout << "더미노드 삭제 불가" << endl;
        else
        {
            x->left->right = x->right;
            x->right->left = x->left;
            delete x;
        }
    }
    friend ostream &operator<<(ostream &os, DblList &d);
};

 
ostream &operator<<(ostream &os, DblList &d)
{
    os << "오른쪽 진행" << endl;
    DblListNode *temp1 = d.first, *temp2 = d.first; //first의 위치 저장
    os << "dummy->";
    while (temp1->right->data!=0)
    {
        os << temp1->right->data;
        if (temp1->right->right->data!=0)
            os << "->";
        else
            os << " ";
        temp1 = temp1->right;
    }
    os << endl << "왼쪽 진행" << endl;
    os << "dummy->";
    while (temp2->left->data != 0)
    {
        os << temp2->left->data;
        if (temp2->left->left->data != 0)
            os << "->";
        else
            os << " ";
        temp2 = temp2->left;
    }
    return os;
}

int main(void)
{

        DblList d;

        DblListNode *temp1 = new DblListNode(1);

        DblListNode *temp2 = new DblListNode(2);

        DblListNode *temp3 = new DblListNode(3);

        DblListNode *temp4 = new DblListNode(4);

 

        d.Insert(temp1);

        d.Insert(temp2);

        d.Insert(temp3);

        d.Insert(temp4, temp3);

 

        cout << "더블 링크드리스트 출력" << endl;

        cout << d << endl;

 

        d.Delete(temp1);

 

        cout << "더블 링크드리스트 출력" << endl;

        cout << d << endl;

 

        return 0;

}



