#include <iostream>
using namespace std;

template <typename T> class LinkedStack; // 전방 선언


template <typename T>
class ChainNode // 기존 ChainNode 그대로 사용
{
private:
    T data;
    ChainNode<T> *link;
public:
    ChainNode(T element = 0, ChainNode *next = NULL) :data(element), link(next)
        {}
        
    friend LinkedStack<T>;
};

template <typename T>
class LinkedStack
{
private:
    ChainNode<T>* top;
public:
    LinkedStack()
    {
        top = NULL;
    }
    bool isEmpty()
    {
        return top == NULL;
    }
    void Push(const T& item)
    {
        top = new ChainNode<T>(item, top);
    }
    void Pop()
    {
        ChainNode<T>* delNode = top;
        top = top->link; //top 노드의 다음 노드로 top넘김
        delete delNode;
    }
    T& Top()
    {
        return top->data;
    }

    void Show() // top 부터 출력
    {
        ChainNode<T>* cur = top;
        while(cur != 0)
        {
            cout<<cur -> data;
            if(cur -> link != 0)
                cout<<" -> ";
            else
                cout<<endl;
            cur = cur -> link;
        }
    }
};