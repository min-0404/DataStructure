#ifndef AVL_H
#define AVL_H
#include <queue>
#include <iostream>
using namespace std;

struct Node
{
    Node(int d): data(d) {}
    int data;
    Node* rightChild;
    Node* leftChild;
};

class bstree
{
private:
    Node* root; // 루트를 가리키는 포인터
public:
    bstree() 
    {
        root = 0;
    }
    Node* getRoot();
    void visit(Node* ptr); // Showresult의 levelorder순회를 구현하기 위한 추가함수
    void insert(const int value);
    void Showresult(); // 트리를 level order방식으로 순회하면서 출력
    void Search(const int key);
    void del(const int key); // 설명서에 나온 방식대로 구현
};

Node* bstree::getRoot()
{
    return root;
}

void bstree::visit(Node* ptr)
{
	cout << ptr -> data << "\t";
	if (ptr->leftChild)
		cout << "left : " << ptr -> leftChild -> data << '\t';
	else
		cout << "left : empty\t";
	
	if (ptr->rightChild)
		cout << "right : " << ptr->rightChild->data << '\t';
	else
		cout << "right : empty\t";
	cout << endl;
}
void bstree::insert(const int value)
{
    if(root == 0) // 만약 비어있는 노드라면
    {
        root = new Node(value);
        return;
    }
    Node* temp = root;
    while(1)
    {
    if(value > temp -> data)
    {
        if(temp -> rightChild == 0)
        {
            temp -> rightChild = new Node(value);
            break;
        }
        else
            temp = temp -> rightChild;
    }
    else if(value < temp -> data)
    {
        if(temp -> leftChild == 0)
        {
            temp -> leftChild = new Node(value);
            return;
        }
        else
            temp = temp -> leftChild;
    }}
};
void bstree::Showresult()
{
	queue<Node* > q1;
	Node* temp = root;
	while(temp)
	{
		visit(temp);
		if(temp -> leftChild)
			q1.push(temp -> leftChild);
		if(temp -> rightChild)
			q1.push(temp -> rightChild);
		if(q1.empty()) return;
		temp = q1.front();
		q1.pop();
	}
};
void bstree::Search(const int key)
{
    queue<int> q1;
    Node* temp = root;
	while(temp -> data != key)
    {
        q1.push(temp -> data);
        if(key > temp -> data)
            temp = temp -> rightChild;
        else if(key < temp -> data)
            temp = temp -> leftChild;
    }
    q1.push(temp -> data);
    while(!q1.empty())
    {
        cout << q1.front() << "->";
        q1.pop();
    }
    cout << endl;
}
void bstree::del(const int key)
{
    Node* del = root; // del을 삭제할 노드를 가리키게함
    while(1)
    {
        if(key > del -> data)
            del = del -> rightChild;
        else if(key < del -> data)
            del = del -> leftChild;
        else
            break;
    }

    if(!(del -> rightChild) && !(del -> leftChild)) // 첫번째: del 이 말단노드라면: 그대로 삭제
    {
        delete del;
        del = NULL;
    }
    else if(!(del -> leftChild) && del -> rightChild) // 왼쪽 자식이없지만 오른쪽 자식은 있는 경우
    {
        Node* temp = del -> rightChild;
        while(1)
        {
            if(temp -> leftChild -> leftChild == 0)
                break;
            temp = temp -> leftChild;
        }
        del -> data = temp -> leftChild -> data;
        delete temp -> leftChild;
        temp -> leftChild = NULL;
    }
    else if(del -> leftChild)
    {
        Node* temp = del -> leftChild; // 
        while(1)
        {
            if(temp -> rightChild -> rightChild == 0)
                break;
            temp = temp -> rightChild;
        }
        del -> data = temp -> rightChild -> data;
        delete temp -> rightChild;
        temp -> rightChild = NULL;
    }
};

#endif