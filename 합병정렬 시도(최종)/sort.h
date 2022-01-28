#ifndef __SORT_H__
#define __SORT_H__
#include <iostream>
using namespace std;

int Insert (const int& e, int* a, int i)
{
    a[0] = e;
    while(e < a[i])
    {
        a[i+1] = a[i];
        i--;
    }
    a[i+1] = e;
}

void InsertionSort (int* a, const int n)
{
    for(int j = 2; j <= n; j++)
    {
        int temp = a[j];
        Insert(temp, a, j-1);
    }
}

void swap(int* x, int* y)
{
    int temp;
    *y = temp;
    temp = *x;
    *x = *y;
}

void QuickSort(int* a, int left, int right)
{
    if(left < right)
    {
        int i = left, j = right, pivot = a[left];
        do
        {
            do i++; while(a[i] < pivot);
            do j--; while(a[j] > pivot);
            if(i < j) swap(a[i], a[j]);
        } while(i < j);
        swap(a[left], a[j]);

        QuickSort(a, left, j - 1);
        QuickSort(a, j + 1, right);
    }
}
void Merge (int* initList, int* mergedList, const int l, const int m, const int n)
{
    int i1, i2, iResult;
    for(int i1 = l, i2 = m + 1, iResult = l; i1 <= m && i2 <= n; iResult++)
        if(initList[i1] <= initList[i2])
        {
            mergedList[iResult] = initList[i1];
            i1++; 
        }
        else
        {
            mergedList[iResult] = initList[i1];
            i2++;
        }
    copy(initList + i1, initList + m + 1, mergedList + iResult);
    copy(initList + i2, initList + n + 1, mergedList + iResult);
}

void MakeRun(int* a, int* run, const int n) // 일단 초기 배열로 run 만들어줌
{
    fill(run, run + n, 0);
    int i = 1;
    int j = 1;
    for(int i = 1; i < n + 1; i++)
        if(a[i] > a[i+1])
            run[j++] = i;
}

int CountRun(int* run) //만들어진 run의 개수 세는 함수
{
    int count = 0;
    int i = 1;
    while(run[i])
    {
        count++;
        i++;
    }
    return count;
    
}
void NaturalMergeSort(int* a, const int n)
{
    int* mergedList = new int[n+1]; // 정렬한 배열을 저장해줄 배열
    int* run = new int[n+1]; // a와 똑같은 배열을 하나 만들어줌. run 들의 배열을 저장할 예정
    int count; //run의 개수 저장
    while(1)
    {
        MakeRun(a, run, n); // run 배열을 초기화고, 새로 채워줌
        count = CountRun(run);
        if(!count)
            break;
        if(count % 2 == 1)
            count--;
        for(int i = 1; i < count + 1; i += 2)
            Merge(a, mergedList, run[i-1] + 1, run[i], run[i+1]);
        for(int i = 0; i < n; i++)
            run[i] = 0;
    }
    delete[] mergedList;
    delete[] run;
}
void Adjust (int* a, const int root, const int n)
{
    int e = a[root];
    int j;
    for(j = 2 * root; j <= n; j *= 2)
    {
        if(j < n && a[j] < a[j+1]) j++;
        if(e >= a[j]) break;
        a[j/2] = a[j];
    }
    a[j/2] = e;
}

void HeapSort (int* a, const int n)
{
    for(int i = n / 2; i >= 1; i--) // 일단 최대힙 형태로 만들어주기
        Adjust(a, i, n);
    for(int i = n-1; i >= 1; i--) // 루트와 마지막 노드 교환해서 오름차순으로 정렬
    {
        swap(a[1], a[i+1]);
        Adjust(a,1,i);
    }
}

#endif





hw11 10 t50.txt t100.txt t200.txt t300.txt t400.txt t500.txt t1000.txt t2000.txt t3000.txt t4000.txt