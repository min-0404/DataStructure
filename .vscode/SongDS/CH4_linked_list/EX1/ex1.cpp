#include "linked_list.h"


int main(void)
{
    //일단 chain하나 만들기
    Chain chain;
    ChainNode *CN = chain.getFirst();
    for (int i = 0; i < 10; i++)
        CN=chain.Insert(CN, i + 1);
    chain.Show();
    cout<<endl;
    
    //chain의 노드 개수 세기
    cout<<"체인의 노드 개수:"<< chain.Length();
}
 