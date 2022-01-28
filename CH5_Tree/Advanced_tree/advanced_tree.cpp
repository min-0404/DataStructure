#include "advanced_tree.h"
int main(void)
{
    Tree t1, t2;
    t1.Initialize();

    t2 = t1;
    cout << "5.3 Exercises 2 정답을 확인할 수 있습니다" << endl;
    cout << endl;

    cout << "전위순회: ";
    t1.Preorder();
    cout << endl;

    cout << "중위순회: ";
    t2.Inorder();
    cout << endl;

    cout << "후위순회: ";
    t1.Postorder();
    cout << endl << endl;
    
    if (t1 == t2)
        cout << "두 트리는 동일합니다" << endl;
    else
        cout << "두 트리는 동일하지 않습니다" << endl;
    
    return 0;
}

