#include <iostream>
using namespace std;

int addArray(int* p, int size)
{
    int sum = 0;
    for(int i = 0; i < size; i++)
        sum += p[i];
    return sum;
}

void makeDouble(int* p, int size)
{
    for(int i = 0; i < size; i++)
        p[i] *= 2;
}
void printArray(int* p, int size)
{
    for(int i = 0; i < size; i++)
        cout << p[i] << " ";
}

int main()
{
    int n[] = {1, 2, 3, 4, 5};
    int sum = addArray(n, 5);
    cout << sum << endl;
    makeDouble(n, 5);
    printArray(n, 5);
    return 0;
}

