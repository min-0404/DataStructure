#include "subway.h"
#include <fstream>

int main(int argc, char *argv[])
{
    int numLine; // 텍스트 파일의 줄 개수(총 72개)
    int line1, line2; // 준회와 현수집의 호선
    string src, dst; // 준회와 현수집의 역이름

    int count = 0; //정점의 개수를 저장할 변수(subway파일의 number와 사실상 동일)
    Graph graph1; //준회를 위한 그래프
        
    if(argc != 3)
    {
        cerr << "Argument Count is " << argc << endl << "Argument must be" << argc << endl;
        return 1;
    }

    fstream fin(argv[1]);
    if(!fin)
    {
        cerr << argv[1] << "open failed" << endl;
        return 1;
    }

    fin >> numLine;
    for(int i = 0; i < numLine; i++)
    {
        int n1, n2;
        string s1, s2;
        int index1, index2;

        fin >> n1;
        fin >> s1;
        fin >> n2;
        fin >> s2;

        if(! graph1.find(n1, s1)) // station 배열에 없을 경우
        {
            graph1.insertVertex(n1, s1, count);
            count++;
        }
        index1 = graph1.findIndex(n1, s1);


        if(! graph1.find(n2, s2))
        {
            graph1.insertVertex(n2, s2, count);
            count++;
        }
        index2 = graph1.findIndex(n2, s2);

        graph1.insertEdge(index1, index2);
    }
    fin.close();
    Graph graph2(graph1); // graph2: 현수를 위한 그래프(graph1의1 노선도를 완성한 직후 깊은복사해준다)

    fstream fin2(argv[2]);
    if(!fin)
    {
        cerr << argv[2] << "open failed" << endl;
        return 1;
    }
    fin2 >> line1 >> src;
    fin2 >> line2 >> dst;
    fin2.close();
    

    int joonhoi = graph1.findIndex(line1, src); // 준회(안국역)의 인덱스
    int hyunsoo = graph1.findIndex(line2, dst); // 현수(충정로)의 인덱스
    
    graph1.ShortestPath(count, joonhoi); // 이 함수로 인해 이제 graph1 객체의 distance 배열은 준회(안국역) 기준으로 초기화됨
    graph1.display_path(joonhoi, hyunsoo); // graph1 기준 현수네까지의 경로 출력
    graph1.display_time(hyunsoo); //graph1 기준 현수네 까지 걸리는 시간 출력

    graph2.ShortestPath(count, hyunsoo); // 이 함수로 인해 이제 graph2 객체의 distance 배열은 현수(충정로) 기준으로 초기화됨
    graph1.min(graph2);
    return 0;
}