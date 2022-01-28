/* 6번.
<< 연산자를 오버로드해서 체인 안에 있는 모든 요소들을 출력하는 "템플릿 함수"를 작성한다.
<< 연산자가 T 데이터 타입에 대해 오버로드되어있다고 가정한다
operator<< 는 ChainIterator 클래스를 기반으로 작성하자
*/

#include <iostream>
using namespace std;

template <typename T> class Chain; // 전방 선언

template <typename T>
class ChainNode
{
private:
        T data;
        ChainNode<T>* link;

public:
        ChainNode(T element = 0, ChainNode* next = NULL) :data(element), link(next)
        {}
        T getData() // 노드의 데이터 반환하는 함수
        {
                return data;
        }
        ChainNode* Link() // 노드의 다음 노드 반환하는 함수
        {
                return link;
        }

        friend class Chain<T>;

        template <typename T>
        friend ostream &operator<<(ostream &os, Chain<T> &c); //출력
};

template <typename T>
class Chain
{
private:
        ChainNode<T> *first;
        ChainNode<T> *last;
public:
        Chain()
        {
                first = NULL;
        }
        ChainNode<T>* getFirst()
        {
                return first;
        }
        ChainNode<T>* Insert(ChainNode<T>* x, T value) // x는 삽입할 노드의 이전 노드
        {
                if (first)
                {
                        ChainNode<T> *temp = new ChainNode<T>(value, x->link);
                        x->link = temp;
                       return x->link;
               }
               else
               {
                       first = new ChainNode<T>(value);
                       return first;
               }
        }
        int Length()
        {
                int len = 0;
                ChainNode *temp = first;
                while (temp != NULL)
               {
                       temp = temp->link;
                       len++;
               }
               return len;
        }
        void Delete(ChainNode<T>* x) // x는 삭제할 노드
        {
                if (first == NULL)
                {
                       cout << "체인은 비어있다" << endl;
                       return;
                }
                if (x == first)
                        first = first->link;
                else
                {
                       ChainNode<T> *temp = first;
                       while (temp->link != x)
                       {
                               temp = temp->link;
                       }
                       temp->link = x->link;
                }
                delete x;
        }
        void InsertBack(const T& value)
        {
                if (first)
                {
                        last->link = new ChainNode<T>(value);
                        last = last->link;
                        last->link = NULL;
               }
               else
               {
                       first = last = new ChainNode<T>(value);
                       first->link = NULL;
               }
        }
        void Concatenate(Chain<T>& b) // 현재 체인과 b체인을 연결한다
        {
                if (first)
                {
                        last->link = b.first;
                        last = b.last;
                }
                else
                {
                        first = b.first;
                        last = b.last;
                }
        }
        void Reverse()
        {
                ChainNode<T> *current = first, *previous = NULL; //previous는 current 전 노드
                while (current)
                {
                        ChainNode<T> *r = previous; //previous의 위치를 기억해두었다가
                        previous = current;
                        current = current->link;
                        previous->link = r; //이전의 current가 이전의 previous를 가르키도록 한다

                }
                first = previous;
        }

        class ChainIterator // nested 클래스!!!!!!!!!!!!!!!!!!
        {
        private:
                ChainNode<T>* current;
        public:
                ChainIterator(ChainNode<T>* startNode = NULL)
                {
                        current = startNode;
                }
                T getData()
                {
                        return current->data;
                }
                T& operator*() const // 반환형이 포인터
                {
                        return current->data;
                }
                T* operator->() // 반환형이 참조자
                {
                        return &current->data;
                }
                ChainIterator& operator++() //전위증가
                {
                        current = current->link;
                        return *this;
                }
                ChainIterator operator++(int) // 후위증가(int 넣어주는 것은 관례상임)
                {
                        ChainIterator old = *this;
                        current = current->link;
                        return old;
                }
                bool operator!=(const ChainIterator right) const
                {
                        return current != right.current;
                }
                bool operator==(const ChainIterator right) const
                {
                        return current = right.current;
                }

                template <typename T>
                friend ostream &operator<<(ostream &os, Chain<T> &c); //출력
        };
        
        // begin()과 end()함수도 Chain의 함수일 뿐
        ChainIterator begin()
        {
                return ChainIterator(first);
        }
        ChainIterator end()
        {
                return ChainIterator(0);
        }
        template <typename T>
        friend ostream &operator<<(ostream &os, Chain<T> &c);
};


template <typename T>
ostream& operator<<(ostream& os, Chain<T> &c)
{
        Chain<T>::ChainIterator i = c.begin();
        while (i != c.end())
        {
                os << i.getData() << "->";
                i++;
        }
        os << i.getData();
        os << endl;
        return os;
}
