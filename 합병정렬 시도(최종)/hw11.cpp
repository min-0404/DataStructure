#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <sys/time.h>
#include "sort.h"
using namespace std;

int main(int argc, char* argv[])
{
    int T = atoi(argv[1]); // 테스트 케이스 파일의 개수를 정수형으로 바꿔서 T에 저장(원래 문자열 형태)
    cout << "T =" << T << endl;
    int N; // 각 테스트 케이스 별 레코드의 길이
    int i; // iterator
    double result[4]; // result 배열에 각 알고리즘 별로 실행시간을 저장
    struct timeval start_t, end_t;
    double diff_t;
    if(argc < 3)
    {
        cerr << "wrong argument count" << endl;
        return 1;
    }
    cout << "--INS-- | --QUICK-- | --NATMG-- | --HEAP-- |" << endl;
    for(i = 2; i < T + 2; i++)
    {
        fstream fin1(argv[i]);
        fin1 >> N;

        int* a = new int[N+2]; // 레코드 개수만큼 배열에 공간 준비해둠 N+1인 이유는 삽입정렬때문에
        for(int j = 1; j < N + 1; j++) // 파일의 레코드 배열에 저장하기
            fin1 >> a[j];
        gettimeofday(&start_t, NULL); // 삽입정렬 수행 파트
        InsertionSort(a, N);
        gettimeofday(&end_t, NULL);
        diff_t = (double)(end_t.tv_sec - start_t.tv_sec) + ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
        result[0] = diff_t;
        delete [] a;
        fin1.close();

        fstream fin2(argv[i]);
        fin2 >> N;
        int* b = new int[N+1]; // 레코드 개수만큼 배열에 공간 준비해둠 N+1인 이유는 삽입정렬때문에
        for(int j = 1; j < N + 1; j++) // 파일의 레코드 배열에 저장하기
            fin2 >> b[j];
        gettimeofday(&start_t, NULL); // 퀵정렬 수행 파트
        QuickSort(b, 1, N);
        gettimeofday(&end_t, NULL);
        diff_t = (double)(end_t.tv_sec - start_t.tv_sec) + ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
        result[1] = diff_t;
        delete [] b;
        fin2.close();

        fstream fin3(argv[i]);
        fin3 >> N;
        int* c = new int[N+1]; // 레코드 개수만큼 배열에 공간 준비해둠 N+1인 이유는 삽입정렬때문에
        for(int j = 1; j < N + 1; j++) // 파일의 레코드 배열에 저장하기
            fin3 >> c[j];
        gettimeofday(&start_t, NULL); // 삽입정렬 수행 파트
        NaturalMergeSort(c, N);
        gettimeofday(&end_t, NULL);
        diff_t = (double)(end_t.tv_sec - start_t.tv_sec) + ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
        result[2] = diff_t;
        delete[] c;
        fin3.close();

        fstream fin4(argv[i]);
        fin4 >> N;
        int* d = new int[N+1]; // 레코드 개수만큼 배열에 공간 준비해둠 N+1인 이유는 삽입정렬때문에
        for(int j = 1; j < N + 1; j++) // 파일의 레코드 배열에 저장하기
            fin4 >> d[j];
        gettimeofday(&start_t, NULL); // 삽입정렬 수행 파트
        HeapSort(d, N);
        gettimeofday(&end_t, NULL);
        diff_t = (double)(end_t.tv_sec - start_t.tv_sec) + ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
        result[3] = diff_t;
        delete [] d;
        fin4.close();

        cout.precision(5); // 출력파트(수정X)
        cout << fixed;
        for(int j = 0; j < 4; j++)
        {
            cout << result[j] << "|";
        }
        cout << "N=" << N <<endl;
    }
}
