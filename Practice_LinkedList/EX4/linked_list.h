/*4번.
x=(x1, x2, ..., xn) 과 y=(y1, y2, ..., ym)가 두개의 체인이라고 가정한다.
m<=n일 경우 z=(x1, y1, x2, y2, ..., xn) 체인이 되도록하고, m>n일 경우z=(x1, y1, x2, y2, ..., ym) 체인이 되도록 하는 merge 함수를 작성한다.
합치고 난 다음에는 x 와 y 체인은 비어있어야 한다(기존에 있던 노드들이 모두 z에 있기 때문에)
추가적인 노드들은 사용불가능하다.
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
        x.Delete(x.getFirst());
        
        CN = z.Insert(CN, y.getData());
        idx2++;
        y.Delete(y.getFirst());
    }

    if (idx1 < length1) // 마무리
    {
        while (idx1 < x.Length())
        {
            CN = z.Insert(CN, x.getData());
            idx1++;
            x.Delete(x.getFirst());
        }
    }
    else if (idx2 < length2) //마무리
    {
        while (idx2 < y.Length())
        {
            CN = z.Insert(CN, y.getData());
            idx2++;
            y.Delete(y.getFirst());
        }
    }
}
