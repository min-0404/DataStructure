/* 5번.
x=(x1, x2, ..., xn) 과 y=(y1, y2, ..., ym)가 두개의 체인이라고 가정한다.
각각의 체인에 노드들은 오름차순으로 정렬되어있다고 가정한다
두 개의 체인을 합치되 똑같이 오름차순으로 정렬되어있는 z를 만들어내는 함수를 구현한다.
합치고 난 다음에는 x 와 y 체인은 비어있어야 한다(기존에 있던 노드들이 모두 z에 있기 때문에)
*/
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
    int getData()
    {
        return first -> data;
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
    
    void ascendingSort() //버블Sort 이용
    {
        if (first == NULL)
        {
            cout << "체인은 비어있다" << endl;
            return;
        }
        else
        {
            ChainNode *End = 0; //마지막 노드 다음 노드 즉 NULL
            ChainNode *current; //현재 가리키고 있는 노드
            ChainNode *next; //다음에 가리킬 노드
            ChainNode *previous; //이전에 가리킨 노드

            while (first->link != End) //끝이 아닐 때까지
            {
                current = first; //현재는 처음을 가리키고
                next = first->link;
                previous = 0;
                while (next != End) //현재 노드가 마지막 노드가 아닐 때까지
                {
                    if (current->data > next->data) //현재가 더 크면
                    {
                        if (previous) //그 전 노드가 존재한다면
                            previous->link = next; //바꾼다
                        else
                            first = next;
                            //바꾼다
                            current->link = next->link;
                            next->link = current;
                            previous = next;
                            next = current->link;
                    }
                    
                    else //오름차순이 맞다면 그냥 다음 노드로 넘어간다
                    {
                        previous = current;
                        current = next;
                        next = next->link;
                    }
                }

                End = current; //현재 노드가 마지막 노드가 되게 한다

            }

        }

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

    friend void Merge(Chain &x, Chain &y, Chain &z);
};


void Merge(Chain& x, Chain& y, Chain& z) // 지금까지 사용한 Lenght함수, Insert함수, Delete함수를 섞어서 사용하면 쉽다
{
    ChainNode *CN = z.getFirst();
    int idx1 = 0, idx2 = 0;
    int length1 = x.Length();
    int length2 = y.Length();
    while (idx1 < length1 && idx2 < length2)
    {
        CN = z.Insert(CN, x.getData());
        idx1++;
        x.Delete(x.getFirst()); // x의 first 노드를 계속 지움
        
        CN = z.Insert(CN, y.getData());
        idx2++;
        y.Delete(y.getFirst()); // y의 first 노드를 계속 지움
    }

    if (idx1 < length1) // 만약 x의 노드들 남았으면 마무리
    {
        while (idx1 < x.Length())
        {
            CN = z.Insert(CN, x.getData());
            idx1++;
            x.Delete(x.getFirst());
        }
    }
    else if (idx2 < length2) //만약 y의 노드들 남았으면 마무리
    {
        while (idx2 < y.Length())
        {
            CN = z.Insert(CN, y.getData());
            idx2++;
            y.Delete(y.getFirst());
        }
    }
}
