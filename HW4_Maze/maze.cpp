#include <iostream>
#include <stack>
using namespace std;

const int MAXSIZE= 100;
bool maze[MAXSIZE+ 2][MAXSIZE+ 2]; // maze 이차원 배열로 구현
bool mark[MAXSIZE+ 1][MAXSIZE+ 1] = {0}; // 방문여부 확인 배열
enum directions { N, NE, E, SE, S, SW, W, NW }; // 총 8가지 방향
struct offsets{
    int a, b;
}
move[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
struct Items{
    Items(int xx= 0, int yy= 0, int dd= 0): x(xx), y(yy), dir(dd) {}
    int x, y, dir;
};

template < class T >
ostream& operator<< (ostream& os, stack< T > & s) {
    // 스택의 내용을 역순으로 출력하는 방식으로 구현
    // 구현방법 = 내용을 하나씩 꺼내 다른 임시 스택에 넣어 저장한 후, 최종적으로 그 임시 스택에서 하나씩 꺼내 출력하면 됨
    stack<T> temp; //역으로 출력하기 위해 임시 스택
    while(!s.empty()){
        term.push(s.top());
        s.pop();
    }
    while(!term.empty()){
        os << "->" << term.top();
        s.push(term.top());
        term.pop();
    }
    return os;
}

ostream& operator<<(ostream& os, Items& item){

    // 5개의 Items가 출력될 때마다 줄바꾸기위해
    static int count = 0;
    os << "(" << item.x << "," << item.y << ")";
    count++;
    if ((count % 5) == 0)
        cout << endl;
    return os;
}

// void Path(const int m, const int p){
//     mark[1][1] = 1;
//     int marked = 1; // 방문한 노드 개수
//     stack<Items> stack;
//     stack.push(temp);
//     while(!stack.empty()){
//         temp = stack.top();
//         stack.pop();
//         int i = temp.x;
//         int j = temp.y;
//         int d = temp.dir;
//         while(d < 8){
//             int g = i + move[d].a;
//             if((g==m) && (h==p)){
//                 cout << stack;
//                 temp.x = i;
//                 temp.y = j;
//                 cout << "->" << temp;
//                 temp.x = m;
//                 temp.y = p;
//                 cout << "->" << temp << end;
//                 cout << endl << marked << m * p << endl;
//                 return;
//             }

//         }
//     }
// }

// 자료화일을 읽어들여 maze에 저장한다.
// void getdata(istream& is, int& m, int & p){ 
//     is >> m >> p;
//     for (int i = 0; i < m+ 2; i+ + ){ 
//         maze[i][0] = 1; 
//         maze[i][p+ 1] =1;
//     }
//     for (int j = 1; j <= p; j++) {
//         maze[0][j] = 1;
//         maze[m+ 1][j] =1;
//     }
//     for (int i = 1; i <= m; i+ + )
//         for (int j = 1; j <= p; j+ + )
//             is >> maze[i][j];
// }