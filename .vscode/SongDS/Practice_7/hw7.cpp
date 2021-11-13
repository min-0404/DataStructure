#include "bt.h"
#include <iostream>
using namespace std;

int main()
{
    Tree<double> tree;
    double dval;
    cout << "Enter doubles:\n";
    while (cin >> dval)
        tree.Insert(dval);
    // 순환 preorder
    cout << endl << "Preorder traversal: ";
    tree.Preorder();
    // 순환 inorder
    cout << endl << "Inorder traversal: ";
    tree.Inorder();
    // 순환 postorder
    cout << endl << "Postorder traversal: ";
    tree.Postorder();

    // 큐 levelorder
    cout << endl << "Levelorder traversal: ";
    tree.Levelorder();
    // 스택 inorder
    cout << endl <<"Stack Inorder traversal: ";
    tree.StackInorder();
    // 스택 preorder
    cout << endl << "Stack Preorder traversal: ";
    tree.StackPreorder();
    // 스택 postorder
    cout << endl << "Stack Postorder traversal: ";
    tree.StackPostorder();

    cout << endl;
    return 1;
}
