#include <iostream>
using namespace std;

template <typename T>
class Chain; //전방선언

template <typename T>
class ChainNode //노드 클래스 정의
{
private:
    T data;
    ChainNode<T>* link;
public:
    ChainNode(T d, ChainNode<T>* l = 0):data(d), link(l)
    {}
    friend class Chain<T>;
};
  
template <typename T>
class Chain //체인 클래스 정의
{
private:
    ChainNode<T>* first;
    ChainNode<T>* last;
public:
    Chain() //생성자
    {
        first = 0;
    }
    void Create(T value) //빈 리스트에 first노드 만들기
    {
        fist = new ChainNode<T>(value);
    }
    void Insert(ChainNode<T>* x, T value) //x는 삽입할 곳 이전노드
    {
        if(first) //빈 리스트 아닐때
        {
            ChainNode* temp = new ChainNode(value);
            temp -> link = x -> link;
            x -> link = temp;
        }
        else //빈 리스트일때
        {
            fist = new ChainNode<T>(value);
        }
    }
    void Delete(ChainNode<T>* x, ChainNode<T>* y) //x는 삭제할 노드, y는 삭제할 노드 이전노드
    {
        if(x == fist)
        {
            first = first -> link;
        }
        else
        {
            y -> link = x -> link;
        }
        delete x;
    }
    void InsertBack(T& e)
    {
        if(first) //빈 체인 아닐때
        {
            last -> link = new ChainNode<T>(e); 
            last = last -> link;
        }
        else //빈 체인일때
        {
            first = last = new ChainNode<T>(e);
        }
    }
    void Concatenate(Chain<T>& b) //현재 체인뒤에 b라는 체인 연결하기
    {
        if(first) //빈 체인이 아닐때
        {
            last -> link = b.first;
            last = b.last;
        }
        else
        {
            fisrt = b.first;
            last = b.last;
        }
        b.first = b.last = 0;
    }
};

template <typename T>
class ChainIterator //체인반복자 정의
{
private:
    ChainNode<T>* current;
public:
    ChainIterator(ChainNode<T>* startNode = 0) //생성자
    {
        current = startNode;
    }
    T& operator* () const //*기호 정의
    {
        return current -> data;
    }
    T* operator->() const //->기호 정의
    {
        return &current -> data;
    }
    ChainIterator& operator++() //전방증가
    {
        current = current -> link;
        return *this;
    }
    ChainIterator& operator++(int) //후방증가
    {
        ChainIterator old = *this;
        current = current -> link;
        return old;
    }
    bool operator!=(const ChainIterator right ) const //!= 정의
    {
        return current != right.current;
    }
    bool operator==(const ChainIterator right) const //== 정의
    {
        return current == right.current; 
    }
};