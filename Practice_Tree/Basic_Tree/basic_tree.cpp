#include "basic_tree.h"

int main(void)
{
    TreeNode*root =NULL;
    Tree intTree;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        int data = (int)(rand() % 100 + 1);
        intTree.Insert(&root, data);
        cout << data << "입력" << endl;
    }
    cout << "트리 출력(루트 노드 " << root->getData() << ")" << endl;

    intTree.InorderTraversal(root);

    cout << endl;

    cout << "트리에 5라는 데이터가 있는가?(존재하지 않는다면 빈칸)" << endl;

    intTree.Search(&root, 5);

    return 0;
}

