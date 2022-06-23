//1. 체인에 있는 노드 개수를 세는 함수 Length 작성하기.
#include <iostream>
using namespace std;

class ChainNode
{
private:
    int data;
    ChainNode* link;
public:
    ChainNode(int element = 0, ChainNode* next = NULL) :data(element), link(next) {}
    int getData()
    {
        return data;
    }
    friend class Chain;
};

class Chain
{
private:
    ChainNode* first;
public:
    Chain() { first = NULL; }
    ChainNode* getFirst()
    {
        return first;
    }
    ChainNode* Insert(ChainNode* x, int value) //x는 삽입할 이전 노드
    {
        if(first) //기존 노드 있을 때
        {
            ChainNode* temp = new ChainNode(value, x -> link);
            x -> link = temp;
            return x -> link; //temp를 return하지 않은 이유 알지?
        }
        else //빈 체인일때
        {
            first = new ChainNode(value);
            return first;
        }
    }

    void Delete(ChainNode* x) //x라는 노드를 삭제하려한다
    {
        if(x == first)
        {
            first = first -> link;
        }
        else
        {
            ChainNode* temp = first;
            while(temp -> link != x) //temp를 x직전 노드로 만들어줌
            {
                temp = temp -> link;
            }
            temp -> link = x -> link;
        }
        delete x;
    }

    int Length()
    {
        int count = 0;
        ChainNode* temp = first;
        while(temp != NULL)
        {
            temp = temp -> link;
            count++;
        }
        return count;
    }

    void Show ()
    {
        ChainNode* temp = first;
        while(temp != NULL)
        {
            cout<<temp -> getData();
            if(temp -> link != NULL)
                cout<<" -> ";
            temp = temp -> link;
        }
    }
};
