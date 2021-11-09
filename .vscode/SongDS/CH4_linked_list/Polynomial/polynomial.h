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
    ChainNode(T element = 0, ChainNode *next = NULL) :data(element), link(next)
    {}
    T getData()
    {
        return data;
    }
    ChainNode* Link()
    {
        return link;
    }
    friend class Chain<T>;
    template <typename T>
    friend ostream &operator<<(ostream &os, Chain<T> &c);
};

template <typename T>
class Chain
{
private:
    ChainNode<T>* first;
    ChainNode<T>* last;
public:
    Chain()
    {
        first = NULL;
    }
    ChainNode<T>* getFirst()
    {
        return first;
    }
    ChainNode<T>* Insert(ChainNode<T>* x, T i) // x는 삽입할 노드의 이전 노드
    {
        if (first)
        {
            ChainNode<T>* temp = new ChainNode<T>(i, x->link);
            x->link = temp;
            return x->link;
        }
        else
        {
            first = new ChainNode<T>(i);
            return first;
        }
    }
    int Length()
    {
        int len = 0;
        ChainNode* temp = first;
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
            return;
        }
        if (x == first)
            first = first->link;
        else
        {
            ChainNode<T>* temp = first;
            while (temp->link != x)
            {
                temp = temp->link;
            }
            temp->link = x->link;
        }
        delete x;
    }
    void InsertBack(const T& item)
    {
        if (first)
        {
            last->link = new ChainNode<T>(item);
            last = last->link;
            last->link = NULL;
        }
        else
        {
            first = last = new ChainNode<T>(item);
            first->link = NULL;
        }
    }
    void Concatenate(Chain<T>& b)
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
    class ChainIterator //nested class
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
            T& operator*() const
            {
                return current->data;
            }
            T* operator->()
            {
                return &current->data;
            }
            ChainIterator& operator++() // 전위 증가
            {
                current = current->link;
                return *this;
            }
            ChainIterator operator++(int) //후의 증가
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
            bool operator&&(const ChainIterator right) const
            {
                return current && right.current;
            }
            template <typename T>
            friend ostream &operator<<(ostream &os, Chain<T> &c);
    };
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
ostream &operator<<(ostream &os, Chain<T> &c)
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

class Polynomial
{
public:
    struct Term // 클래스 안의 구조체 생성(nested struct)
    {
        int coef;
        int exp;
        Term Set(int c, int e)
        {
            coef = c;
            exp = e;
            return *this;
        }
    };
private:
    Chain<Term> poly;
public:
    Polynomial() {}
    void InsertTerm(Term& term)
    {
        poly.InsertBack(term);
    }
    Polynomial operator+(Polynomial& b)
    {
        Term temp;
        Chain<Term>::ChainIterator ai = poly.begin(), bi = b.poly.begin();
        Polynomial c; //두 식의 합을 반환할 클래스
        while (ai && bi)
        {
            if (ai->exp == bi->exp) //지수가 동일할시 더하고
            {
                int sum = ai->coef + bi->coef;
                if (sum)
                    c.poly.InsertBack(temp.Set(sum, ai->exp));
                ai++;
                bi++;
            }
            else if (ai->exp < bi->exp) //지수가 더 작은 쪽을 먼저 더한다, 그래야 높은 지수끼리 기다리고 더할 수 있다
            {
                c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
                ai++;
            }
            else
            {
                c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
                bi++;
            }
        }
        while (ai != 0) //식이 더 많은 쪽을 마저 더한다
        {
            c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
            ai++;
        }
        while (bi != 0)
        {
            c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
            bi++;
        }
        return c;
    }


    
    int Eval(int x)
    {
        int sum = 0;
        Chain<Term>::ChainIterator ai = poly.begin();
        while (ai != 0)
        {
            for (int i = 0; i < ai->exp; i++)
            {
                x *= x;
            }
            sum += ai->coef*x;
            ai++;
        }
        return sum;
    }
    friend ostream &operator<<(ostream &os, Polynomial &p);
    friend istream &operator>>(istream &is, Polynomial &p);
};

ostream &operator<<(ostream &os, Polynomial &p)
{
    Chain<Polynomial::Term>::ChainIterator i = p.poly.begin();
    while (1)
    {
        Polynomial::Term term = *i;
        os << term.coef << "x^(" << term.exp << ")";
        if (++i != p.poly.end())
            os << " + "; //끝이 아닐 경우 +
        else
        {
            os << " ";
            break;
        }
    }
    return os;
}

 

istream &operator>>(istream &is, Polynomial &p)

{

        int coef, exp;

        int num;

 

        cout << "다항식에 몇개의 식을 추가할 것인가?";

        is >> num;

 

        for (int i = 0; i < num; i++)

        {

               cout << i + 1 << "번째 계수: ";

               is >> coef;

               cout << i + 1 << "번째 지수: ";

               is >> exp;

 

               Polynomial::Term temp;

               temp.exp = exp;

               temp.coef = coef;

               p.InsertTerm(temp);

        }

 

        return is;

}
