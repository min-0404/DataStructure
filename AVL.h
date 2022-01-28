#ifndef AVL_H
#define AVL_H
typedef struct Node* nodeptr;
#include <queue>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

struct Node
{
    int data;
    Node* rightChild;
    Node* leftChild;
    int BF; //balance facor
    Node(int d): data(d)
    {
        BF = 0;
        rightChild = 0;
        leftChild = 0;
    }
};

class bstree
{
public:
    bstree() {}
    void visit(Node* ptr); // Showresult함수의 levelorder순회를 구현하기 위한 추가함수
    void Showresult(Node* root); // level order 순회 구현
    void Search(const int key, Node* root);
    void insert(const int value, Node*& root);
    void del(const int key, Node* root); // 설명서에 나온 방식대로 구현
    void LLrotation(Node* start, Node* end);
    void RRrotation(Node* root, Node* start, Node* end);
    void LRrotation(Node* root, Node* start, Node* end);
    void RLrotation(Node* root, Node* start, Node* end);
    int getHeight(Node* root);
    Node* setBF(Node* root);
    void rotation(Node* root);
    Node* WrongNode(Node* root);
    bool IsWrongNode(Node* root);
};

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
void bstree::Showresult(Node* root)
{
	queue<Node* > q1;
    Node* currentNode = root;
	while(currentNode)
	{
		visit(currentNode);
		if(currentNode -> leftChild)
			q1.push(currentNode -> leftChild);
		if(currentNode -> rightChild)
			q1.push(currentNode -> rightChild);
		if(q1.empty()) return;
		currentNode = q1.front();
		q1.pop();
	}
};

void bstree::Search(const int key, Node* root)
{
    queue<int> q1;
	while(root -> data != key)
    {
        q1.push(root -> data);
        if(key > root -> data)
            root = root -> rightChild;
        else if(key < root -> data)
            root = root -> leftChild;
    }
    q1.push(root -> data);
    while(!q1.empty())
    {
        cout << q1.front() << "->";
        q1.pop();
    }
    cout << endl;
}
void bstree::insert(const int value, Node*& root)
{
    if(!root) // 비어있는 트리일 때
        root = new Node(value);
    else if(value < root -> data) // 삽입할 값이 작다면 왼쪽으로
    {
        insert(value, root -> leftChild);
    }
    else if(value > root -> data) // 삽입할 값이 크다면 오른쪽으로
    {
        insert(value, root -> rightChild);
    }
    else // 현재 노드의 값과 동일하다면
        root -> data = value;
};
void bstree::rotation(Node* root)
{
    Node* temp;
    setBF(root);
    if(IsWrongNode(root))
    {
        temp = WrongNode(root);
        if(temp -> BF > 1) //왼쪽 서브트리가 더 높을때 : 일단 L회전임
        {
            if(getHeight(temp -> leftChild -> leftChild) > getHeight(temp -> leftChild-> rightChild))
                LLrotation(temp, temp -> leftChild);
            else
                LRrotation(root, temp, temp -> leftChild);
        }
        else if(temp -> BF < -1) //오른쪽 서브트리가 더 높을때: 일단 R회전임
        {
            if(getHeight(temp -> rightChild -> leftChild) < getHeight(temp -> rightChild -> rightChild))
                RRrotation(root, temp, temp -> rightChild);
            else
                RLrotation(root, temp, temp -> rightChild);
        }
    }

}
void bstree::del(const int key, Node* root)
{};
int bstree::getHeight(Node* root) //높이 반환
{
    int height = 0;
    if (root)
    {
        int leftHeight = getHeight(root -> leftChild);
        int rightHeight = getHeight(root -> rightChild);
        int result = max(leftHeight, rightHeight);
        height = result + 1;
    }
    return height;
}
Node* bstree::setBF(Node* root) // levelorder 순회하면서 각 노드의 bf를 일일히 지정해줌
{
	queue<Node* > q1; // 트리의 모든 노드들을 저장할 큐
    Node* currentNode = root;
	while(currentNode) 
	{
        int leftHeight = getHeight(currentNode -> leftChild);
        int rightHeight = getHeight(currentNode -> rightChild);
        currentNode -> BF = leftHeight - rightHeight;
		if(currentNode -> leftChild)
			q1.push(currentNode -> leftChild);
		if(currentNode -> rightChild)
			q1.push(currentNode -> rightChild);
		if(q1.empty()) break;
        currentNode = q1.front();
        q1.pop();
    }
}
bool bstree::IsWrongNode(Node* root)
{
	queue<Node* > q1;
    Node* currentNode = root;
	while(currentNode) 
	{
        if(currentNode -> BF > 1 || currentNode -> BF < -1)
            return true;
		if(currentNode -> leftChild)
			q1.push(currentNode -> leftChild);
		if(currentNode -> rightChild)
			q1.push(currentNode -> rightChild);
		if(q1.empty()) break;
        currentNode = q1.front();
        q1.pop();
    }
    return false;
}
Node* bstree::WrongNode(Node* root)
{
	queue<Node* > q1;
    stack<Node *> s1;
    Node* currentNode = root;
	while(currentNode) 
	{
        if(currentNode -> BF > 1 || currentNode -> BF < -1)
            s1.push(currentNode);
		if(currentNode -> leftChild)
			q1.push(currentNode -> leftChild);
		if(currentNode -> rightChild)
			q1.push(currentNode -> rightChild);
		if(q1.empty()) break;
        currentNode = q1.front();
        q1.pop();
    }
    return s1.top();
}

Node* Partent_of_WrongNode(Node* root, Node* wrongnode)
{
    queue<Node* > q1;
    Node* currentNode = root;
	while(currentNode) 
	{
        if(currentNode -> leftChild == wrongnode || currentNode -> rightChild == currentNode)
            return currentNode;
		if(currentNode -> leftChild)
			q1.push(currentNode -> leftChild);
		if(currentNode -> rightChild)
			q1.push(currentNode -> rightChild);
        currentNode = q1.front();
        q1.pop();
    }
}

void bstree::LLrotation(Node* start, Node* end)
{
	start -> leftChild = end -> rightChild;
    end -> rightChild = start;
}
void bstree::RRrotation(Node* root, Node* start, Node* end)
{
    start -> rightChild = end -> leftChild;
    end -> leftChild = start;
    if(Partent_of_WrongNode(root,start) -> rightChild == start)
        Partent_of_WrongNode(root, start) -> rightChild = end;
    else if(Partent_of_WrongNode(root, start) -> leftChild == start)
        Partent_of_WrongNode(root, start) ->leftChild = end;
}
void bstree::LRrotation(Node* root, Node* start, Node* end)
{
    RRrotation(root, end, end -> rightChild);
    LLrotation(start, start -> leftChild);
}
void bstree::RLrotation(Node* root, Node* start, Node* end)
{
    LLrotation(end, end -> leftChild);
    RRrotation(root, start, start -> rightChild);
}
#endif

