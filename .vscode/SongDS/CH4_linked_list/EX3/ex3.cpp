#include "linked_list.h"

int main(void)
{
    Chain chain;
    int num;
    ChainNode *CN = chain.getFirst();
    for (int i = 0; i < 10; i++)
        CN = chain.Insert(CN, i + 1);
    chain.Show();

    chain.alternateDelete();
    cout << "홀수번째 노드 삭제" << endl;
    chain.Show();
    return 0;
}