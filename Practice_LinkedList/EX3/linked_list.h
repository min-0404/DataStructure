// 3.홀수 번째 노드를 삭제하는 함수를 작성해라
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
    ChainNode* getLink()
    {
        return link;
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
    ChainNode* Insert(ChainNode* x, int value) //x는 삽입할 노드의 이전 노드
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
    
    void alternateDelete(void)
    {
        if (first == NULL)
        {
            cout << "체인은 비어있다" << endl;
            return;
        }
        else
        {
            ChainNode* temp = first;
            Delete(temp);
            temp = first; //first가 다음 노드를 가리켰으므로 first는 결국 원래 2번째 노드
            while (temp->link != NULL) //다음 노드가 존재할 때까지
            {
                if ((temp->link->link) == NULL) //마지막 하나 남았을 떼
                {
                    delete[](temp->link);
                    temp->link = NULL;
                    break;
                }
                Delete(temp->link);
                temp = temp->link; //2개 건너뛴다
            }
        }
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
