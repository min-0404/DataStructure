#include "genlist.h"

int main(void)
{
    GenList<int> intG;
    for (int i = 0; i < 5; i++)
        intG.Insert(i + 1);
    
    intG.PrintList();
    cout << endl;
    
    GenList<int> intG2;
    for (int i = 5; i < 10; i++)
        intG2.Insert(i + 1);
    intG.Insert(intG2);

    intG.PrintList();
    cout << endl;

    cout << "깊이: " << intG.Depth() << endl;

    return 0;
}