#include "linked_list.h"


int main(void)
{
    Chain<int> intChain;
    ChainNode<int> *CN = intChain.getFirst();
    for (int i = 0; i < 10; i++)
        CN = intChain.Insert(CN, i + 1);
    cout << "체인 출력" << endl;
    cout << intChain << endl;
    return 0;
}
