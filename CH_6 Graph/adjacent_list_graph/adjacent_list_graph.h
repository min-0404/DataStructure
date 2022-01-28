#include <iostream>
using namespace std;

class ChainNode // 노드는 2개의 필드로 구성(데이터 + 링크)
{
private:
    int data;
    ChainNode* link;
public:
    ChainNode(int d = 0, ChainNode* l = NULL): data(d), link(l) {}
    int getData()
    {
        return data;
    }
    ChainNode* getLink()
    {
        return link;
    }
    friend class AdjList;
    friend class Graph;
    friend ostream& operator<<(ostream& os, Graph &g);
};

class AdjList // Chain을 뜻한다
{
private:
    ChainNode* first;
public:
    friend class Graph;
    friend ostream& operator<<(ostream& os, Graph &g);
};

class Graph // 그래프는 정점의 개수만큼  AdjList 를 가진다
{
private:
    AdjList* list; // 정점개수 만큼 인접리스트를 갖는 배열
    int number; // 정점의 개수
public:
    Graph(int n): number(n)
    {
        list = new AdjList[n]; // 정점의 개수만큼 인접리스트를 생성해줌
        for(int i = 0; i < n; i++)
            list[i].first = NULL;
    }
    void linkEdge(int num1, int num2) // 정점 num1과 정점 num2를 이어줌(무방향 그래프일 경우)
    {
        ChainNode* newNode = new ChainNode(num2);
        newNode -> link = list[num1].first;
        list[num1].first = newNode;

        newNode = new ChainNode(num1);
        newNode -> link = list[num2].first;
        list[num2].first = newNode;
    }
    friend ostream& operator<<(ostream& os, Graph &g);
};

ostream& operator<<(ostream& os, Graph& g)
{
    os << "각 정점에 연결된 정점들을 나열" << endl;
    for (int i = 0; i< g.number; i++)
    {
        ChainNode* temp = g.list[i].first;
        os << i << " : ";
        while(temp)
        {
            os << temp -> data;
            temp = temp -> link;
        }
        os << endl;
    }
    return os;
}