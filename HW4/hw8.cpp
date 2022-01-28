#include "bst.h"
using namespace std;

int main(void)
{
    BST<string, double> tree, tree1;
    string command, str;
    double dval;
    while(cin >> command)
    {
        if(command == "insert")
        {
            cin >> str >> dval;
            tree.Insert(str, dval);
        }
        else if(command == "delete")
        {
            cin >> str;
            tree.Delete(str);
        }
        else if(command == "print")
        {
            cout << "Inorder traversal : ";
            tree.Inorder();
            cout << endl;
        }
        else if(command == "find")
        {
            cin >> str;
            if(tree.Find(str, dval))
            {
                cout << "The value of " << str << " is " << dval << endl;
            }
            else
            {
                cout << "No such key : " << str << endl;}
            }
        else if(command == "max")
        {
            tree.Max();
        }
        else if(command == "min")
        {
            tree.Min();
        }
        else cout << "Invalid command : " << command << endl;
    }
}