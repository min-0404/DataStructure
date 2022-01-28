#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Tree;
class TreeNode
{
private:
    int data;
    TreeNode* leftChild;
    TreeNode* rightChild;
public:
    TreeNode(int d)
    {
        data = d;
        leftChild = 0;
        rightChild = 0;
    }
    int getData()
    {
        return data;
    }
    friend class Tree;
};

class Tree
{
public:
    Tree() {}
    void Insert(TreeNode **root, int temp)
    {
        if (*root == 0)
            *root = new TreeNode(temp); //루트가 비었다면 루트부터 채우고
        else
        {
            if (temp < (*root)->data) //root의 데이터보다 작으면 왼쪽
                Insert(&(*root)->leftChild, temp);
            else if (temp > (*root)->data) // root의 데이터보다 크면 오른쪽
                Insert(&(*root)->rightChild, temp);
            else // 해당 값이 이미 트리에 존재하면
            {
                cout << "같은 데이터는 입력 불가능" << endl;
                return;
            }
        }
    }
    void Search(TreeNode **root, int temp)
    {
        if ((*root) == NULL)
            return;
        if ((*root)->data==temp)
        {
            cout << temp << "는 존재합니다" << endl;
            return;
        }
        else //왼쪽 오른쪽 다 찾아본다
        {
            Search(&(*root)->leftChild, temp);
            Search(&(*root)->rightChild, temp);
        }
    }
    void InorderTraversal(TreeNode *root)
    {
        if (root != NULL)
        {
            InorderTraversal(root->leftChild);
            cout << root->data << "->";
            InorderTraversal(root->rightChild);
        }
    }
};
