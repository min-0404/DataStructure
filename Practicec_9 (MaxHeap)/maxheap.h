#ifndef __MAXHEAP_H
#define __MAXHEAP_H_
#include <iostream>
#include <algorithm>
using namespace std;

// MaxHeap의 원리 : 결국 Tree라기 보단 1차원 배열이라고 봐야함
template <typename T>
class MaxHeap
{
private:
    T* heap; // 노드를 저장할 1차원 배열
    int heapSize; // 현재 heap에 저장된 노드의 개수(초기에 0으로 설정)
    int capacity; // heap의 용량
    void ChangSize1D(int size) // 힙배열의 크기를 size만큼 늘려줌
    {
        if(size < 0) throw "New Length must be >= 0";
        T* temp = new T[size];
        int number = min(heapSize, size);
        copy(heap, heap + number, temp);
        delete[] heap;
        heap = temp;
    }
public:
    MaxHeap(int _capacity = 10) // 생성자
    {
        capacity = _capacity;
        heapSize = 0; // 초기에 노드 개수 0개임 당연하지
        heap = new T[capacity + 1]; // 노드를 저장할 heap 배열에게 공간할당
    }
    void Push(const T& newValue) // newVlaue 값을 가진 새로운 노드 추가법
    {
        if(heapSize == capacity) // 만약 꽉찬 상황이면 capacity 늘려줌
        {
            ChangeSize1D(heap, capacity + 1, 2*capacity +1);
            capacity *= 2;
        }
        int currentNode = ++heapSize; // currentNode는 추가할 노드의 번호를 말한다
        while(currentNode != 1 && heap[currentNode/2] < newValue)
        {
            heap[currentNode] = heap[currentNode/2];
            currentNode = currentNode/2;
        }
        heap[currentNode] = newValue; 
    }
    void Pop()
    {
        if(IsEmpty()) throw "heap is empty. Cannot Delete";
        heap[1]. ~T();
        T lastE = heap[heapSize--]; // lastE : 힙의 마지막 노드의 값
        
        int currentNode = 1;
        int child = 2;
        while(child <= heapSize)
        {
            if(child < heapSize && heap[child] < heap[child+1]) child++;
            if(lastE >= heap[child]) break;
            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }
        heap[currentNode] = lastE;
    }
    bool IsEmpty()
    {
        return heapSize == 0;
    }
    T Top()
    {
        return heap[1];
    }
    template <typename T2>
    friend ostream& operator<<(ostream& os, MaxHeap<T2>& H);
};

template <typename T>
ostream& operator<<(ostream& os, MaxHeap<T>& H)
{
    os << "<Heap Contents>" ;
    for(int i = 1; i <= H.heapSize; i++)
        os << i << ":" << H -> heap[i] << " ";
    os << endl;
}
#endif