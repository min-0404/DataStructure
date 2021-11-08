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
    
    //chain의 4번째 노드 삭제해보기
    ChainNode* temp = chain.getFirst();
    for(int i = 0; i <3; i++)
        temp = temp -> getLink(); //
    chain.Delete(temp);
    chain.Show();
}
