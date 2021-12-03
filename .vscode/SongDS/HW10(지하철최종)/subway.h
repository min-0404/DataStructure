#ifndef __SUBWAY_H__
#define __SUBWAY_H__
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <queue>
#define INF 9999
using namespace std;
queue<int> q; // 경로를 저장할 큐 (int인것은 vertex의 인덱스를 저장하기 때문)


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


Vertex::Vertex() {} // 기본 생성자
Vertex::Vertex(int l, string n, int i): line(l), name(n), index(i) {} // 생성자

Graph::Graph()
{
    station = new Vertex[900]; //station 배열 동적 할당
    matrix = new int*[900]; // matrix 행렬 동적 할당
    for(int i = 0 ; i < 900; i++)
        matrix[i] = new int[900];
    distance = new int[900]; // distance 배열 동적 할당
    s = new bool[900]; // s배열 동적 할당
    choosed_vertex = new int[900];

    number = 0;
    count = 0;

    for(int i =0; i < 900; i++)
        for(int j = 0; j < 900; j ++)
            if(i ==j)
                matrix[i][j] = 0;
            else
                matrix[i][j] =INF;
};

Graph::Graph(Graph& g)
{
    station = new Vertex[900];
    for(int i = 0; i < 900; i++)
        station[i] = g.station[i];
    matrix = new int*[900];
    for(int i = 0; i < 900; i++)
        matrix[i] = new int[900];
    distance = new int[900];
    s = new bool[900];
    choosed_vertex = new int[900];
        
    number = g.number;
    count = g.count;

    for(int i = 0; i < 900; i++)
        for(int j = 0; j < 900; j++)
            matrix[i][j] = g.matrix[i][j];
};

bool Graph::find(int n, string s) // 해당 vertex가 station 배열에 존재하는지 확인(n은 정점의 호선, s는 정점의 역이름)
{
    for(int i = 0; i < 900; i ++)
    {
        if(station[i].line == n && station[i].name == s)
            return true; // staiton 배열에 이미 있으면 true 반환
    }
    return false; //station 배열에 없으면 false 반환
};

int Graph::findIndex(int n, string s) // 해당 vertex와 동일한 vertex를 station 배열에서 찾아서 그 vertex의 index를 반환해줌
{
    for(int i = 0; i < 900; i ++)
    {
        if(station[i].line == n && station[i].name == s)
            return station[i].index;
    }
};

void Graph::insertVertex(int n, string s, int c) // 입력받으 내용으로 vertex를 생성하고 station 배열에 추가해줌
{
    station[number] = Vertex(n, s, c);
    number++;
};

void Graph::insertEdge(int i, int j) // 만약 두개의 역의 호선이 다르면 환승(30초), 같으면 이동(60초)
{
    if(station[i].line != station[j].line) // 환승
    {
        matrix[i][j] = 30;
        matrix[j][i] = 30;
    }
    else
    {
        matrix[i][j] = 60;
        matrix[j][i] = 60;
    }
};

int Graph::Choose(const int n)
{
    int min = INF;
    int u;
    for(int w = 0; w < n; w++)
        if(!s[w] && distance[w] < min)
        {
            min = distance[w];
            u = w;
        }
    return u;
};

void Graph::ShortestPath(const int n, const int v) // n은 정점의 개수, v는 다익스트라 알골 출발 정점
{
    for(int i = 0; i<n; i++)
    {
        s[i] = false;
        distance[i] = matrix[v][i]; // distance배열을 시작 정점을 기준으로 초기화 해줌
    }
    s[v] = true;
    distance[v] = 0;
    for(int i = 0; i< n-2; i++)
    {
        int u = Choose(n);
        insertChoosed_Vertex(u); // Choose 함수에 새로 추가해준 함수!!!
        s[u] = true;
        for(int w = 0; w < n; w++)
        {
            if(!s[w] && distance[u] + matrix[u][w] < distance[w])
                distance[w] = distance[u] + matrix[u][w];
        }
    }
};

void Graph::insertChoosed_Vertex(int u)
{
    choosed_vertex[count++] = u;
};

void Graph::display_path(int s,int n) //s는 출발지, n은 목적지 vertex의 인덱스번호
{
    int goal = 0;
    while(choosed_vertex[goal] != n)
        goal++; //goal변수는 이제 choosed_vertex 배열에서 목적지 vertex의 인덱스를 저장하게 된다.

    q.push(s); // 출발 지점도 출력되야 하므로 첫번째로 큐에 넣어줌
    q.push(choosed_vertex[0]); // 일단 첫번째 choose값은 무조건 push 해주고,

    int x = 0;
    int y = 1;
    while(y <= goal)
    {
        if(matrix[ choosed_vertex[x] ][ choosed_vertex[y] ] != INF && isLeaf(choosed_vertex[y]))
        {
            q.push(choosed_vertex[y]);
            x = y;
            y++;
        }
        else
            y++;
    }
    while(!q.empty())
    {
        int z = q.front();
        q.pop();
        if(station[z].name != station[q.front()].name)
            cout << station[z].name << endl;
    }
};
void Graph::display_time(int n) // n은 목적지 vertex의 인덱스 번홓
{
    int minute = distance[n] / 60;
    int second = distance[n] % 60;
    if(second == 0)
        cout << minute << " : " << "00" << endl;
    else
        cout << minute << " : " << second << endl;
};

bool Graph::isLeaf(int n) //display_path함수만을 위해 따로 만든 함수: 해당 vertex가 말단인지 확인, n은 확인하려는 vertex의 인덱스
{
    int k = 0;
    for(int i = 0; i < number; i++ )
    {
        if(matrix[n][i] != INF)
            k++;
    }
    if(k > 2) // 만약 count가 1이상이면 말단노드가 아님
        return true;
    else //말단노드임
        return false;
};

void Graph::min(Graph& g) // 두개의 Graph 객체의 distance 배열을 빼준 후 절댓값중 최솟값 구함. 최솟값 = 최소 시간이 걸리는 정점의 인덱스
{
    int* temp = new int[number];
    for(int i = 0; i < number; i++)
        temp[i] =  distance[i] - g.distance[i];

    int min = 0;
    for(int i = 1; i < number; i++)
    {
        if(abs(temp[min]) > abs(temp[i]))
            min = i;
    }
        
    cout << station[min].name << endl;
    int minute1 = distance[min] / 60;
    int second1 = distance[min] % 60;
    if(second1 == 0)
        cout << minute1 << " : " << "00" << endl;
    else
        cout << minute1 << " : " << second1 << endl;

    int minute2 = g.distance[min] / 60;
    int second2 = g.distance[min] % 60;
    if(second2 == 0)
        cout << minute2 << " : " << "00" << endl;
    else
        cout << minute2 << " : " << second2 << endl;
}

