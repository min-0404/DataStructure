#ifndef AVL_H
#define AVL_H
typedef struct Node* nodeptr;
#include <queue>
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* rightChild;
    Node* leftChild;
    Node() {}
    Node(int d): data(d)
    {
        rightChild = 0;
        leftChild = 0;
    }
};

class bstree
{
private:
    Node* root; // 루트를 가리키는 포인터
public:
    bstree()
    {
        root = NULL;
    }
    void visit(Node* ptr); // Showresult의 levelorder순회를 구현하기 위한 추가함수
    void insert(const int value, Node*& root);
    void Showresult(Node* root); // 트리를 level order방식으로 순회하면서 출력
    void Search(const int key, Node* root);
    void del(const int key, Node* root); // 설명서에 나온 방식대로 구현
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
void bstree::insert(const int value, Node*& root)
{
    if(!root)
    {
        root = new Node(value);
        return;
    }
	if(value > root -> data)
        insert(value, root -> rightChild);
    else
        insert(value, root -> leftChild);
};
void bstree::Showresult(Node* root)
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
void bstree::Search(const int key, Node* root)
{
	int* arr = new int[100]; // 경로를 저장해놓을 배열
	int n = 0; // arr배열의 인덱스가 되어줄 변수
	Node* temp = root;
	while(1)
	{
		if(key == temp -> data) // 찾아냈을 때
		{
			arr[n] = temp -> data;
			break;
		}
		if(key > temp -> data) // key가 클떄 오른쪽으로
		{
			temp = temp -> rightChild;
			arr[n++] = temp -> data;
		}
		else if(key < temp -> data) // ket가 작을때 왼쪽으로
		{
			temp = temp -> leftChild;
			arr[n++] = temp -> data;
		}
	}
	for(int i = 0; i < n; n++)
		cout << arr[i] << " -> ";
	cout << arr[n];
	delete[] arr;
}
void bstree::del(const int key, Node* root)
{
	Node* del = root;
	while(1) // 일단, 삭제할 노드를 del로 만들어줌
	{
		if(key == del -> data) // 찾아냈을 때
			break;
		if(key > del -> data) // key가 클떄 오른쪽으로
			del = del  -> rightChild;
		else if(key < del -> data) // ket가 작을때 왼쪽으로
			del = del -> leftChild;
	}
	if(del -> rightChild == 0 && del -> leftChild == 0) //만약 삭제할 노드가 리프노드라면 그대로 삭제
		delete del;
	else //삭제할 노드가 리프노드가 아니면 왼쪽 서브트리중에서 가장 큰 노드로 대체
	{
		Node* temp = root; // temp는 대체할 노드
		while(1) // del과 동일한 위치로 temp를 일단 설정
		{
			if(key == temp -> data)
				break;
			if(key > temp -> data)
				temp = temp  -> rightChild;
			else if(key < temp -> data) 
				temp = temp -> leftChild;
		}
		temp = temp -> leftChild; // 왼쪽 서브트리중에서
		while(!temp -> rightChild) //temp가 리프노드가 될때까지 계속 오른쪽으로
			temp = temp -> rightChild;
		del -> data = temp -> data; // del의 데이터를 temp의 데이터로 바꿔주줌
		delete temp; //temp가 가리키는 노드를 삭제해줌
	}
};

#endif



void bstree::setBF(Node* startNode, Node* endNode) {
		
}
bool bstree::rotation(Node* start, Node* end) {
	
}



