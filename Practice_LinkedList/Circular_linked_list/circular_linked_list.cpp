#include "circular_linked_list.h"

int main(void)
{
    CircularList<int> intCList;
    int idx;
    
    for (int i = 0; i < 3; i++)
        intCList.InsertFront(i + 1);
    cout << "원형리스트 출력" << endl;
    intCList.Show();

    for (int i = 0; i < 3; i++)
        intCList.InsertRear((i + 1) * 2);
    cout << "원형리스트 출력" << endl;
    intCList.Show();
    
    return 0;
}
