#include <iostream>
using namespace std;

template <typename T> class CircularList; // 전방 선언

template <typename T>
class ChainNode // 기존 ChainNode 그대로 사용
{
private:
    T data;
    ChainNode<T> *link;
public:
    ChainNode(T element = 0, ChainNode *next = NULL) :data(element), link(next)
        {}
        
    friend CircularList<T>;
};

template <typename T>
class CircularList
{
private:
    ChainNode<T>* first; // first 노드가 결국 헤더 노드이다
public:
    CircularList()
    {
        first = new ChainNode<T>; // 더미노드로 만들어줌
        first->link = first; // 원형 리스트의 가장 중요한 특징
    }
    ~CircularList()
    {
        ChainNode<T>* del = first->link;
        while (del != first)
        {
            first->link = del->link; // 노드를 먼저 삭제해버리 끊기기 때문에 미리 연결작업 해둠
            delete del;
            del = first->link;
        }
    }
    bool isEmpty()
    {
        return first->link == first;
    }

    int Length()
    {
        int len = 0;
        ChainNode<T> *cur = first->link;
        while (cur != first)
        {
            len++;
            cur = cur->link;
        }
        return len;
    }

    void Search(const T& item)
    {
        ChainNode<T> *cur = first->link;
        int idx = 1;
        while (1)
        {
            if (cur->data == item)
            break;
            cur = cur->link;
            idx += 1;
        }
        if (cur == first)
            cout << "존재하지 않는 데이터입니다" << endl;
        else
            cout << idx << "번 째 노드에 있는 데이터입니다" << endl;

    }

    void InsertFront(const T &item)
    {
        ChainNode<T> *newNode = new ChainNode<T>(item);
        newNode->link = first->link;
        first->link = newNode;
    }
    
    void InsertRear(const T &item)
    {
        ChainNode<T> *newNode = new ChainNode<T>(item);
        ChainNode<T> *cur = first->link;
        while (cur->link != first)
        {
            cur = cur->link;
        }
        cur->link = newNode; 
        newNode->link = first;
    }


    void Delete(int idx)
    {
        ChainNode<T> *cur = first->link;
        if (idx < 1)
        {
            cout << "1 이상의 숫자를 입력하셔야합니다" << endl;
        }
        else if(idx==1)
        {
            first->link = cur->link;
        }
        else
        {
            int count = 1;
            ChainNode<T> *del = first->link;
            while (count < idx)
            {
                del = del->link;
                count++;
            }
            cur = del->link;
            del->link = cur->link; 
        }
        delete cur;

    }
    void Show()
    {
        ChainNode<T>* cur;
        for(cur = first -> link; cur != first; cur = cur -> link)
        {
            cout<<cur -> data;
            if(cur -> link != first)
                cout<<" -> ";
            else
                cout<<endl;
        }
    }
};

