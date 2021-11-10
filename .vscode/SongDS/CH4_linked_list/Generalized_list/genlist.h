#include <iostream>
using namespace std;

template <typename T>
class GenList; // 전방 선언

template <typename T>
class GenListNode // GenListNode는 3개의 정보로 구성된다.
{
private:
    bool tag; // True이면 리스트, Falss 이면 원소 저장
    union
    {
        T data;
        GenListNode<T>* down;
    };
    GenListNode<T>* next;
public:
    GenListNode<T>()
    {
        data = 0;
        next = NULL;
    }
    ~GenListNode<T>()
    {
        if (list)
            delete list;
    }
};

 
template <typename T>
class GenList
{
private:
    GenListNode<T> *first;
public:
    GenList()
    {
        first = new GenListNode<T>; //더미노드 삽입
        first->next = NULL;
    }

        ~GenList()

        {

               GenListNode<T> *p;

               while (first->data>0) //유효데이터일 때

               {

                       p = first;

                       first = first->next;

                       delete p;

               }

        }

        void Insert(const T &item) // 원소를 추가하는 경우

        {

               GenListNode<T> *temp = new GenListNode<T>;

               temp->data = item;

               temp->type = DATA;

               temp->next = first->next;

               first->next = temp; //더미노드 다음에 삽입

        }

        void Insert(const GenList<T> &gl) // 리스트를 추가하는 경우

        {

               GenList<T> *temp1 = new GenList<T>(gl);

               GenListNode<T> *item = new GenListNode<T>;

               item->type = LIST;

               item->list = temp1;

               item->next = first->next;

               first->next = item;

        }

        int Depth() const

        {

               int depth = 0;

               GenListNode<T> *p = first->next;

               while (p)

               {

                       if (p->type == LIST)

                       {

                              int p_depth = p->list->Depth(); //리스트가 두개 이상인 경우를 위해

                              if (p_depth > depth)

                                      depth = p_depth;

                       }

                       p = p->next;

               }

               return ++depth;

        }

        void PrintList() const

        {

               GenListNode<T> *p = first->next;

               while (p)

               {

                       if (p->type == DATA)

                       {

                              cout << p->data;

                              if (p->next)

                                      cout << "->";

                       }

                       if (p->type == LIST) //리스트가 둘 이상일 경우 재귀식으로 출력한다

                       {

                              p->list->PrintList();

                              if (p->next)

                                      cout << "->";

                       }

                       p = p->next;

               }

        }

};
