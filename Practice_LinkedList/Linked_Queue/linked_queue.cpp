#include "linked_queue.h"

int main(void)
{
    LinkedQueue<int> intLQ;
    for (int i = 0; i < 5; i++)
        intLQ.Enqueue(i + 1);
    intLQ.Show();

    cout << "Front: " << intLQ.Front() << endl;
    cout << "Rear: " << intLQ.Rear() << endl;

    for (int i = 0; i < 5; i++)
        intLQ.Dequeue();
    intLQ.Show();

    return 0;
}