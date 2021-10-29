#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* link;
    Node(int d = 0, Node* l = NULL) : data(d), link(l)
    { }
};

struct IntList
{
    Node *first; // 첫 노드를 가리킴
    Node *last; // 마지막 노드를 가리킴
    IntList()
    { last = first = NULL; }
    void Push_Back(int);// 리스트 뒤에 삽입 중복 허용
    

void IntList::Push_Back(int e) {
 if (!first)
 first = last = new Node(e);
 else {
 last->link = new Node(e);
 last = last->link;
 }
}
    void Push_Front(int); // 리스트 앞에 삽입 중복 허용
    void Insert(int e) // 정렬되어 있다는 가정 하에 제 위치에 삽입
    {
        Node* temp = first;
        if(!first)
        {
            while(temp -> data < e)
            {
                temp = temp -> link;
            }
            temp -> link = new Node(e, temp -> link);
        }
        else
        {
            first = new Node(e);
        }
    }
    void Delete(int e) // 리스트의 원소 삭제
    {
        Node* temp1 = first;
        Node* temp2 = first;
        while(1) //temp1을 삭제할 노드로 만들어줌
        {
            temp1 = temp1 -> link;
            if(temp1 -> data == e)
                break;
        }
        while(temp2 -> data < e) //temp2를 삭제할 이전 노드로 만들어줌
        {
            temp2 = temp2 -> link;
        }
        if(first)
        {
           temp2 -> link = temp1 -> link;
           delete temp1; 
        }
        else 
        {
            delete first;
        }
    }
};

ostream& operator<<(ostream& os, IntList& il)
{
    Node *ptr = il.first;
    while (ptr != NULL)
    {
        os << ptr->data << " ";
        ptr = ptr->link;
    }
    os << endl;
    return os;
}

