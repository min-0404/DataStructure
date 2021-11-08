#include "linked_stack.h"


int main(void)
{
    LinkedStack<int> intLS;
    for (int i = 0; i < 5; i++)
        intLS.Push(i + 1);
    intLS.Show();

    cout << "Top: " << intLS.Top() << endl;

    for (int i = 0; i < 5; i++)
        intLS.Pop();
    intLS.Show();
    return 0;
}