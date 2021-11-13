#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <class T>
struct Node
{
    Node(T d, Node<T>* left = 0, Node<T>* right = 0) : data(d), leftchild(left), rightchild(right) {}
    T data;
    Node<T>* leftchild;
    Node<T>* rightchild;
};

template <class T>
class Tree {
public:
    Tree() {root = 0;}
    void Insert(T& value) // value는 삽입할 노드의 data값
    {
        Insert(root, value);
    }
    void Inorder() {Inorder(root);}
    void Preorder() {Preorder(root);}
    void Postorder() {Postorder(root);}
    void StackInorder() //LVR
    {
        Node<T>* currentNode = root;
        stack<Node<T> * > s;
        while(1)
        {
            // 1단계.
            while(currentNode)
            {
                s.push(currentNode);
                currentNode = currentNode -> leftchild;
            }
            // 2단계
            if(s.isempty()) return;
            // 3단계
            currentNode = s.top();
            s.pop();
            Visit(currentNode);
            currentNode = currentNode -> rightchild;
        }
    }
    void StackPreorder() //VLR
    {
        Node<T>* currentNode = root;
        stack<Node<T> * > s;
        while(1)
        {
            // 1단계
            while(currentNode)
            {
                Visit(currentNode);
                if(currentNode -> rightchild)
                    s.push(currentNode -> rightchild);
                currentNode = currentNode -> leftchild;
            }
            // 2단계
            if(s.isempty())
                return;
            // 3단계
            else
            {
                currentNode = s.top();
                s.pop();
            }
        }
    }
    void StackPostorder() //LRV
    {
        Node<T>* currentNode = root;
        stack<Node<T> * > s;
        while(1)
        {
            // 1단계: 일단 최대 왼쪽 노드 쭉 스택에 삽입(뼈대)
            while(currentNode)
            {
                s.push(currentNode);
                currentNode = currentNode -> leftchild;
            }
            // 2단계
            if(s.isempty())
                return true;
            // 3단계
            currentNode = s.top();
            if(currentNode -> rightchild) // 만약 오른쪽 자식이 있다면, 걔를 스택에 넣고, 이제 걔가 currentNode이다
            {
                s.push(currentNode -> rightchild);
                currentNode = currentNode -> rightchild;
            }
            else //만약 없다면
            {
                do
                {
                    s.pop();
                    Visit(currentNode);
                    prev = currentNode;
                    if(! s.isempty())
                        currentNode = s.top();
                }
                while(currentNode -> rightchild == prev || !currentNode -> rightchild);
                currentNode = currentNode -> rightchild;
            }
        }
    }
    void Levelorder()
    {
        Node<T>* currentNode = root;
        queue<Node<T> * > q;
        while(currentNode)
        {
            Visit(currentNode);
            if(currentNode -> leftchild)
                q.push(currentNode -> leftchild);
            if(currentNode -> rightchild)
                q.push(currentNode -> righttchild);
            if(q.isempty())
                return;
            currentNode = q.Front();
            q.pop();
        }
    }
private:
    Node<T>* root;
    void Visit(Node<T>* ptr)
    {
        cout << ptr -> data << " ";
    };
    //workhorse 함수들
    void Insert(Node<T>*& ptr, T& value) // ptr 은 새로 삽입하고 싶은 노드의 부모노드(value 에 따라 부모노드의 leftchild에 만들어질지, rightchild 에 만들어질 지 결정됨)
    {
        if (ptr==0) // 트리가 아예 비어있는 상태일때 root 노드 만들어 줌
            ptr = new Node<T>(value);
        else if (value < ptr->data) // value 가 ptr보다 클 때
            Insert(ptr->leftChild, value);
        else if (value > ptr->data) // value 가 ptr보다 작을 때
            Insert(ptr->rightChild, value);
        else
            cout << endl << "Duplicate value " << value << " ignored\n";
    }
    void Inorder(Node<T>* ptr)
    {
        Node<T>* currentNode = ptr;
        if(currentNode)
        {
            Inorder(currentNode -> leftchild);
            Visit(currentNode);
            Inorder(currentNode -> rightchild);
        }
    }
    void Preorder(Node<T>* ptr)
    {
        Node<T>* currentNode = ptr;
        if(currentNode)
        {
            Visit(currentNode);
            Preorder(currentNode -> leftchild);
            Preorder(currentNode -> rightchild);
        }
    }
    void Postorder(Node<T>* ptr)
    {
        Node<T>* currentNode = ptr;
        if(currentNode)
        {
            Postorder(currentNode -> leftchild);
            Postorder(currentNode -> rightchild);
            Visit(currentNode);
        }
    }
};

#endif