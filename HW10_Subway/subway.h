#ifndef __SUBWAY_H__
#define __SUBWAY_H__
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <queue>
#define INF 9999
using namespace std;


class Vertex // 정점, 즉 한개의 역을 뜻함
{
private:
    int line; // 해당 역의 호선
    string name; // 해당 역의 이름
    int index; // 각 vertex에게 주어진 번호, 즉 staiton을 세는 번호인 number 와 동일
public:
    Vertex();
    Vertex(int l, string n, int i);
    friend class Graph;
};

class Graph
{
private:
    Vertex* station; // 역(Vertex객체)들을 저장할 배열(역의 개수: 총 70개)
    int number; // station 배열에 추가될 역의 개수 세는 변수, 즉 Vertex에게 할당 된 index와 동일
    int** matrix; // 인접 행렬
    bool* s; // 다익스트라 알골 진행하면서 해당역을 가봤는지 확인하는 배열
    int* distance; // 다익스트라 알골 진행하면서 시작역으로부터의 최단거리 저장하는 배열

    int* choosed_vertex; // Choose 함수로 선택된 vertex들을 차례로 삽입한 배열
    int count; //choosed_vertex의 개수를 셀때 사용할 변수
public:
    Graph();
    Graph(Graph& g); // 깊은 복사를 위한 생성자
    bool find(int n, string s); 
    int findIndex(int n, string s);
    void insertVertex(int n, string s, int c);
    void insertEdge(int i, int j);

    int Choose(const int n);
    void ShortestPath(const int n, const int v);
    void insertChoosed_Vertex(int u);
    void display_path(int s, int n);
    void display_time(int n);
    bool isLeaf(int n); //display_path함수만을 위해 따로 만든 함수: 해당 vertex가 말단인지 확인, n은 확인하려는 vertex의 인덱스
    void min(Graph& g);
};

#endif

