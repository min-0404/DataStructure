#include "adjacent_list_graph.h"

int main(void)
{
    Graph lg(10); // 정점의 개수가 10개인 그래프 선언

    for (int i = 0; i < 10; i++) // 정점 랜덤하게 이어보기
    {
        lg.linkEdge(i, i + 1);
        if (i < 5)
            lg.linkEdge(i, i + 5);
        else
            lg.linkEdge(i, i - 3);
    }

    cout << lg;
    
    return 0;

}
