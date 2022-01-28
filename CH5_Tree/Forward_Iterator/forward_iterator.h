
#include <iostream>
#include <stack>

template <typename T>
class inorderIterator
{
private:
    stack<TreeNode<T>* > s;
    TreeNode<T>* currentNode;
public:
    inorderIterator(Tree<T> tree)
    {
        currentNode = root;
    }
    T *Next()
    {
        while (currentNode)
        {
            s.push(currentNode);
            currentNode = currentNode->leftChild;
        }
        if (s.IsEmpty())
            return 0;
        currentNode = s.Top();
        s.Pop();
        T& temp = currentNode->data;
        currentNode = currentNode->rightChild;
        return &temp;
    }

};
