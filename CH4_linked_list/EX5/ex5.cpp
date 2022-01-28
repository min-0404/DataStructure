#include "linked_list.h"

int main(void)
{
    Chain x, y, z;
    ChainNode* CN1=x.getFirst();
    ChainNode* CN2 = y.getFirst();

    //체인 x 생성
    for (int i = 0; i < 5; i++)
        CN1 = x.Insert(CN1, i + 1);
    cout<<"체인x: ";
    x.Show();
    cout<<endl;

    x.ascendingSort();
    x.Show();
    cout<<endl;


    //체인 y 생성
    for (int i = 0; i < 5; i++)
        CN2 = y.Insert(CN2, (i + 2) * 2);
    cout<<"체인y: ";
    y.Show();
    cout<<endl;

    y.ascendingSort();
    y.Show();
    cout<<endl;

    Merge(x, y, z);
    cout<<"체인z: ";
    z.Show();

    return 0;
}

