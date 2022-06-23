#include <iostream>
#include <string>
using namespace std;

template <class K, class E>
struct Node
{
    Node(K ky, E el, Node<K, E>* left = 0, Node<K, E>* right = 0, bool rt = true, bool lt = true) :key(ky), element(el), leftChild(left), rightChild(right), rightThread(rt), leftThread(lt) {}
    bool leftThread;
    bool rightThread;
    Node<K, E>* leftChild;
    Node<K, E>* rightChild;
    K key;
    E element;
};

template <class K, class E>
class BST
{
public:
    BST() { root = NULL;}
    void Insert(K& newkey, E& el) { Insert(root, newkey, el);}
    void Inorder() { Inorder(root);}
    void Delete(K& oldkey) {Delete(root, root, oldkey); }
    bool Find(const K &, E &);
    void Max() {cout << "Max Value is "; Visit(Max(root)); cout << endl;}
    void Min() {cout << "Min Value is "; Visit(Min(root)); cout << endl;}

private:
    Node<K,E>* root;
    void Visit(Node<K,E>*);
    void Insert(Node<K,E>*& x, K& newkey, E& el)
    {
        Node<K,E>* parentNode = 0;
        while(!x)
        {
            if(newkey == x -> key)
            {
                x -> key = newkey;
                x -> element = el;
                return ;
            }
            parentNode = x;
            if(newkey < (x -> key))
            {
                if(! x -> leftThread)
                    x = x -> leftChild;
                else
                    break;
            }
            else
            {
                if(! x -> rightThread)
                    x = x -> rightChild;
                else
                    break;
            }
        }
        if(! x)
        {
            Node<K,E>* temp = new Node<K,E>(newkey,el);
            root = temp;
            return;
        }

        if(newkey < (parentNode -> key))
            {
                Node<K,E>* newNode = new Node<K,E>(newkey, el);
                newNode -> leftChild = parentNode -> leftChild;
                newNode -> leftThread = parentNode -> leftThread;
                newNode -> rightChild = parentNode;
                newNode -> rightThread = true;
                parentNode -> leftChild = newNode;
                parentNode -> leftThread = false;
            }
            else
            {
                Node<K,E>* newNode = new Node<K,E>(newkey, el);
                newNode -> rightChild = parentNode -> rightChild;
                newNode -> rightThread = parentNode -> rightThread;
                newNode -> leftChild = parentNode;
                newNode -> leftThread = true;
                parentNode -> rightChild = newNode;
                parentNode -> rightThread = false;
            }
        
    }
    void Inorder(Node<K,E>* currentNode)
    {
        while(currentNode -> leftThread == false)
            currentNode = currentNode -> leftChild;
        while(currentNode != 0)
        {
            Visit(currentNode);
            if(currentNode -> rightThread == true)
                currentNode = currentNode -> rightChild;
            else
            {
                Node<K,E>* temp = currentNode -> rightChild;
                while(! temp -> leftThread) temp = temp -> leftChild;
                currentNode = temp;
            }
        }
    }
    void Delete(Node<K,E>*& parentNode, Node<K,E>*& deleteNode, K& oldkey)
    {
        while(deleteNode -> key != oldkey)
        {
            parentNode = deleteNode;
            if(oldkey < deleteNode -> key)
            {
                if(! deleteNode -> leftThread)
                    deleteNode = deleteNode -> leftChild;
                else
                    break;
            }
            else if(oldkey > deleteNode -> key)
            {
                if(deleteNode -> rightThread == false)
                    deleteNode = deleteNode -> rightChild;
                else
                    break;
            }
        }
        
        if(deleteNode -> leftThread == true && deleteNode -> rightThread == true) // 자식이 없는 리프노드의 삭제법
        {
            if(deleteNode == parentNode -> leftChild)
            {
                parentNode -> leftThread = true;
                parentNode -> leftChild = deleteNode -> leftChild;
            }
            else
            {
                parentNode -> rightThread = true;
                parentNode -> rightChild = deleteNode -> rightChild;
            }
            delete deleteNode;
        }
        else if(deleteNode -> leftThread == false || deleteNode -> rightThread == false) // 자식이 하나인 노드의 삭제법
        {
            Node<K,E>* childNode = 0;
            if(! deleteNode -> leftThread) // 자식이 어떤 쪽 노드인지 결정
                childNode = deleteNode -> leftChild;
            else
                childNode = deleteNode -> rightChild;
            
            if(deleteNode = parentNode -> leftChild) // 삭제할 노드가 부모노드의 왼쪽이면 부모노드의 왼쪽을 자식노드와 연결
                parentNode -> leftChild = childNode;
            else
                parentNode -> rightChild = childNode; //삭제할 노드가 부모노드의 오른쪽이면 부모노드의 오른쪽을 자식노드와 연결

            Node<K,E>* predecessor = deleteNode;
            if(predecessor -> leftThread)
                predecessor = predecessor -> leftChild;
            else
            {
                predecessor = predecessor -> leftChild;
                while(! predecessor -> rightThread)
                    predecessor = predecessor -> rightChild;
            }

            Node<K,E>* successor = deleteNode;
            if(successor -> rightThread) 
                successor = successor -> rightChild;
            else
            {
                successor = successor -> rightChild;
                while(! successor -> leftThread)
                    successor = successor -> leftChild;
            }

            if(! deleteNode -> leftThread) //삭제할 노드가 왼쪽 자식았을때
                predecessor -> rightChild = successor;
            else //삭제할 노드가 오른쪽 자식 있을때
            {
                if(! deleteNode -> rightThread)
                    successor -> leftChild = predecessor;
            }
            delete deleteNode;
        }
        else
        {

        }
    }
    Node<K,E>* Max(Node<K,E>* currentNode)
    {
        Node<K,E>* maxNode = currentNode;
        while(currentNode -> leftThread == false)
            currentNode = currentNode -> leftChild;
        while(currentNode != 0)
        {
            if(currentNode -> key > maxNode -> key)
                maxNode = currentNode;
            if(currentNode -> rightThread == true)
                currentNode = currentNode -> rightChild;
            else
            {
                Node<K,E>* temp = currentNode -> rightChild;
                while(! temp -> leftThread)
                    temp = temp -> leftChild;
                currentNode = temp;
            }
        }
        return maxNode;
    }

    Node<K,E>* Min(Node<K,E>* currentNode)
    {
        Node<K,E>* minNode = currentNode;
        while(currentNode -> leftThread == false)
            currentNode = currentNode -> leftChild;
        while(currentNode != 0)
        {
            if(currentNode -> key < minNode -> key) minNode = currentNode;
            if(currentNode -> rightThread == true)
                currentNode = currentNode -> rightChild;
            else
            {
                Node<K,E>* temp = currentNode -> rightChild;
                while(! temp -> leftThread) temp = temp -> leftChild;
                currentNode = temp;
            }
        }
        return minNode;
    }
};

template <class K, class E>
void BST<K,E>::Visit(Node<K, E>* prt)
{
    cout << prt -> key << ":" << prt -> element << " ";
}

template <class K, class E>
bool BST<K, E>::Find(const K &k, E &e)
{
    Node<K, E> *temp = root;
    while (temp)
    {
        if (k > temp->key)
        {
            if (temp->rightThread) break;
            else temp = temp->rightChild;
        }
        else if (k < temp->key)
        {
            if (temp->leftThread) break;
            else temp = temp->leftChild;
        }
        else
        {
            e = temp->element;
            return true;
        }
    }
    return false;
} 
