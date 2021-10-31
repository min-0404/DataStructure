#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <class T>
struct Node
{
    Node(T d, Node<T> *left=0, Node<T> *right=0) : data(d), leftChild(left), rightChild(right)
    { }
    Node<T> *leftChild;
    Node<T> *rightChild;
    T data;
};

template <class T>
class Tree
{
public:
    Tree()
    {
        root = 0;
    }
    void Insert(T &value)
    {
        Insert(root, value);
    }
    void Preorder()
    {
        Preorder(root);
    }
    void Inorder()
    {
        Inorder(root);
    }
    void Postorder()
    {
        Postorder(root);
    }
    void StackInorder()
    {
        stack<Node<T>*> s;
        Node<T>* currentNode = root;
        while(1)
        {
            while(currentNode)
            {
                s.Push(currentNode);
                currentNode = currentNode -> leftChild;
            }
            if(s.isempty())
                return;
            currentNode = s.Top();
            s.pop();
            Visit(currentNode);
            currentNode = currentNode -> rightChild;
        } 
    }
    void StackPreorder()
    {
        stack<Node<T>*> s;
        Node<T>* currentNode = root;
        while(1)
        {
            while(currentNode)
            {
                Visit(currentNode);
                s.push(currentNode);
                currentNode = currentNode -> leftChild;
            }
            if(s.isempty())
                return;
            currentNode = s.top();
            s.pop();
            currentNode = currentNode -> rightChild;
        }

    }
    void StackPostorder()
    {
        stack<Node<T>*> s;
        Node<T>* currentNode = root;
        while(1)
        {
            while(currentNode)
            {
                currentNode = currentNode -> leftChild;
                s.push(currentNode);
                while(currentNode)
                {
                    s.push(currentNode);
                    currentNode = currentNode -> right;
                }
            }
            if(s.isempty())
                return;
            
        }
    }
    void Levelorder();
private: // helper 함수들
    Node<T> *root;
    void Visit(Node<T> *);
    void Insert(Node<T>* &, T &);
    void Preorder(Node<T>* currentNode) //재귀이용 : VLR
    {
        if(currentNode)
        {
            Visit(currentNode);
            Preorder(currentNode -> leftChild);
            PreOrder(currentNode -> rightChild);
        }
    }
    void Inorder(Node<T>* currentNode) //재귀이용 : LVR
    {
        if(currentNode)
        {
            Inorder(currentNode -> leftChild);
            Visit(currentNode);
            InOrder(currentNode -> rightChild);
        }
    }
    void Postorder(Node<T>* currentNode) //재귀이용 : LRV
    {
        if(currentNode)
        {
            Postorder(currentNode -> leftChild);
            PostOrder(currentNode -> rightChild);          
            Visit(currentNode);
        }
    }
};

template <class T>
void Tree<T>::Visit(Node<T> *ptr)
{
    cout << ptr->data << " ";
}

template <class T>
void Tree<T>::Insert(Node<T>* &ptr, T &value)//Insert 의 helper 함수
{
    if (ptr==0)
        ptr = new Node<T>(value);
    else if (value < ptr->data) //insert 하려는 값이 해당 노드보다 작을때 : 왼쪽으로 재귀
        Insert(ptr->leftChild, value);
    else if (value > ptr->data) //insert하려는 값이 해당 노드보다 클 때 : 오른쪽으로 재귀
        Insert(ptr->rightChild, value);
    else
        cout << endl << "Duplicate value " << value << " ignored\n";
}

#endif
