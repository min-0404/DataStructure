#include <iostream>
using namespace std;

struct Node{
    int data; // 노드 값
    Node* link; //다음 노드 가리키는 포인터
    Node(int d = 0, Node* l = NULL) : data(d), link(l) { } // 생성자
};

struct IntList{
    IntList() { last = first = NULL; }
    void Push_Back(int); // 리스트 뒤에 삽입 중복 허용
    void Push_Front(int); // 리스트 앞에 삽입 중복 허용
    void Insert(int); // 정렬되어 있다는 가정 하에 제 위치에 삽입
    void Delete(int); // 리스트의 원소 삭제
    Node *first; // 첫 노드를 가리킴
    Node *last; // 마지막 노드를 가리킴
};
// ostream& operator<<(ostream& os, IntList& il);



