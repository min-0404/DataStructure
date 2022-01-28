// Basic_tree를 구체화해서 구현해본 트리

#include <iostream>
#include <algorithm>
using namespace std;

class Tree;

class TreeNode
{
private:
    int data;
    TreeNode *leftChild;
    TreeNode *rightChild;
public:
    TreeNode(): leftChild(NULL), data(0), rightChild(NULL) {}
    TreeNode(int temp, TreeNode *left, TreeNode *right) :leftChild(left), data(temp), rightChild(right) {}
    friend class Tree;
    friend int Equal(TreeNode* tn1, TreeNode* tn2);
};


class Tree
{
private:
    TreeNode* root;
public:
    Tree() { root = 0; } // 기본 생성자
    Tree(const Tree& t) { root = Copy(t.root);} //
    void Initialize() //트리를 초기화
    {
        root = new TreeNode(1, 0, 0);
        root->leftChild = new TreeNode(2, 0, 0);
        root->rightChild = new TreeNode(3, 0, 0);
        root->leftChild->leftChild = new TreeNode(4, 0, 0);
        root->leftChild->rightChild = new TreeNode(5, 0, 0);
        root->rightChild->leftChild = new TreeNode(6, 0, 0);
        root->rightChild->rightChild = new TreeNode(7, 0, 0);
        root->leftChild->leftChild->leftChild = new TreeNode(8, 0, 0);
        root->leftChild->leftChild->rightChild = new TreeNode(9, 0, 0);
        root->leftChild->rightChild->leftChild = new TreeNode(10, 0, 0);
        root->leftChild->rightChild->rightChild = new TreeNode(11, 0, 0);
        root->rightChild->leftChild->leftChild = new TreeNode(12, 0, 0);
        root->rightChild->leftChild->rightChild = new TreeNode(13, 0, 0);
        root->rightChild->rightChild->leftChild = new TreeNode(14, 0, 0);
        root->rightChild->rightChild->rightChild = new TreeNode(15, 0, 0);
    }
    TreeNode* Copy(TreeNode* origNode)
    {
        if (origNode)
        {
            TreeNode *temp = new TreeNode;
            temp->data = origNode->data;
            temp->leftChild = Copy(origNode->leftChild);
            temp->rightChild = Copy(origNode->rightChild);
        }
        else
            return 0;
    }
    void Preorder() //driver
    {
        Preorder(root);
    }
    void Inorder() //driver
    {
        Inorder(root);
    }
    void Postorder()
    {
        Postorder(root);
    }
    friend int operator==(const Tree& t1, const Tree& t2);
private:
    void Preorder(TreeNode *currentNode) //workhorse
    {
        if (currentNode)
        {
            cout << currentNode->data << "->"; // Visit 함수 만들기 귀찮아서 대신 만듬
            Preorder(currentNode->leftChild);
            Preorder(currentNode->rightChild);
        }
    }
    void Inorder(TreeNode *currentNode) // workhorse
    {
        if (currentNode)
        {
            Inorder(currentNode->leftChild);
            cout << currentNode->data << "->";
            Inorder(currentNode->rightChild);
        }
    }
    void Postorder(TreeNode *currentNode)
    {
        if (currentNode)
        {
            Postorder(currentNode->leftChild);
            Postorder(currentNode->rightChild);
            cout << currentNode->data << "->";
        }
    }
};

 
int operator==(const Tree &t1, const Tree &t2)
{
        return Equal(t1.root, t2.root);
}

int Equal(TreeNode *tn1, TreeNode *tn2)
{
    if ((!tn1) && (!tn2)) //둘다 NULL
        return 1;
    if (tn1 && tn2 && (tn1->data == tn2->data) && Equal(tn1->leftChild, tn2->leftChild) && Equal(tn1->rightChild, tn2->rightChild))
        //둘 다 존재하고 데이터가 같고, 왼쪽 자식 오른쪽 자식이 같다
        return 1;
    return 0;
}


