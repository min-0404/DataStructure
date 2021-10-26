#include "linked_list.h"


int main(void)
{
    Chain chain;
    ChainNode *CN = chain.getFirst();

    for (int i = 0; i < 10; i++)
        CN=chain.Insert(CN, i + 1);
    chain.Show();
    cout<<endl;
    cout<<"체인의 노드 개수:"<< chain.Length();
}
 