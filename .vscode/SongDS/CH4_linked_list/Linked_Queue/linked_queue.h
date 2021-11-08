#include <iostream>
using namespace std;

template <typename T> class LinkedQueue; // 전방 선언

template <typename T>
class ChainNode //기존의 ChainNode 클래스 그대로 사용
{
private:
    T data;
    ChainNode<T>* link;
public:
    ChainNode(T element = 0, ChainNode *next = NULL) :data(element), link(next)
    {}
    friend LinkedQueue<T>;
};


template <typename T>
class LinkedQueue
{
private:
    ChainNode<T> *front;
    ChainNode<T> *rear;
public:
    LinkedQueue()
    {
        front = rear = NULL;
    }
    bool isEmpty()
    {
        return (front == NULL && rear == NULL);
    }
    T& Front()
    {
        return front->data;
    }
    T& Rear()
    {
        return rear->data;
    }
    void Enqueue(const T &item) // rear에 새로운 노드 삽입
    {
        if (isEmpty())
        {
            front = rear = new ChainNode<T>(item, 0); //empty queue
        }
        else
        {
            rear = rear->link = new ChainNode<T>(item, 0); //rear에 추가 InsertRear
        }
    }
    void Dequeue() // fornt 에서 노드 제거
    {
        if (isEmpty())
        {
            return;
        }
        ChainNode<T>* delNode = front;
        front = front->link;
        delete delNode;
    } 
    void Show() // front 부터 출력
    {
        ChainNode<T>* cur = front;
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
