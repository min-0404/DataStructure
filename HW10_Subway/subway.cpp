#include "subway.h"

queue<int> q1; // 경로를 저장하기 큐 선언 
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

    q1.push(s); // 출발 지점도 출력되야 하므로 첫번째로 큐에 넣어줌
    q1.push(choosed_vertex[0]); // 일단 첫번째 choose값은 무조건 push 해주고,

    int x = 0;
    int y = 1;
    while(y <= goal)
    {
        if(matrix[ choosed_vertex[x] ][ choosed_vertex[y] ] != INF && isLeaf(choosed_vertex[y]))
        {
            q1.push(choosed_vertex[y]);
            x = y;
            y++;
        }
        else
            y++;
    }
    while(!q1.empty())
    {
        int z = q1.front();
        q1.pop();
        if(station[z].name != station[q1.front()].name)
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

